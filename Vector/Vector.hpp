#pragma once

#include <iostream>
#include <fstream>

#define TT template<typename T>

TT
class Vector
{
private:
	T* data = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	Vector(size_t newSize);
	void resize(size_t newCapacity);

	const unsigned int getNextPowerOfTwo(unsigned int n) const;
	const unsigned int allocateCapacity(unsigned int n) const;

	void copyFrom(const Vector& other);
	void moveFrom(Vector&& other) noexcept;
	void free();

public:
	Vector();

	Vector(const Vector<T>& other);
	Vector<T>& operator=(const Vector<T>& other);

	Vector(Vector<T>&& other) noexcept;
	Vector<T>& operator=(Vector<T>&& other) noexcept;

	const size_t getSize() const;
	const size_t getCapacity() const;

	void push_back(const T& element);
	void push_back(T&& element);

	void pop_back();

	void insert(const T& element, size_t index);
	void insert(T&& element, size_t index);

	void remove(size_t index);

	const bool isEmpty() const;

	void clear();

	const T& operator[](size_t index) const;
	T& operator[](size_t index);

	TT
	friend std::istream& operator>>(std::istream& is, Vector<T>& vector);

	TT
	friend std::ostream& operator<<(std::ostream& os, const Vector<T>& vector);

	~Vector() noexcept;
};

TT
Vector<T>::Vector() : Vector(4) {}

TT
Vector<T>::Vector(size_t newSize) : size(0)
{
	this->capacity = allocateCapacity(newSize);
	this->data = new T[this->capacity];
}

TT
Vector<T>::Vector(const Vector<T>& other)
{
	copyFrom(other);
}

TT
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

TT
Vector<T>::Vector(Vector<T>&& other) noexcept
{
	moveFrom(std::move(other));
}

TT
Vector<T>& Vector<T>::operator=(Vector<T>&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

TT
inline const size_t Vector<T>::getSize() const
{
	return this->size;
}

TT
inline const size_t Vector<T>::getCapacity() const
{
	return this->capacity;
}

TT
void Vector<T>::push_back(const T& element)
{
	if (getSize() >= getCapacity())
		resize(getCapacity() * 2);

	this->data[this->size++] = element;
}

TT
void Vector<T>::push_back(T&& element)
{
	if (getSize() >= getCapacity())
		resize(getCapacity() * 2);

	this->data[this->size++] = std::move(element);
}

TT
void Vector<T>::pop_back()
{
	if (getSize())
		this->size--;
	else
		return;

	if ((getSize() * 4) <= getCapacity() && getCapacity() > 1)
		resize(getCapacity() / 2);
}

TT
void Vector<T>::insert(const T& element, size_t index)
{
	if (index >= getSize()) return;

	this->data[index] = element;
}

TT
void Vector<T>::insert(T&& element, size_t index)
{
	if (index >= getSize()) return;

	this->data[index] = std::move(element);
}

TT
void Vector<T>::remove(size_t index)
{
	if (index >= getSize()) return;

	if (getSize())
		this->size--;
	else
		return;

	for (size_t i = index; i < getSize(); i++)
	{
		this->data[i] = this->data[i + 1];
	}

	// std::swap(this->data[index], this->data[getSize()]);
}

TT
const bool Vector<T>::isEmpty() const
{
	return getSize() == 0;
}

TT
void Vector<T>::clear()
{
	delete[] this->data;

	this->data = nullptr;
	this->size = 0;
}

TT
const T& Vector<T>::operator[](size_t index) const
{
	return this->data[index];
}

TT
T& Vector<T>::operator[](size_t index)
{
	return this->data[index];
}

TT
std::istream& operator>>(std::istream& is, Vector<T>& vector)
{
	is >> vector.size;
	vector.resize(vector.allocateCapacity(vector.getSize()));

	for (size_t i = 0; i < vector.getSize(); i++)
	{
		is >> vector.data[i];
	}

	return is;
}

TT
std::ostream& operator<<(std::ostream& os, const Vector<T>& vector)
{
	os << "[ ";
	for (size_t i = 0; i < vector.getSize(); i++)
	{
		os << vector.data[i] << " ";
	}
	os << "]";

	return os;
}

TT
Vector<T>::~Vector() noexcept
{
	free();
}

TT
void Vector<T>::resize(size_t newCapacity)
{
	T* newData = new T[newCapacity];
	for (size_t i = 0; i < getSize(); i++)
	{
		newData[i] = this->data[i];
	}

	delete[] this->data;
	this->data = newData;
	this->capacity = newCapacity;
}

TT
void Vector<T>::copyFrom(const Vector<T>& other)
{
	this->size = other.size;
	this->capacity = other.capacity;

	this->data = new T[this->capacity];
	for (size_t i = 0; i < this->capacity; i++)
	{
		this->data[i] = other.data[i];
	}
}

TT
void Vector<T>::moveFrom(Vector<T>&& other) noexcept
{
	this->data = other.data;
	this->size = other.size;
	this->capacity = other.capacity;

	other.data = nullptr;
	other.size = other.capacity = 0;
}

TT
void Vector<T>::free()
{
	delete[] this->data;

	this->data = nullptr;
	this->size = this->capacity = 0;
}

TT
inline const unsigned int Vector<T>::getNextPowerOfTwo(unsigned int n) const
{
	if (n == 0) return 1;

	while (n & (n - 1))
		n &= (n - 1);

	return n << 1;
}

TT
inline const unsigned int Vector<T>::allocateCapacity(unsigned int n) const
{
	return std::max(getNextPowerOfTwo(n + 1), 8u);
}