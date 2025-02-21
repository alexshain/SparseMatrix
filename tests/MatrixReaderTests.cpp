#include <gtest/gtest.h>
#include <vector>

#include "../include/MatrixCSR3.h"
#include "../include/MatrixReader.h"

using SparseMatrix::MatrixReader;
using SparseMatrix::MatrixCSR3;

TEST(MatrixReader, read2x2Matrix) {
    MatrixCSR3 matrix = MatrixReader::read("..//../tests/source/matrix2x2.txt");

    std::vector<double> assert_values{1, 4};
    std::vector<size_t> assert_columns{0, 1};
    std::vector<size_t> assert_row_indices{0, 1, 2};

    EXPECT_EQ(matrix.getValues(), assert_values);
    EXPECT_EQ(matrix.getColumns(), assert_columns);
    EXPECT_EQ(matrix.getRowIndices(), assert_row_indices);
}

TEST(MatrixReader, readEmptyMatrix) {
    MatrixCSR3 matrix = MatrixReader::read("..//../tests/source/emptyMatrix.txt");

    std::vector<double> assert_values(0);
    std::vector<size_t> assert_columns(0);
    std::vector<size_t> assert_row_indices{0};

    EXPECT_EQ(matrix.getValues(), assert_values);
    EXPECT_EQ(matrix.getColumns(), assert_columns);
    EXPECT_EQ(matrix.getRowIndices(), assert_row_indices);
}

TEST(MatrixReader, wrongPath) {
    EXPECT_THROW(MatrixReader::read("/some_path/some_file.txt"), std::runtime_error);
}