#include "EmployeeFactory.h"
#include "HourlyEmployee.h"
#include "CommissionEmployee.h"

Employee* EmployeeFactory::createEmployee(std::istream& is)
{
	char employeeType;
	is >> employeeType;

	if (employeeType == 'h')
	{
		char buff[MAX_TEXT + 1];
		is >> buff;

		size_t salary, overtime;
		is >> salary >> overtime;

		return new HourlyEmployee(buff, salary, overtime);
	}
	else if (employeeType == 'c')
	{
		char buff[MAX_TEXT + 1];
		is >> buff;

		size_t salary, commission;
		is >> salary >> commission;

		return new CommissionEmployee(buff, salary, commission);
	}

	return nullptr;
}
