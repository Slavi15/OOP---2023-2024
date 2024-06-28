#pragma once

#include <iostream>

#define TT template <typename T>

struct Counter
{
	size_t useCount = 0;
	size_t weakCount = 0;

	void addSharedPtr()
	{
		useCount++;

		if (useCount == 1)
			weakCount++;
	}

	void removeSharedPtr()
	{
		useCount--;

		if (useCount == 0)
			weakCount--;
	}

	void addWeakPtr()
	{
		weakCount++;
	}

	void removeWeakPtr()
	{
		weakCount--;
	}
};

TT
class SharedPtr
{
private:
	TT
		friend class WeakPtr;

	T* ptr = nullptr;
	Counter* counter = nullptr;

	void copyFrom(const SharedPtr<T>& other);
	void moveFrom(SharedPtr<T>&& other) noexcept;
	void free();

public:
	SharedPtr();
	SharedPtr(T* ptr);

	SharedPtr(const SharedPtr<T>& other);
	SharedPtr& operator=(const SharedPtr<T>& other);

	SharedPtr(SharedPtr<T>&& other) noexcept;
	SharedPtr& operator=(SharedPtr<T>&& other) noexcept;

	const T* operator->() const;
	T* operator->();

	const T& operator*() const;
	T& operator*();

	bool isInitialized() const;
	operator bool() const;

	~SharedPtr() noexcept;
};

TT
SharedPtr<T>::SharedPtr() = default;

TT
SharedPtr<T>::SharedPtr(T* ptr)
{
	this->ptr = ptr;

	if (this->ptr)
	{
		this->counter = new Counter();
		counter->addSharedPtr();
	}
}

TT
SharedPtr<T>::SharedPtr(const SharedPtr<T>& other)
{
	copyFrom(other);
}

TT
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

TT
SharedPtr<T>::SharedPtr(SharedPtr<T>&& other) noexcept
{
	moveFrom(std::move(other));
}

TT
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<T>&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

TT
const T* SharedPtr<T>::operator->() const
{
	return this->ptr;
}

TT
T* SharedPtr<T>::operator->()
{
	return this->ptr;
}

TT
const T& SharedPtr<T>::operator*() const
{
	if (this->ptr == nullptr)
		throw std::runtime_error("nullptr!"); // !!! IMPORTANT !!!

	return *this->ptr;
}

TT
T& SharedPtr<T>::operator*()
{
	if (this->ptr == nullptr)
		throw std::runtime_error("nullptr!"); // !!! IMPORTANT !!!

	return *this->ptr;
}

TT
bool SharedPtr<T>::isInitialized() const
{
	return this->ptr != nullptr;
}

TT
SharedPtr<T>::operator bool() const
{
	return this->ptr != nullptr;
}

TT
SharedPtr<T>::~SharedPtr() noexcept
{
	free();
}

TT
void SharedPtr<T>::copyFrom(const SharedPtr<T>& other)
{
	this->ptr = other.ptr;
	this->counter = other.counter;

	if (this->counter)
		counter->addSharedPtr();
}

TT
void SharedPtr<T>::moveFrom(SharedPtr<T>&& other) noexcept
{
	this->ptr = other.ptr;
	this->counter = other.counter;

	other.ptr = nullptr;
	other.counter = nullptr;
}

TT
void SharedPtr<T>::free()
{
	if (this->ptr == nullptr && this->counter == nullptr)
		return;

	counter->removeSharedPtr();

	if (counter->useCount == 0)
		delete this->ptr;

	if (counter->weakCount == 0)
		delete this->counter;
}
