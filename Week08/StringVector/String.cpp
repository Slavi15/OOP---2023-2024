#include "String.h"

String::String() : String("") {};

String::String(const char* data)
{
	if (!data)
		throw std::runtime_error("NULLPTR!");

	this->length = strlen(data);
	this->capacity = allocate(this->length);

	this->data = new char[this->capacity + 1];
	strcpy(this->data, data);
}

String::String(size_t stringLength)
{
	this->length = stringLength;
	this->capacity = allocate(stringLength);
	this->data = new char[this->capacity + 1] { '\0' };
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

String::String(String&& other) noexcept
{
	moveFrom(std::move(other));
}

String& String::operator=(String&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

const char* String::c_str() const
{
	return this->data;
}

const size_t String::getLength() const
{
	return this->length;
}

const size_t String::getCapacity() const
{
	return this->capacity;
}

String& String::operator+=(const String& other)
{
	if ((getLength() + other.getLength() + 1) > getCapacity())
		resize(allocate(getLength() + other.getLength()));

	strncat(this->data, other.data, other.getLength());
	this->length += other.getLength();

	return *this;
}

char& String::operator[](size_t index)
{
	return this->data[index];
}

const char& String::operator[](size_t index) const
{
	return this->data[index];
}

String operator+(const String& lhs, const String& rhs)
{
	String toReturn(lhs.getLength() + rhs.getLength());
	toReturn += lhs;
	toReturn += rhs;
	return toReturn;
}

std::istream& operator>>(std::istream& is, String& other)
{
	char buff[MAX_LENGTH + 1];
	is >> buff;
	size_t buffLength = strlen(buff);

	if (buffLength > other.getCapacity())
		other.resize(other.allocate(buffLength));

	strcpy(other.data, buff);
	other.length = buffLength;

	return is;
}

std::ostream& operator<<(std::ostream& os, const String& other)
{
	return os << other.data;
}

const bool operator<(const String& lhs, const String& rhs)
{
	return strcmp(lhs.data, rhs.data) < 0;
}

const bool operator>(const String& lhs, const String& rhs)
{
	return strcmp(lhs.data, rhs.data) > 0;
}

const bool operator<=(const String& lhs, const String& rhs)
{
	return strcmp(lhs.data, rhs.data) <= 0;
}

const bool operator>=(const String& lhs, const String& rhs)
{
	return strcmp(lhs.data, rhs.data) >= 0;
}

const bool operator==(const String& lhs, const String& rhs)
{
	return strcmp(lhs.data, rhs.data) == 0;
}

const bool operator!=(const String& lhs, const String& rhs)
{
	return strcmp(lhs.data, rhs.data) != 0;
}

String::~String() noexcept
{
	free();
}

void String::resize(size_t newCapacity)
{
	this->capacity = newCapacity;

	char* newData = new char[this->capacity + 1];
	strcpy(newData, this->data);
	delete[] this->data;

	this->data = newData;
}

const unsigned int String::allocate(size_t stringLength) const
{
	return std::max(getNextPowerOfTwo(stringLength + 1), 16u); // Minimum string length >= 16
}

void String::copyFrom(const String& other)
{
	this->length = other.length;
	this->capacity = other.capacity;

	this->data = new char[this->capacity + 1];
	strcpy(this->data, other.data);
}

void String::moveFrom(String&& other) noexcept
{
	this->data = other.data;
	this->length = other.length;
	this->capacity = other.capacity;

	other.data = nullptr;
	other.length = other.capacity = 0;
}

void String::free()
{
	delete[] this->data;

	this->data = nullptr;
	this->length = this->capacity = 0;
}

const unsigned int String::getNextPowerOfTwo(unsigned int n) const
{
	while (n & (n - 1))
		n &= (n - 1);

	return n << 1;
}
