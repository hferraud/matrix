cmake_minimum_required(VERSION 3.24.2)
project(matrix)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)

add_executable(matrix
        src/main.cpp
        src/tests/test_constraints.cpp
        src/tests/test.cpp
        src/tests/test_basic_arithmetic.cpp
        src/tests/test_linear_combination.cpp
        src/algebra.hpp
        src/tests/test_linear_interpolation.cpp
        src/tests/test_dot_product.cpp
        src/tests/test_norm.cpp src/tests/test_cosine.cpp src/tests/test_matrix_multiplication.cpp
        src/tests/test_cross_product.cpp
        src/tests/test_transpose.cpp
        src/tests/test_row_echelon.cpp
        src/tests/test_trace.cpp
        src/tests/test_determinant.cpp)
