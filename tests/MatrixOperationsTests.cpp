#include <gtest/gtest.h>
#include <vector>

#include "../src/MatrixCSR3.h"

TEST(MatrixOperations, unarMinus) {
    std::vector<double> values{1, 4};
    std::vector<size_t> columns{0, 1};
    std::vector<size_t> row_indices{0, 1, 2};
    MatrixCSR3 matrix{values, columns, row_indices};

    matrix = -matrix;

    std::vector<double> assert_values{-1, -4};
    std::vector<size_t> assert_columns{0, 1};
    std::vector<size_t> assert_row_indices{0, 1, 2};
    MatrixCSR3 assert_matrix{assert_values, assert_columns, assert_row_indices};

    EXPECT_EQ(matrix, assert_matrix);
}


TEST(MatrixOperations, binarMinus) {
    std::vector<double> values1{1, 4};
    std::vector<size_t> columns1{0, 1};
    std::vector<size_t> row_indices1{0, 1, 2};
    MatrixCSR3 matrix1{values1, columns1, row_indices1};

    std::vector<double> values2{2, 0.5, 4};
    std::vector<size_t> columns2{0, 1, 1};
    std::vector<size_t> row_indices2{0, 2, 3};
    MatrixCSR3 matrix2{values2, columns2, row_indices2};

    MatrixCSR3 result_matrix = matrix1 - matrix2;

    std::vector<double> assert_values{-1, -0.5};
    std::vector<size_t> assert_columns{0, 1};
    std::vector<size_t> assert_row_indices{0, 2, 2};
    MatrixCSR3 assert_matrix{assert_values, assert_columns, assert_row_indices};

    EXPECT_EQ(result_matrix, assert_matrix);
}

TEST(MatrixOperations, multipleOnDoubleScalar) {
    std::vector<double> values{1, 4};
    std::vector<size_t> columns{0, 1};
    std::vector<size_t> row_indices{0, 1, 2};
    MatrixCSR3 matrix{values, columns, row_indices};

    double scalar = 2.5;
    MatrixCSR3 result_matrix = matrix * scalar;

    std::vector<double> assert_values{2.5, 10};
    std::vector<size_t> assert_columns{0, 1};
    std::vector<size_t> assert_row_indices{0, 1, 2};
    MatrixCSR3 assert_matrix{assert_values, assert_columns, assert_row_indices};

    EXPECT_EQ(result_matrix, assert_matrix);
}

TEST(MatrixOperations, multipleOnIntegerScalar) {
    std::vector<double> values{1, 4};
    std::vector<size_t> columns{0, 1};
    std::vector<size_t> row_indices{0, 1, 2};
    MatrixCSR3 matrix{values, columns, row_indices};

    int scalar = 2;
    MatrixCSR3 result_matrix =  matrix * scalar;

    std::vector<double> assert_values{2, 8};
    std::vector<size_t> assert_columns{0, 1};
    std::vector<size_t> assert_row_indices{0, 1, 2};
    MatrixCSR3 assert_matrix{assert_values, assert_columns, assert_row_indices};

    EXPECT_EQ(result_matrix, assert_matrix);
}

TEST(MatrixOperations, binarPlus) {
    std::vector<double> values1{-1, -0.5};
    std::vector<size_t> columns1{0, 1};
    std::vector<size_t> row_indices1{0, 2, 2};
    MatrixCSR3 matrix1{values1, columns1, row_indices1};

    std::vector<double> values2{2, 0.5, 4};
    std::vector<size_t> columns2{0, 1, 1};
    std::vector<size_t> row_indices2{0, 2, 3};
    MatrixCSR3 matrix2{values2, columns2, row_indices2};

    MatrixCSR3 result_matrix = matrix1 + matrix2;

    std::vector<double> assert_values{1, 4};
    std::vector<size_t> assert_columns{0, 1};
    std::vector<size_t> assert_row_indices{0, 1, 2};
    MatrixCSR3 assert_matrix{assert_values, assert_columns, assert_row_indices};

    EXPECT_EQ(result_matrix, assert_matrix);
}

TEST(MatrixOperations, getElementByIndex2x2matrix) {
    std::vector<double> values{1, 4};
    std::vector<size_t> columns{0, 1};
    std::vector<size_t> row_indices{0, 1, 2};
    MatrixCSR3 matrix{values, columns, row_indices};

    EXPECT_EQ(matrix[std::make_tuple(0, 0)], 1);
    EXPECT_EQ(matrix[std::make_tuple(0, 1)], 0);
    EXPECT_EQ(matrix[std::make_tuple(1, 0)], 0);
    EXPECT_EQ(matrix[std::make_tuple(1, 1)], 4);
}

TEST(MatrixOperations, getElementByIndex3x3matrix) {
    std::vector<double> values{1, 2, 3, 4, 5};
    std::vector<size_t> columns{1, 0, 2, 1, 2};
    std::vector<size_t> row_indices{0, 1, 3, 5};
    MatrixCSR3 matrix{values, columns, row_indices};

    EXPECT_EQ(matrix[std::make_tuple(0, 0)], 0);
    EXPECT_EQ(matrix[std::make_tuple(0, 1)], 1);
    EXPECT_EQ(matrix[std::make_tuple(0, 2)], 0);
    EXPECT_EQ(matrix[std::make_tuple(1, 0)], 2);
    EXPECT_EQ(matrix[std::make_tuple(1, 1)], 0);
    EXPECT_EQ(matrix[std::make_tuple(1, 2)], 3);
    EXPECT_EQ(matrix[std::make_tuple(2, 0)], 0);
    EXPECT_EQ(matrix[std::make_tuple(2, 1)], 4);
    EXPECT_EQ(matrix[std::make_tuple(2, 2)], 5);
}

TEST(MatrixOperations, accessByInvalidIndex) {
    std::vector<double> values{1, 2, 3, 4, 5};
    std::vector<size_t> columns{1, 0, 2, 1, 2};
    std::vector<size_t> row_indices{0, 1, 3, 5};
    MatrixCSR3 matrix{values, columns, row_indices};

    EXPECT_THROW(matrix[std::make_tuple(100, 100)], std::runtime_error);
}
