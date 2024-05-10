#pragma once
#pragma warning (disable: 4996)

#include "String.h"

#include <iostream>
#include <fstream>

#define isPowerOfTwo(n) (n & (n - 1)) == 0

class StringVector
{
private:
	String* data = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	explicit StringVector(size_t newCapacity);

	const unsigned int getNextPowerOfTwo(unsigned int n) const;
	const unsigned int allocateCapacity(unsigned int n) const;

	void resize(size_t newCapacity);

	void copyFrom(const StringVector& other);
	void moveFrom(StringVector&& other) noexcept;
	void free();

public:
	StringVector();

	StringVector(const StringVector& other);
	StringVector& operator=(const StringVector& other);

	StringVector(StringVector&& other) noexcept;
	StringVector& operator=(StringVector&& other) noexcept;

	const size_t getSize() const;
	const size_t getCapacity() const;

	void push_back(const String& element);
	void push_back(String&& element);

	void pop_back();

	void insert(const String& element, size_t index);
	void insert(String&& element, size_t index);

	void erase(size_t index);

	const bool empty() const;
	void clear();

	const String& operator[](size_t index) const;
	String& operator[](size_t index);

	friend std::istream& operator>>(std::istream& is, StringVector& ref);
	friend std::ostream& operator<<(std::ostream& os, const StringVector& ref);

	~StringVector() noexcept;
};