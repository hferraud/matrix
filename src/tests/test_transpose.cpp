#include <iostream>
#include <cassert>

#include "test.hpp"
#include "matrix.hpp"

void test_transpose() {
	Matrix<int> m;
	Matrix<int> t;

	m = {{1, 0}, {0, 1}};
	assert(m.transpose() == m);

	m = {{1, 2, 3}};
	t = {{1}, {2}, {3}};
	assert(m.transpose() == t);

	m = {{1, 2, 3}, {4, 5, 6}};
	t = {{1, 4}, {2, 5}, {3, 6}};
	assert(m.transpose() == t);

	std::cout << "TEST_TRACE_MATRIX: SUCCESS" << std::endl;
}
