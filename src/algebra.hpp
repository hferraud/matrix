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

#endif
