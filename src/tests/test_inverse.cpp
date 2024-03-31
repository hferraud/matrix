#include <iostream>
#include <cassert>

#include "test.hpp"
#include "matrix.hpp"

void test_inverse() {
	Matrix<float> m;
	Matrix<float> r;

	m = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
	assert(m.inverse() == m);

	m = {{2, 0, 0}, {0, 2, 0}, {0, 0, 2}};
	r = {{0.5, 0, 0}, {0, 0.5, 0}, {0, 0, 0.5}};
	assert(m.inverse() == r);

//	m = {{8, 5, -2}, {4, 7, 20}, {7, 6, 1}};
//	std::cout << m.inverse() << std::endl;

	std::cout << "TEST_INVERSE_MATRIX: SUCCESS" << std::endl;
}
