#pragma once

#include <iostream>
#include <fstream>

#define TT template<typename T>

TT
class Matrix
{
private:
	T** matrix = nullptr;
	size_t rows = 0;
	size_t columns = 0;

	void resize(size_t oldRows, size_t oldColumns);

	void copyFrom(const Matrix& other);
	void moveFrom(Matrix&& other) noexcept;
	void free();

public:
	Matrix();
	Matrix(size_t rows, size_t columns);

	Matrix(const Matrix& other);
	Matrix& operator=(const Matrix& other);

	Matrix(Matrix&& other) noexcept;
	Matrix& operator=(Matrix&& other) noexcept;

	const size_t getRows() const;
	const size_t getColumns() const;

	const T& getAt(size_t x, size_t y) const;
	void setAt(size_t x, size_t y, const T& element);

	Matrix& operator+=(const Matrix& other);
	Matrix& operator-=(const Matrix& other);

	Matrix& operator*=(const Matrix& other);

	TT
		friend Matrix operator+(const Matrix& lhs, const Matrix& rhs);

	TT
		friend Matrix operator-(const Matrix& lhs, const Matrix& rhs);

	TT
		friend Matrix operator*(const Matrix& lhs, const Matrix& rhs);

	TT
		friend bool operator==(const Matrix& lhs, const Matrix& rhs);

	TT
		friend bool operator!=(const Matrix& lhs, const Matrix& rhs);

	TT
		friend std::istream& operator>>(std::istream& is, Matrix<T>& matrix);

	TT
		friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix);

	void transpose();

	~Matrix() noexcept;
};

TT
Matrix<T>::Matrix() : Matrix(2, 2) {}

TT
Matrix<T>::Matrix(size_t rows, size_t columns) : rows(rows), columns(columns)
{
	this->matrix = new T * [this->rows];
	for (size_t i = 0; i < this->rows; i++)
		this->matrix[i] = new T[this->columns]{ 0 };
}

TT
Matrix<T>::Matrix(const Matrix<T>& other)
{
	copyFrom(other);
}

TT
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

TT
Matrix<T>::Matrix(Matrix<T>&& other) noexcept
{
	moveFrom(std::move(other));
}

TT
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

TT
const size_t Matrix<T>::getRows() const
{
	return this->rows;
}

TT
const size_t Matrix<T>::getColumns() const
{
	return this->columns;
}

TT
const T& Matrix<T>::getAt(size_t x, size_t y) const
{
	if (x >= getRows() || y >= getColumns())
		throw std::out_of_range("Invalid index!");

	return this->matrix[x][y];
}

TT
void Matrix<T>::setAt(size_t x, size_t y, const T& element)
{
	if (x >= getRows() || y >= getColumns())
		throw std::out_of_range("Invalid index!");

	this->matrix[x][y] = element;
}

TT
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& other)
{
	if (getRows() != other.getRows() || getColumns() != other.getColumns())
		throw std::out_of_range("Invalid dimensions!");

	for (size_t i = 0; i < getRows(); i++)
		for (size_t j = 0; j < getColumns(); j++)
			this->matrix[i][j] += other.matrix[i][j];
}

TT
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& other)
{
	if (getRows() != other.getRows() || getColumns() != other.getColumns())
		throw std::out_of_range("Invalid dimensions!");

	for (size_t i = 0; i < getRows(); i++)
		for (size_t j = 0; j < getColumns(); j++)
			this->matrix[i][j] -= other.matrix[i][j];
}

TT
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& other)
{
	if (getColumns() != other.getRows())
		throw std::out_of_range("Invalid dimensions!");

	T** newMatrix = new T * [this->rows];

	for (size_t i = 0; i < getRows(); i++)
	{
		newMatrix[i] = new T[other.getColumns()]{ 0 };

		for (size_t j = 0; j < other.getColumns(); j++)
		{
			for (size_t k = 0; k < other.getRows(); k++)
			{
				newMatrix[i][j] += (this->matrix[i][k] * other.matrix[k][j]);
			}
		}
	}

	for (size_t i = 0; i < this->rows; i++)
		delete[] this->matrix[i];

	delete[] this->matrix;
	this->matrix = newMatrix;
}

