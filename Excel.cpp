#include <OpenXLSX.hpp>
#include "au_all_units.hh"
#include "Matrix.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <functional>

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
        row[i].value = unit(get(2 + i, rowValue));
        row[i].error = unit(get(2 + i, rowError));
    }
    m.add(row);
}
template <std::size_t N>
void addRowByUnit(Matrix& m,
                  const std::string& unitName,
                  const std::string& rowName,
                  const std::function<double(std::size_t, std::size_t)>& get,
                  std::size_t rowValue,
                  std::size_t rowError)
{
    if (unitName == "meters" || unitName == "m") {
        fillAndAddRow<au::Meters, N>(m, rowName, get, au::meters, rowValue, rowError);
    }
    else if (unitName == "seconds" || unitName == "s") {
        fillAndAddRow<au::Seconds, N>(m, rowName, get, au::seconds, rowValue, rowError);
    }
    else if (unitName == "kelvins" || unitName == "K") {
        fillAndAddRow<au::Kelvins, N>(m, rowName, get, au::kelvins, rowValue, rowError);
    }
    else {
        throw std::runtime_error("Unknown unit in Excel: '" + unitName + "'");
    }
}

template <std::size_t N>
Matrix ExcelEnterI(const std::string& path) {
    try {
        OpenXLSX::XLDocument doc;
        doc.open(path);

        auto wks = doc.workbook().worksheet(1);

        auto get = [&](std::size_t r, std::size_t c) -> double {
            return wks.cell(r, c).value().get<double>();
        };
        auto getName = [&](std::size_t r, std::size_t c) -> std::string {
            return wks.cell(r, c).value().get<std::string>();
        };

        Matrix m;

        std::string unit1Name = getName(1, 2);
        std::string unit2Name = getName(1, 4);

        std::cout << "row1 unit: " << unit1Name << "\n";
        std::cout << "row2 unit: " << unit2Name << "\n";

        addRowByUnit<N>(m, unit1Name, getName(1, 1), get, 1, 2);
        addRowByUnit<N>(m, unit2Name, getName(1, 3), get, 3, 4);

        return m;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        throw;
    }
}
Matrix ExcelEnter(const std::string& path, std::size_t count) {
    switch (count)
    {
        case 1:  return ExcelEnterI<1>(path);
        case 2:  return ExcelEnterI<2>(path);
        case 3:  return ExcelEnterI<3>(path);
        case 4:  return ExcelEnterI<4>(path);
        case 5:  return ExcelEnterI<5>(path);
        case 6:  return ExcelEnterI<6>(path);
        case 7:  return ExcelEnterI<7>(path);
        case 8:  return ExcelEnterI<8>(path);
        case 9:  return ExcelEnterI<9>(path);
        case 10: return ExcelEnterI<10>(path);
        case 11:  return ExcelEnterI<11>(path);
        case 12:  return ExcelEnterI<12>(path);
        case 13:  return ExcelEnterI<13>(path);
        case 14:  return ExcelEnterI<14>(path);
        case 15:  return ExcelEnterI<15>(path);
        case 16:  return ExcelEnterI<16>(path);
        case 17:  return ExcelEnterI<17>(path);
        case 18:  return ExcelEnterI<18>(path);
        case 19:  return ExcelEnterI<19>(path);
        case 20:  return ExcelEnterI<20>(path);
        case 21:  return ExcelEnterI<21>(path);
        case 22:  return ExcelEnterI<22>(path);
        case 23:  return ExcelEnterI<23>(path);
        case 24:  return ExcelEnterI<24>(path);
        case 25:  return ExcelEnterI<25>(path);
        case 26:  return ExcelEnterI<26>(path);
        case 27:  return ExcelEnterI<27>(path);
        case 28:  return ExcelEnterI<28>(path);
        case 29:  return ExcelEnterI<29>(path);
        case 30: return ExcelEnterI<30>(path);
        case 31:  return ExcelEnterI<31>(path);
        case 32:  return ExcelEnterI<32>(path);
        case 33:  return ExcelEnterI<33>(path);
        case 34:  return ExcelEnterI<34>(path);
        case 35:  return ExcelEnterI<35>(path);
        case 36:  return ExcelEnterI<36>(path);
        case 37:  return ExcelEnterI<37>(path);
        case 38:  return ExcelEnterI<38>(path);
        case 39:  return ExcelEnterI<39>(path);
        case 40: return ExcelEnterI<40>(path);
        case 41:  return ExcelEnterI<41>(path);
        case 42:  return ExcelEnterI<42>(path);
        case 43:  return ExcelEnterI<43>(path);
        case 44:  return ExcelEnterI<44>(path);
        case 45:  return ExcelEnterI<45>(path);
        case 46:  return ExcelEnterI<46>(path);
        case 47:  return ExcelEnterI<47>(path);
        case 48:  return ExcelEnterI<48>(path);
        case 49:  return ExcelEnterI<49>(path);
        case 50: return ExcelEnterI<50>(path);

        default: throw std::runtime_error("Unsupported count: " + std::to_string(count));
    }
}