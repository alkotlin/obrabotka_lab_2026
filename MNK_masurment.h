#pragma once
#include "Matrix.h"    
#include "MNK_base.h"
#include <cmath>
#include <stdexcept>
#include <memory>
#include <algorithm> // Для std::max

template <typename UnitX, typename UnitY, std::size_t N>
class MNK {
public:
    LinearFitResult<UnitX, UnitY> fit(const Matrix& m, size_t idx_x, size_t idx_y) {
        if (N < 3) throw std::runtime_error("МНК требует минимум 3 точки для оценки погрешности (N-2 > 0)");

        // 1. Безопасно извлекаем типизированные строки
        auto row_x = std::dynamic_pointer_cast<const Row<UnitX, N>>(m[idx_x]);
        auto row_y = std::dynamic_pointer_cast<const Row<UnitY, N>>(m[idx_y]);

        if (!row_x || !row_y) {
            throw std::runtime_error("Ошибка приведения типов: проверьте индексы строк и единицы измерения");
        }

        // 2. Считаем суммы для коэффициентов
        double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;
        for (std::size_t i = 0; i < N; ++i) {
            double x = (*row_x)[i].value.in(UnitX{});
            double y = (*row_y)[i].value.in(UnitY{});
            sum_x += x; 
            sum_y += y; 
            sum_xy += x * y; 
            sum_x2 += x * x; 
        }

        double mean_x = sum_x / N;
        double mean_y = sum_y / N;
        double mean_xy = sum_xy / N;
        double mean_x2 = sum_x2 / N;

        // Коэффициенты
        double denom_x = sum_x2 - N * mean_x * mean_x; // Сумма квадратов отклонений по X
        if (std::abs(denom_x) < 1e-15) {
            throw std::runtime_error("Все точки имеют одинаковый X. Наклон не определен.");
        }
        
        double k = (mean_xy - mean_x * mean_y) / (mean_x2 - mean_x * mean_x);
        double b = mean_y - k * mean_x;

        // 3. Считаем chi2 (сумму квадратов остатков)
        double chi2 = 0;
        for (std::size_t i = 0; i < N; ++i) {
            double x = (*row_x)[i].value.in(UnitX{});
            double y = (*row_y)[i].value.in(UnitY{}); // ИСПРАВЛЕНО: берем .value.in()
            double y_pred = k * x + b;
            chi2 += (y - y_pred) * (y - y_pred);
        }

        double sigma_y2 = chi2 / (N - 2);
        double sigma_k2 = sigma_y2 / denom_x;
        double sigma_k = std::sqrt(std::max(0.0, sigma_k2));
        double sigma_b2 = sigma_k2 * (sum_x2 / N);
        double sigma_b = std::sqrt(std::max(0.0, sigma_b2));

        using UnitK = decltype(UnitY{} / UnitX{});
        
        return {
            PhysValue<UnitK>(au::QuantityD<UnitK>(k), au::QuantityD<UnitK>(sigma_k)),
            PhysValue<UnitY>(au::QuantityD<UnitY>(b), au::QuantityD<UnitY>(sigma_b)),
            chi2, 
            static_cast<int>(N) - 2, 
            (N > 2) ? chi2 / (N - 2) : 0.0
        };
    }
};