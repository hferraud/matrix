cmake_minimum_required(VERSION 3.27)
project(matrix)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)

add_executable(matrix
        src/vector.cpp
        src/matrix.cpp
        src/main.cpp
        src/tests/test_constraints.cpp
        src/tests/test.cpp
        src/tests/test_linear_combination.cpp
)
