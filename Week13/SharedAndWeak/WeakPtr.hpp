#pragma once

#include "SharedPtr.hpp"

#define TT template <typename T>

TT
class WeakPtr
{
private:
	T* ptr = nullptr;
	Counter* counter = nullptr;

	void copyFrom(const WeakPtr<T>& other);
	void moveFrom(WeakPtr<T>&& other) noexcept;
	void free();

public:
	WeakPtr();
	WeakPtr(SharedPtr<T>& ptr);

	WeakPtr(const WeakPtr<T>& other);
	WeakPtr& operator=(const WeakPtr<T>& other);

	WeakPtr(WeakPtr<T>&& other) noexcept;
	WeakPtr& operator=(WeakPtr<T>&& other) noexcept;

	SharedPtr<T> lock() const;

	bool expired() const;

	~WeakPtr() noexcept;
};

TT
WeakPtr<T>::WeakPtr() = default;

TT
WeakPtr<T>::WeakPtr(SharedPtr<T>& other)
{
	this->ptr = other.ptr;
	this->counter = other.counter;

	if (this->counter)
		counter->addWeakPtr();
}

TT
WeakPtr<T>::WeakPtr(const WeakPtr<T>& other)
{
	copyFrom(other);
}

TT
WeakPtr<T>& WeakPtr<T>::operator=(const WeakPtr<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

TT
WeakPtr<T>::WeakPtr(WeakPtr<T>&& other) noexcept
{
	moveFrom(std::move(other));
}

TT
WeakPtr<T>& WeakPtr<T>::operator=(WeakPtr<T>&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

TT
bool WeakPtr<T>::expired() const
{
	return this->counter && counter->useCount == 0;
}

TT
SharedPtr<T> WeakPtr<T>::lock() const
{
	if (expired())
		return SharedPtr<T>();
	else
		return SharedPtr<T>(this->ptr);
}

TT
WeakPtr<T>::~WeakPtr() noexcept
{
	free();
}

TT
void WeakPtr<T>::copyFrom(const WeakPtr<T>& other)
{
	this->ptr = other.ptr;
	this->counter = other.counter;

	if (counter)
		counter->addWeakPtr();
}

TT
void WeakPtr<T>::moveFrom(WeakPtr<T>&& other) noexcept
{
	this->ptr = other.ptr;
	this->counter = other.counter;

	other.ptr = nullptr;
	other.counter = nullptr;
}

TT
void WeakPtr<T>::free()
{
	if (this->ptr == nullptr && this->counter == nullptr)
		return;

	counter->removeWeakPtr();

	// weak_count = weak_ptr + 1 / 0
	// 1 => use_count >= 1
	// 0 => use_count = 0

	if (counter->weakCount == 0) // useCount = 0
		delete counter;
}
