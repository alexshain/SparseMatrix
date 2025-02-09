#include "MatrixCSR3.h"

#include <iostream>
#include <fstream>
#include <algorithm>

MatrixCSR3::MatrixCSR3(size_t row_number, size_t column_number, size_t non_zero_elements_number) : 
    row_number_(row_number),
    column_number_(column_number),
    non_zero_elements_number_(non_zero_elements_number),
    values_(non_zero_elements_number),
    columns_(non_zero_elements_number),
    row_index_(row_number + 1) {}

MatrixCSR3::MatrixCSR3(std::vector<double> values, std::vector<size_t> columns, std::vector<size_t> row_index, size_t column_number) : 
    values_(values),
    columns_(columns),
    row_index_(row_index),
    row_number_(row_index.size() - 1),
    column_number_(column_number),
    non_zero_elements_number_(values.size()) {}

MatrixCSR3 MatrixCSR3::operator*(double scalar) const {
    MatrixCSR3 result{row_number_, column_number_, non_zero_elements_number_};
    result.columns_ = columns_;
    result.row_index_ = row_index_;
    for(size_t i = 0; i < values_.size(); i++) {
        result.values_[i] = values_[i] * scalar;
    }
    return result;
}

MatrixCSR3 MatrixCSR3::operator+(const MatrixCSR3 &other) const {
    if(other.column_number_ != column_number_ && other.row_number_ != row_number_) {
        throw "The matrices have different sizes!";
    }
    MatrixCSR3 result{row_number_, column_number_, non_zero_elements_number_};
    result = *this - other*(-1);
    return result;
}

MatrixCSR3 MatrixCSR3::operator-() {
    return *this * (-1);
}

MatrixCSR3 MatrixCSR3::operator-(const MatrixCSR3 &other) const {
    if(other.column_number_ != column_number_ && other.row_number_ != row_number_) {
        throw "The matrices have different sizes!";
    }
    std::vector<size_t> temp_columns;
    std::vector<size_t> temp_row_index;
    std::vector<double> temp_left_values;
    std::vector<double> temp_right_values; 
    MatrixCSR3 result{};
    getIntermediateColumnsAndRowIndexes(other, temp_row_index, temp_columns);
    getIntermediateValues(other, temp_left_values, temp_right_values, temp_columns, temp_row_index);
    getResultFromIntermediateData(result, temp_left_values, temp_right_values, temp_columns, temp_row_index);
    return result;
}

