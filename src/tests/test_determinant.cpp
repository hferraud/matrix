#include <iostream>
#include <cassert>

#include "test.hpp"
#include "matrix.hpp"

void test_determinant() {
	Matrix<float> m;

	m = {{1, -1}, {-1, 1}};
	assert(m.determinant() == 0);

	m = {{2, 0, 0}, {0, 2, 0}, {0, 0, 2}};
	assert(m.determinant() == 8);

	m = {{8, 5, -2, 4}, {4, 2.5, 20, 4}, {8, 5, 1, 4}, {28, -4, 17, 1}};
	assert(m.determinant() == 1032);

	m = {{4, 0, -7, 3, -5}, {0, 0, 2, 0, 0}, {7, 3, -6, 4, -8}, {5, 0, 5, 2, -3}, {0, 0, 9, -1, 2}};
	assert(m.determinant() == 6);

	std::cout << "TEST_DETERMINANT_MATRIX: SUCCESS" << std::endl;
}
