#include "String.h"

String::String() : String("") {}

String::String(size_t newSize) : size(0)
{
	this->capacity = allocateCapacity(newSize);
	this->data = new char[this->capacity] {};
}

String::String(const char* data)
{
	if (!data)
		throw std::runtime_error("nullptr!");

	this->size = strlen(data);
	this->capacity = allocateCapacity(this->size);

	this->data = new char[getSize() + 1];
	strcpy(this->data, data);
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

size_t String::getSize() const
{
	return this->size;
}

size_t String::getCapacity() const
{
	return this->capacity;
}

const char* String::c_str() const
{
	return this->data;
}

String& String::operator+=(const String& other)
{
	if (getSize() + other.getSize() >= getCapacity())
		resize(allocateCapacity(getSize() + other.getSize()));

	strncat(this->data, other.data, other.getSize());

	this->size += other.getSize();

	return *this;
}

const char& String::operator[](size_t index) const
{
	return this->data[index];
}

char& String::operator[](size_t index)
{
	return this->data[index];
}

String String::substr(size_t begin, size_t howMany) const
{
	if (begin + howMany > getSize())
		throw std::out_of_range("Not enough space!");

	String toReturn(howMany);
	strncat(toReturn.data, this->data + begin, howMany);
	return toReturn;
}

String operator+(const String& lhs, const String& rhs)
{
	String toReturn(lhs.getSize() + rhs.getSize());

	toReturn += lhs;
	toReturn += rhs;

	return toReturn;
}

bool operator==(const String& lhs, const String& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator!=(const String& lhs, const String& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) != 0;
}

bool operator<=(const String& lhs, const String& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) <= 0;
}

bool operator<(const String& lhs, const String& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator>=(const String& lhs, const String& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) >= 0;
}

bool operator>(const String& lhs, const String& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) > 0;
}

std::istream& operator>>(std::istream& is, String& string)
{
	char buff[MAX_BUFF_LENGTH + 1] {};
	is >> buff;

	size_t buffLength = strlen(buff);

	if (buffLength >= string.getCapacity())
		string.resize(string.allocateCapacity(buffLength));

	string.size = buffLength;
	strcpy(string.data, buff);

	return is;
}

std::ostream& operator<<(std::ostream& os, const String& string)
{
	return os << string.data;
}

String::~String() noexcept
{
	free();
}

unsigned int String::getNextPowerTwo(unsigned int n) const
{
	if (n == 0) return 1;

	while (n & (n - 1))
		n &= (n - 1);

	return n << 1;
}

unsigned int String::allocateCapacity(unsigned int size) const
{
	return std::max(getNextPowerTwo(size + 1), 8u);
}

void String::resize(size_t newCapacity)
{
	char* newData = new char[newCapacity] {};
	strcpy(newData, this->data);

	/*for (size_t i = 0; i < this->size; i++)
		newData[i] = this->data[i];*/

	delete[] this->data;
	this->data = newData;
	this->capacity = newCapacity;
}

void String::copyFrom(const String& other)
{
	this->size = other.size;
	this->capacity = other.capacity;

	this->data = new char[this->capacity] {};
	strcpy(this->data, other.data);
}

void String::moveFrom(String&& other) noexcept
{
	this->data = other.data;
	other.data = nullptr;

	this->size = other.size;
	this->capacity = other.capacity;

	other.size = other.capacity = 0;
}

void String::free()
{
	delete[] this->data;
	this->data = nullptr;
}
