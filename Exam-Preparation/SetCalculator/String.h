#pragma once

#include <iostream>
#include <fstream>

#define MAX_BUFF_LENGTH 1024

class String
{
private:
	char* data = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	explicit String(size_t newSize);

	unsigned int getNextPowerTwo(unsigned int n) const;
	unsigned int allocateCapacity(unsigned int size) const;

	void resize(size_t newCapacity);

	void copyFrom(const String& other);
	void moveFrom(String&& other) noexcept;
	void free();

public:
	String();
	String(const char* data);

	String(const String& other);
	String& operator=(const String& other);

	String(String&& other) noexcept;
	String& operator=(String&& other) noexcept;

	size_t getSize() const;
	size_t getCapacity() const;

	const char* c_str() const;

	String& operator+=(const String& other);
	friend String operator+(const String& lhs, const String& rhs);

	const char& operator[](size_t index) const;
	char& operator[](size_t index);

	String substr(size_t begin, size_t howMany) const;

	friend bool operator==(const String& lhs, const String& rhs);
	friend bool operator!=(const String& lhs, const String& rhs);
	friend bool operator<=(const String& lhs, const String& rhs);
	friend bool operator<(const String& lhs, const String& rhs);
	friend bool operator>=(const String& lhs, const String& rhs);
	friend bool operator>(const String& lhs, const String& rhs);

	friend std::istream& operator>>(std::istream& is, String& string);
	friend std::ostream& operator<<(std::ostream& os, const String& string);

	~String() noexcept;
};