#include "HourlyEmployee.h"

HourlyEmployee::HourlyEmployee() = default;

HourlyEmployee::HourlyEmployee(const char* name, size_t salary, size_t overtime) : Employee(name, salary), overtime(overtime) {}

const size_t HourlyEmployee::getOvertime() const
{
    return this->overtime;
}

void HourlyEmployee::setOvertime(size_t overtime)
{
    this->overtime = overtime;
}

size_t HourlyEmployee::calculateSalary() const
{
    return 160 * getSalary() + (getSalary() * getOvertime()) / 2;
}

Employee* HourlyEmployee::clone() const
{
    return new HourlyEmployee(*this);
}