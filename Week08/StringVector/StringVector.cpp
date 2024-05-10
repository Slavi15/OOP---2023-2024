#include "StringVector.h"

StringVector::StringVector() : StringVector(4) {}

StringVector::StringVector(size_t newCapacity)
{
	this->capacity = getNextPowerOfTwo(newCapacity);
	this->data = new String[this->capacity];
}

const unsigned int StringVector::getNextPowerOfTwo(unsigned int n) const
{
	if (n == 0) return 1;

	while (n & (n - 1))
		n &= (n - 1);

	return n << 1;
}

const unsigned int StringVector::allocateCapacity(unsigned int n) const
{
	return std::max(getNextPowerOfTwo(n), 8u);
}

StringVector::StringVector(const StringVector& other)
{
	copyFrom(other);
}

StringVector& StringVector::operator=(const StringVector& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

StringVector::StringVector(StringVector&& other) noexcept
{
	moveFrom(std::move(other));
}

StringVector& StringVector::operator=(StringVector&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

const size_t StringVector::getSize() const
{
	return this->size;
}

const size_t StringVector::getCapacity() const
{
	return this->capacity;
}

void StringVector::push_back(const String& element)
{
	if (getSize() >= getCapacity())
		resize(getCapacity() * 2);

	this->data[this->size] = element;
	this->size++;
}

void StringVector::push_back(String&& element)
{
	if (getSize() >= getCapacity())
		resize(getCapacity() * 2);

	this->data[this->size] = std::move(element);
	this->size++;
}

void StringVector::pop_back()
{
	if (this->size)
		this->size--;
	else
		throw std::logic_error("Already empty!");

	if ((getSize() * 4) <= getCapacity() && getCapacity() >= 1)
		resize(getCapacity() / 2);
}

void StringVector::insert(const String& element, size_t index)
{
	if (index < 0 || index > getSize())
		throw std::out_of_range("Invalid index!");

	this->data[index] = element;
}

void StringVector::insert(String&& element, size_t index)
{
	if (index < 0 || index > getSize())
		throw std::out_of_range("Invalid index!");

	this->data[index] = std::move(element);
}

void StringVector::erase(size_t index)
{
	if (index < 0 || index > getSize())
		throw std::out_of_range("Invalid index!");

	if (this->size)
		this->size--;
	else
		throw std::logic_error("Already empty!");

	// First variant - keeping order!
	for (size_t i = index; i < getSize(); i++)
		this->data[i] = this->data[i + 1];
	// First variant

	// Second variant - faster!
	// std::swap(this->data[index], this->data[this->size]);
	// Second variant
}

const bool StringVector::empty() const
{
	return this->size == 0;
}

void StringVector::clear()
{
	free();
}

const String& StringVector::operator[](size_t index) const
{
	return this->data[index];
}

String& StringVector::operator[](size_t index)
{
	return this->data[index];
}

std::istream& operator>>(std::istream& is, StringVector& ref)
{
	is >> ref.size;
	ref.resize(ref.allocateCapacity(ref.getSize()));

	for (size_t i = 0; i < ref.getSize(); i++)
		is >> ref.data[i];

	return is;
}

std::ostream& operator<<(std::ostream& os, const StringVector& ref)
{
	os << "[ ";
	for (size_t i = 0; i < ref.getSize(); i++)
		os << ref.data[i] << " ";
	os << "]" << std::endl;

	return os;
}

StringVector::~StringVector() noexcept
{
	free();
}

void StringVector::resize(size_t newCapacity)
{
	String* newData = new String[newCapacity];

	for (size_t i = 0; i < this->size; i++)
		newData[i] = this->data[i];

	delete[] this->data;
	this->data = newData;
	this->capacity = newCapacity;
}

void StringVector::copyFrom(const StringVector& other)
{
	this->size = other.size;
	this->capacity = other.capacity;

	this->data = new String[this->capacity];
	for (size_t i = 0; i < this->size; i++)
		this->data[i] = other.data[i];
}

void StringVector::moveFrom(StringVector&& other) noexcept
{
	this->data = other.data;
	this->size = other.size;
	this->capacity = other.capacity;

	other.data = nullptr;
	other.size = other.capacity = 0;
}

void StringVector::free()
{
	delete[] this->data;

	this->data = nullptr;
	this->size = this->capacity = 0;
}