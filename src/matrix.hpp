#ifndef MATRIX_MATRIX_HPP
#define MATRIX_MATRIX_HPP

#include <iostream>

#include "vector.hpp"

template <class K>
class Vector;

template <class K>
class Matrix {
	typedef struct shape_s {
		size_t row;
		size_t column;
	} shape_t;

 private:
	shape_t	shape_;
	K**		data_;

 public:
	explicit Matrix(size_t row, size_t column) {
		shape_.row = row;
		shape_.column = column;
		data_ = new K*[row];
		for (size_t i = 0; i < row; ++i) {
			data_[i] = new K[column];
		}
	}

	explicit Matrix(shape_t shape) : Matrix(shape.row, shape.column) {}

	Matrix (Matrix<K> const & other) {
		data_ = nullptr;
		*this = other;
	}

	~Matrix() {
		for (size_t row = 0; row < shape_.row; ++row) {
			delete[] data_[row];
		}
		delete[] data_;
	}

	Matrix<K>& operator=(Matrix<K> const & other) {
		if (this == &other) {
			return *this;
		}
		if (data_ != nullptr) {
			for (size_t row = 0; row < shape_.row; ++row) {
				delete[] data_[row];
			}
			delete[] data_;
		}
		shape_ = other.shape_;
		data_ = new K*[shape_.row];
		for (size_t row = 0; row < shape_.row; ++row) {
			data_[row] = new K[shape_.column];
			for (size_t column = 0; column < shape_.column; ++column) {
				data_[row][column] = other[row][column];
			}
		}
		return *this;
	}

	K* operator[](size_t index) {
		return data_[index];
	}

	const K* operator[](size_t index) const {
		return data_[index];
	}

	shape_t get_shape() const {
		return shape_;
	}

	bool isSquare() const {
		return (shape_.row == shape_.column);
	}

	Vector<K> to_vector() {
		if (shape_.column != 1) {
			throw MatrixException("Cannot convert to a vector");
		}
		Vector<K> vector(shape_.row);

		for (size_t row = 0; row < shape_.row; ++row) {
			vector[row] = data_[row][0];
		}
		return vector;
	}

	class MatrixException : public std::exception {
	 private:
		std::string error_message_;
	 public:
		explicit MatrixException(std::string const & message) : error_message_(message) {}

		const char *what() const noexcept override {
			return error_message_.c_str();
		}
	};
};

template <typename K>
std::ostream& operator<<(std::ostream& os, const Matrix<K>& matrix) {
	for (size_t row = 0; row < matrix.get_shape().row ; ++row) {
		os << '[';
		for (size_t column = 0; column < matrix.get_shape().column; column++) {
			os << matrix[row][column] ;
			if (column + 1 < matrix.get_shape().column) {
				os << ", ";
			}
		}
		os << ']' << std::endl;
	}
	os << std::flush;
	return os;
}

#endif
