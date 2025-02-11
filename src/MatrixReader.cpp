#include <fstream>

#include "MatrixReader.h"

MatrixCSR3 MatrixReader::read(std::filesystem::path file_path) {
    //обработать неправильный формат данных в файле 
    std::ifstream matrix_file(file_path);
    size_t row_number;
    size_t column_number;
    size_t non_zero_elements_number;
    matrix_file >> row_number 
                >> column_number 
                >> non_zero_elements_number;
    std::vector<double> values(non_zero_elements_number);
    std::vector<size_t> columns(non_zero_elements_number);
    std::vector<size_t> row_index(row_number + 1);
    MatrixCSR3 matrix = MatrixCSR3(values, columns, row_index);
    setCSR3FormatData(matrix, matrix_file);
    return matrix;
}

//divide
void MatrixReader::setCSR3FormatData(MatrixCSR3 &matrix, std::ifstream &matrix_file) {
    size_t ind = 0;
    size_t counter = 0;
    size_t row_index_value = 1;
    matrix.setRowIndex(counter, 0);
    for(size_t i = 0; i < matrix.getValues().size(); i++) {
        MatrixElement index_data;
        matrix_file >> index_data.row_ind 
                    >> index_data.column_ind
                    >> index_data.value;
        matrix.setValue(index_data.value, i);
        matrix.setColumn(index_data.column_ind, i);
        
        if(ind < index_data.row_ind) {
            while (ind < index_data.row_ind) {
                matrix.setRowIndex(counter, row_index_value);
                ind++;
                row_index_value++;
            }
            counter++;
        } else if(index_data.row_ind == ind) {
            counter++;
        } 
    }
    while (row_index_value < matrix.getRowIndices().size()) {
        matrix.setRowIndex(counter, row_index_value);
        row_index_value++;
    }
}