void MatrixCSR3::getIntermediateColumnsAndRowIndexes(const MatrixCSR3 &other, std::vector<size_t> &temp_row_index,std::vector<size_t> &temp_columns) const {
    size_t row_index_element = 0;
    temp_row_index.push_back(row_index_element);
    for(size_t i = 1; i < row_index_.size(); i++) {
        size_t current_row_start = row_index_[i-1];
        size_t current_row_end = row_index_[i];
        for(size_t j = current_row_start; j < current_row_end; j++) {
            row_index_element++;
            temp_columns.push_back(columns_[j]);
        }

        size_t other_row_start = other.row_index_[i-1];
        size_t other_row_end = other.row_index_[i];
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

void MatrixCSR3::getIntermediateValues(const MatrixCSR3 &other, std::vector<double> &temp_left_values, std::vector<double> &temp_right_values, 
                                std::vector<size_t> &temp_columns, std::vector<size_t> &temp_row_index) const {
    size_t vector_size = temp_columns.size();
    temp_left_values.resize(vector_size);
    temp_right_values.resize(vector_size); 
    std::vector<double>::const_iterator current_iter = values_.begin();
    std::vector<double>::const_iterator other_iter = other.values_.begin();
    for(size_t i = 1; i < row_index_.size(); i++) {
        size_t start = temp_row_index[i-1];
        size_t end = temp_row_index[i];
        for(size_t j = start; j < end; j++) {
            if(containsElementInPosition(i, temp_columns[j], *this)) {
                temp_left_values[j] = *(current_iter++);
            } else {
                temp_left_values[j] = 0;
            }
            if(containsElementInPosition(i, temp_columns[j], other)) {
                temp_right_values[j] = (*other_iter++);
            } else {
                temp_right_values[j] = 0;
            }
        }
    }
}

bool MatrixCSR3::containsElementInPosition(size_t ind_i, size_t column, const MatrixCSR3 &matrix) const {
    auto first_column_in_row = matrix.columns_.begin() + matrix.row_index_[ind_i-1];
    auto lust_column_in_row = matrix.columns_.begin() + matrix.row_index_[ind_i];
    return std::find(first_column_in_row, lust_column_in_row, column) != lust_column_in_row;
}

void MatrixCSR3::getResultFromIntermediateData(MatrixCSR3 &result, std::vector<double> &temp_values1, 
                                std::vector<double> &temp_values2, std::vector<size_t> &temp_columns, std::vector<size_t> &temp_row_index) const {
    size_t row_index_element = 0;
    result.row_index_.push_back(row_index_element);
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
        result.row_index_.push_back(row_index_element);
    }
    result.row_number_ = row_number_;
    result.column_number_ = column_number_;
    result.non_zero_elements_number_ = result.values_.size();
}

double MatrixCSR3::operator[](std::tuple<size_t, size_t> ind) const {
    if(std::get<0>(ind) > row_number_ - 1 || std::get<1>(ind) > column_number_ - 1) {
        throw "You have gone beyond the matrix!";
    }
    size_t start = row_index_[std::get<0>(ind)];
    size_t end = row_index_[std::get<0>(ind) + 1];
    for(size_t i = start; i < end; i++) {
        auto it = std::find(columns_.begin() + start, columns_.begin() + end, std::get<1>(ind));
        if(it != columns_.begin() + end) {
            return values_[*it + start];
        } else return 0;
    }
}

MatrixCSR3 MatrixCSR3::slice(size_t row_start, size_t row_end, size_t column_start, size_t colum_end) {
    sliceParameters slice_params;
    slice_params.row_start = row_start;
    slice_params.row_end = row_end; 
    slice_params.column_start = column_start; 
    slice_params.colum_end = colum_end;

    std::vector<double> new_values((row_end - row_start)*(colum_end - column_start));
    std::vector<size_t> new_columns((row_end - row_start)*(colum_end - column_start));
    std::vector<size_t> new_row_index(row_end - row_start + 1);


    //setSliceValuesAndColumns();
    setSliceValues(new_values, slice_params);
    setSliceColumns(new_columns, slice_params);
    setSliceRowIndex(new_row_index, slice_params);

    return MatrixCSR3{new_values, new_columns, new_row_index, colum_end - column_start};
}

void MatrixCSR3::setSliceValuesAndColumns(std::vector<size_t> &new_columns, std::vector<double> &new_values, sliceParameters slice_params) {
    size_t new_ind = 0;
    size_t start_ind = row_index_[slice_params.row_start];
    size_t end_ind = row_index_[slice_params.row_end];
    for(size_t i = start_ind; i < end_ind; i++) {
        if(columns_[i] >= slice_params.column_start && columns_[i] < slice_params.colum_end) {
            new_values[new_ind] = values_[i];
            new_columns[new_ind] = columns_[i] - slice_params.column_start;
            new_ind++;
        }
    }
}

void MatrixCSR3::setSliceValues(std::vector<double> &new_values, sliceParameters slice_params) {
    size_t new_value_ind = 0;
    size_t start_ind = row_index_[slice_params.row_start];
    size_t end_ind = row_index_[slice_params.row_end];
    for(size_t i = start_ind; i < end_ind; i++) {
        if(columns_[i] >= slice_params.column_start && columns_[i] < slice_params.colum_end) {
            new_values[new_value_ind] = values_[i];
            new_value_ind++;
        }
    }
}

//убрать бы дублирование
void MatrixCSR3::setSliceColumns(std::vector<size_t> &new_columns, sliceParameters slice_params) {
    size_t new_columns_ind = 0;
    size_t start_ind = row_index_[slice_params.row_start];
    size_t end_ind = row_index_[slice_params.row_end];
    for(size_t i = start_ind; i < end_ind; i++) {
        if(columns_[i] >= slice_params.column_start && columns_[i] < slice_params.colum_end) {
            new_columns[new_columns_ind] = columns_[i] - slice_params.column_start;
            new_columns_ind++;
        }
    }
}

void MatrixCSR3::setSliceRowIndex(std::vector<size_t> &new_row_indices, sliceParameters slice_params) {
    size_t counter = 0;
    for(size_t i = slice_params.row_start; i <= slice_params.row_end; i++) {
        new_row_indices[i - slice_params.row_start] = counter;
        for(size_t j = row_index_[i]; j < row_index_[i+1]; j++) {
            if(columns_[j] >= slice_params.column_start && columns_[j] < slice_params.colum_end) {
                counter++;
            } 
        }
    }
}

std::vector<double> MatrixCSR3::getValues() const {
    return values_;
}

std::vector<size_t> MatrixCSR3::getColumns() const {
    return columns_;
}

std::vector<size_t> MatrixCSR3::getRowIndices() const {
    return row_index_;
}

//поработать над инкапсуляцией 
void MatrixCSR3::setValue(double value, size_t non_zero_element_ind) {
    values_[non_zero_element_ind] = value;
}

void MatrixCSR3::setColumn(size_t column_ind, size_t non_zero_element_ind) {
    columns_[non_zero_element_ind] = column_ind;
}

void MatrixCSR3::setRowIndex(size_t row_index_value, size_t arr_ind) {
    row_index_[arr_ind] = row_index_value;
}