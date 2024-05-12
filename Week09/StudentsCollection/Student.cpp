#include "Student.h"

Student::Student() = default;

Student::Student(const char* name, size_t age)
{
	setName(name);
	setAge(age);
}

Student::Student(const Student& other)
{
	copyFrom(other);
}

Student& Student::operator=(const Student& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Student::Student(Student&& other) noexcept
{
	moveFrom(std::move(other));
}

Student& Student::operator=(Student&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

const char* Student::getName() const
{
	return this->name;
}

const size_t Student::getAge() const
{
	return this->age;
}

void Student::setName(const char* name)
{
	if (!name)
		throw std::runtime_error("NULLPTR!");

	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

void Student::setAge(size_t age)
{
	this->age = age;
}

Student::~Student() noexcept
{
	free();
}

void Student::copyFrom(const Student& other)
{
	this->name = new char[strlen(other.name) + 1];
	strcpy(this->name, other.name);

	this->age = other.age;
}

void Student::moveFrom(Student&& other) noexcept
{
	this->name = other.name;
	this->age = other.age;

	other.name = nullptr;
	other.age = 0;
}

void Student::free()
{
	delete[] this->name;

	this->name = nullptr;
	this->age = 0;
}
