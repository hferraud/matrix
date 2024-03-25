#include <iostream>
#include <cassert>

#include "test.hpp"
#include "vector.hpp"
#include "matrix.hpp"

void test_matrix_multiplication_vector();
void test_matrix_multiplication_matrix();

void test_matrix_multiplication() {
	test_matrix_multiplication_vector();
	std::cout << "TEST_MATRIX_MULTIPLICATION_VECTOR: SUCCESS" << std::endl;
	test_matrix_multiplication_matrix();
	std::cout << "TEST_MATRIX_MULTIPLICATION_MATRIX: SUCCESS" << std::endl;
}

void test_matrix_multiplication_vector() {
	Matrix<int> m;
	Vector<int> v;
	Vector<int> res;

	m = {{1, 0}, {0, 1}};
	v = {4, 2};
	res = m * v;
	assert(res[0] == 4);
	assert(res[1] == 2);

	m = {{2, 0}, {0, 2}};
	res = m * v;
	assert(res[0] == 8);
	assert(res[1] == 4);

	m = {{2, -2}, {-2, 2}};
	res = m * v;
	assert(res[0] == 4);
	assert(res[1] == -4);
}

void test_matrix_multiplication_matrix() {
	Matrix<int> m1;
	Matrix<int> m2;
	Matrix<int> result;
	Matrix<int> valid;

	m1 = {{1, 0}, {0, 1}};
	m2 = {{1, 0}, {0, 1}};
	valid = {{1, 0}, {0, 1}};
	result = m1 * m2;
	assert(result == valid);

	m2 = {{2, 1}, {4, 2}};
	valid = {{2, 1}, {4, 2}};
	result = m1 * m2;
	assert(result == valid);

	m1 = {{3, -5}, {6, 8}};
	valid = {{-14, -7}, {44, 22}};
	result = m1 * m2;
	assert(result == valid);
}
