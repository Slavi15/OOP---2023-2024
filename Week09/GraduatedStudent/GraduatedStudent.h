#pragma once
#pragma warning (disable : 4996)

#include <iostream>

#define QUOTE_MAX_LENGTH 30

class GraduatedStudent
{
private:
	char* name = nullptr;
	int* grades = nullptr;
	size_t gradesCount = 0;
	char quote[QUOTE_MAX_LENGTH + 1];

	void copyFrom(const GraduatedStudent& other);
	void moveFrom(GraduatedStudent&& other) noexcept;
	void free();

public:
	GraduatedStudent();
	GraduatedStudent(const char* name, const int* grades, size_t gradesCount, const char* quote);

	GraduatedStudent(const GraduatedStudent& other);
	GraduatedStudent& operator=(const GraduatedStudent& other);

	GraduatedStudent(GraduatedStudent&& other) noexcept;
	GraduatedStudent& operator=(GraduatedStudent&& other) noexcept;

	const char* getName() const;
	const int* getGrades() const;
	const size_t getGradesCount() const;
	const char* getQuote() const;

	void setName(const char* name);
	void setGrades(const int* grades);
	void setGradesCount(size_t gradesCount);
	void setQuote(const char* quote);

	~GraduatedStudent() noexcept;
};