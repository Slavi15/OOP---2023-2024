#include "Event.h"

Event::Event() = default;

Event::Event(const char* title, const Date& date, const Time& startTime, const Time& endTime) : _date(date), _startTime(startTime), _endTime(endTime)
{
	setTitle(title);
	validateTimes();
}

Event::Event(const char* title, size_t day, size_t month, size_t year, size_t startHours, size_t startMins, size_t startSeconds, size_t endHours, size_t endMins, size_t endSeconds)
	: _date(day, month, year), _startTime(startHours, startMins, startSeconds), _endTime(endHours, endMins, endSeconds)
{
	setTitle(title);
	validateTimes();
}

const char* Event::getTitle() const
{
	return _title;
}

const Date& Event::getDate() const
{
	return _date;
}

const Time& Event::getStartTime() const
{
	return _startTime;
}

const Time& Event::getEndTime() const
{
	return _endTime;
}

void Event::printEvent() const
{
	std::cout << "Event: " << _title << " : ";
	_date.print(); 
	std::cout << " : ";
	_startTime.print();
	std::cout << " - ";
	_endTime.print();
	std::cout << std::endl;
}

void Event::setTitle(const char* title)
{
	if (!title) return;

	if (strlen(title) < MAX_TITLE_LENGTH)
		strcpy(_title, title);
}

void Event::validateTimes()
{
	if (compareTimes(_startTime, _endTime) == 1)
		std::swap(_startTime, _endTime);
}