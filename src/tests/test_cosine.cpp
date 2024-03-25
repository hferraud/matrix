#include <iostream>
#include <cassert>

#include "test.hpp"
#include "vector.hpp"
#include "algebra.hpp"

void test_cosine() {
	Vector<int> v1;
	Vector<int> v2;

	v1 = {1, 0};
	v2 = {1, 0};
	assert(angle_cos(v1, v2) == 1);

	v1 = {1, 0};
	v2 = {0, 1};
	assert(angle_cos(v1, v2) == 0);

	v1 = {-1, 1};
	v2 = {1, -1};
	assert_float(angle_cos(v1, v2), -1.);

	v1 = {2, 1};
	v2 = {4, 2};
	assert(angle_cos(v1, v2) == 1);

	v1 = {1, 2, 3};
	v2 = {4, 5, 6};
	assert_float(angle_cos(v1, v2), 0.974631846);

	std::cout << "TEST_COSINE_VECTOR: SUCCESS" << std::endl;
}
