#include <iostream>
#include <cassert>

#include "vector.hpp"
#include "matrix.hpp"
#include "test.hpp"

template<typename K>
void test_linear_combination_vector();
template<typename K>
void test_linear_combination_matrix();

void test_linear_combination() {
	test_linear_combination_vector<int>();
	std::cout << "TEST_LINEAR_COMBINATION_VECTOR: SUCCESS" << std::endl;
	test_linear_combination_matrix<int>();
	std::cout << "TEST_LINEAR_COMBINATION_MATRIX: SUCCESS" << std::endl;
}

template<typename K>
void test_linear_combination_vector() {
	Vector<K> v1(3);
	Vector<K> v2(3);
	Vector<K> v3(4);

	for (size_t i = 0; i < v1.get_size(); ++i) {
		v1[i] = static_cast<K>(i + 1);
		v2[i] = static_cast<K>(i * 2 + 1);
	}

	Vector<K> addResult = v1;
	addResult.add(v2);
	addResult.foreach([&v1, &v2](K& element, size_t& i) {
		assert(element == v1[i] + v2[i]);
	});

	Vector<K> subResult = v1;
	subResult.sub(v2);
	subResult.foreach([&v1, &v2](K& element, size_t& i) {
		assert(element == v1[i] - v2[i]);
	});

	K scalar = static_cast<K>(3);
	Vector<K> scaleResult = v1;
	scaleResult.scale(scalar);
	scaleResult.foreach([&v1, &scalar](K& element, size_t& i) {
		assert(element == v1[i] * scalar);
	});

	assert_throws([&v1, &v3]() { v1.add(v3); });
	assert_throws([&v1, &v3]() { v1.sub(v3); });
}

template<typename K>
void test_linear_combination_matrix() {
	Matrix<K> m1(3, 3);
	Matrix<K> m2(3, 3);
	Matrix<K> m3(4, 4);

	m1.foreach([](K& element, size_t& row, size_t& column) {
		element = row * column;
	});

	m2.foreach([](K& element, size_t& row, size_t& column) {
		element = row * column * 2;
	});

	Matrix<K> addResult = m1;
	addResult.add(m2);
	addResult.foreach([&m1, &m2](K& element, size_t& row, size_t& column) {
		assert(element == m1[row][column] + m2[row][column]);
	});

	Matrix<K> subResult = m1;
	subResult.sub(m2);
	subResult.foreach([&m1, &m2](K& element, size_t& row, size_t& column) {
		assert(element == m1[row][column] - m2[row][column]);
	});

	K scalar = static_cast<K>(3);
	Matrix<K> scaleResult = m1;
	scaleResult.scale(scalar);
	scaleResult.foreach([&m1, &scalar](K& element, size_t& row, size_t& column) {
		assert(element == m1[row][column] * scalar);
	});

	assert_throws([&m1, &m3]() { m1.add(m3); });
	assert_throws([&m1, &m3]() { m1.sub(m3); });
}
