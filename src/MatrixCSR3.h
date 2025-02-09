#pragma once

#include <filesystem>
#include <vector>

class MatrixCSR3 {
    size_t row_number_;
    size_t column_number_;
    size_t non_zero_elements_number_;
    std::vector<double> values_;
    std::vector<size_t> columns_;
    std::vector<size_t> row_index_;

    struct sliceParameters
    {
        size_t row_start;
        size_t row_end; 
        size_t column_start; 
        size_t colum_end;
    };

public:
    MatrixCSR3() = default;
    //убрать этот конструктор 
    MatrixCSR3(size_t row_number, size_t column_number, size_t non_zero_elements_number);
    MatrixCSR3(std::vector<double> values, std::vector<size_t> columns, std::vector<size_t> row_index, size_t column_number);

    MatrixCSR3 operator+(const MatrixCSR3 &other) const;
    MatrixCSR3 operator-(const MatrixCSR3 &other) const;    
    MatrixCSR3 operator-();
    MatrixCSR3 operator*(double scalar) const;
    double operator[](std::tuple<size_t, size_t> ind) const;
    MatrixCSR3 slice(size_t row_start, size_t row_end,
			        size_t column_start, size_t colum_end);

    std::vector<double> getValues() const;
    std::vector<size_t> getColumns() const;
    std::vector<size_t> getRowIndices() const;

    void setValue(double value, size_t non_zero_element_ind);
    void setColumn(size_t column_ind, size_t non_zero_element_ind);
    void setRowIndex(size_t row_index_value, size_t non_zero_element_ind);

private:
    void getIntermediateColumnsAndRowIndexes(const MatrixCSR3 &other, std::vector<size_t> &temp_row_index,
                                std::vector<size_t> &temp_columns) const;
    void getIntermediateValues(const MatrixCSR3 &other, std::vector<double> &temp_values1, std::vector<double> &temp_values2, 
                                std::vector<size_t> &temp_columns, std::vector<size_t> &temp_row_index) const;
    void getResultFromIntermediateData(MatrixCSR3 &result, std::vector<double> &temp_values1, std::vector<double> &temp_values2,
                                std::vector<size_t> &temp_columns, std::vector<size_t> &temp_row_index) const;
    bool containsElementInPosition(size_t ind_i, size_t column, const MatrixCSR3 &matrix) const;
    void setSliceValues(std::vector<double> &new_values, sliceParameters slice_params);
    void setSliceColumns(std::vector<size_t> &new_columns, sliceParameters slice_params);
    void setSliceValuesAndColumns(std::vector<size_t> &new_columns, std::vector<double> &new_values, sliceParameters slice_params);
    void setSliceRowIndex(std::vector<size_t> &new_row_indices, sliceParameters slice_params);
};