#include <iostream>

class Teacher
{
private:
	enum class Subject { Maths, Physics, Chemistry };

	char* name = nullptr;
	size_t age = 0;
	Subject subject;
	double salary = 0.0;

public:
	Teacher(const char* name, size_t age, const char* subject, double salary);

	const char* getName() const;
	const size_t getAge() const;
	const char* getSubject(Subject subject) const;
	const double getSalary() const;

	void setName(const char* name);
	void setAge(size_t age);
	void setSubject(const char* subject);
	void setSalary(double salary);

	void freeTeacher();
};

Teacher::Teacher(const char* name, size_t age, const char* subject, double salary)
{
	setName(name);
	setAge(age);
	setSubject(subject);
	setSalary(salary);
}

void Teacher::setName(const char* name)
{
	if (!name) return;

	size_t length = strlen(name);
	this->name = new char[length + 1];
	strcpy(this->name, name);
}

void Teacher::setAge(size_t age)
{
	if (age >= 18 && age <= 70)
		this->age = age;
}

void Teacher::setSubject(const char* subject)
{
	if (!subject) return;

	if (strcmp(subject, "Maths") == 0)
		this->subject = Subject::Maths;
	else if (strcmp(subject, "Physics") == 0)
		this->subject = Subject::Physics;
	else if (strcmp(subject, "Chemistry") == 0)
		this->subject = Subject::Chemistry;
}

void Teacher::setSalary(double salary)
{
	if (salary > 500)
		this->salary = salary;
}

const char* Teacher::getName() const
{
	return name;
}

const size_t Teacher::getAge() const
{
	return age;
}

const char* Teacher::getSubject(const Subject subject) const
{
	switch (subject)
	{
	case Subject::Maths:
		return "Maths";
	case Subject::Physics:
		return "Physics";
	case Subject::Chemistry:
		return "Chemistry";
	default:
		return "Maths";
	}
}

const double Teacher::getSalary() const
{
	return salary;
}

void Teacher::freeTeacher()
{
	delete[] name;
	name = nullptr;
	age = 0;
	salary = 0.0;
}

int main()
{
	return 0;
}