#pragma once

#include <filesystem>
#include <vector>

class MatrixCSR3 {
    size_t row_number_;
    size_t column_number_;
    size_t non_zero_elements_number_;
    std::vector<double> values_;
    std::vector<size_t> columns_;
    std::vector<size_t> row_indices_;

public:
    MatrixCSR3() = default;
    MatrixCSR3(std::vector<double> values, std::vector<size_t> columns, std::vector<size_t> row_indices_);

    MatrixCSR3 operator+(const MatrixCSR3 &other) const;
    MatrixCSR3 operator-(const MatrixCSR3 &other) const;    
    MatrixCSR3 operator-();

    double operator[](std::tuple<size_t, size_t> ind) const;
    bool operator==(const MatrixCSR3& other) const;
    MatrixCSR3 slice(size_t row_start, size_t row_end,
			        size_t column_start, size_t colum_end) const;

    std::vector<double> getValues() const;
    std::vector<size_t> getColumns() const;
    std::vector<size_t> getRowIndices() const;

private:
    void getIntermediateColumnsAndRowIndices(const MatrixCSR3 &other, std::vector<size_t> &temp_row_index,
                                std::vector<size_t> &temp_columns) const;
    void getIntermediateValues(const MatrixCSR3 &other, std::vector<double> &temp_values1, std::vector<double> &temp_values2, 
                                std::vector<size_t> &temp_columns, std::vector<size_t> &temp_row_index) const;
    void getResultFromIntermediateData(MatrixCSR3 &result, std::vector<double> &temp_values1, std::vector<double> &temp_values2,
                                std::vector<size_t> &temp_columns, std::vector<size_t> &temp_row_index) const;
    bool containsElementInPosition(size_t ind_i, size_t column, const MatrixCSR3 &matrix) const;
};

MatrixCSR3 operator*(const MatrixCSR3& matrix, double scalar);
MatrixCSR3 operator*(double scalar, const MatrixCSR3& matrix);