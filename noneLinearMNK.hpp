#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include <lsqcpp/lsqcpp.hpp> // Подключаем саму библиотеку

// 1. Опишем функцию ошибки как функтор (структуру с operator()).
struct ExponentialError {
    // Говорим библиотеке, что мы НЕ вычисляем якобиан вручную,
    // она сделает это сама через конечные разности.
    static constexpr bool ComputesJacobian = false;

    // Данные, которые мы хотим аппроксимировать.
    const std::vector<double>& x_data;
    const std::vector<double>& y_data;

    ExponentialError(const std::vector<double>& x, const std::vector<double>& y)
        : x_data(x), y_data(y) {}

    // Основная функция. xval — текущие значения параметров (например, A и alpha).
    // fval — вектор ошибок (невязок) для каждого измерения.
    template<typename Scalar, int Inputs, int Outputs>
    void operator()(const Eigen::Matrix<Scalar, Inputs, 1> &xval,
                    Eigen::Matrix<Scalar, Outputs, 1> &fval) const {
        
        // xval(0) — параметр A, xval(1) — параметр alpha.
        double A = xval(0);
        double alpha = xval(1);

        fval.resize(x_data.size()); // Размер вектора ошибок = число точек.
        for (size_t i = 0; i < x_data.size(); ++i) {
            double y_pred = A * std::exp(-alpha * x_data[i]); // Наша модель
            fval(i) = y_data[i] - y_pred; // Невязка (ошибка)
        }
    }
};