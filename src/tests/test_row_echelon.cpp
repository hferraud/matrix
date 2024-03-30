#include <iostream>
#include <cassert>

#include "test.hpp"
#include "matrix.hpp"

void test_row_echelon() {
	Matrix<float> m;
	Matrix<float> r;

	m = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
	assert(m.row_echelon() == m);

	m = {{1, 2}, {3, 4}};
	r = {{1, 0}, {0, 1}};
	assert(m.row_echelon() == r);

	m = {{2, -1, 0}, {-1, 2, -1}, {0, -1, 2}};
	r = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
	assert(m.row_echelon() == r);

	m = {{1, 2}, {2, 4}};
	r = {{1, 2}, {0, 0}};
	assert(m.row_echelon() == r);

	m = {{1, 2, 0}, {1, 3, 3}, {-1, 0, -1}, {-3, 0, 0}};
	r = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {0, 0, 0}};
	assert(m.row_echelon() == r);

//	m = {{8, 5, -2, 4, 28}, {4, 2.5, 20, 4, -4}, {8, 5, 1, 4, 17}};
//	std::cout << m.row_echelon() << std::endl;

	std::cout << "TEST_ROW_ECHELON_MATRIX: SUCCESS" << std::endl;
}
