    #pragma once
    #include "PhysValue.h"
    #include <functional>
    #include <vector>
    #include <string>
    #include <stdexcept>
    #include <cmath>
    #include <algorithm>
    #include <numeric>

    template <typename UnitX, typename UnitY>
    class Model {
    protected:
        using ModelFunc = std::function<double(double, const std::vector<double>&)>;
        ModelFunc model_func_;
        std::string name_;
        std::vector<double> current_params_; // Хранит текущие параметры для operator() количество степеней свободы - количество точек  (для линейной 2 для квадратичной 3 )

    public:
        Model(ModelFunc func, std::string name, int num_params)
            : model_func_(std::move(func)), name_(std::move(name)), current_params_(num_params, 0.0) {}

        virtual ~Model() = default;
        double operator()(double x) const {
            return model_func_(x, current_params_);
        }

        double evaluate(double x, const std::vector<double>& params) const {
            return model_func_(x, params);
        }

        // Управление параметрами
        void setParams(const std::vector<double>& params) {
            if (params.size() != current_params_.size())
                throw std::invalid_argument("Неверное количество параметров");
            current_params_ = params;
        }
        
        const std::vector<double>& getParams() const { return current_params_; }
        int numParameters() const { return current_params_.size(); }
        const std::string& getName() const { return name_; }

        // ✅ Чистый виртуальный метод: каждая модель должна уметь давать начальные приближения
        virtual std::vector<double> getInitialGuess(
            const std::vector<double>& x_data,
            const std::vector<double>& y_data
        ) const = 0;
    };

    template <typename UnitX, typename UnitY>
    class LinearModel : public Model<UnitX, UnitY> {
    public:
        LinearModel() : Model<UnitX, UnitY>(
            [](double x, const std::vector<double>& p) { return p[0] * x + p[1]; },
            "Линейная: y = kx + b", 2
        ) {}

        std::vector<double> getInitialGuess(const std::vector<double>& x, const std::vector<double>& y) const override {
            if (x.size() < 2) return {1.0, 0.0};
            double k = (y.back() - y.front()) / (x.back() - x.front() + 1e-10);
            double b = y.front() - k * x.front();
            return {k, b};
        }
    };

    template <typename UnitX, typename UnitY>
    class ExponentialModel : public Model<UnitX, UnitY> {
    public:
        ExponentialModel() : Model<UnitX, UnitY>(
            [](double x, const std::vector<double>& p) { return p[0] * std::exp(-p[1] * x); },
            "Экспоненциальная: y = A * exp(-αx)", 2
        ) {}
        // замена переменных для линейной зависимости 
        std::vector<double> getInitialGuess(const std::vector<double>& x,
                                            const std::vector<double>& y) const override {
            if (x.empty() || y.empty() || x.size() != y.size() || x.size() < 2)
                return {1.0, 0.01};

            // 1. Отбираем точки, пригодные для лог-линеаризации: y > 0, конечные x
            std::vector<double> xs, ls; // xs — x, ls — ln(y)
            xs.reserve(x.size());
            ls.reserve(x.size());
            for (size_t i = 0; i < x.size(); ++i) {
                if (std::isfinite(x[i]) && std::isfinite(y[i]) && y[i] > 0.0) {
                    xs.push_back(x[i]);
                    ls.push_back(std::log(y[i]));
                }
            }
            if (xs.size() < 2)
                return {y[0] > 0.0 ? y[0] : 1.0, 0.01};

            // 2. Полный МНК в координатах (x, ln y):  ln y = ln A - alpha * x
            const double n  = static_cast<double>(xs.size());
            const double sx = std::accumulate(xs.begin(), xs.end(), 0.0);
            const double sl = std::accumulate(ls.begin(), ls.end(), 0.0);
            double sxx = 0.0, sxl = 0.0;
            for (size_t i = 0; i < xs.size(); ++i) {
                sxx += xs[i] * xs[i];
                sxl += xs[i] * ls[i];
            }
            const double denom = n * sxx - sx * sx;
            if (std::abs(denom) < 1e-15 || std::abs(xs.back() - xs.front()) < 1e-15)
                return {std::exp(sl / n), 0.01}; // x почти не меняется: затухание не оценить

            const double slope = (n * sxl - sx * sl) / denom; // это -alpha
            const double intercept = (sl - slope * sx) / n;   // это ln A

            // 3. Санитайзинг результатов
            double A = std::exp(std::clamp(intercept, -50.0, 50.0));
            double alpha = -slope;

            // Данные должны затухать; если МНК дал рост/ноль — ставим безопасный минимум
            if (!(alpha > 0.0))
                alpha = 0.01;
            alpha = std::clamp(alpha, 1e-6, 1e6);
            if (!(A > 0.0) || !std::isfinite(A))
                A = 1.0;

            return {A, alpha};
        }
    };

    template <typename UnitX, typename UnitY>
    class SquarModel : public Model<UnitX, UnitY> {
    public:
        SquarModel() : Model<UnitX, UnitY>(
            // Правильная квадратичная функция: p[0]=a, p[1]=b, p[2]=c
            [](double x, const std::vector<double>& p) {
                return p[0] * x * x + p[1] * x + p[2];
            },
            "Квадратичная: y = ax² + bx + c",
            3 // ВАЖНО: 3 параметра!
        ) {}

        std::vector<double> getInitialGuess(
            const std::vector<double>& x,
            const std::vector<double>& y
        ) const override {
            if (x.size() < 3 || y.size() < 3) {
                throw std::runtime_error("Для квадратичной модели нужно минимум 3 точки");
            }

            // Берем 3 хорошо разнесенные точки для оценки (первая, середина, последняя)
            size_t n = x.size();
            size_t i0 = 0;
            size_t i1 = n / 2;
            size_t i2 = n - 1;

            double x0 = x[i0], y0 = y[i0];
            double x1 = x[i1], y1 = y[i1];
            double x2 = x[i2], y2 = y[i2];

            // Решаем систему из 3 уравнений:
            // y0 = a*x0^2 + b*x0 + c
            // y1 = a*x1^2 + b*x1 + c
            // y2 = a*x2^2 + b*x2 + c
            
            double denom = (x2*x2 - x0*x0)*(x1 - x0) - (x1*x1 - x0*x0)*(x2 - x0);
            
            // Защита от вырожденной матрицы (например, если все точки имеют одинаковый x)
            if (std::abs(denom) < 1e-10) {
                return {1.0, 0.0, 0.0}; 
            }

            double a = ((y2 - y0)*(x1 - x0) - (y1 - y0)*(x2 - x0)) / denom;
            double b = (y1 - y0 - a*(x1*x1 - x0*x0)) / (x1 - x0 + 1e-10); // +1e-10 защита от деления на 0
            double c = y0 - a*x0*x0 - b*x0;

            return {a, b, c};
        }
    };


    // y = A * x^n (линеаризация: ln(y) = ln(A) + n * ln(x))
    template <typename UnitX, typename UnitY>
    class PowerLawModel : public Model<UnitX, UnitY> {
    public:
        PowerLawModel() : Model<UnitX, UnitY>(
            [](double x, const std::vector<double>& p) { return p[0] * std::pow(std::max(1e-10, x), p[1]); },
            "Степенная: y = A * xⁿ", 2
        ) {}

        std::vector<double> getInitialGuess(const std::vector<double>& x, const std::vector<double>& y) const override {
            if (x.size() < 2 || y.size() < 2) return {1.0, 1.0};
            double x0 = std::max(1e-10, x.front()), y0 = std::max(1e-10, y.front());
            double x1 = std::max(1e-10, x.back()), y1 = std::max(1e-10, y.back());
            double n = std::log(y1 / y0) / std::log(x1 / x0 + 1e-10);
            double A = y0 / std::pow(x0, n);
            return {A, n};
        }
    };
    template <typename UnitX, typename UnitY>
    class LogarithmicModel : public Model<UnitX, UnitY> {
    public:
        LogarithmicModel() : Model<UnitX, UnitY>(
            [](double x, const std::vector<double>& p) { return p[0] * std::log(std::max(1e-10, x)) + p[1]; },
            "Логарифмическая: y = A * ln(x) + b", 2
        ) {}

        std::vector<double> getInitialGuess(const std::vector<double>& x, const std::vector<double>& y) const override {
            if (x.size() < 2 || y.size() < 2) return {1.0, 0.0};
            double lx0 = std::log(std::max(1e-10, x.front()));
            double lx1 = std::log(std::max(1e-10, x.back()));
            double A = (y.back() - y.front()) / (lx1 - lx0 + 1e-10);
            double b = y.front() - A * lx0;
            return {A, b};
        }
    };

    // y = A * sin(omega * x + phi)
    template <typename UnitX, typename UnitY>
    class SinusoidalModel : public Model<UnitX, UnitY> {
    public:
        SinusoidalModel() : Model<UnitX, UnitY>(
            [](double x, const std::vector<double>& p) { return p[0] * std::sin(p[1] * x + p[2]); },
            "Синусоидальная: y = A * sin(ωx + φ)", 3
        ) {}

        std::vector<double> getInitialGuess(const std::vector<double>& x, const std::vector<double>& y) const override {
            if (x.size() < 4 || y.size() < 4) return {1.0, 1.0, 0.0};
            auto minmax = std::minmax_element(y.begin(), y.end());
            double A = (*minmax.second - *minmax.first) / 2.0;
            double omega = 2.0 * M_PI / (x.back() - x.front()); // Грубая оценка: 1 период на весь диапазон
            double phi = 0.0;
            return {std::max(1e-3, A), std::max(1e-3, omega), phi};
        }
    };

    template <typename UnitX, typename UnitY>
    class DampedOscillationModel : public Model<UnitX, UnitY> {
    public:
        DampedOscillationModel() : Model<UnitX, UnitY>(
            [](double x, const std::vector<double>& p) { 
                return p[0] * std::exp(-p[1] * x) * std::sin(p[2] * x + p[3]); 
            },
            "Затухающие колебания: y = A * exp(-αx) * sin(ωx + φ)", 4
        ) {}

        std::vector<double> getInitialGuess(const std::vector<double>& x, const std::vector<double>& y) const override {
            if (x.size() < 4 || y.size() < 4) return {1.0, 0.1, 1.0, 0.0};
            auto minmax = std::minmax_element(y.begin(), y.end());
            double A = std::abs(*minmax.second);
            double alpha = 0.1; // Грубая оценка затухания
            double omega = 2.0 * M_PI / (x.back() - x.front());
            double phi = 0.0;
            return {A, alpha, omega, phi};
            
        }
    };

