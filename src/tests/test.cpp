#include "test.hpp"

void assert_float(float a, float b, float epsilon) {
	assert(std::abs(a - b) < epsilon);
}

void test() {
	test_constraints();
	test_basic_arithmetic();
	test_linear_combination();
	test_linear_interpolation();
	test_dot_product();
	test_norm();
	test_cosine();
	test_cross_product();
}