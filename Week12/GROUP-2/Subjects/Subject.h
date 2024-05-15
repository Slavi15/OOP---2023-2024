#pragma once
#pragma warning (disable : 4996)

#include <iostream>

class Subject
{
private:
	char* subject = nullptr;
	char* lecturer = nullptr;
	char** asistents = nullptr;
	size_t asistentsLength = 0;
	size_t neededPoints = 0;

	void copyFrom(const Subject& other);
	void moveFrom(Subject&& other);
	void free();

public:
	virtual double gradeToPass() const = 0;
	virtual const char* getSubjectName() const = 0;

	virtual Subject* clone() const = 0;

	Subject();
	Subject(const char* subject, const char* lecturer, const char* const* asistents, size_t length, size_t neededPoints);

	Subject(const Subject& other);
	Subject& operator=(const Subject& other);

	Subject(Subject&& other) noexcept;
	Subject& operator=(Subject&& other) noexcept;

	const char* getSubject() const;
	const char* getLecturer() const;
	const char* const* getAsistents() const;
	const size_t getAsistentsLength() const;
	const size_t getNeededPoints() const;

	void setSubject(const char* subject);
	void setLecturer(const char* lecturer);
	void setAsistents(const char* const* asistents, size_t length);
	void setAsistentsLength(size_t asistentsLength);
	void setNeededPoints(size_t neededPoints);

	virtual ~Subject() noexcept;
};