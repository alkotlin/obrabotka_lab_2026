#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <stdexcept>

#include <Eigen/Dense>
#include <lsqcpp/lsqcpp.hpp>

// Подключаем твои заголовочные файлы
#include "Matrix.h"
#include "PhysValue.h"
#include "LeastSquares.hpp"
#include "MNK_base.h"
#include "au_all_units.hh"

// Функция из твоего Excel.cpp
Matrix ExcelEnter(const std::string& path, std::size_t count = 0);

// ============================================================================
// Функтор для нелинейного МНК (Экспонента y = A * exp(-alpha * x))
// ============================================================================
struct ExponentialError {
    static constexpr bool ComputesJacobian = false;
    const std::vector<double>& x_data;
    const std::vector<double>& y_data;

    ExponentialError(const std::vector<double>& x, const std::vector<double>& y)
        : x_data(x), y_data(y) {}

    template<typename Scalar, int Inputs, int Outputs>
    void operator()(const Eigen::Matrix<Scalar, Inputs, 1> &xval,
                    Eigen::Matrix<Scalar, Outputs, 1> &fval) const {
        double A = xval(0);
        double alpha = xval(1);

        fval.resize(x_data.size());
        for (size_t i = 0; i < x_data.size(); ++i) {
            double y_pred = A * std::exp(-alpha * x_data[i]);
            fval(i) = y_data[i] - y_pred; // Невязка
        }
    }
};

int main() {
    std::cout << "=== ЛАБОРАТОРНАЯ РАБОТА: ОБРАБОТКА ДАННЫХ ===\n\n";

    // ВАЖНО: Укажи здесь точное количество строк (точек) из твоего Excel-файла.
    // Судя по скриншоту, у тебя 12 строк с данными.
    constexpr std::size_t N = 12; 
    const std::string filename = "data.xlsx"; // Имя твоего файла

    try {
        // =====================================================================
        // 1. ЧТЕНИЕ ДАННЫХ ИЗ EXCEL
        // =====================================================================
        std::cout << "1. Чтение данных из " << filename << "...\n";
        Matrix data = ExcelEnter(filename, N);
        
        // Извлекаем строки (0 - путь (l), 1 - время (t))
        auto* row_l = dynamic_cast<Row<au::Meters, N>*>(&data[0]);
        auto* row_t = dynamic_cast<Row<au::Seconds, N>*>(&data[1]);

        if (!row_l || !row_t) {
            throw std::runtime_error("Ошибка: Не удалось привести типы строк. Проверь единицы измерения в Excel (должны быть 'meters' и 'seconds').");
        }

        std::cout << "\n[Исходные данные]\n";
        data.print();

        // =====================================================================
        // 2. ВЫПОЛНЕНИЕ ОПЕРАЦИЙ (Сложение, вычитание, деление)
        // =====================================================================
        std::cout << "\n2. Косвенные расчеты по точкам (операции над PhysValue)\n";
        
        // Пример 1: Найдем скорость v = l / t для каждой точки
        std::cout << "Скорость v = l / t:\n";
        for (std::size_t i = 0; i < N; ++i) {
            auto v = (*row_l)[i] / (*row_t)[i];
            std::cout << "  Точка " << i+1 << ": v = " 
                      << v.value.in(au::meters / au::seconds) << " ± " 
                      << v.error.in(au::meters / au::seconds) << " м/с\n";
        }

        // Пример 2: Вычитание (найдем приращение пути между соседними точками)
        std::cout << "\nПриращение пути (l[i] - l[i-1]):\n";
        for (std::size_t i = 1; i < N; ++i) {
            auto delta_l = (*row_l)[i] - (*row_l)[i-1];
            std::cout << "  l[" << i << "] - l[" << i-1 << "] = " 
                      << delta_l.value.in(au::meters) << " ± " 
                      << delta_l.error.in(au::meters) << " м\n";
        }

        // =====================================================================
        // 3. ЛИНЕЙНЫЙ МНК (Обычный и Взвешенный)
        // =====================================================================
        std::cout << "\n3. Линейный МНК (Зависимость l от t)\n";
        
        // Обычный МНК (не учитывает погрешности, fitOLS)
        std::cout << "\n--- Обычный МНК (без учета погрешностей) ---\n";
        auto fit_ols = fitMatrix<au::Seconds, au::Meters, N>(data, 1, 0, false);
        fit_ols.print();

        // Взвешенный МНК (учитывает погрешности, fitWOLS)
        std::cout << "\n--- Взвешенный МНК (с учетом погрешностей) ---\n";
        auto fit_wols = fitMatrix<au::Seconds, au::Meters, N>(data, 1, 0, true);
        fit_wols.print();

        // =====================================================================
        // 4. НЕЛИНЕЙНЫЙ МНК (Экспонента y = A * exp(-alpha * x))
        // =====================================================================
        std::cout << "\n4. Нелинейный МНК (Аппроксимация экспонентой)\n";
        
        // Подготовка данных для lsqcpp (чистые double)
        std::vector<double> xs(N), ys(N);
        for (std::size_t i = 0; i < N; ++i) {
            xs[i] = (*row_t)[i].value.in(au::Seconds{});
            ys[i] = (*row_l)[i].value.in(au::Meters{});
        }

        ExponentialError err(xs, ys);
        lsqcpp::LevenbergMarquardtX<double, ExponentialError> opt;
        
        // Начальное приближение: A = первый y, alpha = 0.1
        Eigen::VectorXd guess(2);
        guess << ys[0], 0.1; 

        auto result = opt.minimize(guess, err);

        std::cout << "A = " << result.xval(0) << "\n";
        std::cout << "alpha = " << result.xval(1) << "\n";
        std::cout << "chi2 = " << result.fval.squaredNorm() << "\n";
        std::cout << "Итераций: " << result.iterations << "\n";

    } catch (const std::exception& e) {
        std::cerr << "\n[ОШИБКА] " << e.what() << "\n";
        return 1;
    }

    std::cout << "\n=== РАСЧЕТ ЗАВЕРШЕН ===\n";
    return 0;
}