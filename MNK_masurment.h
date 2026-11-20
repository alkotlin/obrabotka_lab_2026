#pragma once
#include "Matrix.h"       // Ваш существующий файл с IRow, Row и Matrix
#include "MNK_base.h"   // LinearFitResult из предыдущего ответа
#include <cmath>
#include <stdexcept>
#include <memory>

// ============================================================================
// ОБЫЧНЫЙ МНК (Формулы 4.4, 4.10 методички)
// ============================================================================
template <typename UnitX, typename UnitY, std::size_t N>
class MNK {
public:
    LinearFitResult<UnitX, UnitY> fit(const Matrix& m, size_t idx_x, size_t idx_y) {
        if (N < 2) throw std::runtime_error("МНК требует минимум 2 точки");

        // 1. Безопасно извлекаем типизированные строки из матрицы
        auto row_x = std::dynamic_pointer_cast<const Row<UnitX, N>>(m[idx_x]);
        auto row_y = std::dynamic_pointer_cast<const Row<UnitY, N>>(m[idx_y]);

        if (!row_x || !row_y) {
            throw std::runtime_error("Ошибка приведения типов: проверьте индексы строк и единицы измерения (UnitX, UnitY)");
        }

        // 2. Стандартный расчет МНК
        double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0, sum_y2 = 0;
        for (std::size_t i = 0; i < N; ++i) {
            double x = (*row_x)[i].value.in(UnitX{});
            double y = (*row_y)[i].value.in(UnitY{});
            sum_x += x; sum_y += y; sum_xy += x * y; sum_x2 += x * x; sum_y2 += y * y;
        }

        double mean_x = sum_x / N, mean_y = sum_y / N;
        double mean_xy = sum_xy / N, mean_x2 = sum_x2 / N, mean_y2 = sum_y2 / N;

        double k = (mean_xy - mean_x * mean_y) / (mean_x2 - mean_x * mean_x);
        double b = mean_y - k * mean_x;

        double sigma_k2 = (mean_y2 - mean_y * mean_y) / (mean_x2 - mean_x * mean_x) - k * k;
        sigma_k2 = std::max(0.0, sigma_k2 / (N - 2));
        double sigma_k = std::sqrt(sigma_k2);
        double sigma_b = std::sqrt(std::max(0.0, sigma_k2 * mean_x2));

        double chi2 = 0;
        for (std::size_t i = 0; i < N; ++i) {
            double x = (*row_x)[i].value.in(UnitX{});
            double y = (*row_x)[i];
            double y = (*row_y)[i].value.in(UnitY{});
            double y_pred = k * x + b;
            chi2 += (y - y_pred) * (y - y_pred);
        }

        using UnitK = decltype(UnitY{} / UnitX{});
        return {
            PhysValue<UnitK>(au::QuantityD<UnitK>(k), au::QuantityD<UnitK>(sigma_k)),
            PhysValue<UnitY>(au::QuantityD<UnitY>(b), au::QuantityD<UnitY>(sigma_b)),
            chi2, static_cast<int>(N) - 2, (N > 2) ? chi2 / (N - 2) : 0.0
        };
    }
};