#include "Date.h"

Date::Date() = default;

Date::Date(size_t day, size_t month, size_t year)
{
	setYear(year);
	setMonth(month);
	setDay(day);
}

void Date::setDay(size_t day)
{
	if (!isDateValid()) return;
	this->day = day;
	isModified = true;
	setValid();
}

void Date::setMonth(size_t month)
{
	if (!isDateValid()) return;
	this->month = month;
	isModified = true;
	setValid();
}

void Date::setYear(size_t year)
{
	if (!isDateValid()) return;
	this->year = year;

	isLeapYear() ? monthDays[1] = 29 : monthDays[1] = 28;

	isModified = true;
	setValid();
}

void Date::goToNextDay()
{
	if (!isDateValid()) return;

	if (year == 1916 && month == 3 && day == 31)
	{
		day = 14;
		month = 4;
	}
	else
	{
		day++;

		if (day > monthDays[month - 1])
		{
			day = 1;
			setMonth(month == 12 ? 1 : (month + 1));

			if (month == 1)
				setYear(year + 1);
		}
	}

	isModified = true;
}

const size_t Date::getDay() const
{
	return day;
}

const size_t Date::getMonth() const
{
	return month;
}

const size_t Date::getYear() const
{
	return year;
}

const size_t Date::getDayOfWeek() const
{
	if (!isDateValid()) return -1;

	if (!isModified) return dayOfWeek;

	Date initialDate(1, 1, 1);

	while (compareDates(initialDate, *this) != 0)
	{
		initialDate.goToNextDay();
		(++dayOfWeek) %= 7;
	}

	isModified = false;
	return dayOfWeek + 1;
}

void Date::setValid()
{
	isValid = !((month == 0 || month > 12) ||
		(day == 0 || day > monthDays[month - 1]) ||
		(year == 0) ||
		(year == 1916 && month == 4 && day < 14));
}

bool Date::isDateValid() const
{
	return isValid;
}

bool Date::isLeapYear() const
{
	return (year > 1916) ? 
		((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) : 
		year % 4 == 0;
}

void Date::print() const
{
	if (!isDateValid()) return;
	std::cout << "Date: " << day << "/" << month << "/" << year;
}

const int compareDates(const Date& lhs, const Date& rhs)
{
	if (lhs.getYear() < rhs.getYear())
		return -1;
	else if (lhs.getYear() > rhs.getYear())
		return 1;
	else
	{
		if (lhs.getMonth() < rhs.getMonth())
			return -1;
		else if (lhs.getMonth() > rhs.getMonth())
			return 1;
		else
		{
			if (lhs.getDay() < rhs.getDay())
				return -1;
			else if (lhs.getDay() > rhs.getDay())
				return 1;
			else
				return 0;
		}
	}
}