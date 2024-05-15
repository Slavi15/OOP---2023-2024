#pragma once

#include "Subject.h"

class OOP : public Subject
{
private:
	size_t bonusPoints = 0;

public:
	double gradeToPass() const override;
	const char* getSubjectName() const override;

	Subject* clone() const override;

	OOP(const char* subject, const char* lecturer, const char* const* asistents, size_t length, size_t neededPoints, size_t bonusPoints);

	const size_t getBonusPoints() const;
};