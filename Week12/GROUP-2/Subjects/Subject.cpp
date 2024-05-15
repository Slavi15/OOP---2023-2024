#include "Subject.h"

Subject::Subject() = default;

Subject::Subject(const char* subject, const char* lecturer, const char* const* asistents, size_t length, size_t neededPoints)
{
	setSubject(subject);
	setLecturer(lecturer);
	setAsistents(asistents, length);
	setAsistentsLength(length);
	setNeededPoints(neededPoints);
}

Subject::Subject(const Subject& other)
{
	copyFrom(other);
}

Subject& Subject::operator=(const Subject& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Subject::Subject(Subject&& other) noexcept
{
	moveFrom(std::move(other));
}

Subject& Subject::operator=(Subject&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

const char* Subject::getSubject() const
{
	return this->subject;
}

const char* Subject::getLecturer() const
{
	return this->lecturer;
}

const char* const* Subject::getAsistents() const
{
	return this->asistents;
}

const size_t Subject::getAsistentsLength() const
{
	return this->asistentsLength;
}

const size_t Subject::getNeededPoints() const
{
	return this->neededPoints;
}

void Subject::setSubject(const char* subject)
{
	if (!subject) return;

	delete[] this->subject;

	this->subject = new char[strlen(subject) + 1];
	strcpy(this->subject, subject);
}

void Subject::setLecturer(const char* lecturer)
{
	if (!lecturer) return;

	delete[] this->lecturer;

	this->lecturer = new char[strlen(lecturer) + 1];
	strcpy(this->lecturer, lecturer);
}

void Subject::setAsistents(const char* const* asistents, size_t length)
{
	if (!asistents) return;

	this->asistents = new char* [length];

	for (size_t i = 0; i < length; i++)
	{
		this->asistents[i] = new char[strlen(asistents[i]) + 1];
		strcpy(this->asistents[i], asistents[i]);
	}
}

void Subject::setAsistentsLength(size_t asistentsLength)
{
	this->asistentsLength = asistentsLength;
}

void Subject::setNeededPoints(size_t neededPoints)
{
	this->neededPoints = neededPoints;
}

void Subject::copyFrom(const Subject& other)
{
	this->subject = new char[strlen(other.subject) + 1];
	strcpy(this->subject, other.subject);

	this->lecturer = new char[strlen(other.lecturer) + 1];
	strcpy(this->lecturer, other.lecturer);

	this->asistents = copyArrayOfStrings(other.asistents, other.asistentsLength);

	this->asistentsLength = other.asistentsLength;
	this->neededPoints = other.neededPoints;
}

void Subject::moveFrom(Subject&& other)
{
	this->subject = other.subject;
	this->lecturer = other.lecturer;
	this->asistents = other.asistents;
	this->asistentsLength = other.asistentsLength;
	this->neededPoints = other.neededPoints;

	other.subject = nullptr;
	other.lecturer = nullptr;
	other.asistents = nullptr;
	other.asistentsLength = other.neededPoints = 0;
}

void Subject::free()
{
	for (size_t i = 0; i < this->asistentsLength; i++)
		delete[] this->asistents[i];

	delete[] this->asistents;
	delete[] this->subject;
	delete[] this->lecturer;

	this->asistents = nullptr;
	this->subject = nullptr;
	this->lecturer = nullptr;
	this->asistentsLength = this->neededPoints = 0;
}

Subject::~Subject() noexcept
{
	free();
}

static char** copyArrayOfStrings(const char* const* asistentsArray, size_t size)
{
	char** result = new char* [size];

	for (size_t i = 0; i < size; i++)
	{
		result[i] = new char[strlen(asistentsArray[i]) + 1];
		strcpy(result[i], asistentsArray[i]);
	}

	return result;
}
