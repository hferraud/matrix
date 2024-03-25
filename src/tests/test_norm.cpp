#include <iostream>
#include <cassert>

#include "test.hpp"
#include "vector.hpp"

void test_norm() {
	Vector<int> v1;

	v1 = {0, 0, 0};
	assert(v1.norm() == 0);
	assert(v1.norm_1() == 0);
	assert(v1.norm_inf() == 0);

	v1 = {1, 2, 3};
	assert_float(v1.norm(), 3.74165738);
	assert(v1.norm_1() == 6);
	assert(v1.norm_inf() == 3);

	v1 = {-1, -2};
	assert_float(v1.norm(), 2.236067977);
	assert(v1.norm_1() == 3);
	assert(v1.norm_inf() == 2);
	std::cout << "TEST_NORM_VECTOR: SUCCESS" << std::endl;
}
