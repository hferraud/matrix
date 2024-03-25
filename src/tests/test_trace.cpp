#include <iostream>
#include <cassert>

#include "test.hpp"
#include "matrix.hpp"

void test_trace() {
	Matrix<int> m;

	m = {{1, 0}, {0, 1}};
	assert(m.trace() == 2);

	m = {{2, -5, 0}, {4, 3, 7}, {-2, 3, 4}};
	assert(m.trace() == 9);

	m = {{-2, -8, 4}, {1, -23, 4}, {0, 6, 4}};
	assert(m.trace() == -21);
	std::cout << "TEST_TRACE_MATRIX: SUCCESS" << std::endl;
}
