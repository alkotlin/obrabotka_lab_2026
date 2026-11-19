#pragma once
#include <cstddef>
#include <string>
#include <utility>
#include "PhysValue.h"
#include "Matrix.h"

template <typename Unit, std::size_t N>
void addZeroRow(Matrix& m,
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