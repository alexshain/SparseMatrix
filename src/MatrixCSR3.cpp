#include "MatrixCSR3.h"

#include <iostream>
#include <fstream>
#include <algorithm>

MatrixCSR3::MatrixCSR3(std::vector<double> values, std::vector<size_t> columns, std::vector<size_t> row_indices) : 
    values_(values),
    columns_(columns),
    row_indices_(row_indices),
    row_number_(row_indices.size() - 1),
    column_number_(columns.size()),
    non_zero_elements_number_(values.size()) {}

MatrixCSR3 MatrixCSR3::operator+(const MatrixCSR3 &other) const {
    if(other.column_number_ != column_number_ && other.row_number_ != row_number_) {
        throw "The matrices have different sizes!";
    }
    MatrixCSR3 result = *this - other*(-1);
    return result;
}

MatrixCSR3 MatrixCSR3::operator-() {
    return *this * (-1);
}

MatrixCSR3 operator*(const MatrixCSR3& matrix, double scalar) {
    std::vector<double> result_values(matrix.getValues().size());
    for(size_t i = 0; i < result_values.size(); i++) {
        result_values[i] = matrix.getValues()[i] * scalar;
    }
    MatrixCSR3 result{result_values, matrix.getColumns(), matrix.getRowIndices()};
    return result;
}

MatrixCSR3 operator*(double scalar, const MatrixCSR3& matrix) {
    return matrix * scalar;
}

MatrixCSR3 MatrixCSR3::operator-(const MatrixCSR3 &other) const {
    if(other.column_number_ != column_number_ && other.row_number_ != row_number_) {
        throw std::runtime_error("The matrices have different sizes!");
    }
    std::vector<size_t> temp_columns;
    std::vector<size_t> temp_row_index;
    std::vector<double> temp_left_values;
    std::vector<double> temp_right_values; 
    getTempColumnsAndRowIndices(other, temp_row_index, temp_columns);
    getTempValues(other, temp_left_values, temp_right_values, temp_columns, temp_row_index);

    return getResultFromTempData(temp_left_values, temp_right_values, temp_columns, temp_row_index);
}

void MatrixCSR3::getTempColumnsAndRowIndices(const MatrixCSR3 &other, std::vector<size_t> &temp_row_index, std::vector<size_t> &temp_columns) const {
    size_t row_index_element = 0;
    temp_row_index.push_back(row_index_element);
    for(size_t i = 1; i < row_indices_.size(); i++) {
        size_t current_row_start = row_indices_[i-1];
        size_t current_row_end = row_indices_[i];
        for(size_t j = current_row_start; j < current_row_end; j++) {
            row_index_element++;
            temp_columns.push_back(columns_[j]);
        }

        size_t other_row_start = other.row_indices_[i-1];
        size_t other_row_end = other.row_indices_[i];
        for(size_t j = other_row_start; j < other_row_end; j++) {
            auto curr_row_first_column = temp_columns.begin() + current_row_start;
            auto curr_row_lust_column = temp_columns.begin() + current_row_end;
            size_t other_column = other.columns_[j];
            bool not_contains_element_in_position = std::find(curr_row_first_column, curr_row_lust_column, other_column) == curr_row_lust_column;
            if(not_contains_element_in_position) {
                row_index_element++;
                temp_columns.push_back(other_column);
            }
        }
        temp_row_index.push_back(row_index_element);
        std::sort(temp_columns.begin() + temp_row_index[i-1], temp_columns.begin() + temp_row_index[i]);
    }
}

void MatrixCSR3::getTempValues(const MatrixCSR3 &other, std::vector<double> &temp_left_values, std::vector<double> &temp_right_values, 
                                std::vector<size_t> &temp_columns, std::vector<size_t> &temp_row_index) const {
    size_t vector_size = temp_columns.size();
    temp_left_values.resize(vector_size);
    temp_right_values.resize(vector_size); 
    std::vector<double>::const_iterator current_iter = values_.begin();
    std::vector<double>::const_iterator other_iter = other.values_.begin();
    for(size_t i = 1; i < row_indices_.size(); i++) {
        size_t start = temp_row_index[i-1];
        size_t end = temp_row_index[i];
        for(size_t j = start; j < end; j++) {
            size_t column = temp_columns[j];
            if(containsElementInPosition(i, column, *this)) {
                temp_left_values[j] = *(current_iter++);
            } else {
                temp_left_values[j] = 0;
            }
            if(containsElementInPosition(i, column, other)) {
                temp_right_values[j] = (*other_iter++);
            } else {
                temp_right_values[j] = 0;
            }
        }
    }
}

