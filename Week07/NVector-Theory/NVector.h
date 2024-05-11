#pragma once

#include <iostream>
#include <fstream>

class NVector
{
private:
	int* data = nullptr;
	size_t size = 0;

	void copyFrom(const NVector& other);
	void moveFrom(NVector&& other) noexcept;
	void free();

public:
	NVector();
	NVector(size_t size);
	NVector(const int* data, size_t size);

	NVector(const NVector& other);
	NVector& operator=(const NVector& other);

	NVector(NVector&& other) noexcept;
	NVector& operator=(NVector&& other) noexcept;

	const size_t getSize() const;

	NVector& operator+=(const NVector& other);
	NVector& operator-=(const NVector& other);

	NVector& operator*=(int scalar);

	const int& operator[](size_t index) const;
	int& operator[](size_t index);

	// vector size
	// ~  -  left-side operator when invoked
	const size_t operator~() const;

	// scalar product
	friend const size_t operator%(const NVector& lhs, const NVector& rhs);

	// adjacent
	friend const bool operator||(const NVector& lhs, const NVector& rhs);

	// perpendicular
	friend const bool operator|=(const NVector& lhs, const NVector& rhs);

	friend NVector operator+(const NVector& lhs, const NVector& rhs);
	friend NVector operator-(const NVector& lhs, const NVector& rhs);

	friend NVector operator*(const NVector& other, int scalar);
	friend NVector operator*(int scalar, const NVector& other);

	friend std::istream& operator>>(std::istream& is, NVector& ref);
	friend std::ostream& operator<<(std::ostream& os, const NVector& ref);

	~NVector() noexcept;
};