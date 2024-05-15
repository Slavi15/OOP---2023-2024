#pragma once

#include <fstream>

#include "Employee.h"
#include "EmployeeFactory.h"

#include "HourlyEmployee.h"
#include "CommissionEmployee.h"

class EmployeesContainer
{
private:
	Employee** employees = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	EmployeesContainer(size_t newSize);
	void resize(size_t newCapacity);

	const unsigned int getNextPowerOfTwo(unsigned int n) const;
	const unsigned int allocateCapacity(unsigned int size) const;

	void selectionSort(bool(*isLower)(const Employee& e1, const Employee& e2)); // O(n^2)

	void copyFrom(const EmployeesContainer& other);
	void moveFrom(EmployeesContainer&& other) noexcept;
	void free();

	void addEmployee(Employee* employee);

public:
	EmployeesContainer();

	EmployeesContainer(const EmployeesContainer& other);
	EmployeesContainer& operator=(const EmployeesContainer& other);

	EmployeesContainer(EmployeesContainer&& other) noexcept;
	EmployeesContainer& operator=(EmployeesContainer&& other) noexcept;

	const size_t getSize() const;
	const size_t getCapacity() const;

	void addHourlyEmployee(const char* name, size_t salary, size_t overtime);
	void addCommissionEmployee(const char* name, size_t salary, size_t commission);

	void removeEmployee(size_t index);

	void sortBySalary();

	friend std::ostream& operator<<(std::ostream& os, const EmployeesContainer& container);

	~EmployeesContainer() noexcept;
};