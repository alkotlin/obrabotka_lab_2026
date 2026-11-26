#pragma once
// LeastSquares.hpp: линейный МНК y = a*x + b (обычный fitOLS и взвешенный fitWOLS).
// Вход: Row<UX,N> и Row<UY,N> одного размера. Выход: LinearFit (a, b с погрешностями и единицами, R^2, n).
// Зависит только от Matrix.h и PhysValue.h.

#include <cmath>      // std::sqrt
#include <cstddef>    // std::size_t
#include <ostream>    // std::ostream
#include <stdexcept>  // исключения
#include <vector>     // временные массивы чисел

#include "Matrix.h"
#include "PhysValue.h"

namespace detail { // математика на чистых double, без единиц

struct RawFit {
    double a = 0, da = 0;  // наклон и его погрешность
    double b = 0, db = 0;  // свободный член и его погрешность
    double r2 = 0;         // R^2: 1 = точки лежат точно на прямой
};

inline RawFit olsRaw(const std::vector<double>& x, const std::vector<double>& y) // обычный МНК
{
    const std::size_t n = x.size();                                    // число точек
    if (n != y.size()) throw std::invalid_argument("olsRaw: x и y разной длины");
    if (n < 3) throw std::invalid_argument("olsRaw: нужно минимум 3 точки"); // делим на (n-2)

    double Sx = 0, Sy = 0, Sxx = 0, Sxy = 0;                           // суммы: Σx, Σy, Σx², Σxy
    for (std::size_t i = 0; i < n; ++i) {
        Sx  += x[i];                                                   // Σx
        Sy  += y[i];                                                   // Σy
        Sxx += x[i] * x[i];                                            // Σx²
        Sxy += x[i] * y[i];                                            // Σxy
    }

    const double N = static_cast<double>(n);                           // n как double
    const double D = N * Sxx - Sx * Sx;                                // знаменатель формул, 0 если все x равны
    if (D == 0.0) throw std::domain_error("olsRaw: все x одинаковы");

    RawFit r;
    r.a = (N * Sxy - Sx * Sy) / D;                                     // наклон
    r.b = (Sy - r.a * Sx) / N;                                         // свободный член

    const double ymean = Sy / N;                                       // среднее y
    double ssRes = 0, ssTot = 0;                                       // остатки² и полный разброс y²
    for (std::size_t i = 0; i < n; ++i) {
        const double e = y[i] - r.a * x[i] - r.b;                      // отклонение точки от прямой
        ssRes += e * e;                                                // Σ(y - ax - b)²
        ssTot += (y[i] - ymean) * (y[i] - ymean);                      // Σ(y - ȳ)²
    }

    const double s2 = ssRes / (N - 2.0);                               // дисперсия точки (2 параметра уже оценены)
    r.da = std::sqrt(s2 * N / D);                                      // σ_a
    r.db = std::sqrt(s2 * Sxx / D);                                    // σ_b
    r.r2 = ssTot > 0 ? 1.0 - ssRes / ssTot : 1.0;                      // R^2 (если все y равны, считаем 1)
    return r;
}

inline RawFit wolsRaw(const std::vector<double>& x, const std::vector<double>& y,
                      const std::vector<double>& sy) // взвешенный МНК, sy = погрешности y
{
    const std::size_t n = x.size();                                    // число точек
    if (n != y.size() || n != sy.size()) throw std::invalid_argument("wolsRaw: x, y, sy разной длины");
    if (n < 2) throw std::invalid_argument("wolsRaw: нужно минимум 2 точки");

    double S = 0, Sx = 0, Sy = 0, Sxx = 0, Sxy = 0;                    // суммы с весами w
    for (std::size_t i = 0; i < n; ++i) {
        if (!(sy[i] > 0.0)) throw std::domain_error("wolsRaw: погрешность y должна быть > 0"); // ловит и NaN
        const double w = 1.0 / (sy[i] * sy[i]);                        // вес точки 1/σ²
        S   += w;                                                      // Σw
        Sx  += w * x[i];                                               // Σwx
        Sy  += w * y[i];                                               // Σwy
        Sxx += w * x[i] * x[i];                                        // Σwx²
        Sxy += w * x[i] * y[i];                                        // Σwxy
    }

    const double D = S * Sxx - Sx * Sx;                                // знаменатель, 0 если все x равны
    if (D == 0.0) throw std::domain_error("wolsRaw: все x одинаковы");

    RawFit r;
    r.a  = (S * Sxy - Sx * Sy) / D;                                    // наклон
    r.b  = (Sxx * Sy - Sx * Sxy) / D;                                  // свободный член
    r.da = std::sqrt(S / D);                                           // σ_a из заданных погрешностей
    r.db = std::sqrt(Sxx / D);                                         // σ_b из заданных погрешностей

    const double ymean = Sy / S;                                       // взвешенное среднее y
    double ssRes = 0, ssTot = 0;                                       // взвешенные суммы квадратов
    for (std::size_t i = 0; i < n; ++i) {
        const double w = 1.0 / (sy[i] * sy[i]);                        // вес точки
        const double e = y[i] - r.a * x[i] - r.b;                      // остаток точки
        ssRes += w * e * e;                                            // Σw·e²
        ssTot += w * (y[i] - ymean) * (y[i] - ymean);                  // Σw·(y - ȳ)²
    }
    r.r2 = ssTot > 0 ? 1.0 - ssRes / ssTot : 1.0;                      // взвешенный R^2
    return r;
}

} // namespace detail

