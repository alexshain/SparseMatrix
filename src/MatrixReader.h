#pragma once

#include <filesystem>

#include "MatrixDataByIndex.h"
#include "MatrixCSR3.h"

class MatrixReader {
    public:
    static MatrixCSR3 read(std::filesystem::path file_path);

    private:
    static void setCSR3FormatData(MatrixCSR3 &matrix, std::ifstream &matrix_file);
};