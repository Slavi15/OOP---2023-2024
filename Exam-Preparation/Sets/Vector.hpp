#pragma once

#include <iostream>

#define TT template <typename T>

TT
class Vector
{
private:
	T* data = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	Vector(size_t newSize);

	void resize(size_t newCap);

	unsigned int getNextPowerTwo(unsigned int n) const;
	unsigned int allocateCapacity(unsigned int n) const;

	void copyFrom(const Vector<T>& other);
	void moveFrom(Vector<T>&& other) noexcept;
	void free();

public:
	Vector();
	
	Vector(const Vector<T>& other);
	Vector& operator=(const Vector<T>& other);

	Vector(Vector<T>&& other) noexcept;
	Vector& operator=(Vector<T>&& other) noexcept;

	size_t getSize() const;
	size_t getCapacity() const;

	void push_back(const T& element);
	void push_back(T&& element);

	void pop_back();

	bool contains(const T& element) const;

	const T& operator[](size_t index) const;
	T& operator[](size_t index);

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
inline Vector<T>::Vector(const Vector<T>& other)
{
	copyFrom(other);
}

TT
inline Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

TT
inline Vector<T>::Vector(Vector<T>&& other)
{
	moveFrom(std::move(other));
}

TT
inline Vector<T>& Vector<T>::operator=(Vector<T>&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

TT
inline size_t Vector<T>::getSize() const
{
	return this->size;
}

TT
inline size_t Vector<T>::getCapacity() const
{
	return this->capacity;
}

TT
inline void Vector<T>::push_back(const T& element)
{
	if (getSize() >= getCapacity())
		resize(getCapacity() * 2);

	this->data[this->size++] = element;
}

TT
inline void Vector<T>::push_back(T&& element)
{
	if (getSize() >= getCapacity())
		resize(getCapacity() * 2);

	this->data[this->size++] = std::move(element);
}

TT
inline void Vector<T>::pop_back()
{
	if (getSize())
		this->size--;
	else
		return;

	if (getSize() * 4 <= getCapacity() && getCapacity() > 1)
		resize(getCapacity() / 2);
}

TT
inline bool Vector<T>::contains(const T& element) const
{
	for (size_t i = 0; i < getSize(); i++)
	{
		if (data[i] == element)
		{
			return true;
		}
	}

	return false;
}

TT
inline const T& Vector<T>::operator[](size_t index) const
{
	return this->data[index];
}

TT
inline T& Vector<T>::operator[](size_t index)
{
	return this->data[index];
}

TT
inline Vector<T>::~Vector() noexcept
{
	free();
}

TT
inline void Vector<T>::resize(size_t newCap)
{
	T* newData = new T[newCap];
	for (size_t i = 0; i < this->size; i++)
	{
		newData[i] = this->data[i];
	}

	delete[] this->data;
	this->data = newData;
	this->capacity = newCap;
}

TT
inline unsigned int Vector<T>::getNextPowerTwo(unsigned int n) const
{
	if (n == 0) return 1;

	while (n & (n - 1))
		n &= (n - 1);

	return n << 1;
}

TT
inline unsigned int Vector<T>::allocateCapacity(unsigned int n) const
{
	return std::max(getNextPowerTwo(n + 1), 8u);
}

TT
void Vector<T>::copyFrom(const Vector<T>& other)
{
	this->size = other.size;
	this->capacity = other.capacity;

	this->data = new T[this->capacity];
	for (size_t i = 0; i < this->capacity; i++)
		this->data[i] = other.data[i];
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
}
