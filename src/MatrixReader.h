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
    static void readFileHeader(std::ifstream &matrix_file,
                               std::vector<double> &values, 
                               std::vector<size_t> &columns, 
                               std::vector<size_t> &row_indices);
    static void readMatrixData(std::ifstream &matrix_file,
                               std::vector<double> &values, 
                               std::vector<size_t> &columns, 
                               std::vector<size_t> &row_indices);
};