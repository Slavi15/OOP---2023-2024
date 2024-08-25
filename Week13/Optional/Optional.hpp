#pragma once

#include <iostream>

template <typename T>
class Optional
{
private:
	T* data;

	void copyFrom(const Optional<T>& other);
	void free();

public:
	Optional();
	Optional(const T& data);

	Optional(const Optional<T>& other);
	Optional& operator=(const Optional<T>& other);

	const T& getData() const;
	void setData(const T& data);

	bool containsData() const;

	void clear();

	~Optional() noexcept;
};

template<typename T>
Optional<T>::Optional() : data(nullptr) {}

template<typename T>
Optional<T>::Optional(const T& data)
{
	setData(data);
}

template<typename T>
Optional<T>::Optional(const Optional<T>& other)
{
	copyFrom(other);
}

template<typename T>
Optional<T>& Optional<T>::operator=(const Optional<T>& other)
{
	if (this != &other)
	{
		copyFrom(other);
		free();
	}

	return *this;
}

template<typename T>
const T& Optional<T>::getData() const
{
	if (!containsData())
		throw std::logic_error("No data to retrieve!");

	return *this->data;
}

template<typename T>
void Optional<T>::setData(const T& data)
{
	delete this->data;
	this->data = new T(data);
}

template<typename T>
bool Optional<T>::containsData() const
{
	return this->data != nullptr;
}

template<typename T>
void Optional<T>::clear()
{
	free();
}

template<typename T>
Optional<T>::~Optional() noexcept
{
	free();
}

template <typename T>
void Optional<T>::copyFrom(const Optional<T>& other)
{
	if (other.containsData())
		this->data = new T(*other.data);
	else
		this->data = nullptr;
}

template<typename T>
void Optional<T>::free()
{
	delete this->data;
	this->data = nullptr;
}
