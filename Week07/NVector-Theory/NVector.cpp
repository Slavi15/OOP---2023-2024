#include "NVector.h"

NVector::NVector() : NVector(20) {}

NVector::NVector(size_t size)
{
	this->size = size;
	this->data = new int[this->size] { 0 };
}

NVector::NVector(const int* data, size_t size) : size(size)
{
	if (!data)
		throw std::runtime_error("NULLPTR!");

	this->data = new (std::nothrow) int[this->size];
	for (size_t i = 0; i < this->size; i++)
		this->data[i] = data[i];
}

NVector::NVector(const NVector& other)
{
	copyFrom(other);
}

NVector& NVector::operator=(const NVector& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

NVector::NVector(NVector&& other) noexcept
{
	moveFrom(std::move(other));
}

NVector& NVector::operator=(NVector&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

const size_t NVector::getSize() const
{
	return this->size;
}

NVector& NVector::operator+=(const NVector& other)
{
	if (getSize() != other.getSize())
		throw std::invalid_argument("Vectors should be of the same size!");

	for (size_t i = 0; i < getSize(); i++)
		this->data[i] += other.data[i];

	return *this;
}

NVector& NVector::operator-=(const NVector& other)
{
	if (getSize() != other.getSize())
		throw std::invalid_argument("Vectors should be of the same size!");

	for (size_t i = 0; i < getSize(); i++)
		this->data[i] -= other.data[i];

	return *this;
}

NVector& NVector::operator*=(int scalar)
{
	for (size_t i = 0; i < getSize(); i++)
		this->data[i] *= scalar;

	return *this;
}

const int& NVector::operator[](size_t index) const
{
	return this->data[index];
}

int& NVector::operator[](size_t index)
{
	return this->data[index];
}

const size_t NVector::operator~() const
{
	return this->size;
}

const bool operator||(const NVector& lhs, const NVector& rhs)
{
	if (lhs.getSize() != rhs.getSize())
		throw std::invalid_argument("Vectors should be of the same size!");

	double ratio = lhs[0] / rhs[0];

	for (size_t i = 1; i < lhs.getSize(); i++)
	{
		if (lhs[i] == 0 && rhs[i] == 0)
			continue;

		if (lhs[i] == 0 || rhs[i] == 0)
			return false;

		double currentRatio = lhs[i] / rhs[i];

		if (std::abs(ratio - currentRatio) > 1e-6)
			return false;
	}

	return true;
}

const size_t operator%(const NVector& lhs, const NVector& rhs)
{
	if (lhs.getSize() != rhs.getSize())
		throw std::invalid_argument("Vectors should be of the same size!");

	size_t result = 0;

	// lhs.getSize() == ~lhs
	for (size_t i = 0; i < lhs.getSize(); i++)
		result += (lhs[i] * rhs[i]);

	return result;
}

const bool operator|=(const NVector& lhs, const NVector& rhs)
{
	if (lhs.getSize() != rhs.getSize())
		throw std::invalid_argument("Vectors should be of the same size!");

	return (lhs % rhs) == 0;
}

NVector operator+(const NVector& lhs, const NVector& rhs)
{
	NVector toReturn(lhs);
	toReturn += rhs;
	return toReturn;
}

NVector operator-(const NVector& lhs, const NVector& rhs)
{
	NVector toReturn(lhs);
	toReturn -= rhs;
	return toReturn;
}

NVector operator*(const NVector& other, int scalar)
{
	NVector toReturn(other);
	toReturn *= scalar;
	return toReturn;
}

NVector operator*(int scalar, const NVector& other)
{
	NVector toReturn(other);
	toReturn *= scalar;
	return toReturn;
}

std::istream& operator>>(std::istream& is, NVector& ref)
{
	is >> ref.size;

	for (size_t i = 0; i < ref.getSize(); i++)
		is >> ref.data[i];

	return is;
}

std::ostream& operator<<(std::ostream& os, const NVector& ref)
{
	os << ref.getSize() << std::endl;

	os << "[ ";
	for (size_t i = 0; i < ref.getSize(); i++)
		os << ref.data[i] << ' ';
	os << "]";

	return os;
}

NVector::~NVector() noexcept
{
	free();
}

void NVector::copyFrom(const NVector& other)
{
	this->size = other.size;

	this->data = new int[this->size];
	for (size_t i = 0; i < this->size; i++)
		this->data[i] = other.data[i];
}

void NVector::moveFrom(NVector&& other) noexcept
{
	this->data = other.data;
	this->size = other.size;

	other.data = nullptr;
	other.size = 0;
}

void NVector::free()
{
	delete[] this->data;

	this->data = nullptr;
	this->size = 0;
}