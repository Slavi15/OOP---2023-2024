#include "EventJanuary.h"

void EventJanuary::addDay(size_t day)
{
	if (day == 0 || day > MAX_DAYS) return;

	this->days |= (1 << day);
}

void EventJanuary::removeDay(size_t day)
{
	if (day == 0 || day > MAX_DAYS) return;

	this->days &= (1 << day);
}

bool EventJanuary::containsDay(size_t day) const
{
	if (day == 0 || day > MAX_DAYS) return false;

	size_t mask = (1 << day);
	return (this->days & mask) == mask;
}

size_t EventJanuary::getDaysFromDayOfWeek(size_t weekDay) const
{
	if (weekDay == 0 || weekDay > DAYS_OF_WEEK) return 0;

	size_t result = 0;
	size_t offset = (weekDay == DAYS_OF_WEEK) ? 0 : weekDay; // !!!

	for (size_t i = 1 + offset; i <= MAX_DAYS; i += weekDay)
	{
		if (containsDay(i))
		{
			result++;
		}
	}

	return result;
}

void EventJanuary::readFromFile(std::ifstream& ifs)
{
	ifs.read(reinterpret_cast<char*>(&this->days), sizeof(uint32_t));
	ifs.close();
}

void EventJanuary::readFromFile(const char* fileName)
{
	if (!fileName) return;

	std::ifstream ifs(fileName, std::ios::in | std::ios::binary);

	if (!ifs.is_open()) return;

	return readFromFile(ifs);
}

void EventJanuary::saveToFile(std::ofstream& ofs) const
{
	ofs.write(reinterpret_cast<const char*>(&this->days), sizeof(uint32_t));
	ofs.close();
}

void EventJanuary::saveToFile(const char* fileName) const
{
	if (!fileName) return;

	std::ofstream ofs(fileName, std::ios::out | std::ios::binary);

	if (!ofs.is_open()) return;

	return saveToFile(ofs);
}

EventJanuary getUnion(const EventJanuary& lhs, const EventJanuary& rhs)
{
	EventJanuary toReturn;
	toReturn.days = (lhs.days | rhs.days);
	return toReturn;
}

EventJanuary getIntersection(const EventJanuary& lhs, const EventJanuary& rhs)
{
	EventJanuary toReturn;
	toReturn.days = (lhs.days & rhs.days);
	return toReturn;
}
