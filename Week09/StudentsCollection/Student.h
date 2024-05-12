#pragma once
#pragma warning (disable : 4996)

#include <iostream>

class Student
{
private:
	char* name = nullptr;
	size_t age = 0;

	void copyFrom(const Student& other);
	void moveFrom(Student&& other) noexcept;
	void free();

public:
	Student();
	Student(const char* name, size_t age);

	Student(const Student& other);
	Student& operator=(const Student& other);

	Student(Student&& other) noexcept;
	Student& operator=(Student&& other) noexcept;

	const char* getName() const;
	const size_t getAge() const;

	void setName(const char* name);
	void setAge(size_t age);

	~Student() noexcept;
};