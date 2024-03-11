cmake_minimum_required(VERSION 3.27)
project(matrix)

set(CMAKE_CXX_STANDARD 20)

add_executable(matrix
        src/vector.cpp
        src/matrix.cpp
        src/main.cpp
)
