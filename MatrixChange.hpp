#pragma once
#include <cstddef>
#include <string>
#include <utility>
#include "PhysValue.h"
#include "Matrix.h"
#include <cmath>
template <typename Unit, std::size_t N>
void setCell(Matrix& m, std::size_t n, std::size_t col,
             au::QuantityMaker<Unit> unit, double value, double error)
{
    if (n >= m.rowCount()) throw std::out_of_range("setCell: row");
    auto* row = dynamic_cast<Row<Unit, N>*>(&m[n]);
    if (!row) throw std::runtime_error("setCell: Unit/N mismatch");
    if (col >= row->size()) throw std::out_of_range("setCell: col");
    (*row)[col].value = unit(value);
    (*row)[col].error = unit(error);
}

template <typename Unit, std::size_t N>
void addRow(Matrix& m,
                const std::string& name,
                au::QuantityMaker<Unit> unit)
{
    Row<Unit, N> row(name);
    for (std::size_t i = 0; i < N; ++i) {
        row[i].value = unit(0.0);
        row[i].error = unit(0.0);
    }
    m.add(std::move(row));
}
template <typename Unit1, typename Unit2, std::size_t N>
std::size_t Multiplicate(Matrix& m,
                  std::size_t first,
                  std::size_t second,
                  const std::string& name)
{
    auto* r1 = dynamic_cast<Row<Unit1, N>*>(&m[first]);
    auto* r2 = dynamic_cast<Row<Unit2, N>*>(&m[second]);
    if (!r1) throw std::runtime_error(
        "Multiplicate: строка " + std::to_string(first) + " — не Row<Unit1, N>");
    if (!r2) throw std::runtime_error(
        "Multiplicate: строка " + std::to_string(second) + " — не Row<Unit2, N>");

    using ResultUnit = typename decltype(au::QuantityD<Unit1>{} * au::QuantityD<Unit2>{})::unit;
    addRow<ResultUnit, N>(m, name, au::QuantityMaker<ResultUnit>{});
    const std::size_t third = m.rowCount() - 1;
    auto* r3 = dynamic_cast<Row<ResultUnit, N>*>(&m[third]);
    if (!r3) throw std::runtime_error(
        "Multiplicate: строка " + std::to_string(third) +
        " должна быть Row<ResultUnit, N>");

    for (std::size_t i = 0; i < N; ++i) {
        PhysValue<ResultUnit> product = (*r1)[i] * (*r2)[i];
        (*r3)[i].value = product.value;
        (*r3)[i].error = product.error;
    }
    return third;
}

template <typename Unit, std::size_t N, int Num, int Den = 1>
std::size_t Power(Matrix& m,
                  std::size_t first,
                  const std::string& name)
{
    auto* r1 = dynamic_cast<Row<Unit, N>*>(&m[first]);
    if (!r1) throw std::runtime_error(
        "Power: строка " + std::to_string(first) + " — не Row<Unit, N>");

    using ResultUnit = typename decltype(
        PhysValue<Unit>{}.template pow<Num, Den>()
    )::unit;

    addRow<ResultUnit, N>(m, name, au::QuantityMaker<ResultUnit>{});
    const std::size_t result = m.rowCount() - 1;
    auto* r3 = dynamic_cast<Row<ResultUnit, N>*>(&m[result]);
    if (!r3) throw std::runtime_error(
        "Power: строка " + std::to_string(result) +
        " должна быть Row<ResultUnit, N>");

    for (std::size_t i = 0; i < N; ++i) {
        auto pv = (*r1)[i].template pow<Num, Den>();
        (*r3)[i].value = pv.value;
        (*r3)[i].error = pv.error;
    }
    return result;
}

template <typename Unit, std::size_t N>
std::size_t Sum(Matrix& m,
          std::size_t first,  double a,
          std::size_t second, double b,
          const std::string& name)
{
    if (first >= m.rowCount() || second >= m.rowCount())
        throw std::out_of_range("Sum: row index out of range");

    auto* r1 = dynamic_cast<Row<Unit, N>*>(&m[first]);
    auto* r2 = dynamic_cast<Row<Unit, N>*>(&m[second]);
    if (!r1) throw std::runtime_error(
        "Sum: строка " + std::to_string(first) + " — не Row<Unit, N>");
    if (!r2) throw std::runtime_error(
        "Sum: строка " + std::to_string(second) + " — не Row<Unit, N>");
    addRow<Unit, N>(m, name, au::QuantityMaker<Unit>{});
    const std::size_t third = m.rowCount() - 1;
    auto* r3 = dynamic_cast<Row<Unit, N>*>(&m[third]);
    if (!r3) throw std::runtime_error(
        "Sum: строка " + std::to_string(third) + " — не Row<Unit, N>");

    for (std::size_t i = 0; i < N; ++i) {
        (*r3)[i] = a * (*r1)[i] + b * (*r2)[i];
    }
    return third;
}