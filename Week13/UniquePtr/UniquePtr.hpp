#include <iostream>

#define TT template <typename T>

TT
class UniquePtr
{
private:
	T* ptr = nullptr;

	void moveFrom(UniquePtr&& other) noexcept;
	void free();

public:
	UniquePtr(T* ptr);

	UniquePtr(const UniquePtr& other) = delete;
	UniquePtr& operator=(const UniquePtr& other) = delete;

	UniquePtr(UniquePtr&& other) noexcept;
	UniquePtr& operator=(UniquePtr&& other) noexcept;

	const T* operator->() const;
	T* operator->();

	const T& operator*() const;
	T& operator*();

	const T* get() const;
	T* get();

	~UniquePtr() noexcept;
};

TT
UniquePtr<T>::UniquePtr(T* ptr) : ptr(ptr) {}

TT
UniquePtr<T>::UniquePtr(UniquePtr<T>&& other) noexcept
{
	moveFrom(std::move(other));
}

TT
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr<T>&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

TT
const T* UniquePtr<T>::operator->() const
{
	return this->ptr;
}

TT
T* UniquePtr<T>::operator->()
{
	return this->ptr;
}

TT
const T& UniquePtr<T>::operator*() const
{
	if (!this->ptr)
		throw std::runtime_error("nullptr!");

	return *this->ptr;
}

TT
T& UniquePtr<T>::operator*()
{
	if (!this->ptr)
		throw std::runtime_error("nullptr!");

	return *this->ptr;
}

TT
const T* UniquePtr<T>::get() const
{
	return this->ptr;
}

TT
T* UniquePtr<T>::get()
{
	return this->ptr;
}

TT
UniquePtr<T>::~UniquePtr() noexcept
{
	free();
}

TT
void UniquePtr<T>::moveFrom(UniquePtr<T>&& other) noexcept
{
	this->ptr = other.ptr;
	other.ptr = nullptr;
}

TT
void UniquePtr<T>::free()
{
	delete this->ptr;
	this->ptr = nullptr;
}