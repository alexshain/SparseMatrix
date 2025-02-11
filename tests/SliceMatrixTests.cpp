#include <gtest/gtest.h>
#include <vector>

#include "../src/MatrixCSR3.h"

TEST(SliceMatrix, emptySlice) {
    std::vector<double> values{1, 2, 3, 4, 5};
    std::vector<size_t> columns{1, 0, 2, 1, 2};
    std::vector<size_t> row_indices{0, 1, 3, 5};
    MatrixCSR3 matrix{values, columns, row_indices};

    MatrixCSR3 result = matrix.slice(0, 0, 0, 0);

    std::vector<double> assert_values(0);
    std::vector<size_t> assert_columns(0);
    std::vector<size_t> assert_row_indices{0};
    
    EXPECT_EQ(result.getValues(), assert_values);
    EXPECT_EQ(result.getColumns(), assert_columns);
    EXPECT_EQ(result.getRowIndices(), assert_row_indices);

    result = matrix.slice(1, 1, 1, 1);
    EXPECT_EQ(result.getValues(), assert_values);
    EXPECT_EQ(result.getColumns(), assert_columns);
    EXPECT_EQ(result.getRowIndices(), assert_row_indices);
}

TEST(SliceMatrix, correctSlice) {
    std::vector<double> values{1, 2, 3, 4, 5};
    std::vector<size_t> columns{1, 0, 2, 1, 2};
    std::vector<size_t> row_indices{0, 1, 3, 5};
    MatrixCSR3 matrix{values, columns, row_indices};

    MatrixCSR3 result = matrix.slice(1, 3, 0, 2);

    std::vector<double> assert_values{2, 4};
    std::vector<size_t> assert_columns{0, 1};
    std::vector<size_t> assert_row_indices{0, 1, 2};
    
    EXPECT_EQ(result.getValues(), assert_values);
    EXPECT_EQ(result.getColumns(), assert_columns);
    EXPECT_EQ(result.getRowIndices(), assert_row_indices);
}

TEST(SliceMatrix, sliceWithMatrixOverflow) {
    std::vector<double> values{1, 2, 3, 4, 5};
    std::vector<size_t> columns{1, 0, 2, 1, 2};
    std::vector<size_t> row_indices{0, 1, 3, 5};
    MatrixCSR3 matrix{values, columns, row_indices};

    EXPECT_THROW(matrix.slice(1, 4, 0, 4), std::runtime_error);
    EXPECT_THROW(matrix.slice(-1, 3, 0, 2), std::runtime_error);
}

TEST(SliceMatrix, sliceWithStartParametersExceedEndParameters) {
    std::vector<double> values{1, 2, 3, 4, 5};
    std::vector<size_t> columns{1, 0, 2, 1, 2};
    std::vector<size_t> row_indices{0, 1, 3, 5};
    MatrixCSR3 matrix{values, columns, row_indices};

    EXPECT_THROW(matrix.slice(2, 1, 0, 2), std::runtime_error);
}