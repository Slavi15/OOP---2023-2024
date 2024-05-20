#pragma once

#include <iostream>

#define TT template<typename T>

TT
class Queue
{
private:
	T* data = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	size_t get = 0;
	size_t put = 0;

	Queue(size_t newSize);
	void resize(size_t newCapacity);

	const unsigned int getNextPowerOfTwo(unsigned int n) const;
	const unsigned int allocateCapacity(unsigned int size) const;

	void copyFrom(const Queue& other);
	void moveFrom(Queue&& other) noexcept;
	void free();

public:
	Queue();

	Queue(const Queue& other);
	Queue& operator=(const Queue& other);

	Queue(Queue&& other) noexcept;
	Queue& operator=(Queue&& other) noexcept;

	const size_t getSize() const;
	const size_t getCapacity() const;

	void push(const T& element);
	void push(T&& element);

	const T& peek() const;

	void pop();

	const bool isEmpty() const;

	~Queue() noexcept;
};

TT
Queue<T>::Queue() : Queue(4) {}

TT
Queue<T>::Queue(size_t newSize) : size(0)
{
	this->capacity = allocateCapacity(newSize);
	this->data = new T[this->capacity];
}

TT
Queue<T>::Queue(const Queue<T>& other)
{
	copyFrom(other);
}

TT
Queue<T>& Queue<T>::operator=(const Queue<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

TT
Queue<T>::Queue(Queue<T>&& other) noexcept
{
	moveFrom(std::move(other));
}

TT
Queue<T>& Queue<T>::operator=(Queue<T>&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

TT
const size_t Queue<T>::getSize() const
{
	return this->size;
}

TT
const size_t Queue<T>::getCapacity() const
{
	return this->capacity;
}

TT
void Queue<T>::push(const T& element)
{
	if (getSize() >= getCapacity())
		resize(getCapacity() * 2);

	this->data[put] = element;
	(++put) %= getCapacity();
	this->size++;
}

TT
void Queue<T>::push(T&& element)
{
	if (getSize() >= getCapacity())
		resize(getCapacity() * 2);

	this->data[put] = std::move(element);
	(++put) %= getCapacity();
	this->size++;
}

TT
const T& Queue<T>::peek() const
{
	return this->data[get];
}

TT
void Queue<T>::pop()
{
	if (isEmpty())
		throw std::logic_error("Already empty!");

	(++get) %= getCapacity();
	this->size--;

	if (getSize() * 4 <= getCapacity() && getCapacity() > 1)
		resize(getCapacity() / 2);
}

TT
const bool Queue<T>::isEmpty() const
{
	return getSize() == 0;
}

TT
Queue<T>::~Queue() noexcept
{
	free();
}

TT
void Queue<T>::resize(size_t newCapacity)
{
	T* newData = new T[newCapacity];
	for (size_t i = 0; i < getSize(); i++)
	{
		newData[i] = this->data[get];
		(++get) %= getCapacity();
	}

	delete[] this->data;
	this->data = newData;
	this->capacity = newCapacity;

	this->get = 0;
	this->put = this->size;
}

TT
const unsigned int Queue<T>::getNextPowerOfTwo(unsigned int n) const
{
	if (n == 0) return 1;

	while (n & (n - 1))
		n &= (n - 1);

	return n << 1;
}

TT
const unsigned int Queue<T>::allocateCapacity(unsigned int size) const
{
	return std::max(getNextPowerOfTwo(size + 1), 8u);
}

TT
void Queue<T>::copyFrom(const Queue<T>& other)
{
	this->size = other.size;
	this->capacity = other.capacity;

	this->get = other.get;
	this->put = other.put;

	this->data = new T[this->capacity];
	for (size_t i = 0; i < this->capacity; i++)
		this->data[i] = other.data[i];
}

TT
void Queue<T>::moveFrom(Queue<T>&& other) noexcept
{
	this->data = other.data;

	this->size = other.size;
	this->capacity = other.capacity;

	this->get = other.get;
	this->put = other.put;

	other.data = nullptr;
	other.size = other.capacity = other.get = other.put = 0;
}

TT
void Queue<T>::free()
{
	delete[] this->data;

	this->data = nullptr;
	this->size = this->capacity = this->get = this->put = 0;
}