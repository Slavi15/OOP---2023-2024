#include "Student.h"

Student::Student() = default;

Student::Student(const char* name, size_t age, size_t FN) : Person(name, age)
{
	setFN(FN);
}

const size_t Student::getFN() const
{
	return this->FN;
}

void Student::setFN(size_t FN)
{
	this->FN = FN;
}
