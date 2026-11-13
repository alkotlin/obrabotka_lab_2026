#pragma once

#include "au_all_units.hh"
#include <cmath>
#include <iostream>


template <typename Unit>
class PhysValue {
private:
    // PhysValue(): value(au::QuantityD<Unit>::zero()), error(au::QuantityD<Unit>::zero()){};
    PhysValue() = delete;
public:
    au::QuantityD<Unit> value;
    au::QuantityD<Unit> error;

    PhysValue(au::QuantityD<Unit> value, au::QuantityD<Unit> error): value(value), error(error){}
    PhysValue(const PhysValue<Unit>& other): value(other.value), error(other.error){}
    PhysValue(PhysValue<Unit>&& other): value(other.value), error(other.error){}
    ~PhysValue() = default;

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
    PhysValue<Unit>& operator-=(PhysValue<Unit>& other)
    {
        value -= other.value;
        error = au::sqrt(au::pow<2>(error) + au::pow<2>(other.error));
        return *this;
    }
    PhysValue<Unit> operator-(PhysValue<Unit> other) const
    {
        PhysValue<Unit> temp(value, error);
        temp -= other;
        return temp;
    }
    PhysValue<Unit> operator+(PhysValue<Unit> other) const 
    {
        PhysValue<Unit> temp(value, error);
        temp += other;
        return temp;
    } 
    
    
    template<typename Unit2>
    auto operator*(PhysValue<Unit2> other) const 
    {
        auto new_value = value * other.value;
        auto new_error = new_value * au::sqrt(au::pow<2>(error / value) + au::pow<2>(other.error / other.value));
        return PhysValue<typename decltype(new_value)::unit>(new_value, new_error);
    }
    PhysValue<Unit>& operator*=(double scalr)
    {
        value *= scalr;
        error *= std::abs(scalr);
        return *this;
    }
    
    template<typename Unit2>
    auto operator/(PhysValue<Unit2> other) const 
    {
        auto new_value = value / other.value;
        auto new_error = new_value * au::sqrt(au::pow<2>(error / value) + au::pow<2>(other.error / other.value));
        if (value.in(Unit{}) == 0.0 || other.value.in(Unit2{}) == 0.0) {
            throw std::domain_error("Деление на ноль при расчете относительной погрешности");
        }
        return PhysValue<typename decltype(new_value)::unit>(new_value, new_error);
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
        auto relative_error = (error / value) * N;
        auto new_error = new_value * relative_error;
        using NewUnit = typename decltype(new_value)::unit;

        return PhysValue<NewUnit>(new_value, new_error);
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