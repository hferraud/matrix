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

		bool operator!=(struct dimension_s const & other) const {
			return !(*this == other);
		}
	} dimension_t;

 private:
	dimension_t	dimension_;
	K**		data_;

	void assert_dimension_match(Matrix<K> const & other) const {
		if (other.get_dimension() != dimension_) {
			throw MatrixException("Matrix dimension mismatch");
		}
	}

 public:

	// CONSTRUCTORS

	explicit Matrix(): data_(nullptr) {
		dimension_.row = 0;
		dimension_.column = 0;
	}

	explicit Matrix(size_t row, size_t column) {
		dimension_.row = row;
		dimension_.column = column;
		data_ = new K*[row];
		for (size_t i = 0; i < row; ++i) {
			data_[i] = new K[column];
		}
		foreach([](K& element) {
			element = K();
		});
	}

	explicit Matrix(dimension_t dimension) : Matrix(dimension.row, dimension.column) {}

	Matrix (Matrix<K> const & other) {
		data_ = nullptr;
		*this = other;
	}

	Matrix (std::initializer_list<std::initializer_list<K>> entries) {
		data_ = nullptr;
		*this = entries;
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

	Matrix<K>& operator=(std::initializer_list<std::initializer_list<K>> entries) {
		if (data_ != nullptr) {
			for (size_t row = 0; row < dimension_.row; ++row) {
				delete[] data_[row];
			}
			delete[] data_;
		}
		dimension_.row = entries.size();
		dimension_.column = entries.begin()->size();
		data_ = new K*[dimension_.row];
		for (size_t i = 0; i < dimension_.row; ++i) {
			data_[i] = new K[dimension_.column];
			std::copy(
					entries.begin()[i].begin(),
					entries.begin()[i].end(),
					data_[i]);
		}
		return *this;
	}

	bool operator==(Matrix<K> const & rhs) const {
		for (size_t row = 0; row < rhs.dimension_.row; ++row) {
			for (size_t column = 0; column < rhs.dimension_.column; ++column) {
				if (data_[row][column] != rhs[row][column]) {
					return false;
				}
			}
		}
		return true;
	}

	K* operator[](size_t index) {
		return data_[index];
	}

	K const * operator[](size_t index) const {
		return data_[index];
	}

	Matrix<K> operator+(Matrix<K> const & rhs) const {
		assert_dimension_match(rhs);
		Matrix<K> result(dimension_);

		result.foreach([this, &rhs](K& element, size_t& row, size_t& column) {
			element = (*this)[row][column] + rhs[row][column];
		});
		return result;
	}

	Matrix<K> operator+=(Matrix<K> const & rhs) {
		assert_dimension_match(rhs);

		foreach([&rhs](K& element, size_t& row, size_t& column) {
			element += rhs[row][column];
		});
		return *this;
	}

	Matrix<K> operator-(Matrix<K> const & rhs) const {
		assert_dimension_match(rhs);
		Matrix<K> result(dimension_);

		result.foreach([this, &rhs](K& element, size_t& row, size_t& column) {
			element = (*this)[row][column] - rhs[row][column];
		});
		return result;
	}

	Matrix<K> operator-=(Matrix<K> const & rhs) {
		assert_dimension_match(rhs);

		foreach([&rhs](K& element, size_t& row, size_t& column) {
			element -= rhs[row][column];
		});
		return *this;
	}

	Matrix<K> operator*(K const & scalar) const {
		Matrix<K> result(dimension_);

		result.foreach([this, &scalar](K& element, size_t& row, size_t& column) {
			element = (*this)[row][column] * scalar;
		});
		return result;
	}

	Matrix<K> operator*=(K const & scalar) {
		foreach([&scalar](K& element) {
			element *= scalar;
		});
		return *this;
	}

	Vector<K> operator*(Vector<K> const & lhs) const {
		Vector<K> res(dimension_.row);

		for (size_t row = 0; row < dimension_.row; ++row) {
			for (size_t column = 0; column < dimension_.column; ++column) {
				res[row] = std::fma(data_[row][column], lhs[column], res[row]);
			}
		}
		return res;
	}

	Matrix<K> operator*(Matrix<K> const & lhs) const {
		Matrix<K> res(dimension_.row, lhs.dimension_.column);

		res.foreach([this, &lhs](K& element, size_t row, size_t column) {
			for (size_t i = 0; i < this->dimension_.column; ++i) {
				element = std::fma((*this)[row][i], lhs[i][column], element);
			}
		});
		return res;
	}

	Matrix<K> operator*=(Matrix<K> const & lhs) {
		if (!is_square()) {
			throw (MatrixException("Invalid operation"));
		}
		Matrix<K> rhs(*this);
		foreach([this, &rhs, &lhs](K& element, size_t row, size_t column) {
			this[row][column] = 0;
			for (size_t i = 0; i < this->dimension_.column; ++i) {
				this[row][column] = std::fma(rhs[row][i], lhs[i][column], this[row][column]);
			}
		});
	}

	// GETTERS

	dimension_t get_dimension() const {
		return dimension_;
	}

	// METHODS

	bool is_square() const {
		return (dimension_.row == dimension_.column);
	}

	void add(Matrix<K> const & operand) {
		*this += operand;
	}

	void sub(Matrix<K> const & operand) {
		*this -= operand;
	}

	void scale(K const & scalar) {
		*this *= scalar;
	}

	Vector<K> mul_vec(Vector<K> operand) const {
		return *this * operand;
	}

	Matrix<K> mul_mat(Matrix<K> operand) const {
		return *this * operand;
	}

	K trace() const {
		K result;

		for (size_t i = 0; i < dimension_.column; ++i) {
			result += data_[i][i];
		}
		return result;
	}

	Matrix<K> transpose() const {
		Matrix<K> res(dimension_.column, dimension_.row);

		res.foreach([this](K& element, size_t row, size_t column) {
			element = (*this)[column][row];
		});
		return res;
	}

	Matrix<K> row_echelon() const {
		Matrix<K> res(*this);
		size_t row = 0;
		size_t pivot_row;

		for (size_t column = 0; column < dimension_.column && row < dimension_.row; ++column) {
			pivot_row = res.find_pivot_row(row, column);
			if (res[pivot_row][column] == 0) {
				continue;
			}
			res.normalize_pivot_row(pivot_row, column);
			if (pivot_row != row) {
				res.swap_rows(pivot_row, row);
			}
			res.reduce_rows(row, column);
			++row;
		}
		return res;
	}

	K determinant() const {
//		std::cout << "Matrix:" << std::endl << *this << std::endl;
		if (dimension_.row == 1) {
			return data_[0][0];
		}
		if (dimension_.row == 2) {
			return det2();
		}
		K determinant = 0;
		for (size_t column = 0; column < dimension_.column; ++column) {
			determinant +=
					((column % 2) ? -1: 1) *
					data_[0][column] *
					minor(0, column).determinant();
		}
//		std::cout << "det: " << determinant << std::endl;
		return determinant;
	}

	K det2() const {
		return (data_[0][0] * data_[1][1] - data_[1][0] * data_[0][1]);
	}

	Matrix<K> minor(size_t minor_row, size_t minor_column) const {
		Matrix<K> res(dimension_.row - 1, dimension_.column - 1);
		res.foreach([&minor_row, &minor_column, this](K& element, size_t row, size_t column) {
			row = (row >= minor_row) ? row + 1 : row;
			column = (column >= minor_column) ? column + 1 : column;
			element = (*this)[row][column];
		});
		return res;
	}

	size_t find_pivot_row(size_t row, size_t column) const {
		size_t pivot_index = row;
		K pivot_abs_value = data_[row][column];
		K current_abs_value;

		for (size_t i = row + 1; i < dimension_.row; ++i) {
			current_abs_value = data_[i][column];
			current_abs_value = (current_abs_value > -current_abs_value) ?
				current_abs_value : -current_abs_value;
			if (current_abs_value > pivot_abs_value) {
				pivot_index = i;
				pivot_abs_value = current_abs_value;
			}
		}
		return pivot_index;
	}

	void normalize_pivot_row(size_t row, size_t column) {
		K divider = data_[row][column];
		for (size_t i = column; i < dimension_.column; ++i) {
			data_[row][i] /= divider;
		}
	}

	void swap_rows(size_t row_1, size_t row_2) {
		std::swap(data_[row_1], data_[row_2]);
	}

	void reduce_rows(size_t pivot_row, size_t pivot_column) {
		for (size_t row = 0; row < dimension_.row; ++row) {
			K factor = data_[row][pivot_column];
			if (row == pivot_row) {
				continue;
			}
			for (size_t column = 0; column < dimension_.column; ++column) {
				data_[row][column] = std::fma(data_[pivot_row][column], -factor, data_[row][column]);
			}
		}
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
