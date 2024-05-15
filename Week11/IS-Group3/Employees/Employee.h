#pragma once
#pragma warning (disable : 4996)

#include <iostream>
#include <fstream>

class Employee
{
private:
	char* name = nullptr;
	size_t salary = 0;

	void copyFrom(const Employee& other);
	void moveFrom(Employee&& other) noexcept;
	void free();

public:
	virtual size_t calculateSalary() const = 0;
	virtual Employee* clone() const = 0;

	Employee();
	Employee(const char* name, size_t salary);

	Employee(const Employee& other);
	Employee& operator=(const Employee& other);

	Employee(Employee&& other) noexcept;
	Employee& operator=(Employee&& other) noexcept;

	const char* getName() const;
	const size_t getSalary() const;

	void setName(const char* name);
	void setSalary(size_t salary);

	friend std::ostream& operator<<(std::ostream& os, const Employee& employee);

	virtual ~Employee() noexcept;
};