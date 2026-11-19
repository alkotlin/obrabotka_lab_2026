#pragma once
#include <array>
#include <iostream>
#include "PhysValue.h"
#include "Matrix.h"

template <typename Unit, std::size_t N>
void addRow(Matrix& m,
            const std::string& name,
            au::QuantityMaker<Unit> unit)
{
    Row<Unit, N> row(name);
    for (std::size_t i = 0; i < N; ++i) {
        row[i].value = unit(m[0][i].value);
        row[i].error = unit(m[0][i].value);
    }
    m.add(std::move(row));
}