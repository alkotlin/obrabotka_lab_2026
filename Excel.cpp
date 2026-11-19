#include <OpenXLSX.hpp>
#include "au_all_units.hh"
#include "Matrix.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <functional>
#include "PhysValue.h"

template <typename Unit, std::size_t N>
void fillAndAddRow(Matrix& m,
                   const std::string& name,
                   const std::function<double(std::size_t, std::size_t)>& get,
                   au::QuantityMaker<Unit> unit,
                   std::size_t rowValue,
                   std::size_t rowError)
{
    Row<Unit, N> row(name);
    for (std::size_t i = 0; i < N; ++i) {
        row[i].value = unit(get(rowValue, 2 + i));
        row[i].error = unit(get(rowError, 2 + i));
    }
    m.add(row);
}

void addRowByUnit(Matrix& m,
                  const std::string& unitName,
                  const std::string& rowName,
                  const std::function<double(std::size_t, std::size_t)>& get,
                  std::size_t rowValue,
                  std::size_t rowError)
{
    if (unitName == "meters" || unitName == "m") {
        fillAndAddRow<au::Meters, 12>(m, rowName, get, au::meters, rowValue, rowError);
    }
    else if (unitName == "seconds" || unitName == "s") {
        fillAndAddRow<au::Seconds, 12>(m, rowName, get, au::seconds, rowValue, rowError);
    }
    else if (unitName == "kelvins" || unitName == "K") {
        fillAndAddRow<au::Kelvins, 12>(m, rowName, get, au::kelvins, rowValue, rowError);
    }
    else {
        throw std::runtime_error("Unknown unit in Excel: '" + unitName + "'");
    }
}

Matrix ExcelEnter() {
    try {
        OpenXLSX::XLDocument doc;
        std::string path;
        std::cout << "Enter path to .xlsx: ";
        std::getline(std::cin, path);
        doc.open(path);

        auto wks = doc.workbook().worksheet("Sheet1");

        auto get = [&](std::size_t r, std::size_t c) -> double {
            return wks.cell(r, c).value().get<double>();
        };
        auto getName = [&](std::size_t r, std::size_t c) -> std::string {
            return wks.cell(r, c).value().get<std::string>();
        };

        Matrix m;

        //  Единицы читаются из Excel
        std::string unit1Name = getName(1, 2);
        std::string unit2Name = getName(1, 4);

        std::cout << "row1 unit: " << unit1Name << "\n";
        std::cout << "row2 unit: " << unit2Name << "\n";

        addRowByUnit(m, unit1Name, getName(1, 1), get, 1, 2);
        addRowByUnit(m, unit2Name, getName(1, 3), get, 3, 4);

        return m;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        throw;
    }
}