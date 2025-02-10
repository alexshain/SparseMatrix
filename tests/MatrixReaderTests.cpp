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

/*void testUnarMinus() {
    MatrixCSR3 matrix = MatrixReader::readMatrix("matrixMTX1.txt");

    for(size_t i = 0; i < matrix.getValues().size(); i++) {
        std::cout << matrix.getValues()[i] << " ";
    }
    std::cout << std::endl;

    matrix = -matrix;

    for(size_t i = 0; i < matrix.getValues().size(); i++) {
        std::cout << matrix.getValues()[i] << " ";
    }
    std::cout << std::endl;

}

void testMinus() {
    MatrixCSR3 m1 = MatrixReader::readMatrix("matrixMTX1.txt");
    MatrixCSR3 m2 = MatrixReader::readMatrix("matrixMTX2.txt");
    MatrixCSR3 m3 = m1 - m2;

    std::cout << "firstMatrix" << std::endl;
    for(size_t i = 0; i < m1.getValues().size(); i++) {
        std::cout << m1.getValues()[i] << " ";
    }
    std::cout << std::endl;
    for(size_t i = 0; i < m1.getColumns().size(); i++) {
        std::cout << m1.getColumns()[i] << " ";
    }
    std::cout << std::endl;
    for(size_t i = 0; i < m1.getRowIndices().size(); i++) {
        std::cout << m1.getRowIndices()[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "secondMatrix" << std::endl;
    for(size_t i = 0; i < m2.getValues().size(); i++) {
        std::cout << m2.getValues()[i] << " ";
    }
    std::cout << std::endl;
    for(size_t i = 0; i < m2.getColumns().size(); i++) {
        std::cout << m2.getColumns()[i] << " ";
    }
    std::cout << std::endl;
    for(size_t i = 0; i < m2.getRowIndices().size(); i++) {
        std::cout << m2.getRowIndices()[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "resultMatrix" << std::endl;
    for(size_t i = 0; i < m3.getValues().size(); i++) {
        std::cout << m3.getValues()[i] << " ";
    }
    std::cout << std::endl;
    for(size_t i = 0; i < m3.getColumns().size(); i++) {
        std::cout << m3.getColumns()[i] << " ";
    }
    std::cout << std::endl;
    for(size_t i = 0; i < m3.getRowIndices().size(); i++) {
        std::cout << m3.getRowIndices()[i] << " ";
    }
    std::cout << std::endl;
}

void testMultipleOnScalar() {
    MatrixCSR3 matrix = MatrixReader::readMatrix("matrixMTX1.txt");

    for(size_t i = 0; i < matrix.getValues().size(); i++) {
        std::cout << matrix.getValues()[i] << " ";
    }
    std::cout << std::endl;

    matrix = matrix*2;

    for(size_t i = 0; i < matrix.getValues().size(); i++) {
        std::cout << matrix.getValues()[i] << " ";
    }
    std::cout << std::endl;
}

void testPlus() {
    MatrixCSR3 m1 = MatrixReader::readMatrix("matrixMTX1.txt");
    MatrixCSR3 m2 = MatrixReader::readMatrix("matrixMTX2.txt");
    MatrixCSR3 m3 = m1 + m2;

    std::cout << "firstMatrix" << std::endl;
    for(size_t i = 0; i < m1.getValues().size(); i++) {
        std::cout << m1.getValues()[i] << " ";
    }
    std::cout << std::endl;
    for(size_t i = 0; i < m1.getColumns().size(); i++) {
        std::cout << m1.getColumns()[i] << " ";
    }
    std::cout << std::endl;
    for(size_t i = 0; i < m1.getRowIndices().size(); i++) {
        std::cout << m1.getRowIndices()[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "secondMatrix" << std::endl;
    for(size_t i = 0; i < m2.getValues().size(); i++) {
        std::cout << m2.getValues()[i] << " ";
    }
    std::cout << std::endl;
    for(size_t i = 0; i < m2.getColumns().size(); i++) {
        std::cout << m2.getColumns()[i] << " ";
    }
    std::cout << std::endl;
    for(size_t i = 0; i < m2.getRowIndices().size(); i++) {
        std::cout << m2.getRowIndices()[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "resultMatrix" << std::endl;
    for(size_t i = 0; i < m3.getValues().size(); i++) {
        std::cout << m3.getValues()[i] << " ";
    }
    std::cout << std::endl;
    for(size_t i = 0; i < m3.getColumns().size(); i++) {
        std::cout << m3.getColumns()[i] << " ";
    }
    std::cout << std::endl;
    for(size_t i = 0; i < m3.getRowIndices().size(); i++) {
        std::cout << m3.getRowIndices()[i] << " ";
    }
    std::cout << std::endl;
}

void testGetByIndex() {

    MatrixCSR3 matrix = MatrixReader::readMatrix("matrixMTX1.txt");

    for(size_t i = 0; i < matrix.getValues().size(); i++) {
        std::cout << matrix.getValues()[i] << " ";
    }
    std::cout << std::endl;

    std::cout << matrix[{1,1}] << std::endl;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}*/