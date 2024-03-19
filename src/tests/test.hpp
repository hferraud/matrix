#ifndef MATRIX_TEST_HPP
#define MATRIX_TEST_HPP

#include <stdexcept>

template <typename Function>
void assert_throws(Function f) {
	try {
		f();
		throw std::logic_error("Expected function to throw an exception");
	} catch (std::exception const & e) {
		return;
	}
}

void test();
void test_constraints();
void test_basic_arithmetic();
void test_linear_combination();
void test_linear_interpolation();
void test_dot_product();

#endif
