#pragma once
#pragma warning (disable: 4996)

#include <iostream>
#include <fstream>

#define MAX_TEXT_LENGTH 1024

class String
{
private:
	char* _data = nullptr;
	size_t _length = 0;
	size_t _capacity = 0;

	void copyFrom(const String& str);
	void free();

	void resize();
	const size_t getNextPowerOfTwo(size_t num) const;

public:
	String();
	String(const char* str);

	String(const String& other);
	String& operator=(const String& other);

	void setData(const char* str);
	void setLength(const char* str);
	void setCapacity();

	const char* c_str() const;
	const size_t getLength() const;

	String& concat(const String& other);

	String& operator+=(const String& other);
	String& operator+=(char ch);
	friend String operator+(const String& lhs, const String& rhs);

	char operator[](size_t index) const;
	char& operator[](size_t index);

	friend std::istream& operator>>(std::istream& is, String& str);

	~String();
};

std::ostream& operator<<(std::ostream& os, const String& str);