#include <iostream>
#include <cassert>

#include "test.hpp"
#include "vector.hpp"
#include "algebra.hpp"

void test_cross_product() {
	Vector<int> u;
	Vector<int> v;
	Vector<int> res;

	u = {0, 0, 1};
	v = {1, 0, 0};
	res = cross_product(u, v);
	assert(res[0] == 0);
	assert(res[1] == 1);
	assert(res[2] == 0);

	u = {1, 2, 3};
	v = {4, 5, 6};
	res = cross_product(u, v);
	assert(res[0] == -3);
	assert(res[1] == 6);
	assert(res[2] == -3);

	u = {4, 2, -3};
	v = {-2, -5, 16};
	res = cross_product(u, v);
	assert(res[0] == 17);
	assert(res[1] == -58);
	assert(res[2] == -16);

	std::cout << "TEST_CROSS_PRODUCT_VECTOR: SUCCESS" << std::endl;
}
