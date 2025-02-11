#include <gtest/gtest.h>
#include <vector>

#include "../src/MatrixCSR3.h"
#include "../src/MatrixReader.h"

TEST(MatrixReader, read2x2Matrix) {
    MatrixCSR3 matrix = MatrixReader::read("../source/matrix2x2.txt");

    std::vector<double> assert_values{1, 4};
    std::vector<size_t> assert_columns{0, 1};
    std::vector<size_t> assert_row_indices{0, 1, 2};
    
    EXPECT_EQ(matrix.getValues(), assert_values);
    EXPECT_EQ(matrix.getColumns(), assert_columns);
    EXPECT_EQ(matrix.getRowIndices(), assert_row_indices);
}

TEST(MatrixReader, readEmptyMatrix) {
    MatrixCSR3 matrix = MatrixReader::read("../source/emptyMatrix.txt");

    std::vector<double> assert_values(0);
    std::vector<size_t> assert_columns(0);
    std::vector<size_t> assert_row_indices{0};

    EXPECT_EQ(matrix.getValues(), assert_values);
    EXPECT_EQ(matrix.getColumns(), assert_columns);
    EXPECT_EQ(matrix.getRowIndices(), assert_row_indices);
}