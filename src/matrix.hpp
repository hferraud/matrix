#ifndef MATRIX_MATRIX_HPP
#define MATRIX_MATRIX_HPP

#include <iostream>
#include <utility>

#include "vector.hpp"

template <class K>
class Vector;

template <class K>
class Matrix {
	typedef struct dimension_s {
		size_t row;
		size_t column;

		bool operator==(struct dimension_s const & other) const {
			return row == other.row && column == other.column;
		}
	} dimension_t;

 private:
	dimension_t	dimension_;
	K**		data_;

 public:

	// CONSTRUCTORS

	explicit Matrix(size_t row, size_t column) {
		dimension_.row = row;
		dimension_.column = column;
		data_ = new K*[row];
		for (size_t i = 0; i < row; ++i) {
			data_[i] = new K[column];
		}
	}

	explicit Matrix(dimension_t dimension) : Matrix(dimension.row, dimension.column) {}

	Matrix (Matrix<K> const & other) {
		data_ = nullptr;
		*this = other;
	}

	~Matrix() {
		for (size_t row = 0; row < dimension_.row; ++row) {
			delete[] data_[row];
		}
		delete[] data_;
	}

	// OPERATORS

	Matrix<K>& operator=(Matrix<K> const & other) {
		if (this == &other) {
			return *this;
		}
		if (data_ != nullptr) {
			for (size_t row = 0; row < dimension_.row; ++row) {
				delete[] data_[row];
			}
			delete[] data_;
		}
		dimension_ = other.dimension_;
		data_ = new K*[dimension_.row];
		for (size_t row = 0; row < dimension_.row; ++row) {
			data_[row] = new K[dimension_.column];
			for (size_t column = 0; column < dimension_.column; ++column) {
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

	// GETTERS

	dimension_t get_dimension() const {
		return dimension_;
	}

	// METHODS

	bool isSquare() const {
		return (dimension_.row == dimension_.column);
	}

	void add(Matrix<K> const & operand) {
		if (operand.get_dimension() != dimension_) {
			throw (MatrixException("Matrix of different dimension"));
		}
		foreach([&operand](K& element, size_t row, size_t column) {
			element += operand[row][column];
		});
	}

	void sub(Matrix<K> const & operand) {
		if (operand.get_dimension() != dimension_) {
			throw (MatrixException("Matrix of different dimension"));
		}
		foreach([&operand](K& element, size_t row, size_t column) {
			element -= operand[row][column];
		});
	}

	void scale(K const & scalar) {
		foreach([&scalar](K& element) {
			element *= scalar;
		});
	}

	template <typename Function>
	auto foreach(Function f) -> std::enable_if_t<std::is_invocable_v<Function, K&>> {
		for (size_t row = 0; row < dimension_.row; ++row) {
			for (size_t column = 0; column < dimension_.column; ++column) {
				f(data_[row][column]);
			}
		}
	}

	template <typename Function>
	auto foreach(Function f) -> std::enable_if_t<std::is_invocable_v<Function, K&, size_t&, size_t&>> {
		for (size_t row = 0; row < dimension_.row; ++row) {
			for (size_t column = 0; column < dimension_.column; ++column) {
				f(data_[row][column], row, column);
			}
		}
	}

	Vector<K> to_vector() {
		if (dimension_.column != 1) {
			throw MatrixException("Cannot convert to a vector");
		}
		Vector<K> vector(dimension_.row);

		for (size_t row = 0; row < dimension_.row; ++row) {
			vector[row] = data_[row][0];
		}
		return vector;
	}

	// EXCEPTIONS

	class MatrixException : public std::exception {
	 private:
		std::string error_message_;
	 public:
		explicit MatrixException(std::string  message) : error_message_(std::move(message)) {}

		char const * what() const noexcept override {
			return error_message_.c_str();
		}
	};
};

template <typename K>
std::ostream& operator<<(std::ostream& os, const Matrix<K>& matrix) {
	for (size_t row = 0; row < matrix.get_dimension().row ; ++row) {
		os << '[';
		for (size_t column = 0; column < matrix.get_dimension().column; column++) {
			os << matrix[row][column] ;
			if (column + 1 < matrix.get_dimension().column) {
				os << ", ";
			}
		}
		os << ']' << std::endl;
	}
	os << std::flush;
	return os;
}

#endif