bool MatrixCSR3::containsElementInPosition(size_t ind_i, size_t column, const MatrixCSR3 &matrix) const {
    auto first_column_in_row = matrix.columns_.begin() + matrix.row_indices_[ind_i-1];
    auto lust_column_in_row = matrix.columns_.begin() + matrix.row_indices_[ind_i];
    return std::find(first_column_in_row, lust_column_in_row, column) != lust_column_in_row;
}

MatrixCSR3 MatrixCSR3::getResultFromTempData(std::vector<double> &temp_values1, 
                                std::vector<double> &temp_values2, std::vector<size_t> &temp_columns, std::vector<size_t> &temp_row_index) const {
    MatrixCSR3 result;
    size_t row_index_element = 0;
    result.row_indices_.push_back(row_index_element);
    for(size_t i = 1; i < temp_row_index.size(); i++) {
        size_t start = temp_row_index[i-1];
        size_t end = temp_row_index[i];
        for(size_t j = start; j < end; j++) {
            double val_result = temp_values1[j] - temp_values2[j];
            if(abs(val_result) > 1e-10) {
                result.values_.push_back(val_result);
                result.columns_.push_back(temp_columns[j]);
                row_index_element++;
            }
        }
        result.row_indices_.push_back(row_index_element);
    }
    result.row_number_ = row_number_;
    result.column_number_ = column_number_;
    result.non_zero_elements_number_ = result.values_.size();
    return result;
}

double MatrixCSR3::operator[](std::tuple<size_t, size_t> ind) const {
    if(std::get<0>(ind) > row_number_ - 1 || std::get<1>(ind) > column_number_ - 1) {
        throw std::runtime_error("You have gone beyond the matrix!");
    }
    size_t start = row_indices_[std::get<0>(ind)];
    size_t end = row_indices_[std::get<0>(ind) + 1];
    for(size_t i = start; i < end; i++) {
        auto it = std::find(columns_.begin() + start, columns_.begin() + end, std::get<1>(ind));
        size_t index = std::distance(columns_.begin(), it);
        if(it != columns_.begin() + end) {
            return values_[index];
        } else return 0;
    }
}

bool MatrixCSR3::operator==(const MatrixCSR3& other) const {
    if(values_ == other.values_ && columns_ == other.columns_ && row_indices_ == other.row_indices_) {
        return true;
    } else return false;
}

MatrixCSR3 MatrixCSR3::slice(size_t row_start, size_t row_end, size_t column_start, size_t column_end) const {
    if(row_start < 0 || column_start < 0 || row_end < 0 || column_end < 0) {
        throw std::runtime_error("The value of the parameters cannot be negative!");
    }
    if(row_end > row_number_ || column_end > column_number_) {
        throw std::runtime_error("row_end or colum_end exceeds matrix size!");
    }
    if(row_start > row_end || column_start > column_end) {
        throw std::runtime_error("Start parameters should not exceed end parameters!");
    }

    std::vector<double> new_values{};
    std::vector<size_t> new_columns{};
    std::vector<size_t> new_row_indices{};

    size_t start_ind = row_indices_[row_start];
    size_t end_ind = row_indices_[row_end];
    for(size_t i = start_ind; i < end_ind; i++) {
        if(columns_[i] >= column_start && columns_[i] < column_end) {
            new_values.push_back(values_[i]);
            new_columns.push_back(columns_[i] - column_start);
        }
    }

    size_t counter = 0;
    for(size_t i = row_start; i <= row_end; i++) {
        new_row_indices.push_back(counter);
        for(size_t j = row_indices_[i]; j < row_indices_[i+1]; j++) {
            if(columns_[j] >= column_start && columns_[j] < column_end) {
                counter++;
            } 
        }
    }

    return MatrixCSR3{new_values, new_columns, new_row_indices};
}

std::vector<double> MatrixCSR3::getValues() const {
    return values_;
}

std::vector<size_t> MatrixCSR3::getColumns() const {
    return columns_;
}

std::vector<size_t> MatrixCSR3::getRowIndices() const {
    return row_indices_;
}