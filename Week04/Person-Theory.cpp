#include <iostream>
#pragma warning (disable: 4996)

#define MAX_NAME_LENGTH 20
#define AGE_MIN 5
#define AGE_MAX 90

class Person
{
private:
	char name[MAX_NAME_LENGTH + 1] = "";
	size_t age = AGE_MIN;

	const bool isCapitalLetter(char ch) const;
	const bool isLowerLetter(char ch) const;
	const bool isValidName(const char* name) const;
	const bool isValidAge(size_t age) const;

public:
	Person();
	Person(const char* name, size_t age);

	const char* getName() const;
	const size_t getAge() const;

	void setName(const char* name);
	void setAge(size_t age);
};

Person::Person() = default;

Person::Person(const char* name, size_t age)
{
	setName(name);
	setAge(age);
}

const bool Person::isCapitalLetter(char ch) const
{
	return ch >= 'A' && ch <= 'Z';
}

const bool Person::isLowerLetter(char ch) const
{
	return ch >= 'a' && ch <= 'z';
}

const bool Person::isValidName(const char* name) const
{
	if (!name) return false;

	if (!isCapitalLetter(*name)) return false;
	name++;

	while (*name)
	{
		if (!isLowerLetter(*name))
			return false;

		name++;
	}

	return true;
}

const bool Person::isValidAge(size_t age) const
{
	return age >= AGE_MIN && age <= AGE_MAX;
}

const char* Person::getName() const
{
	return name;
}

const size_t Person::getAge() const
{
	return age;
}

void Person::setName(const char* name)
{
	if (!name) return;

	if (strlen(name) <= MAX_NAME_LENGTH && isValidName(name))
		strcpy(this->name, name);
}

void Person::setAge(size_t age)
{
	if (!isValidAge(age))
		this->age = 5;

	this->age = age;
}

int main()
{
	Person("Slavi", 19);

	return 0;
}