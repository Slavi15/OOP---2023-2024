#pragma once

#include "ModifiedSharedPtr.hpp"

#define TT template <typename T, size_t N>

TT
class WeakPtr
{
private:
	T* ptr = nullptr;
	Counter* counter = nullptr;

	void copyFrom(const WeakPtr<T, N>& other);
	void moveFrom(WeakPtr<T, N>&& other) noexcept;
	void free();

public:
	WeakPtr();
	WeakPtr(SharedPtr<T, N>& ptr);

	WeakPtr(const WeakPtr<T, N>& other);
	WeakPtr& operator=(const WeakPtr<T, N>& other);

	WeakPtr(WeakPtr<T, N>&& other) noexcept;
	WeakPtr& operator=(WeakPtr<T, N>&& other) noexcept;

	SharedPtr<T, N> lock() const;

	bool expired() const;

	~WeakPtr() noexcept;
};

TT
WeakPtr<T, N>::WeakPtr() = default;

TT
WeakPtr<T, N>::WeakPtr(SharedPtr<T, N>& other)
{
	this->ptr = other.ptr;
	this->counter = other.counter;

	if (this->counter)
		counter->addWeakPtr();
}

TT
WeakPtr<T, N>::WeakPtr(const WeakPtr<T, N>& other)
{
	copyFrom(other);
}

TT
WeakPtr<T, N>& WeakPtr<T, N>::operator=(const WeakPtr<T, N>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

TT
WeakPtr<T, N>::WeakPtr(WeakPtr<T, N>&& other)
{
	moveFrom(std::move(other));
}

TT
WeakPtr<T, N>& WeakPtr<T, N>::operator=(WeakPtr<T, N>&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

TT
SharedPtr<T, N> WeakPtr<T, N>::lock() const
{
	if (expired())
		return SharedPtr<T, N>();
	else
		return SharedPtr<T, N>(this->ptr);
}

TT
bool WeakPtr<T, N>::expired() const
{
	return this->counter && counter->useCount == 0;
}

TT
WeakPtr<T, N>::~WeakPtr() noexcept
{
	free();
}

TT
void WeakPtr<T, N>::copyFrom(const WeakPtr<T, N>& other)
{
	this->ptr = other.ptr;
	this->counter = other.counter;

	if (this->counter)
		counter->addWeakPtr();
}

TT
void WeakPtr<T, N>::moveFrom(WeakPtr<T, N>&& other) noexcept
{
	this->ptr = other.ptr;
	this->counter = other.counter;

	other.ptr = nullptr;
	other.counter = nullptr;
}

TT
void WeakPtr<T, N>::free()
{
	if (this->ptr == nullptr && this->counter == nullptr)
		return;

	counter->removeWeakPtr();

	if (counter->weakCount == 0)
		delete counter;
}
