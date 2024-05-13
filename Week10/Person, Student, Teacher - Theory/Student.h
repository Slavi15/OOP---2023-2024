#pragma once

#include "Person.h"

class Student : public Person
{
private:
	size_t FN = 0;

public:
	Student();
	Student(const char* name, size_t age, size_t FN);

	const size_t getFN() const;

	void setFN(size_t FN);
};