#include <iostream>
#include <cassert>

#include "test.hpp"
#include "vector.hpp"

void test_dot_product() {
	Vector<float> u;
	Vector<float> v;

	u = {0., 0.};
	v = {1., 1.};
	assert(u.dot(v) == 0);

	u = {1., 1.};
	v = {1., 1.,};
	assert(u.dot(v) == 2);

	u = {-1., 6.};
	v = {3., 2.,};
	assert(u.dot(v) == 9);

	u = {1., 3., -5.};
	v = {4., -2., -1};
	assert(u.dot(v) == 3);
	assert(u.dot(u) == 35);
	std::cout << "TEST_DOT_PRODUCT_VECTOR: SUCCESS" << std::endl;
}

