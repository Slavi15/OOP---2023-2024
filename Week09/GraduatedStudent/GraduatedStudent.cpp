#include "GraduatedStudent.h"

GraduatedStudent::GraduatedStudent() = default;

GraduatedStudent::GraduatedStudent(const char* name, const int* grades, size_t gradesCount, const char* quote)
{
	setName(name);
	setGradesCount(gradesCount);
	setGrades(grades);
	setQuote(quote);
}

GraduatedStudent::GraduatedStudent(const GraduatedStudent& other)
{
	copyFrom(other);
}

GraduatedStudent& GraduatedStudent::operator=(const GraduatedStudent& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

GraduatedStudent::GraduatedStudent(GraduatedStudent&& other) noexcept
{
	moveFrom(std::move(other));
}

GraduatedStudent& GraduatedStudent::operator=(GraduatedStudent&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

const char* GraduatedStudent::getName() const
{
	return this->name;
}

const int* GraduatedStudent::getGrades() const
{
	return this->grades;
}

const size_t GraduatedStudent::getGradesCount() const
{
	return this->gradesCount;
}

const char* GraduatedStudent::getQuote() const
{
	return this->quote;
}

void GraduatedStudent::setName(const char* name)
{
	if (!name)
		throw std::runtime_error("NULLPTR!");

	this->name = new (std::nothrow) char[strlen(name) + 1];
	strcpy(this->name, name);
}

void GraduatedStudent::setGrades(const int* grades)
{
	if (!grades)
		throw std::runtime_error("NULLPTR!");

	this->grades = new (std::nothrow) int[getGradesCount()];

	for (size_t i = 0; i < getGradesCount(); i++)
		this->grades[i] = grades[i];
}

void GraduatedStudent::setGradesCount(size_t gradesCount)
{
	this->gradesCount = gradesCount;
}

void GraduatedStudent::setQuote(const char* quote)
{
	if (!quote)
		throw std::runtime_error("NULLPTR!");

	if (strlen(quote) > QUOTE_MAX_LENGTH)
		throw std::out_of_range("Quote is too long!");

	strcpy(this->quote, quote);
}

GraduatedStudent::~GraduatedStudent() noexcept
{
	free();
}

void GraduatedStudent::copyFrom(const GraduatedStudent& other)
{
	this->name = new char[strlen(other.name) + 1];
	strcpy(this->name, other.name);

	this->gradesCount = other.gradesCount;

	this->grades = new int[this->gradesCount];
	for (size_t i = 0; i < this->gradesCount; i++)
		this->grades[i] = other.grades[i];

	strcpy(this->quote, other.quote);
}

void GraduatedStudent::moveFrom(GraduatedStudent&& other) noexcept
{
	this->name = other.name;
	this->grades = other.grades;
	this->gradesCount = other.gradesCount;
	strcpy(this->quote, other.quote);

	other.name = nullptr;
	other.grades = nullptr;
	other.gradesCount = 0;
	strcpy(other.quote, "");
}

void GraduatedStudent::free()
{
	delete[] this->name;
	delete[] this->grades;

	this->name = nullptr;
	this->grades = nullptr;
	this->gradesCount = 0;
	strcpy(this->quote, "");
}