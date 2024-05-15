#pragma once

#define MAX_TEXT 1024

#include "Employee.h"

class EmployeeFactory
{
public:
	Employee* createEmployee(std::istream& is);
};