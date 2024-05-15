#pragma once

#include "Subject.h"

class DIS : public Subject
{
public:
	double gradeToPass() const override;
	const char* getSubjectName() const override;

	Subject* clone() const override;

	DIS(const char* subject, const char* lecturer, const char* const* asistents, size_t length, size_t neededPoints);
};