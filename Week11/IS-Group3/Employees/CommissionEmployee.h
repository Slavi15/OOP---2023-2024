#pragma once

#include "Employee.h"

class CommissionEmployee : public Employee
{
private:
	size_t commission = 0;

public:
	CommissionEmployee();
	CommissionEmployee(const char* name, size_t salary, size_t commission);

	const size_t getCommission() const;

	void setCommission(size_t commission);

	size_t calculateSalary() const override;

	Employee* clone() const override;
};