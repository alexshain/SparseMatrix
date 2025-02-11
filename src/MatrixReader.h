#pragma once

#include <filesystem>

#include "MatrixCSR3.h"

class MatrixReader {
    struct MatrixElement {
        double value;
        size_t row_ind;
        size_t column_ind;
    };
public:
    static MatrixCSR3 read(std::filesystem::path file_path);

private:
    static void setCSR3FormatData(MatrixCSR3 &matrix, std::ifstream &matrix_file);
};