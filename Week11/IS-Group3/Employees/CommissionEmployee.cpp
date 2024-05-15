#include "CommissionEmployee.h"

CommissionEmployee::CommissionEmployee() = default;

CommissionEmployee::CommissionEmployee(const char* name, size_t salary, size_t commission) : Employee(name, salary), commission(commission) {}

const size_t CommissionEmployee::getCommission() const
{
	return this->commission;
}

void CommissionEmployee::setCommission(size_t commission)
{
	this->commission = commission;
}

size_t CommissionEmployee::calculateSalary() const
{
	return getSalary() + getSalary() * getCommission();
}

Employee* CommissionEmployee::clone() const
{
	return new CommissionEmployee(*this);
}
