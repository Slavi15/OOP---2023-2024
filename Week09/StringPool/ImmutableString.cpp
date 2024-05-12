#include "ImmutableString.h"

StringPool ImmutableString::pool;

ImmutableString::ImmutableString() : ImmutableString("") {}

ImmutableString::ImmutableString(const char* data)
{
	this->size = strlen(data);
	
	this->data = new char[strlen(data) + 1];
	strcpy(this->data, data);
}

ImmutableString::ImmutableString(const ImmutableString& other)
{
	copyFrom(other);
}

ImmutableString::ImmutableString(ImmutableString&& other) noexcept
{
	moveFrom(std::move(other));
}

const char* ImmutableString::c_str() const
{
	return this->data;
}

const size_t ImmutableString::getSize() const
{
	return this->size;
}

const char& ImmutableString::operator[](size_t index) const
{
	return this->data[index];
}

ImmutableString::~ImmutableString() noexcept
{
	free();
}

void ImmutableString::copyFrom(const ImmutableString& other)
{
	this->size = other.size;

	this->data = new char[strlen(other.data) + 1];
	strcpy(this->data, other.data);
}

void ImmutableString::moveFrom(ImmutableString&& other) noexcept
{
	this->data = other.data;
	this->size = other.size;

	other.data = nullptr;
	other.size = 0;
}

void ImmutableString::free()
{
	delete[] this->data;

	this->data = nullptr;
	this->size = 0;
}

const bool operator==(const ImmutableString& lhs, const ImmutableString& rhs)
{
	return strcmp(lhs.data, rhs.data) == 0;
}

const bool operator!=(const ImmutableString& lhs, const ImmutableString& rhs)
{
	return strcmp(lhs.data, rhs.data) != 0;
}

std::ostream& operator<<(std::ostream& os, const ImmutableString& ref)
{
	return os << ref.data;
}
