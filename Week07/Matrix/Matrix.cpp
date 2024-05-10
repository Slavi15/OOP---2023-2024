#include "Matrix.h"

Matrix::Matrix() : Matrix(MIN_DIMENSIONS, MIN_DIMENSIONS) {}

Matrix::Matrix(size_t rows, size_t columns)
{
	this->_rows = rows;
	this->_columns = columns;

	this->_matrix = new int* [this->_rows];
	for (size_t i = 0; i < this->_rows; i++)
		this->_matrix[i] = new int[this->_columns] { 0 };
}

Matrix::Matrix(const Matrix& other)
{
	copyFrom(other);
}

Matrix& Matrix::operator=(const Matrix& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Matrix::Matrix(Matrix&& other) noexcept
{
	moveFrom(std::move(other));
}

Matrix& Matrix::operator=(Matrix&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

Matrix& Matrix::operator+=(const Matrix& other)
{
	if (this->_rows != other._rows || this->_columns != other._columns)
		throw std::logic_error("Cannot add two matrices with different dimensions!");

	isModified = true;

	for (size_t i = 0; i < this->_rows; i++)
		for (size_t j = 0; j < this->_columns; j++)
			this->_matrix[i][j] += other._matrix[i][j];

	return *this;
}

Matrix& Matrix::operator-=(const Matrix& other)
{
	if (this->_rows != other._rows || this->_columns != other._columns)
		throw std::logic_error("Cannot subtract two matrices with different dimensions!");

	isModified = true;

	for (size_t i = 0; i < this->_rows; i++)
		for (size_t j = 0; j < this->_columns; j++)
			this->_matrix[i][j] -= other._matrix[i][j];

	return *this;
}

Matrix& Matrix::operator*=(const Matrix& other)
{
	if (this->_columns != other._rows)
		throw std::logic_error("Cannot multiply matrices with incompatible dimensions!");

	isModified = true;

	int** result = new int* [this->_rows] { 0 };

	for (size_t i = 0; i < this->_rows; i++)
	{
		result[i] = new int[other._columns] { 0 };

		for (size_t j = 0; j < other._columns; j++)
		{
			for (size_t k = 0; k < other._rows; k++)
				result[i][j] += (this->_matrix[i][k] * other._matrix[k][j]);
		}
	}

	for (size_t i = 0; i < this->_rows; i++)
		delete[] this->_matrix[i];
	delete[] this->_matrix;

	this->_matrix = result;
	this->_columns = other._columns;

	return *this;
}

Matrix& Matrix::operator*=(int scalar)
{
	isModified = true;

	for (size_t i = 0; i < this->_rows; i++)
		for (size_t j = 0; j < this->_columns; j++)
			this->_matrix[i][j] *= scalar;

	return *this;
}

const int* const Matrix::operator[](size_t index) const
{
	return this->_matrix[index];
}

int* Matrix::operator[](size_t index)
{
	isModified = true;
	return this->_matrix[index];
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs)
{
	Matrix toReturn(lhs);
	toReturn += rhs;
	return toReturn;
}

Matrix operator-(const Matrix& lhs, const Matrix& rhs)
{
	Matrix toReturn(lhs);
	toReturn -= rhs;
	return toReturn;
}

Matrix operator*(const Matrix& lhs, const Matrix& rhs)
{
	Matrix toReturn(lhs);
	toReturn *= rhs;
	return toReturn;
}

Matrix operator*(const Matrix& lhs, int scalar)
{
	Matrix toReturn(lhs);
	toReturn *= scalar;
	return toReturn;
}

const bool operator==(const Matrix& lhs, const Matrix& rhs)
{
	if (lhs._rows != rhs._rows || lhs._columns != rhs._columns)
		throw std::logic_error("Invalid dimensions!");

	for (size_t i = 0; i < lhs._rows; i++)
		for (size_t j = 0; j < lhs._columns; j++)
			if (lhs._matrix[i][j] != rhs._matrix[i][j])
				return false;

	return true;
}

const bool operator!=(const Matrix& lhs, const Matrix& rhs)
{
	return !(lhs == rhs);
}

Matrix::operator bool() const
{
	if (!isModified)
		return isEmpty;

	isModified = false;

	for (size_t i = 0; i < this->_rows; i++)
		for (size_t j = 0; j < this->_columns; j++)
			if (this->_matrix[i][j] != 0)
			{
				isEmpty = false;
				return isEmpty;
			}

	isEmpty = true;
	return isEmpty;
}

std::istream& operator>>(std::istream& is, Matrix& mtx)
{
	for (size_t i = 0; i < mtx._rows; i++)
		for (size_t j = 0; j < mtx._columns; j++)
			is >> mtx._matrix[i][j];

	return is;
}

std::ostream& operator<<(std::ostream& os, const Matrix& mtx)
{
	for (size_t i = 0; i < mtx._rows; i++)
	{
		os << "[ ";

		for (size_t j = 0; j < mtx._columns; j++)
			os << mtx._matrix[i][j] << " ";

		os << "]" << std::endl;
	}

	return os;
}

Matrix::~Matrix()
{
	free();
}

void Matrix::copyFrom(const Matrix& other)
{
	this->_rows = other._rows;
	this->_columns = other._columns;

	this->_matrix = new int* [this->_rows];
	for (size_t i = 0; i < this->_rows; i++)
		this->_matrix[i] = new int[this->_columns] { 0 };

	isModified = true;
}

void Matrix::moveFrom(Matrix&& other) noexcept
{
	this->_rows = other._rows;
	this->_columns = other._columns;
	this->_matrix = other._matrix;

	other._matrix = nullptr;
	other._rows = other._columns = 0;

	isModified = true;
}

void Matrix::free()
{
	for (size_t i = 0; i < this->_rows; i++)
		delete[] this->_matrix[i];

	delete[] this->_matrix;
}