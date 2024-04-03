#include "String.h"

String::String() = default;

String::String(const char* str)
{
	setLength(str);
	setCapacity();
	setData(str);
}

void String::copyFrom(const String& other)
{
	this->_length = other._length;
	this->_capacity = other._capacity;

	this->_data = new char[_capacity] { '\0' };
	for (size_t i = 0; i < _capacity; i++)
		_data[i] = other._data[i];

	_data[_length] = '\0';
}

void String::free()
{
	delete[] _data;

	_data = nullptr;
	_length = 0;
}

String::String(const String& other)
{
	copyFrom(other);
}

String& String::operator=(const String& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

String::~String()
{
	free();
}

void String::setData(const char* str)
{
	if (!str) return;

	delete[] _data;
	this->_data = new char[_capacity] { '\0' };
	strcpy(this->_data, str);
}

void String::setLength(const char* str)
{
	if (!str) return;
	_length = strlen(str);
}

void String::setCapacity()
{
	_capacity = std::max((int)getNextPowerOfTwo(_length), 16);
}

const char* String::c_str() const
{
	return _data;
}

const size_t String::getLength() const
{
	return _length;
}

String& String::concat(const String& other)
{
	if (_length + other._length < _capacity)
	{
		_length += other._length;
		strcat(this->_data, other._data);
		return *this;
	}

	_length += other._length;
	setCapacity();

	char* buff = new char[_capacity];
	strcpy(buff, this->_data);
	strcat(buff, other._data);

	delete[] _data;
	this->_data = buff;

	return *this;
}

String& String::operator+=(const String& other)
{
	return concat(other);
}

String& String::operator+=(char ch)
{
	if (_length == _capacity)
		resize();

	this->_data[_length++] = ch;
	this->_data[_length] = '\0';

	return *this;
}

String operator+(const String& lhs, const String& rhs)
{
	String result(lhs);
	result += rhs;
	return result;
}

char String::operator[](size_t index) const
{
	if (index < _length)
		return this->_data[index];
}

char& String::operator[](size_t index)
{
	if (index < _length)
		return this->_data[index];
}

std::istream& operator>>(std::istream& is, String& str)
{
	char buffer[MAX_TEXT_LENGTH + 1];
	is >> buffer;

	delete[] str._data;
	str._length = strlen(buffer);
	str._capacity = std::max((int)str.getNextPowerOfTwo(str._length), 16);
	str._data = new char[str._capacity] { '\0' };
	strcpy(str._data, buffer);

	return is;
}

std::ostream& operator<<(std::ostream& os, const String& str)
{
	os << str.c_str();
	return os;
}

void String::resize()
{
	setCapacity();

	char* newData = new char[_capacity] { '\0' };
	strcpy(newData, this->_data);

	delete[] _data;
	_data = newData;
}

const size_t String::getNextPowerOfTwo(size_t num) const
{
	num -= 1;

	while (num & (num - 1))
		num &= (num - 1);

	return num << 1;
}