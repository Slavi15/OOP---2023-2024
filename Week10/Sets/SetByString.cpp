#include "SetByString.h"

SetByString::SetByString() : SetByString("", 20) {}

SetByString::SetByString(const char* str, size_t N) : BitSet(N)
{
	if (!str)
		throw std::runtime_error("NULLPTR!");

	this->str = new char[strlen(str) + 1];
	strcpy(this->str, str);

	extractNumbers();
}

SetByString::SetByString(const SetByString& other) : BitSet(other)
{
	copyFrom(other);
}

SetByString& SetByString::operator=(const SetByString& other)
{
	if (this != &other)
	{
		BitSet::operator=(other);
		free();
		copyFrom(other);
	}

	return *this;
}

SetByString::SetByString(SetByString&& other) noexcept : BitSet(other)
{
	moveFrom(std::move(other));
}

SetByString& SetByString::operator=(SetByString&& other) noexcept
{
	if (this != &other)
	{
		BitSet::operator=(std::move(other));
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

void SetByString::extractNumbers()
{
	std::stringstream ss(str);

	while (!ss.eof())
	{
		size_t num;
		ss >> num;
		BitSet::add(num);
	}
}

void SetByString::setText(const char* str)
{
	if (!str)
		throw std::runtime_error("NULLPTR!");

	delete[] this->str;

	this->str = new char[strlen(str) + 1];
	strcpy(this->str, str);

	BitSet::clear();
	extractNumbers();
}

void SetByString::setAt(size_t index, char ch)
{
	this->str[index] = ch;
	BitSet::clear();
	extractNumbers();
}

void SetByString::print() const
{
	BitSet::print();
}

SetByString::~SetByString() noexcept
{
	free();
}

void SetByString::copyFrom(const SetByString& other)
{
	this->str = new char[strlen(other.str) + 1];
	strcpy(this->str, other.str);
}

void SetByString::moveFrom(SetByString&& other) noexcept
{
	this->str = other.str;
	other.str = nullptr;
}

void SetByString::free()
{
	delete[] this->str;
	this->str = nullptr;
}
