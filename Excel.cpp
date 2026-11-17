#include <OpenXLSX.hpp>
#include "au_all_units.hh"
#include "Matrix.h"
#include <iostream>
#include <string>
#include "PhysValue.h"

// Matrix больше не шаблонный
Matrix ExcelEnter() {
    try {
        OpenXLSX::XLDocument doc;
        std::string path;
        std::cout << "Enter path to .xlsx: ";
        std::getline(std::cin, path);
        doc.open(path);

        constexpr std::size_t num = 12;
        auto wks = doc.workbook().worksheet("Sheet1");

        auto get = [&](std::size_t r, std::size_t c) -> double {
            return wks.cell(r, c).value().get<double>();
        };
        auto getName = [&](std::size_t r, std::size_t c) -> std::string {
            return wks.cell(r, c).value().get<std::string>();
        };

        // row1 в метрах
        Row<au::Meters, num> row1(getName(1, 1));
        // row2 в секундах
        Row<au::Seconds, num> row2(getName(1, 3));

        for (std::size_t i = 0; i < row1.size(); ++i) {
            row1[i].value = au::meters(get(1, 2 + i));
            row1[i].error = au::meters(get(2, 2 + i));
        }
        for (std::size_t i = 0; i < row2.size(); ++i) {
            row2[i].value = au::seconds(get(3, 2 + i));
            row2[i].error = au::seconds(get(4, 2 + i));
        }

        Matrix m;
        m.add(row1);
        m.add(row2);
        return m;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        throw;
    }
}
