#pragma once
#pragma warning (disable: 4996);

#include "Date.h"
#include "Time.h"

#define MAX_TITLE_LENGTH 20

class Event
{
private:
	char _title[MAX_TITLE_LENGTH + 1] = "";
	Date _date;
	Time _startTime;
	Time _endTime;

	void setTitle(const char* title);
	void validateTimes();

public:
	Event();
	Event(const char* title, const Date& date, const Time& startTime, const Time& endTime);
	Event(const char* title, size_t day, size_t month, size_t year,
		size_t startHours, size_t startMins, size_t startSeconds,
		size_t endHours, size_t endMins, size_t endSeconds);

	const char* getTitle() const;
	const Date& getDate() const;
	const Time& getStartTime() const;
	const Time& getEndTime() const;

	void printEvent() const;
};