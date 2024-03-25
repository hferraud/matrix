#ifndef MATRIX_ALGEBRA_HPP
#define MATRIX_ALGEBRA_HPP

#include <cmath>

#include "vector.hpp"

template <typename K>
Vector<K> linear_combination(Vector<K>* vectors, K* scalars, size_t length) {
	Vector<K> result(vectors[0].get_size());

	result.foreach([vectors, scalars, length](K& element, size_t& entry) {
		for (size_t i = 0; i < length; ++i) {
			element = std::fma(vectors[i][entry], scalars[i], element);
		}
	});
	return result;
}

template <typename K>
K lerp(K u, K v, float t) {
	return u + (v - u) * t;
}

template <typename K>
float angle_cos(Vector<K> const & v1, Vector<K> const & v2) {
	return (v1.dot(v2) / (v1.norm() * v2.norm()));
}

template <typename K>
Vector<K> cross_product(Vector<K> const & v1, Vector<K> const & v2) {
	Vector<K> result(3);

	result[0] = std::fma(v1[1], v2[2], -v1[2] * v2[1]);
	result[1] = std::fma(v1[2], v2[0], -v1[0] * v2[2]);
	result[2] = std::fma(v1[0], v2[1], -v1[1] * v2[0]);
	return result;
}

#endif