template <typename UnitX, typename UnitY>
struct LinearFit { // результат подгонки с единицами измерения
    using UnitA = typename decltype(au::QuantityD<UnitY>{} / au::QuantityD<UnitX>{})::Unit; // единица a = Y/X (::Unit — тип, ::unit — значение)

    PhysValue<UnitA> a;   // наклон (значение и погрешность)
    PhysValue<UnitY> b;   // свободный член
    double      r2 = 0;   // R^2
    std::size_t n  = 0;   // число точек
};

template <typename UX, typename UY>
std::ostream& operator<<(std::ostream& os, const LinearFit<UX, UY>& f) // вывод: std::cout << fit
{
    os << "y = a*x + b\n"
       << "a = " << f.a << "\n"                                        // "значение ед.±погрешность"
       << "b = " << f.b << "\n"
       << "R^2 = " << f.r2 << ", n = " << f.n << "\n";
    return os;
}

namespace detail {

template <typename UX, typename UY, std::size_t N>
LinearFit<UX, UY> wrap(const RawFit& r) // числа -> величины с единицами (без конструктора PhysValue(v,e))
{
    using Fit = LinearFit<UX, UY>;
    Fit f;
    f.a.value = au::QuantityMaker<typename Fit::UnitA>{}(r.a);         // число -> величина в единицах Y/X
    f.a.error = au::QuantityMaker<typename Fit::UnitA>{}(r.da);
    f.b.value = au::QuantityMaker<UY>{}(r.b);                          // число -> величина в единицах Y
    f.b.error = au::QuantityMaker<UY>{}(r.db);
    f.r2 = r.r2;
    f.n  = N;                                                          // N известно на этапе компиляции
    return f;
}

} // namespace detail

template <typename UX, typename UY, std::size_t N>
LinearFit<UX, UY> fitOLS(const Row<UX, N>& x, const Row<UY, N>& y) // обычный МНК, погрешности не используются
{
    static_assert(N >= 3, "fitOLS: нужно минимум 3 точки");            // проверка при компиляции

    std::vector<double> xs(N), ys(N);                                  // значения без единиц
    for (std::size_t i = 0; i < N; ++i) {
        xs[i] = x[i].value.in(UX{});                                   // величина -> double в единицах UX
        ys[i] = y[i].value.in(UY{});
    }
    return detail::wrap<UX, UY, N>(detail::olsRaw(xs, ys));            // считаем и добавляем единицы
}

template <typename UX, typename UY, std::size_t N>
LinearFit<UX, UY> fitWOLS(const Row<UX, N>& x, const Row<UY, N>& y) // взвешенный МНК, вес = 1/error_y²
{
    static_assert(N >= 2, "fitWOLS: нужно минимум 2 точки");           // проверка при компиляции

    std::vector<double> xs(N), ys(N), sy(N);                           // значения и погрешности без единиц
    for (std::size_t i = 0; i < N; ++i) {
        xs[i] = x[i].value.in(UX{});                                   // x в единицах UX
        ys[i] = y[i].value.in(UY{});                                   // y в единицах UY
        sy[i] = y[i].error.in(UY{});                                   // погрешность y в тех же единицах
    }
    return detail::wrap<UX, UY, N>(detail::wolsRaw(xs, ys, sy));       // считаем и добавляем единицы
}