#pragma once

#include "au_all_units.hh"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

template <typename Unit>
class PhysValue {
public:
    PhysValue(): value(au::ZERO), error(au::ZERO){};
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
        return PhysValue(-(this->value), this->error);
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
    PhysValue<Unit> operator-(const PhysValue<Unit>& other) const
    {
        PhysValue<Unit> temp(value, error);
        temp -= other;
        return temp;
    }
    PhysValue<Unit> operator+(const PhysValue<Unit>& other) const 
    {
        PhysValue<Unit> temp(value, error);
        temp += other;
        return temp;
    }
    
    template<typename Unit2>
    auto operator*(const PhysValue<Unit2>& other) const 
    {
        auto new_value = value * other.value;
        using NewUnit = typename decltype(new_value)::unit;
        auto new_error = au::sqrt( au::pow<2>(other.value * error)
                                 + au::pow<2>(value     * other.error) );
        return PhysValue<NewUnit>(new_value, new_error);
    }
    PhysValue<Unit>& operator*=(double scalr)
    {
        value *= scalr;
        error *= std::abs(scalr);
        return *this;
    }
    
    template<typename Unit2>
    auto operator/(const PhysValue<Unit2>& other) const 
    {
        if (other.value.in(Unit2{}) == 0.0)
            throw std::domain_error("PhysValue: деление на ноль");

        auto new_value = value / other.value;
        using NewUnit = typename decltype(new_value)::unit;
        auto new_error = au::sqrt( au::pow<2>(error / other.value)
                                 + au::pow<2>(new_value * other.error / other.value) );
        return PhysValue<NewUnit>(new_value, new_error);
    }

    PhysValue<Unit>& operator/=(double scalr)
    {
        value /= scalr;
        error /= std::abs(scalr);
        return *this;
    }

    template <int N>
    auto pow() const 
    {
        auto new_value = au::pow<N>(value);
        using NewUnit = typename decltype(new_value)::unit;

        if constexpr (N == 0) {
            return PhysValue<NewUnit>(new_value,
                                      au::QuantityD<NewUnit>(au::ZERO));
        } else {
            auto new_error = std::abs(N) * au::pow<N-1>(value) * error;
            return PhysValue<NewUnit>(new_value, new_error);
        }
    }
    // PhysValue<Unit>& operator=(const PhysValue<Unit>& other)
    // {
    //     value = other.value;
    //     error = other.error;
    //     return *this;
    // }
    // PhysValue<Unit>& operator=(PhysValue<Unit>&& other)
    // {
    //     if(this != *other)
    //     {
    //         value = other.value;
    //         error = other.error;
    //     }
    //     return *this;
    // }
    friend std::ostream& operator<<(std::ostream& os, const PhysValue<Unit>& masurement)
    {
        os << masurement.value << "±" << masurement.error;               // создать гост вывод 
        return os;
    }
};


template<typename Unit>
bool operator==(const PhysValue<Unit>& lhs, const PhysValue<Unit>& rhs)
{
    au::QuantityD<Unit> delta = au::abs(rhs.value - lhs.value);
    au::QuantityD<Unit> delta_error = au::sqrt(rhs.error * rhs.error + lhs.error * lhs.error);
    return delta.in(Unit{}) < delta_error.in(Unit{});
}

template<typename Unit>
bool operator<(const PhysValue<Unit>& lhs, const PhysValue<Unit>& rhs)
{
    if( lhs == rhs ) return false;
    return lhs.value < rhs.value;
}

template<typename Unit>
bool operator>(const PhysValue<Unit>& lhs, const PhysValue<Unit>& rhs)
{
    if( lhs == rhs ) return false;
    return lhs.value > rhs.value;
}

template<typename Unit>
bool operator>=(const PhysValue<Unit>& lhs, const PhysValue<Unit>& rhs)
{
    return lhs == rhs || lhs.value > rhs.value;
}

template<typename Unit>
bool operator<=(const PhysValue<Unit>& lhs, const PhysValue<Unit>& rhs)
{
    return lhs == rhs || lhs.value < rhs.value;
}

template<typename Unit>
bool operator!=(const PhysValue<Unit>& lhs, const PhysValue<Unit>& rhs)
{
    if( lhs == rhs ) return false;
    return true;
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