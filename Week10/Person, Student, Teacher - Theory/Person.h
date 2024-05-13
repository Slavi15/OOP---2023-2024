#pragma once
#pragma warning (disable : 4996)

#include <iostream>

class Person
{
private:
	char* name = nullptr;
	size_t age = 0;

	void copyFrom(const Person& other);
	void moveFrom(Person&& other) noexcept;
	void free();

protected:
	void setName(const char* name);
	void setAge(size_t age);

public:
	Person();
	Person(const char* name, size_t age);

	Person(const Person& other);
	Person& operator=(const Person& other);

	Person(Person&& other) noexcept;
	Person& operator=(Person&& other) noexcept;

	const char* getName() const;
	const size_t getAge() const;

	~Person() noexcept;
};