#include <iostream>

using std::cin;
using std::cout;
using std::endl;

namespace GroupsNS
{
	enum class Major { SI, IS, KN, PM, M, INF };
	enum class Criteria { sortByGrade, sortByFN };

	struct Student
	{
		unsigned int fN;
		char name[100 + 1];
		double grade;
		Major major;
	};

	struct Group
	{
		Student* students;
		double averageGrade;
		size_t studentsCount;
	};

	const char* getMajor(Major major)
	{
		switch (major)
		{
		case Major::SI:
			return "Software Engineering";
		case Major::KN:
			return "Computer Science";
		case Major::IS:
			return "Information Systems";
		case Major::INF:
			return "Informatics";
		case Major::PM:
			return "Applied Mathematics";
		case Major::M:
			return "Mathematics";
		}
	}

	void inputStudent(Student& student)
	{
		unsigned int majorChoice;
		cin >> student.fN >> student.name >> student.grade >> majorChoice;

		switch (majorChoice)
		{
		case 0:
			student.major = Major::SI;
			break;
		case 1:
			student.major = Major::IS;
			break;
		case 2:
			student.major = Major::KN;
			break;
		case 3:
			student.major = Major::PM;
			break;
		case 4:
			student.major = Major::M;
			break;
		case 5:
			student.major = Major::INF;
			break;
		default:
			student.major = Major::SI;
			break;
		}
	}

	void printStudent(const Student& student)
	{
		cout << "Name: " << student.name << endl;
		cout << "Faculty number: " << student.fN << endl;
		cout << "Major: " << getMajor(student.major) << endl;
		cout << "Grade: " << student.grade << endl;
	}

	void createGroup(Group& group, size_t N)
	{
		for (size_t i = 0; i < N; i++)
		{
			inputStudent(group.students[i]);
			group.averageGrade += group.students[i].grade;
		}

		group.studentsCount = N;
		group.averageGrade /= N;
	}

	unsigned int getStipendStudents(const Group& group, double minimumGrade)
	{
		unsigned int counter = 0;

		for (size_t i = 0; i < group.studentsCount; i++)
			if (group.students[i].grade >= minimumGrade)
				counter++;

		return counter;
	}

	void insertionSort(Group& group, bool(*isBigger)(const Student& s1, const Student& s2))
	{
		for (size_t i = 1; i < group.studentsCount; i++)
		{
			Student currentStudent = group.students[i];
			int currentIndex = i - 1;

			while (currentIndex >= 0 && isBigger(group.students[currentIndex], currentStudent))
			{
				group.students[currentIndex + 1] = group.students[currentIndex];
				currentIndex--;
			}

			group.students[currentIndex + 1] = currentStudent;
		}
	}

	void sortByCriteria(Group& group, Criteria criteria)
	{
		switch (criteria)
		{
		case Criteria::sortByGrade:
			return insertionSort(group, [](const Student& s1, const Student& s2) { return s1.grade > s2.grade; });
		case Criteria::sortByFN:
			return insertionSort(group, [](const Student& s1, const Student& s2) { return s1.fN > s2.fN; });
		}
	}

	void printArray(const Group& group)
	{
		for (size_t i = 0; i < group.studentsCount; i++)
			printStudent(group.students[i]);
	}

	void sortStipendStudents(Group& group, double minimumGrade)
	{
		unsigned int stipendStudentsCount = getStipendStudents(group, minimumGrade);

		Student* stipendStudents = new Student[stipendStudentsCount + 1];

		for (size_t i = 0, newIdx = 0; i < group.studentsCount; i++)
			if (group.students[i].grade >= minimumGrade)
				stipendStudents[newIdx++] = group.students[i];

		sortByCriteria(group, Criteria::sortByGrade);

		printArray(group);

		delete[] stipendStudents;
	}

	bool isFound(Group& group, unsigned int fN)
	{
		sortByCriteria(group, Criteria::sortByFN);

		unsigned int left = 0, right = group.studentsCount - 1;

		while (left <= right)
		{
			unsigned mid = left + (right - left) / 2;

			if (group.students[mid].fN < fN)
				left = mid + 1;
			else if (group.students[mid].fN > fN)
				right = mid - 1;
			else
				return true;
		}

		return false;
	}
}

int main()
{
	size_t N;
	cin >> N;

	GroupsNS::Student* students = new GroupsNS::Student[N];
	GroupsNS::Group group = { students, 0, 0 };

	/*GroupsNS::createGroup(group, N);
	GroupsNS::sortStipendStudents(group, 4);

	cout << GroupsNS::isFound(group, 6) << endl;

	cout << "Average grade: " << group.averageGrade << endl;*/

	delete[] students;

	return 0;
}