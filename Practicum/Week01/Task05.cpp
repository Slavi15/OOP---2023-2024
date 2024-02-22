#include <iostream>

using std::cin;
using std::cout;
using std::endl;

namespace EmployeesNS
{
	enum class Positions { SE, SSE, EM, LSE };
	const char* positions[] = { "Software Engineer", "Senior Software Engineer", "Engineer Manager", "Lead Software Engineer" };

	struct Employee
	{
		char name[100];
		double salary;
		int rating;
		Positions position;
	};

	struct Firm
	{
		Employee* employees;
		double averagePay;
		size_t employeesCount;
	};

	void readEmployee(Employee& employee)
	{
		unsigned int num;
		cin >> employee.name >> employee.salary >> employee.rating >> num;

		switch (num)
		{
		case 0:
			employee.position = Positions::SE;
			break;
		case 1:
			employee.position = Positions::SSE;
			break;
		case 2:
			employee.position = Positions::EM;
			break;
		case 3:
			employee.position = Positions::LSE;
			break;
		default:
			employee.position = Positions::SE;
			break;
		}
	}

	void readFirm(Firm& firm, size_t N)
	{
		for (size_t i = 0; i < N; i++)
		{
			readEmployee(firm.employees[i]);
			firm.averagePay += firm.employees[i].salary;
		}

		firm.employeesCount = N;
		firm.averagePay /= N;
	}

	int myStrCmp(const char* first, const char* second)
	{
		if (!first || !second)
			return 0;

		while ((*first) && (*second) && ((*first) == (*second)))
		{
			first++;
			second++;
		}

		return *first - *second;
	}

	void selectionSort(Employee* employees, size_t len)
	{
		if (!employees)
			return;

		for (size_t i = 0; i < len - 1; i++)
		{
			size_t minIndex = i;

			for (size_t j = i + 1; j < len; j++)
				if (myStrCmp(employees[j].name, employees[minIndex].name) < 0)
					minIndex = j;

			if (minIndex != i)
				std::swap(employees[minIndex], employees[i]);
		}
	}

	void getMaxAndMinRating(const Firm& firm, int& minRating, int& maxRating, size_t position)
	{
		int min = INT_MAX, max = INT_MIN;

		for (size_t i = 1; i < firm.employeesCount; i++)
			if ((int)firm.employees[i].position == position)
			{
				if (firm.employees[i].rating < min)
					min = firm.employees[i].rating;

				if (firm.employees[i].rating > max)
					max = firm.employees[i].rating;
			}

		minRating = min;
		maxRating = max;
	}

	void printMaxAndMinRatings(const Firm& firm)
	{
		int minSERating, maxSERating, minSSERating, maxSSERating, minEMRating, maxEMRating, minLSERating, maxLSERating;

		getMaxAndMinRating(firm, minSERating, maxSERating, 0);
		getMaxAndMinRating(firm, minSSERating, maxSSERating, 1);
		getMaxAndMinRating(firm, minEMRating, maxEMRating, 2);
		getMaxAndMinRating(firm, minLSERating, maxLSERating, 3);

		cout << "Software Engineer => Max: " << maxSERating << " Min: " << minSERating << endl;
		cout << "Senior Software Engineer => Max: " << maxSSERating << " Min: " << minSSERating << endl;
		cout << "Engineer Manager => Max: " << maxEMRating << " Min: " << minEMRating << endl;
		cout << "Lead Software Engineer => Max: " << maxLSERating << " Min: " << minLSERating << endl;
	}

	void printLexicographicalOrder(const Firm& firm)
	{
		selectionSort(firm.employees, firm.employeesCount);

		for (size_t i = 0; i < firm.employeesCount; i++)
			if (firm.employees[i].salary > firm.averagePay)
				cout << firm.employees[i].name << ' ';

		cout << endl;
	}

	void printEmployee(const Employee& employee)
	{
		cout << "Name: " << employee.name << endl;
		cout << "Salary: " << employee.salary << endl;
		cout << "Rating: " << employee.rating << endl;
		cout << "Position: " << positions[(int)employee.position] << endl;
	}
}

int main()
{
	size_t N;
	cin >> N;

	EmployeesNS::Employee* employees = new EmployeesNS::Employee[N];
	EmployeesNS::Firm firm = { employees, 0, 0 };

	EmployeesNS::readFirm(firm, N);
	EmployeesNS::printLexicographicalOrder(firm);

	EmployeesNS::printMaxAndMinRatings(firm);

	delete[] employees;

	return 0;
}