#include <gtest/gtest.h>

TEST(MatrixReader, read) {
    std::vector<float> grid_func{1, 1, 1, 1, 1, 1, 1, 1, 1};
    Grid grid1 = Grid{grid_func, 1};

    ClosestNeighborGridInterpolation c = ClosestNeighborGridInterpolation{};
    std::vector<float> new_grid_func = grid1.downscale(2, &c).getGridFunction();
    std::vector<float> assert_grid_func{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

    ASSERT_EQ(assert_grid_func.size(), new_grid_func.size());

    for (size_t i = 0; i < assert_grid_func.size(); ++i) {
        EXPECT_NEAR(new_grid_func[i], assert_grid_func[i], 1e-6);
    }
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
}*/

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}