#pragma once
#include <array>
#include <string>
#include <utility>
#include <vector>
#include <cstddef>

template <std::size_t N>
class Row {
public:
    explicit Row(std::string name)
        : name_(std::move(name)), data_{} {}

    Row(std::string name, std::array<PhysValue, N> data)
        : name_(std::move(name)), data_(std::move(data)) {}

    const std::string& name() const { return name_; }
    std::array<PhysValue, N>&       data()       { return data_; }
    const std::array<PhysValue, N>& data() const { return data_; }

    PhysValue&       operator[](std::size_t i)       { return data_[i]; }
    const PhysValue& operator[](std::size_t i) const { return data_[i]; }

    constexpr std::size_t size() const { return N; }

private:
    std::string              name_;
    std::array<PhysValue, N> data_;
};

template <std::size_t N>
class Matrix {
public:
    void add(Row<N> row) { rows_.push_back(std::move(row)); }

    Row<N>&       operator[](std::size_t i)       { return rows_[i]; }
    const Row<N>& operator[](std::size_t i) const { return rows_[i]; }

    std::size_t rowCount() const { return rows_.size(); }
    constexpr std::size_t colCount() const { return N; }

private:
    std::vector<Row<N>> rows_;
};