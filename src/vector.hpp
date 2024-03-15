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

	void assert_size_match(Vector<K> const & other) {
		if (other.get_size() != size_) {
			throw VectorException("Vector size mismatch");
		}
	}

 public:

	// CONSTRUCTORS

	explicit Vector(size_t size): size_(size) {
		data_ = new K[size];
		foreach([](K& element) {
			element = 0;
		});
	}

	Vector(Vector<K> const & other) {
		data_ = nullptr;
		*this = other;
	}

	Vector(std::initializer_list<K> entries): size_(entries.size()), data_(new K[size_]) {
		std::copy(entries.begin(), entries.end(), data_);
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

	K const & operator[](size_t index) const {
		return data_[index];
	}

	Vector<K> operator+(Vector<K> const & rhs) const {
		assert_size_match(rhs);
		Vector<K> result(size_);

		result.foreach([this, &rhs](K& element, size_t& i) {
			element = (*this)[i] + rhs[i];
		});
		return result;
	}

	Vector<K> operator+=(Vector<K> const & rhs) {
		assert_size_match(rhs);

		foreach([&rhs](K& element, size_t& i) {
			element += rhs[i];
		});
		return *this;
	}

	Vector<K> operator-(Vector<K> const & rhs) const {
		assert_size_match(rhs);
		Vector<K> result(size_);

		result.foreach([this, &rhs](K& element, size_t& i) {
			element = (*this)[i] - rhs[i];
		});
		return result;
	}

	Vector<K> operator-=(Vector<K> const & rhs) {
		assert_size_match(rhs);

		foreach([&rhs](K& element, size_t& i) {
			element -= rhs[i];
		});
		return *this;
	}

	Vector<K> operator*(K const & scalar) const {
		Vector<K> result(size_);

		result.foreach([this, &scalar](K& element, size_t& i) {
			element = (*this)[i] * scalar;
		});
		return result;
	}

	Vector<K> operator*=(K const & scalar) {
		foreach([&scalar](K& element) {
			element *= scalar;
		});
		return *this;
	}

	// GETTERS

	size_t get_size() const {
		return size_;
	}

	// METHODS

	void add(Vector<K> const & operand) {
		*this += operand;
	}

	void sub(Vector<K> const & operand) {
		*this -= operand;
	}

	void scale(K const & scalar) {
		*this *= scalar;
	}

	template <typename Function>
	auto foreach(Function f) -> std::enable_if_t<std::is_invocable_v<Function, K&>> {
		for (size_t i = 0; i < size_; ++i) {
			f(data_[i]);
		}
	}

	template <typename Function>
	auto foreach(Function f) -> std::enable_if_t<std::is_invocable_v<Function, K&, size_t&>> {
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

template <typename K>
Vector<K> linear_combination(Vector<K>* vectors, K* scalars, size_t length) {
	Vector<K> result(vectors[0].get_size());

	for (size_t i = 0; i < length; ++i) {
		result += vectors[i] * scalars[i];
	}
	return result;
}

#endif
