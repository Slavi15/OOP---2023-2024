#include "Person.h"

Person::Person() = default;

Person::Person(const char* name, size_t age)
{
	if (!name)
		throw std::runtime_error("NULLPTR!");

	setName(name);
	setAge(age);
}

Person::Person(const Person& other)
{
	copyFrom(other);
}

Person& Person::operator=(const Person& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Person::Person(Person&& other) noexcept
{
	moveFrom(std::move(other));
}

Person& Person::operator=(Person&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

const char* Person::getName() const
{
	return this->name;
}

const size_t Person::getAge() const
{
	return this->age;
}

void Person::setName(const char* name)
{
	if (!name)
		throw std::runtime_error("NULLPTR!");

	delete[] this->name;

	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

void Person::setAge(size_t age)
{
	this->age = age;
}

Person::~Person() noexcept
{
	delete[] this->name;

	this->name = nullptr;
	this->age = 0;
}

void Person::copyFrom(const Person& other)
{
	this->name = new char[strlen(other.name) + 1];
	strcpy(this->name, other.name);

	this->age = other.age;
}

void Person::moveFrom(Person&& other) noexcept
{
	this->name = other.name;
	this->age = other.age;

	other.name = nullptr;
	other.age = 0;
}

void Person::free()
{
	delete[] this->name;

	this->name = nullptr;
	this->age = 0;
}
