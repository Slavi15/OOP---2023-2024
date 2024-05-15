#include "DIS.h"

Subject* DIS::clone() const
{
	return new DIS(*this);
}

double DIS::gradeToPass() const
{
	return getNeededPoints() * 0.3;
}

const char* DIS::getSubjectName() const
{
	return getSubject();
}

DIS::DIS(const char* subject, const char* lecturer, const char* const* asistents, size_t length, size_t neededPoints) :
	Subject(subject, lecturer, asistents, length, neededPoints) {}