TT
Matrix<T> operator+(const Matrix<T>& lhs, const Matrix<T>& rhs)
{
	Matrix<T> toReturn(lhs);
	toReturn += rhs;
	return toReturn;
}

TT
Matrix<T> operator-(const Matrix<T>& lhs, const Matrix<T>& rhs)
{
	Matrix<T> toReturn(lhs);
	toReturn -= rhs;
	return toReturn;
}

TT
Matrix<T> operator*(const Matrix<T>& lhs, const Matrix<T>& rhs)
{
	Matrix<T> toReturn(lhs);
	toReturn *= rhs;
	return toReturn;
}

TT
bool operator==(const Matrix<T>& lhs, const Matrix<T>& rhs)
{
	if (lhs.getRows() != rhs.getRows() || lhs.getColumns() != rhs.getColumns())
		return false;

	for (size_t i = 0; i < lhs.getRows(); i++)
		for (size_t j = 0; j < lhs.getColumns(); j++)
			if (lhs.getAt(i, j) != rhs.getAt(i, j))
				return false;

	return true;
}

TT
bool operator!=(const Matrix<T>& lhs, const Matrix<T>& rhs)
{
	return !(lhs == rhs);
}

TT
std::istream& operator>>(std::istream& is, Matrix<T>& matrix)
{
	size_t oldRows = matrix.getRows();
	size_t oldColumns = matrix.getColumns();

	is >> matrix.rows >> matrix.columns;
	if (oldRows != matrix.getRows() || oldColumns != matrix.getColumns())
		matrix.resize(oldRows, oldColumns);

	for (size_t i = 0; i < matrix.getRows(); i++)
		for (size_t j = 0; j < matrix.getColumns(); j++)
			is >> matrix.matrix[i][j];

	return is;
}

TT
std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix)
{
	for (size_t i = 0; i < matrix.getRows(); i++)
	{
		os << "[ ";

		for (size_t j = 0; j < matrix.getColumns(); j++)
		{
			os << matrix.getAt(i, j) << " ";
		}

		os << "]" << std::endl;
	}

	return os;
}

TT
void Matrix<T>::transpose()
{
	T** newMatrix = new T * [this->columns];
	for (size_t i = 0; i < this->columns; i++)
	{
		newMatrix[i] = new T[this->rows]{ 0 };

		for (size_t j = 0; j < this->rows; j++)
			newMatrix[i][j] = this->matrix[j][i];
	}

	for (size_t i = 0; i < this->rows; i++)
		delete[] this->matrix[i];

	delete[] this->matrix;
	this->matrix = newMatrix;
	std::swap(this->rows, this->columns);
}

TT
Matrix<T>::~Matrix() noexcept
{
	free();
}

TT
void Matrix<T>::resize(size_t oldRows, size_t oldColumns)
{
	T** newMatrix = new T * [getRows()];
	for (size_t i = 0; i < getRows(); i++)
	{
		newMatrix[i] = new T[getColumns()]{0};
	}

	for (size_t i = 0; i < oldRows; i++)
		delete[] this->matrix[i];

	delete[] this->matrix;
	this->matrix = newMatrix;
}

TT
void Matrix<T>::copyFrom(const Matrix<T>& other)
{
	this->rows = other.rows;
	this->columns = other.columns;

	this->matrix = new T * [this->rows];
	for (size_t i = 0; i < this->rows; i++)
	{
		this->matrix[i] = new T[this->columns];
		for (size_t j = 0; j < this->columns; j++)
			this->matrix[i][j] = other.matrix[i][j];
	}
}

TT
void Matrix<T>::moveFrom(Matrix&& other) noexcept
{
	this->matrix = other.matrix;
	this->rows = other.rows;
	this->columns = other.columns;

	other.matrix = nullptr;
	other.rows = other.columns = 0;
}

TT
void Matrix<T>::free()
{
	for (size_t i = 0; i < this->rows; i++)
		delete[] this->matrix[i];

	delete[] this->matrix;
	this->matrix = nullptr;
	this->rows = this->columns = 0;
}