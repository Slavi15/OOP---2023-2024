#include <iostream>

using std::cin;
using std::cout;
using std::endl;

namespace GroupsNS
{
	enum class Major { SI, IS, KN, PM, M, INF };

	struct Student
	{
		unsigned int fN;
		char name[100];
		double grade;
		Major major;
	};

	struct Group
	{
		Student* students;
		double averageGrade;
		size_t studentsCount;
	};

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

	void insertionSort(Student* students, size_t len)
	{
		if (!students)
			return;

		for (size_t i = 1; i < len; i++)
		{
			Student currentStudent = students[i];
			int currentIndex = i - 1;

			while (currentIndex >= 0 && students[currentIndex].grade > currentStudent.grade)
			{
				students[currentIndex + 1] = students[currentIndex];
				currentIndex--;
			}

			students[currentIndex + 1] = currentStudent;
		}
	}

	void printArray(const Student* students, size_t len)
	{
		if (!students)
			return;

		for (size_t i = 0; i < len; i++)
			cout << "Student: " << students[i].fN << ' ' << students[i].name << ' ' << students[i].grade << endl;
	}

	void sortStipendStudents(const Group& group, double minimumGrade)
	{
		unsigned int stipendStudentsCount = getStipendStudents(group, minimumGrade);

		Student* stipendStudents = new Student[stipendStudentsCount + 1];

		for (size_t i = 0, newIdx = 0; i < group.studentsCount; i++)
			if (group.students[i].grade >= minimumGrade)
				stipendStudents[newIdx++] = group.students[i];

		// Insertion Sort <=> elements are near to each other
		insertionSort(stipendStudents, stipendStudentsCount);

		printArray(stipendStudents, stipendStudentsCount);

		delete[] stipendStudents;
	}

	bool isFound(const Group& group, unsigned int fN)
	{
		insertionSort(group.students, group.studentsCount);

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
	unsigned int N;
	cin >> N;

	GroupsNS::Student* students = new GroupsNS::Student[N];
	GroupsNS::Group group = { students, 0, 0 };

	GroupsNS::createGroup(group, N);
	GroupsNS::sortStipendStudents(group, 4);

	cout << GroupsNS::isFound(group, 6) << endl;

	cout << "Average grade: " << group.averageGrade << endl;

	delete[] students;

	return 0;
}