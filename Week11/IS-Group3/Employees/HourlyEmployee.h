#pragma once

#include "Employee.h"

class HourlyEmployee : public Employee
{
private:
	size_t overtime = 0;

public:
	size_t calculateSalary() const override;

	HourlyEmployee();
	HourlyEmployee(const char* name, size_t salary, size_t overtime);

	const size_t getOvertime() const;

	void setOvertime(size_t overtime);

	Employee* clone() const override;
};