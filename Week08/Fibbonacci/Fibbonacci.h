#pragma once

#include <iostream>

class Fibbonacci
{
private:
	size_t* values = nullptr;
	size_t size = 0;
	size_t nullValue = 0;

	void copyFrom(const Fibbonacci& other);
	void moveFrom(Fibbonacci&& other) noexcept;
	void free();

public:
	Fibbonacci();
	Fibbonacci(size_t size, size_t nullValue);

	Fibbonacci(const Fibbonacci& other);
	Fibbonacci& operator=(const Fibbonacci& other);

	Fibbonacci(Fibbonacci&& other) noexcept;
	Fibbonacci& operator=(Fibbonacci&& other) noexcept;

	const size_t getSize() const;
	const size_t getValue(size_t index) const;

	void add(size_t index, size_t value);
	const bool contains(size_t index) const;

	~Fibbonacci() noexcept;
};