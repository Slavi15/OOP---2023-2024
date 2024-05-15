#include "EmployeesContainer.h"

EmployeesContainer::EmployeesContainer() : EmployeesContainer(4) {}

EmployeesContainer::EmployeesContainer(size_t newSize) : size(0)
{
	this->capacity = allocateCapacity(newSize);
	this->employees = new Employee * [this->capacity];
}

EmployeesContainer::EmployeesContainer(const EmployeesContainer& other)
{
	copyFrom(other);
}

EmployeesContainer& EmployeesContainer::operator=(const EmployeesContainer& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

EmployeesContainer::EmployeesContainer(EmployeesContainer&& other) noexcept
{
	moveFrom(std::move(other));
}

EmployeesContainer& EmployeesContainer::operator=(EmployeesContainer&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

const size_t EmployeesContainer::getSize() const
{
	return this->size;
}

const size_t EmployeesContainer::getCapacity() const
{
	return this->capacity;
}

void EmployeesContainer::addEmployee(Employee* employee)
{
	if (getSize() >= getCapacity())
		resize(getCapacity() * 2);

	this->employees[this->size++] = employee;
}

void EmployeesContainer::addHourlyEmployee(const char* name, size_t salary, size_t overtime)
{
	HourlyEmployee* hourlyEmployee = new HourlyEmployee(name, salary, overtime); // createEmployee(std::cin);
	addEmployee(hourlyEmployee);
}

void EmployeesContainer::addCommissionEmployee(const char* name, size_t salary, size_t commission)
{
	CommissionEmployee* commissionEmployee = new CommissionEmployee(name, salary, commission);
	addEmployee(commissionEmployee);
}

void EmployeesContainer::removeEmployee(size_t index)
{
	if (index >= getSize()) return;

	if (getSize())
		this->size--;
	else
		return;

	std::swap(this->employees[index], this->employees[getSize()]);

	if (getSize() * 4 <= getCapacity() && getCapacity() > 1)
		resize(getCapacity() / 2);
}

void EmployeesContainer::selectionSort(bool(*isLower)(const Employee& e1, const Employee& e2))
{
	for (size_t i = 0; i < getSize(); i++)
	{
		size_t minIndex = i;

		for (size_t j = i + 1; j < getSize(); j++)
			if (isLower(*this->employees[j], *this->employees[minIndex]))
				minIndex = j;

		if (minIndex != i)
			std::swap(this->employees[minIndex], this->employees[i]);
	}
}

void EmployeesContainer::sortBySalary()
{
	return selectionSort([](const Employee& e1, const Employee& e2) -> bool { return e1.getSalary() < e2.getSalary(); });
}

std::ostream& operator<<(std::ostream& os, const EmployeesContainer& container)
{
	os << "[ " << std::endl;
	for (size_t i = 0; i < container.getSize(); i++)
		os << container.employees[i]->getName() << " - " << container.employees[i]->getSalary() << std::endl;
	os << "]";

	return os;
}

EmployeesContainer::~EmployeesContainer() noexcept
{
	free();
}

void EmployeesContainer::resize(size_t newCapacity)
{
	Employee** newEmployees = new Employee * [newCapacity];
	for (size_t i = 0; i < getSize(); i++)
		newEmployees[i] = this->employees[i];

	delete[] this->employees;
	this->employees = newEmployees;
	this->capacity = newCapacity;
}

const unsigned int EmployeesContainer::getNextPowerOfTwo(unsigned int n) const
{
	if (n == 0) return 1;

	while (n & (n - 1))
		n &= (n - 1);

	return n << 1;
}

const unsigned int EmployeesContainer::allocateCapacity(unsigned int size) const
{
	return std::max(getNextPowerOfTwo(size + 1), 8u);
}

void EmployeesContainer::copyFrom(const EmployeesContainer& other)
{
	this->size = other.size;
	this->capacity = other.capacity;

	this->employees = new Employee * [this->capacity];
	for (size_t i = 0; i < this->capacity; i++)
		this->employees[i] = other.employees[i]->clone();
}

void EmployeesContainer::moveFrom(EmployeesContainer&& other) noexcept
{
	this->employees = other.employees;
	this->size = other.size;
	this->capacity = other.capacity;

	other.employees = nullptr;
	other.size = other.capacity = 0;
}

void EmployeesContainer::free()
{
	for (size_t i = 0; i < this->size; i++)
		delete this->employees[i];

	delete[] this->employees;

	this->employees = nullptr;
	this->size = this->capacity = 0;
}
