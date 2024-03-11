#include <iostream>
#include <cassert>

#include "vector.hpp"

int main() {
	{
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

		assert(m1.get_shape().row == 3);
		assert(m1.get_shape().column == 1);
		for (size_t i = 0; i < m1.get_shape().row; ++i) {
			assert(m1[i][0] == v1[i]);
		}

		std::cout << "Vector:" << std::endl;
		std::cout << v1 << std::endl;
		std::cout << "Matrix:" << std::endl;
		std::cout << m1;
		std::cout << "VECTOR TESTS: SUCCESS" << std::endl;
	}
	{
		Matrix<int> m1(3, 3);

		for (size_t i = 0; i < m1.get_shape().row; ++i) {
			for (size_t j = 0; j < m1.get_shape().column; ++j) {
				m1[i][j] = static_cast<int>(i * m1.get_shape().column + j + 1);
				assert(m1[i][j] == static_cast<int>(i * m1.get_shape().column + j + 1));
			}
		}

		Matrix<int> m2(m1);

		for (size_t i = 0; i < m2.get_shape().row; ++i) {
			for (size_t j = 0; j < m2.get_shape().column; ++j) {
				assert(m1[i][j] == m2[i][j]);
			}
		}

		m1[0][1] = 10;
		assert(m1[0][1] == 10);
		m2[1][1] = 20;
		assert(m2[1][1] == 20);

		m2 = m1;
		for (size_t i = 0; i < m2.get_shape().row; ++i) {
			for (size_t j = 0; j < m2.get_shape().column; ++j) {
				assert(m1[i][j] == m2[i][j]);
			}
		}

		Matrix<int> m3(3, 1);
		for (size_t i = 0; i < m3.get_shape().row; ++i) {
			m3[i][0] = m1[i][0];
		}

		assert(m1.isSquare());
		assert(!m3.isSquare());

		Vector<int> v1 = m3.to_vector();

		assert(v1.get_size() == 3);
		for (size_t i = 0; i < m1.get_shape().row; ++i) {
			assert(v1[i] == m3[i][0]);
		}

		std::cout << "Matrix:" << std::endl;
		std::cout << m1;

		std::cout << "Vector:" << std::endl;
		std::cout << v1;
		std::cout << "MATRIX TESTS: SUCCESS" << std::endl;
	}
	return 0;
}
