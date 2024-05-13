#include "Teacher.h"

static char** copyArrayOfStrings(const char* const* subjects, size_t size)
{
	char** result = new char* [size];

	for (size_t i = 0; i < size; i++)
	{
		result[i] = new char[strlen(subjects[i]) + 1];
		strcpy(result[i], subjects[i]);
	}

	return result;
}

Teacher::Teacher() = default;

Teacher::Teacher(const char* name, size_t age, const char* const* subjects, size_t size) : Person(name, age)
{
	this->subjects = copyArrayOfStrings(subjects, size);
}

Teacher::Teacher(const Teacher& other) : Person(other)
{
	copyFrom(other);
}

Teacher& Teacher::operator=(const Teacher& other)
{
	if (this != &other)
	{
		Person::operator=(other);
		free();
		copyFrom(other);
	}

	return *this;
}

Teacher::Teacher(Teacher&& other) noexcept : Person(std::move(other))
{
	moveFrom(std::move(other));
}

Teacher& Teacher::operator=(Teacher&& other) noexcept
{
	if (this != &other)
	{
		Person::operator=(std::move(other));
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

const size_t Teacher::getSize() const
{
	return this->size;
}

void Teacher::setSize(size_t size)
{
	this->size = size;
}

Teacher::~Teacher() noexcept
{
	free();
}

void Teacher::copyFrom(const Teacher& other)
{
	this->size = other.size;
	this->subjects = copyArrayOfStrings(other.subjects, other.size);
}

void Teacher::moveFrom(Teacher&& other) noexcept
{
	this->subjects = other.subjects;
	this->size = other.size;

	other.subjects = nullptr;
	other.size = 0;
}

void Teacher::free()
{
	for (size_t i = 0; i < this->size; i++)
		delete[] this->subjects[i];

	delete[] this->subjects;
}
