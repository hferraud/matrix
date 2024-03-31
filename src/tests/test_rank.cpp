#include <iostream>
#include <cassert>

#include "test.hpp"
#include "matrix.hpp"

void test_rank() {
	Matrix<float> m;

	m = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
	assert(m.rank() == 3);

	m = {{1, 2, 0, 0}, {2, 4, 0, 0}, {-1, 2, 1, 1}};
	assert(m.rank() == 2);

	m = {{8, 5, -2}, {4, 7, 20}, {7, 6, 1}, {21, 18, 7}};
	assert(m.rank() == 3);

	std::cout << "TEST_RANK_MATRIX: SUCCESS" << std::endl;
}