// ============================================================================
// 1. Результат для ЛИНЕЙНОЙ аппроксимации (Строго типизированный)
// ============================================================================
template <typename UnitX, typename UnitY>
struct LinearFitResult {
    // Размерности выводятся автоматически: k = [Y]/[X], b = [Y]
    using UnitK = decltype(UnitY{} / UnitX{});
    using UnitB = UnitY;

    PhysValue<UnitK> k;
    PhysValue<UnitB> b;
    
    double chi_squared;
    int degrees_of_freedom;
    double reduced_chi_squared;

    bool isGoodFit() const {
        // Критерий из п. 4.3 методички
        return reduced_chi_squared >= 0.5 && reduced_chi_squared <= 1.5; 
    }

    void print() const {
        std::cout << "=== Результаты линейной аппроксимации ===\n";
        std::cout << "k = " << k << "\n";
        std::cout << "b = " << b << "\n";
        std::cout << "χ² = " << chi_squared << ", df = " << degrees_of_freedom 
                  << ", χ²/df = " << reduced_chi_squared << "\n";
        
        if (isGoodFit()) std::cout << "✓ Модель адекватна данным\n";
        else std::cout << "✗ Плохое соответствие (проверьте погрешности или модель)\n";
        std::cout << "=========================================\n";
    }
};

// ============================================================================
// 2. Результат для НЕЛИНЕЙНОЙ аппроксимации (Универсальный)
// ============================================================================
struct NonLinearFitResult {
    std::vector<double> optimal_params;
    std::vector<double> param_errors; // σ_θ для каждого параметра
    std::vector<std::vector<double>> covariance_matrix;
    
    double chi_squared;
    int degrees_of_freedom;
    double reduced_chi_squared;

    bool isGoodFit() const {
        return reduced_chi_squared >= 0.5 && reduced_chi_squared <= 1.5;
    }

    void print(const std::vector<std::string>& param_names) const {
        std::cout << "=== Результаты нелинейной аппроксимации ===\n";
        for (size_t i = 0; i < optimal_params.size(); ++i) {
            std::cout << param_names[i] << " = " << optimal_params[i] 
                      << " ± " << param_errors[i] << "\n";
        }
        std::cout << "χ² = " << chi_squared << ", df = " << degrees_of_freedom 
                  << ", χ²/df = " << reduced_chi_squared << "\n";
        if (isGoodFit()) std::cout << "✓ Модель адекватна данным\n";
        else std::cout << "✗ Плохое соответствие\n";
        std::cout << "=========================================\n";
    }
};