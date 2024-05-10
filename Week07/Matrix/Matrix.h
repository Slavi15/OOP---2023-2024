#pragma once

#include <iostream>
#include <fstream>

#define MIN_DIMENSIONS 2

class Matrix
{
private:
	int** _matrix = nullptr;
	size_t _rows = 0;
	size_t _columns = 0;

	mutable bool isModified = true;
	mutable bool isEmpty = false;

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

	Matrix& operator+=(const Matrix& other);
	Matrix& operator-=(const Matrix& other);

	Matrix& operator*=(const Matrix& other);
	Matrix& operator*=(int scalar);

	const int* const operator[](size_t index) const;
	int* operator[](size_t index);

	friend Matrix operator+(const Matrix& lhs, const Matrix& rhs);
	friend Matrix operator-(const Matrix& lhs, const Matrix& rhs);

	friend Matrix operator*(const Matrix& lhs, const Matrix& rhs);
	friend Matrix operator*(const Matrix& lhs, int scalar);

	friend const bool operator==(const Matrix& lhs, const Matrix& rhs);
	friend const bool operator!=(const Matrix& lhs, const Matrix& rhs);

	operator bool() const;

	friend std::istream& operator>>(std::istream& is, Matrix& mtx);
	friend std::ostream& operator<<(std::ostream& os, const Matrix& mtx);

	~Matrix() noexcept;
};