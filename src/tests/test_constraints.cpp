#include <iostream>
#include <cassert>

#include "vector.hpp"
#include "matrix.hpp"

void test_constraints_vector();
void test_constraints_matrix();

void test_constraints() {
	test_constraints_vector();
	std::cout << "TEST_CONSTRAINT_VECTOR: SUCCESS" << std::endl;
	test_constraints_matrix();
	std::cout << "TEST_CONSTRAINT_MATRIX: SUCCESS" << std::endl;
}

void test_constraints_vector() {
	Vector<int> v1(3);

	for (size_t i = 0; i < v1.get_size(); ++i) {
		v1[i] = static_cast<int>(i) + 1;
		assert(v1[i] == static_cast<int>(i) + 1);
	}

	Vector<int> v2(v1);

	for (size_t i = 0; i < v1.get_size(); ++i) {
		assert(v1[i] == v2[i]);
	}

	v1[0] = 10;
	assert(v1[0] == 10);
	v2[1] = 20;
	assert(v2[1] == 20);

	v2 = v1;
	for (size_t i = 0; i < v1.get_size(); ++i) {
		assert(v1[i] == v2[i]);
	}

	Matrix<int> m1 = v1.to_matrix();

	assert(m1.get_dimension().row == 3);
	assert(m1.get_dimension().column == 1);
	for (size_t i = 0; i < m1.get_dimension().row; ++i) {
		assert(m1[i][0] == v1[i]);
	}
}

void test_constraints_matrix() {
	Matrix<int> m1(3, 3);

	for (size_t i = 0; i < m1.get_dimension().row; ++i) {
		for (size_t j = 0; j < m1.get_dimension().column; ++j) {
			m1[i][j] = static_cast<int>(i * m1.get_dimension().column + j + 1);
			assert(m1[i][j] == static_cast<int>(i * m1.get_dimension().column + j + 1));
		}
	}

	Matrix<int> m2(m1);

	for (size_t i = 0; i < m2.get_dimension().row; ++i) {
		for (size_t j = 0; j < m2.get_dimension().column; ++j) {
			assert(m1[i][j] == m2[i][j]);
		}
	}

	m1[0][1] = 10;
	assert(m1[0][1] == 10);
	m2[1][1] = 20;
	assert(m2[1][1] == 20);

	m2 = m1;
	for (size_t i = 0; i < m2.get_dimension().row; ++i) {
		for (size_t j = 0; j < m2.get_dimension().column; ++j) {
			assert(m1[i][j] == m2[i][j]);
		}
	}

	Matrix<int> m3(3, 1);
	for (size_t i = 0; i < m3.get_dimension().row; ++i) {
		m3[i][0] = m1[i][0];
	}

	assert(m1.is_square());
	assert(!m3.is_square());

	Vector<int> v1 = m3.to_vector();

	assert(v1.get_size() == 3);
	for (size_t i = 0; i < m1.get_dimension().row; ++i) {
		assert(v1[i] == m3[i][0]);
	}
}