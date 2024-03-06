#include <iostream>
#include <fstream>
#include <sstream>

namespace CONSTANTS
{
	const unsigned int MAX_NAME_LENGTH = 16;
	const unsigned int MAX_STUDENTS_COUNT = 1024;
}

namespace StudentsNS
{
	enum class HairColors { Brown, Black, Blonde, Red, White };

	struct Student
	{
		char firstName[CONSTANTS::MAX_NAME_LENGTH + 1];
		char lastName[CONSTANTS::MAX_NAME_LENGTH + 1];
		unsigned int facultyNum;
		double averageGrade;
		HairColors hairColor;
	};

	struct Students
	{
		Student students[CONSTANTS::MAX_STUDENTS_COUNT];
		size_t currentRows = 0;
	};

	void readStudent(Student& student, const char* row)
	{
		if (!row) return;

		std::stringstream ss(row);

		unsigned int columnIndex = 0;

		while (!ss.eof())
		{
			switch (columnIndex)
			{
			case 0:
				ss.getline(student.firstName, 1024, ',');
				break;
			case 1:
				ss.getline(student.lastName, 1024, ',');
				break;
			case 2:
				ss >> student.facultyNum;
				ss.ignore();
				break;
			case 3:
				ss >> student.averageGrade;
				ss.ignore();
				break;
			case 4:
				int hairColor;
				ss >> hairColor;
				student.hairColor = (HairColors)hairColor;
				break;
			}

			columnIndex++;
		}
	}

	Students readStudents(std::ifstream& ifs)
	{
		Students students;

		char buffer[1024];
		while (!ifs.eof())
		{
			ifs.getline(buffer, 1024);
			readStudent(students.students[students.currentRows++], buffer);
		}

		return students;
	}

	Students readStudents(const char* fileName)
	{
		if (!fileName) return {};

		std::ifstream ifs(fileName, std::ios::in);
		if (!ifs.is_open()) return {};

		return readStudents(ifs);
	}

	void writeStudent(std::ofstream& ofs, const Student& student)
	{
		ofs << student.firstName << ',' <<
			student.lastName << ',' <<
			student.facultyNum << ',' <<
			student.averageGrade << ',' << (int)student.hairColor << std::endl;
	}

	void writeToFile(std::ofstream& ofs, const Students& students)
	{
		for (size_t i = 0; i < students.currentRows; i++)
			writeStudent(ofs, students.students[i]);
	}

	void writeToFile(const char* fileName, const Students& students)
	{
		if (!fileName) return;

		std::ofstream ofs(fileName, std::ios::out);
		if (!ofs.is_open()) return;

		return writeToFile(ofs, students);
	}
}

int main()
{
	StudentsNS::Students students = StudentsNS::readStudents("input.txt");
	StudentsNS::writeToFile("output.txt", students);

	return 0;
}