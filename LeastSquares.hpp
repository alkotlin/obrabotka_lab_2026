#pragma once
#include <cmath>
#include <cstddef>
#include <ostream>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <string>
#include <memory>

#include <Eigen/Dense>
#include <lsqcpp/lsqcpp.hpp>

#include "Matrix.h"
#include "PhysValue.h"

// ============================================================================
// 1. Структура результата (без изменений)
// ============================================================================
template <typename UnitX, typename UnitY>
struct LinearFitResult {
    using UnitK = typename decltype(au::QuantityD<UnitY>{} / au::QuantityD<UnitX>{})::Unit;
    using UnitB = UnitY;

    PhysValue<UnitK> k;
    PhysValue<UnitB> b;
    double chi_squared = 0;
    int degrees_of_freedom = 0;
    double reduced_chi_squared = 0;

    bool isGoodFit() const { 
        return reduced_chi_squared >= 0.5 && reduced_chi_squared <= 1.5; 
    }
    
    void print() const {
        std::cout << "=== Результаты аппроксимации ===\n";
        std::cout << "k = " << k << "\n";
        std::cout << "b = " << b << "\n";
        std::cout << "χ² = " << chi_squared << ", df = " << degrees_of_freedom 
                  << ", χ²/df = " << reduced_chi_squared << "\n";
        if (isGoodFit()) std::cout << "✓ Модель адекватна данным\n";
        else std::cout << "✗ Плохое соответствие\n";
        std::cout << "================================\n";
    }
};

// ============================================================================
// 2. Математика (исправленный функтор)
// ============================================================================
namespace detail { 

// Храним данные по значению (копии), чтобы избежать проблем с ссылками
struct LinearError {
    static constexpr bool ComputesJacobian = false;
    
    std::vector<double> x;
    std::vector<double> y;
    std::vector<double> sy;

    // Конструктор по умолчанию (требуется библиотекой)
    LinearError() = default;

    // Конструктор с данными
    LinearError(const std::vector<double>& x_, const std::vector<double>& y_, const std::vector<double>& sy_)
        : x(x_), y(y_), sy(sy_) {}

    template<typename Scalar, int Inputs, int Outputs>
    void operator()(const Eigen::Matrix<Scalar, Inputs, 1> &xval, Eigen::Matrix<Scalar, Outputs, 1> &fval) const {
        fval.resize(x.size());
        for (size_t i = 0; i < x.size(); ++i) {
            double y_pred = xval(0) * x[i] + xval(1);
            fval(i) = sy.empty() ? (y[i] - y_pred) : (y[i] - y_pred) / sy[i];
        }
    }
};

template <typename UX, typename UY>
LinearFitResult<UX, UY> wrapLSQ(const std::vector<double>& x, const std::vector<double>& y, const std::vector<double>& sy) {
    // 1. Создаем функтор с данными
    LinearError err(x, y, sy);
    
    // 2. Создаем оптимизатор, передавая тип функтора в шаблон
    lsqcpp::LevenbergMarquardtX<double, LinearError> opt;
    
    // 3. Задаем начальное приближение
    Eigen::VectorXd guess(2);
    guess << 1.0, 0.0; 

    // 4. Запускаем оптимизацию (только один аргумент!)
    auto res = opt.minimize(guess);

    double chi2 = res.fval.squaredNorm();
    int dof = x.size() - 2;
    double red_chi2 = (dof > 0) ? chi2 / dof : 0;

    // 5. Считаем погрешности
    Eigen::MatrixXd J(x.size(), 2);
    Eigen::VectorXd W = Eigen::VectorXd::Ones(x.size());
    for (size_t i = 0; i < x.size(); ++i) {
        J(i, 0) = x[i]; 
        J(i, 1) = 1.0;
        if (!sy.empty()) W(i) = 1.0 / (sy[i] * sy[i]);
    }
    
    Eigen::Matrix2d cov = Eigen::Matrix2d::Zero();
    Eigen::Matrix2d JtWJ = J.transpose() * W.asDiagonal() * J;
    
    if (std::abs(JtWJ.determinant()) > 1e-15) {
        cov = red_chi2 * JtWJ.inverse();
    }
    
    // 6. Упаковываем результат
    LinearFitResult<UX, UY> f;
    f.k.value = au::QuantityMaker<typename LinearFitResult<UX, UY>::UnitK>{}(res.xval(0));
    f.k.error = au::QuantityMaker<typename LinearFitResult<UX, UY>::UnitK>{}(std::sqrt(cov(0,0)));
    f.b.value = au::QuantityMaker<UY>{}(res.xval(1));
    f.b.error = au::QuantityMaker<UY>{}(std::sqrt(cov(1,1)));
    f.chi_squared = chi2;
    f.degrees_of_freedom = dof;
    f.reduced_chi_squared = red_chi2;
    return f;
}

} // namespace detail

// ============================================================================
// 3. Публичные функции (API не меняется)
// ============================================================================

template <typename UX, typename UY, std::size_t N>
LinearFitResult<UX, UY> fitOLS(const Row<UX, N>& x, const Row<UY, N>& y) {
    std::vector<double> xs(N), ys(N);
    for (std::size_t i = 0; i < N; ++i) {
        xs[i] = x[i].value.in(UX{});
        ys[i] = y[i].value.in(UY{});
    }
    return detail::wrapLSQ<UX, UY>(xs, ys, {});
}

template <typename UX, typename UY, std::size_t N>
LinearFitResult<UX, UY> fitWOLS(const Row<UX, N>& x, const Row<UY, N>& y) {
    std::vector<double> xs(N), ys(N), sy(N);
    for (std::size_t i = 0; i < N; ++i) {
        xs[i] = x[i].value.in(UX{});
        ys[i] = y[i].value.in(UY{});
        sy[i] = y[i].error.in(UY{});
    }
    return detail::wrapLSQ<UX, UY>(xs, ys, sy);
}

template <typename UX, typename UY, std::size_t N>
LinearFitResult<UX, UY> fitMatrix(const Matrix& m, size_t idx_x, size_t idx_y, bool weighted = false) {
    auto row_x = std::dynamic_pointer_cast<const Row<UX, N>>(m[idx_x]);
    auto row_y = std::dynamic_pointer_cast<const Row<UY, N>>(m[idx_y]);

    if (!row_x || !row_y) {
        throw std::runtime_error("Ошибка приведения типов в fitMatrix");
    }
    
    return weighted ? fitWOLS(*row_x, *row_y) : fitOLS(*row_x, *row_y);
}