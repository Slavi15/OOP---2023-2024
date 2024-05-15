#include "OOP.h"

Subject* OOP::clone() const
{
	return new OOP(*this);
}

double OOP::gradeToPass() const
{
	return (getNeededPoints() + getBonusPoints()) * 0.2;
}

const char* OOP::getSubjectName() const
{
	return getSubject();
}

OOP::OOP(const char* subject, const char* lecturer, const char* const* asistents, size_t length, size_t neededPoints, size_t bonusPoints) :
	Subject(subject, lecturer, asistents, length, neededPoints), bonusPoints(bonusPoints) {}

const size_t OOP::getBonusPoints() const
{
	return this->bonusPoints;
}
