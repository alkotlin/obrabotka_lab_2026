#pragma once
#include <array>
#include <string>
#include <utility>
#include <vector>
#include <cstddef>
#include <memory>
#include <iostream>
#include "PhysValue.h"

// Базовый интерфейс для стирания типа
class IRow {
public:
    virtual ~IRow() = default;
    virtual const std::string& name() const = 0;
    virtual std::size_t size() const = 0;
    virtual void print(std::ostream& os) const = 0;
};

template <typename Unit, std::size_t N>
class Row : public IRow {
public:
    explicit Row(std::string name)
        : name_(std::move(name)), data_{} {}

    Row(std::string name, std::array<PhysValue<Unit>, N> data)
        : name_(std::move(name)), data_(std::move(data)) {}

    const std::string& name() const override { return name_; }
    std::size_t size() const override { return N; }

    std::array<PhysValue<Unit>, N>&       data()       { return data_; }
    const std::array<PhysValue<Unit>, N>& data() const { return data_; }

    PhysValue<Unit>&       operator[](std::size_t i)       { return data_[i]; }
    const PhysValue<Unit>& operator[](std::size_t i) const { return data_[i]; }

    void print(std::ostream& os) const override {
        os << name_ << ": ";
        for (const auto& val : data_) {
            os << val << " ";
        }
        os << "\n";
    }

private:
    std::string              name_;
    std::array<PhysValue<Unit>, N> data_;
};

class Matrix {
public:
    // Шаблонный метод добавления, который упаковывает Row в shared_ptr
    template <typename Unit, std::size_t N>
    void add(Row<Unit, N> row) {
        rows_.push_back(std::make_shared<Row<Unit, N>>(std::move(row)));
    }

    IRow&       operator[](std::size_t i)       { return *rows_[i]; }
    const IRow& operator[](std::size_t i) const { return *rows_[i]; }

    std::size_t rowCount() const { return rows_.size(); }

    void print() const {
        for (const auto& row : rows_) {
            row->print(std::cout);
        }
    }

private:
    std::vector<std::shared_ptr<IRow>> rows_;
};