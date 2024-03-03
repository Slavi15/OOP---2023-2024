#include <iostream>

using std::cin;
using std::cout;
using std::endl;

namespace EmployeesNS
{
	enum class Positions { SE, SSE, EM, LSE };
	enum class Criteria { sortByName, sortBySalary, sortByRating };

	struct Employee
	{
		char name[100 + 1];
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

	const char* getPosition(Positions position)
	{
		switch (position)
		{
		case Positions::SE:
			return "Software Engineer";
		case Positions::SSE:
			return "Senior Software Engineer";
		case Positions::EM:
			return "Engineer Manager";
		case Positions::LSE:
			return "Lead Software Engineer";
		default:
			return "No position";
		}
	}

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

	void selectionSort(Firm& firm, bool(*compare)(const Employee& e1, const Employee& e2))
	{
		for (size_t i = 0; i < firm.employeesCount - 1; i++)
		{
			size_t minIndex = i;

			for (size_t j = i + 1; j < firm.employeesCount; j++)
				if (compare(firm.employees[j], firm.employees[minIndex]))
					minIndex = j;

			if (minIndex != i)
				std::swap(firm.employees[minIndex], firm.employees[i]);
		}
	}

	void sortByCriteria(Firm& firm, Criteria criteria)
	{
		switch (criteria)
		{
		case Criteria::sortByName:
			return selectionSort(firm, [](const Employee& e1, const Employee& e2) { return myStrCmp(e1.name, e2.name) < 0; });
		case Criteria::sortBySalary:
			return selectionSort(firm, [](const Employee& e1, const Employee& e2) { return e1.salary < e2.salary; });
		case Criteria::sortByRating:
			return selectionSort(firm, [](const Employee& e1, const Employee& e2) { return e1.rating < e2.rating; });
		}
	}

	void getMaxAndMinRating(const Firm& firm, int& minRating, int& maxRating, size_t position)
	{
		int min = INT_MAX, max = INT_MIN;

		for (size_t i = 0; i < firm.employeesCount; i++)
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

	void printEmployee(const Employee& employee)
	{
		cout << "Name: " << employee.name << endl;
		cout << "Salary: " << employee.salary << endl;
		cout << "Rating: " << employee.rating << endl;
		cout << "Position: " << getPosition(employee.position) << endl;
	}

	void printLexicographicalOrder(Firm& firm)
	{
		sortByCriteria(firm, Criteria::sortByName);

		for (size_t i = 0; i < firm.employeesCount; i++)
			if (firm.employees[i].salary > firm.averagePay)
				printEmployee(firm.employees[i]);

		cout << endl;
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