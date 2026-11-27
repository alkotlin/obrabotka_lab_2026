#pragma once

#include "au_all_units.hh"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

template <typename Unit>
class PhysValue {
private:
    PhysValue() = delete; // у каждого au::QuantityD есть шаблонный параметр, известный на этапе компиляции

public:
    au::QuantityD<Unit> value;
    au::QuantityD<Unit> error;

    PhysValue(const PhysValue&)                = default;
    PhysValue(PhysValue&&) noexcept            = default;
    PhysValue& operator=(const PhysValue&)     = default;
    PhysValue& operator=(PhysValue&&) noexcept = default;
    ~PhysValue()                               = default;

    using unit = Unit;

    PhysValue<Unit> operator-() const
    {
        return PhysValue<Unit>(-value, error);
    }

    PhysValue<Unit>& operator+=(const PhysValue<Unit>& other)
    {
        value += other.value;
        error = au::sqrt(au::pow<2>(error) + au::pow<2>(other.error));
        return *this;
    }

    PhysValue<Unit>& operator-=(const PhysValue<Unit>& other)
    {
        value -= other.value;
        error = au::sqrt(au::pow<2>(error) + au::pow<2>(other.error));
        return *this;
    }

    PhysValue<Unit> operator+(const PhysValue<Unit>& other) const
    {
        PhysValue<Unit> temp(*this);
        temp += other;
        return temp;
    }

    PhysValue<Unit> operator-(const PhysValue<Unit>& other) const
    {
        PhysValue<Unit> temp(*this);
        temp -= other;
        return temp;
    }

    template <typename Unit2>
    auto operator*(const PhysValue<Unit2>& other) const
    {
        auto new_value = value * other.value;
        using NewUnit = typename decltype(new_value)::unit;
        auto new_error = au::sqrt(au::pow<2>(other.value * error) + au::pow<2>(value * other.error));
        return PhysValue<NewUnit>(new_value, new_error);
    }

    PhysValue<Unit>& operator*=(double scalar)
    {
        value *= scalar;
        error *= std::abs(scalar);
        return *this;
    }

    template <typename Unit2>
    auto operator/(const PhysValue<Unit2>& other) const
    {
        if (other.value.in(Unit2{}) == 0.0) {
            throw std::domain_error("PhysValue: деление на ноль");
        }
        auto new_value = value / other.value;
        using NewUnit = typename decltype(new_value)::unit;
        auto new_error = au::sqrt(
            au::pow<2>(error / other.value) +
            au::pow<2>(new_value * (other.error / other.value))
        );
        return PhysValue<NewUnit>(new_value, new_error);
    }

    PhysValue<Unit>& operator/=(double scalar)
    {
        if (scalar == 0.0) {
            throw std::domain_error("PhysValue: деление на ноль");
        }
        value /= scalar;
        error /= std::abs(scalar);
        return *this;
    }

    template <int Num, int Den = 1>
    auto pow() const
    {
        static_assert(Den != 0, "Den must be nonzero");

        auto new_value = au::pow<Num, Den>(value);
        using NewUnit = typename decltype(new_value)::unit;

        if (value.in(Unit{}) == 0.0) {
            return PhysValue<NewUnit>(new_value, au::QuantityD<NewUnit>::zero());
        }

        const double factor = std::abs(static_cast<double>(Num) / static_cast<double>(Den));
        auto relative_error = (error / value) * factor;
        auto new_error = au::abs(new_value * relative_error);
        return PhysValue<NewUnit>(new_value, new_error);
    }
};

template <typename Unit>
bool operator==(const PhysValue<Unit>& lhs, const PhysValue<Unit>& rhs)
{
    double delta = std::abs((rhs.value - lhs.value).in(Unit{}));
    double delta_error = std::sqrt(
        std::pow(rhs.error.in(Unit{}), 2) + std::pow(lhs.error.in(Unit{}), 2)
    );
    return delta < delta_error;
}

template <typename Unit>
bool operator!=(const PhysValue<Unit>& lhs, const PhysValue<Unit>& rhs)
{
    return !(lhs == rhs);
}

template <typename Unit>
bool operator<(const PhysValue<Unit>& lhs, const PhysValue<Unit>& rhs)
{
    if (lhs == rhs) return false;
    return lhs.value < rhs.value;
}

template <typename Unit>
bool operator>(const PhysValue<Unit>& lhs, const PhysValue<Unit>& rhs)
{
    if (lhs == rhs) return false;
    return lhs.value > rhs.value;
}

template <typename Unit>
bool operator<=(const PhysValue<Unit>& lhs, const PhysValue<Unit>& rhs)
{
    return (lhs == rhs) || (lhs.value < rhs.value);
}

template <typename Unit>
bool operator>=(const PhysValue<Unit>& lhs, const PhysValue<Unit>& rhs)
{
    return (lhs == rhs) || (lhs.value > rhs.value);
}

template <typename Unit>
std::ostream& operator<<(std::ostream& os, const PhysValue<Unit>& v)
{
    os << v.value.in(Unit{}) << "±" << v.error.in(Unit{});
    return os;
}

template <typename Unit>
PhysValue<Unit> operator*(double k, const PhysValue<Unit>& x)
{
    return PhysValue<Unit>(k * x.value, std::abs(k) * x.error);
}

template <typename Unit>
PhysValue<Unit> operator*(const PhysValue<Unit>& x, double k)
{
    return k * x;
}