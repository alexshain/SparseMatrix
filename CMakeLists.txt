cmake_minimum_required(VERSION 3.10)
project(SparseMatrix)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_library(SparseMatrix STATIC src/MatrixCSR3.cpp src/MatrixReader.cpp)

target_include_directories(SparseMatrix PUBLIC include)

enable_testing()
add_subdirectory(tests)
