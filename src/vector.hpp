#ifndef MATRIX_VECTOR_HPP
#define MATRIX_VECTOR_HPP

#include <iostream>
#include <utility>

#include "matrix.hpp"

template <class K>
class Matrix;

template <class K>
class Vector {
 private:
	size_t	size_;
	K*		data_;

 public:

	// CONSTRUCTORS

	explicit Vector(size_t size) : size_(size) {
		data_ = new K[size];
	}

	Vector(Vector<K> const & other) {
		data_ = nullptr;
		*this = other;
	}

	~Vector() {
		delete[] data_;
	}

	// OPERATORS

	Vector<K>& operator=(Vector<K> const & other) {
		if (this == &other) {
			return *this;
		}
		delete[] data_;
		size_ = other.size_;
		data_ = new K[size_];
		for (size_t i = 0; i < size_; ++i) {
			data_[i] = other[i];
		}
		return *this;
	}

	K& operator[](size_t index) {
		return data_[index];
	}

	const K& operator[](size_t index) const {
		return data_[index];
	}

	// GETTERS

	size_t get_size() const {
		return size_;
	}

	// METHODS

	void add(Vector<K> const & operand) {
		if (operand.get_size() != size_)
			throw VectorException("Vector of different size");

		foreach([&operand](K& element, size_t index) {
			element += operand[index];
		});
	}

	void sub(Vector<K> const & operand) {
		if (operand.get_size() != size_)
			throw VectorException("Vector of different size");

		foreach([&operand](K& element, size_t index) {
			element -= operand[index];
		});
	}

	void scale(K const & scalar) {
		foreach([&scalar](K& element) {
			element *= scalar;
		});
	}

	void foreach(void (*f)(K&)) {
		for (size_t i = 0; i < size_; ++i) {
			f(data_[i]);
		}
	}

	void foreach(void (*f)(K&, size_t)) {
		for (size_t i = 0; i < size_; ++i) {
			f(data_[i], i);
		}
	}

	Matrix<K> to_matrix() {
		Matrix<K> matrix(size_, 1);

		for (size_t i = 0; i < size_; ++i) {
			matrix[i][0] = data_[i];
		}
		return matrix;
	}

	// EXCEPTIONS

	class VectorException : public std::exception {
	private:
		std::string error_message_;
	public:
		explicit VectorException(std::string message) : error_message_(std::move(message)) {}

		char const * what() const noexcept override {
			return error_message_.c_str();
		}
	};
};

template <typename K>
std::ostream& operator<<(std::ostream& os, const Vector<K>& vector) {
	for (size_t i = 0; i < vector.get_size(); i++) {
		os << '[' << vector[i] << ']' << std::endl;
	}
	return os;
}

#endif
