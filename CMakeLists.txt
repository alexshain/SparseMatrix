cmake_minimum_required(VERSION 3.10)
project(SparseMatrix)

set(CMAKE_CXX_STANDARD 20)

# GoogleTest
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Основные файлы
add_library(my_lib src/MatrixCSR3.cpp src/MatrixReader.cpp)
#add_executable(my_lib src/main.cpp src/MatrixCSR3.cpp src/MatrixReader.cpp)

# Файлы с тестами
add_executable(run_tests tests/MatrixReaderTests.cpp)
target_link_libraries(run_tests my_lib GTest::GTest GTest::Main)

# Регистрация тестов
add_test(NAME MyTests COMMAND run_tests)
