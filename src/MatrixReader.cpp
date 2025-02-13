#include <fstream>

#include "MatrixReader.h"

MatrixCSR3 MatrixReader::read(std::filesystem::path file_path) {
    //обработать неправильный формат данных в файле 
    std::ifstream matrix_file(file_path);
    static std::vector<double> values;
    static std::vector<size_t> columns;
    static std::vector<size_t> row_indices;
    readFileHeader(matrix_file, values, columns, row_indices);
    readMatrixData(matrix_file, values, columns, row_indices);
    return MatrixCSR3(values, columns, row_indices);
}

void MatrixReader::readFileHeader(std::ifstream &matrix_file,
                                  std::vector<double> &values, 
                                  std::vector<size_t> &columns, 
                                  std::vector<size_t> &row_indices) {
    size_t row_number;
    size_t column_number;
    size_t non_zero_elements_number;
    matrix_file >> row_number 
                >> column_number 
                >> non_zero_elements_number;
    values.resize(non_zero_elements_number);
    columns.resize(non_zero_elements_number);
    row_indices.resize(row_number + 1);
}

void MatrixReader::readMatrixData(std::ifstream &matrix_file,
                                  std::vector<double> &values, 
                                  std::vector<size_t> &columns, 
                                  std::vector<size_t> &row_indices) {
    size_t ind = 0;
    size_t sum_of_non_zero_values = 0;
    size_t row_index_value = 1;
    row_indices[0] = 0;
    for(size_t i = 0; i < values.size(); i++) {
        MatrixElement element;
        matrix_file >> element.row_ind 
                    >> element.column_ind
                    >> element.value;
        values[i] = element.value;
        columns[i] = element.column_ind;
        
        while (ind < element.row_ind) {
            row_indices[row_index_value] = sum_of_non_zero_values;
            ind++;
            row_index_value++;
        }
        sum_of_non_zero_values++;

    }
    while (row_index_value < row_indices.size()) {
        row_indices[row_index_value] = sum_of_non_zero_values;
        row_index_value++;
    }
}