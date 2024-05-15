#include "Employee.h"

Employee::Employee() = default;

Employee::Employee(const char* name, size_t salary) : salary(salary)
{
	setName(name);
}

Employee::Employee(const Employee& other)
{
	copyFrom(other);
}

Employee& Employee::operator=(const Employee& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Employee::Employee(Employee&& other) noexcept
{
	moveFrom(std::move(other));
}

Employee& Employee::operator=(Employee&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

const char* Employee::getName() const
{
	return this->name;
}

const size_t Employee::getSalary() const
{
	return this->salary;
}

void Employee::setName(const char* name)
{
	if (!name) return;

	delete[] this->name;

	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

void Employee::setSalary(size_t salary)
{
	this->salary = salary;
}

std::ostream& operator<<(std::ostream& os, const Employee& employee)
{
	os << "Name: " << employee.getName() << std::endl;
	os << "Salary: " << employee.getSalary() << std::endl;

	return os;
}

Employee::~Employee() noexcept
{
	free();
}

void Employee::copyFrom(const Employee& other)
{
	this->name = new char[strlen(other.name) + 1];
	strcpy(this->name, other.name);

	this->salary = other.salary;
}

void Employee::moveFrom(Employee&& other) noexcept
{
	this->name = other.name;
	this->salary = other.salary;

	other.name = nullptr;
	other.salary = 0;
}

void Employee::free()
{
	delete[] this->name;
	
	this->name = nullptr;
	this->salary = 0;
}
