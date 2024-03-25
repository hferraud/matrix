#include <iostream>
#include <cassert>

#include "test.hpp"
#include "vector.hpp"
#include "matrix.hpp"
#include "algebra.hpp"

void test_linear_interpolation() {
	assert(0.0 == lerp(0., 1., 0.));
	assert(1.0 == lerp(0., 1., 1.));
	assert(0.5 == lerp(0., 1., 0.5));
	assert(Vector<float>({2.6, 1.3}) == lerp(
			Vector<float>({2., 1.}),
			Vector<float>({4., 2.}),
			0.3));
	assert(Matrix<float>({{11., 5.5}, {16.5, 22.}}) == lerp(
			Matrix<float>({{2., 1.}, {3., 4.}}),
			Matrix<float>({{20., 10.}, {30., 40.}}),
			0.5));
	std::cout << "TEST_LINEAR_INTERPOLATION_VECTOR: SUCCESS" << std::endl;
}
