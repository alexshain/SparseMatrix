find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(run_tests MatrixReaderTests.cpp MatrixOperationsTests.cpp SliceMatrixTests.cpp)
target_link_libraries(run_tests SparseMatrix GTest::GTest GTest::Main)

# Регистрация тестов
add_test(NAME MyTests COMMAND run_tests)
