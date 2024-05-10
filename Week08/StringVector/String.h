#pragma once

#include <iostream>
#include <fstream>

#define MAX_LENGTH 1024

class String
{
private:
	char* data = nullptr;
	size_t length = 0;
	size_t capacity = 0;

	void resize(size_t newCapacity);

	void copyFrom(const String& other);
	void moveFrom(String&& other) noexcept;
	void free();

	const unsigned int allocate(size_t stringLength) const;
	const unsigned int getNextPowerOfTwo(unsigned int n) const;

public:
	String();
	String(const char* data);

	explicit String(size_t stringLength);

	String(const String& other);
	String& operator=(const String& other);

	String(String&& other) noexcept;
	String& operator=(String&& other) noexcept;

	const char* c_str() const;
	const size_t getLength() const;
	const size_t getCapacity() const;

	String& operator+=(const String& other);
	friend String operator+(const String& lhs, const String& rhs);

	char& operator[](size_t index);
	const char& operator[](size_t index) const;

	friend std::istream& operator>>(std::istream& is, String& other);
	friend std::ostream& operator<<(std::ostream& os, const String& other);

	friend const bool operator<(const String& lhs, const String& rhs);
	friend const bool operator>(const String& lhs, const String& rhs);

	friend const bool operator<=(const String& lhs, const String& rhs);
	friend const bool operator>=(const String& lhs, const String& rhs);

	friend const bool operator==(const String& lhs, const String& rhs);
	friend const bool operator!=(const String& lhs, const String& rhs);

	~String() noexcept;
};