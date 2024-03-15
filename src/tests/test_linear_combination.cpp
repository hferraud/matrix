#include <iostream>
#include <cassert>

#include "test.hpp"
#include "vector.hpp"

void test_linear_combination_vector();

void test_linear_combination() {
	test_linear_combination_vector();
	std::cout << "TEST_LINEAR_COMBINATION_VECTOR: SUCCESS" << std::endl;
}

void test_linear_combination_vector() {
	Vector<float> v1({1., 0., 0.});
	Vector<float> v2({0., 1., 0.});
	Vector<float> v3({0., 0., 1.});
	float scalars_value[] = {10., -2., 0.5};
	Vector<float> vectors_list_1[] = {v1, v2, v3};

	Vector<float> result = linear_combination(vectors_list_1, scalars_value, 3);

	assert(result[0] == 10.);
	assert(result[1] == -2.);
	assert(result[2] == 0.5);

	Vector<float> e1({1., 2., 3.});
	Vector<float> e2({0., 10., -100.});
	Vector<float> vectors_list_2[] = {e1, e2};

	result = linear_combination(vectors_list_2, scalars_value, 2);

	assert(result[0] == 10.);
	assert(result[1] == 0.);
	assert(result[2] == 230.);

	Vector<float> e3(4);
	Vector<float> vectors_list_3[] = {e1, e2, e3};

	try {
		linear_combination(vectors_list_3, scalars_value, 3);
		assert(false);
	} catch (Vector<float>::VectorException const & e) {}
}
