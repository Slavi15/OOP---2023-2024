#include <iostream>

#include "EmployeesContainer.h"

int main()
{
	EmployeesContainer container;

	container.addHourlyEmployee("ABC", 1000, 40);
	container.addHourlyEmployee("DEF", 1200, 50);
	container.addCommissionEmployee("HIJ", 2000, 30);
	container.addHourlyEmployee("KLMNO", 1750, 20);

	std::cout << container;

	return 0;
}