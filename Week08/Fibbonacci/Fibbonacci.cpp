#include "Fibbonacci.h"

Fibbonacci::Fibbonacci() : Fibbonacci(100, 0) {}

Fibbonacci::Fibbonacci(size_t size, size_t nullValue)
{
	this->size = size;

	this->values = new size_t[this->size];
	for (size_t i = 0; i < this->size; i++)
		this->values[i] = nullValue;
}

Fibbonacci::Fibbonacci(const Fibbonacci& other)
{
	copyFrom(other);
}

Fibbonacci& Fibbonacci::operator=(const Fibbonacci& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Fibbonacci::Fibbonacci(Fibbonacci&& other) noexcept
{
	moveFrom(std::move(other));
}

Fibbonacci& Fibbonacci::operator=(Fibbonacci&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

const size_t Fibbonacci::getSize() const
{
	return this->size;
}

const size_t Fibbonacci::getValue(size_t index) const
{
	return this->values[index];
}

void Fibbonacci::add(size_t index, size_t value)
{
	if (index < 0 || index >= getSize())
		throw std::out_of_range("Invalid index!");

	this->values[index] = value;
}

const bool Fibbonacci::contains(size_t index) const
{
	return this->values[index] != 0;
}

Fibbonacci::~Fibbonacci() noexcept
{
	free();
}

void Fibbonacci::copyFrom(const Fibbonacci& other)
{
	this->size = other.size;
	
	this->values = new size_t[this->size];
	for (size_t i = 0; i < this->size; i++)
		this->values[i] = other.values[i];
}

void Fibbonacci::moveFrom(Fibbonacci&& other) noexcept
{
	this->values = other.values;
	this->size = other.size;

	other.values = nullptr;
	other.size = 0;
}

void Fibbonacci::free()
{
	delete[] this->values;

	this->values = nullptr;
	this->size = 0;
}