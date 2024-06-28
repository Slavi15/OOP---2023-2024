#pragma once

#include <iostream>
#include <fstream>

#define MAX_DAYS 31
#define DAYS_OF_WEEK 7

class EventJanuary
{
private:
	uint32_t days = 0;

	void readFromFile(std::ifstream& ifs);
	void saveToFile(std::ofstream& ofs) const;

public:
	void addDay(size_t day);
	void removeDay(size_t day);

	bool containsDay(size_t day) const;

	size_t getDaysFromDayOfWeek(size_t weekDay) const;

	void readFromFile(const char* fileName);
	void saveToFile(const char* fileName) const;

	friend EventJanuary getUnion(const EventJanuary& lhs, const EventJanuary& rhs);
	friend EventJanuary getIntersection(const EventJanuary& lhs, const EventJanuary& rhs);
};