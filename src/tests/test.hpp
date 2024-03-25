#ifndef MATRIX_TEST_HPP
#define MATRIX_TEST_HPP

#include <stdexcept>
#include <cassert>

template <typename Function>
void assert_throws(Function f) {
	try {
		f();
		throw std::logic_error("Expected function to throw an exception");
	} catch (std::exception const & e) {
		return;
	}
}

void assert_float(float a, float b, float epsilon = 1e-5);

void test();
void test_constraints();
void test_basic_arithmetic();
void test_linear_combination();
void test_linear_interpolation();
void test_dot_product();
void test_norm();
void test_cosine();
void test_cross_product();
void test_matrix_multiplication();
void test_trace();

#endif
