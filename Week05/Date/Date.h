#pragma once
#include <iostream>

#define MONTHS_COUNT 12

class Date
{
private:
	size_t monthDays[MONTHS_COUNT] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	bool isLeapYear() const;

	size_t day = 1;
	size_t month = 1;
	size_t year = 1;

	mutable size_t dayOfWeek = 5;
	mutable bool isModified = true;

	bool isValid = true;
	void setValid();

public:
	Date();
	Date(size_t day, size_t month, size_t year);

	void setDay(size_t day);
	void setMonth(size_t month);
	void setYear(size_t year);

	const size_t getDay() const;
	const size_t getMonth() const;
	const size_t getYear() const;

	void goToNextDay();
	const size_t getDayOfWeek() const;

	bool isDateValid() const;

	void print() const;
};

const int compareDates(const Date& lhs, const Date& rhs);