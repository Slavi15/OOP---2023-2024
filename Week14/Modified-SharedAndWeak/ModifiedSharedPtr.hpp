#pragma once

#include <iostream>

#define TT template <typename T, size_t N>

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

	void copyFrom(const SharedPtr<T, N>& other);
	void moveFrom(SharedPtr<T, N>&& other) noexcept;
	void free();

public:
	SharedPtr();
	SharedPtr(T* ptr);

	SharedPtr(const SharedPtr<T, N>& other);
	SharedPtr& operator=(const SharedPtr<T, N>& other);

	SharedPtr(SharedPtr<T, N>&& other) noexcept;
	SharedPtr& operator=(SharedPtr<T, N>&& other) noexcept;

	const T* operator->() const;
	T* operator->();

	const T& operator*() const;
	T& operator*();

	operator bool() const;

	~SharedPtr() noexcept;
};

TT
SharedPtr<T, N>::SharedPtr() = default;

TT
SharedPtr<T, N>::SharedPtr(T* ptr) : ptr(ptr)
{
	if (this->ptr)
	{
		this->counter = new Counter();
		counter->addSharedPtr();
	}
}

TT
SharedPtr<T, N>::SharedPtr(const SharedPtr<T, N>& other)
{
	copyFrom(other);
}

TT
SharedPtr<T, N>& SharedPtr<T, N>::operator=(const SharedPtr<T, N>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

TT
SharedPtr<T, N>::SharedPtr(SharedPtr<T, N>&& other) noexcept
{
	moveFrom(std::move(other));
}

TT
SharedPtr<T, N>& SharedPtr<T, N>::operator=(SharedPtr<T, N>&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

TT
const T* SharedPtr<T, N>::operator->() const
{
	return this->ptr;
}

TT
T* SharedPtr<T, N>::operator->()
{
	return this->ptr;
}

TT
const T& SharedPtr<T, N>::operator*() const
{
	if (this->ptr == nullptr)
		throw std::runtime_error("nullptr!");

	return *this->ptr;
}

TT
T& SharedPtr<T, N>::operator*()
{
	if (this->ptr == nullptr)
		throw std::runtime_error("nullptr!");

	return *this->ptr;
}

TT
SharedPtr<T, N>::operator bool() const
{
	return this->ptr != nullptr;
}

TT
SharedPtr<T, N>::~SharedPtr() noexcept
{
	free();
}

TT
void SharedPtr<T, N>::copyFrom(const SharedPtr<T, N>& other)
{
	this->ptr = other.ptr;
	this->counter = other.counter;

	if (this->counter && counter->useCount < N)
		counter->addSharedPtr();
	else
		throw std::runtime_error("Cannot make a shared ptr of more than N instances!");
}

TT
void SharedPtr<T, N>::moveFrom(SharedPtr<T, N>&& other) noexcept
{
	this->ptr = other.ptr;
	this->counter = other.counter;

	other.ptr = nullptr;
	other.counter = nullptr;
}

TT
void SharedPtr<T, N>::free()
{
	if (this->ptr == nullptr && this->counter == nullptr)
		return;

	counter->removeSharedPtr();

	if (counter->useCount == 0)
		delete this->ptr;

	if (counter->weakCount == 0)
		delete this->counter;
}
