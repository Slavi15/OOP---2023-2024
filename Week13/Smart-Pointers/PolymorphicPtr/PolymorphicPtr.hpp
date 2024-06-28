#pragma once

#include <iostream>

#define TT template <typename T>

TT
class PolymorphicPtr
{
private:
	T* ptr = nullptr;

	void copyFrom(const PolymorphicPtr<T>& other);
	void moveFrom(PolymorphicPtr<T>&& other) noexcept;
	void free();

public:
	PolymorphicPtr();
	PolymorphicPtr(T* ptr);

	PolymorphicPtr(const PolymorphicPtr<T>& other);
	PolymorphicPtr& operator=(const PolymorphicPtr<T>& other);

	PolymorphicPtr(PolymorphicPtr<T>&& other) noexcept;
	PolymorphicPtr& operator=(PolymorphicPtr<T>&& other) noexcept;

	const T* operator->() const;
	T* operator->();

	const T& operator*() const;
	T& operator*();

	const T* get() const;
	T* get();

	~PolymorphicPtr() noexcept;
};

TT
PolymorphicPtr<T>::PolymorphicPtr() = default;

TT
PolymorphicPtr<T>::PolymorphicPtr(T* ptr) : ptr(ptr) {}

TT
PolymorphicPtr<T>::PolymorphicPtr(const PolymorphicPtr<T>& other)
{
	copyFrom(other);
}

TT
PolymorphicPtr<T>& PolymorphicPtr<T>::operator=(const PolymorphicPtr<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

TT
PolymorphicPtr<T>::PolymorphicPtr(PolymorphicPtr<T>&& other) noexcept
{
	moveFrom(std::move(other));
}

TT
PolymorphicPtr<T>& PolymorphicPtr<T>::operator=(PolymorphicPtr<T>&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

TT
const T* PolymorphicPtr<T>::operator->() const
{
	return this->ptr;
}

TT
T* PolymorphicPtr<T>::operator->()
{
	return this->ptr;
}

TT
const T& PolymorphicPtr<T>::operator*() const
{
	if (!this->ptr)
		throw std::runtime_error("nullptr!");

	return *this->ptr;
}

TT
T& PolymorphicPtr<T>::operator*() 
{
	if (!this->ptr)
		throw std::runtime_error("nullptr!");

	return *this->ptr;
}

TT
const T* PolymorphicPtr<T>::get() const
{
	return this->ptr;
}

TT
T* PolymorphicPtr<T>::get()
{
	return this->ptr;
}

TT
PolymorphicPtr<T>::~PolymorphicPtr() noexcept
{
	free();
}

TT
void PolymorphicPtr<T>::copyFrom(const PolymorphicPtr<T>& other)
{
	this->ptr = other.ptr->clone();
}

TT
void PolymorphicPtr<T>::moveFrom(PolymorphicPtr<T>&& other) noexcept
{
	this->ptr = other.ptr;
	other.ptr = nullptr;
}

TT
void PolymorphicPtr<T>::free()
{
	delete this->ptr;
	this->ptr = nullptr;
}
