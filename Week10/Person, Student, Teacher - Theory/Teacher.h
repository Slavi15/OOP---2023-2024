#pragma once
#pragma warning (disable : 4996)

#include "Person.h"

class Teacher : public Person
{
private:
	char** subjects = nullptr;
	size_t size = 0;

	void copyFrom(const Teacher& other);
	void moveFrom(Teacher&& other) noexcept;
	void free();

public:
	Teacher();
	Teacher(const char* name, size_t age, const char* const* subjects, size_t size);

	Teacher(const Teacher& other);
	Teacher& operator=(const Teacher& other);

	Teacher(Teacher&& other) noexcept;
	Teacher& operator=(Teacher&& other) noexcept;

	const size_t getSize() const;

	void setSize(size_t size);

	~Teacher() noexcept;
};