#include "Time.h"

Time::Time() = default;

Time::Time(size_t hrs, size_t mins, size_t secs)
{
	setHours(hrs);
	setMinutes(mins);
	setSeconds(secs);
}

const size_t Time::getTime() const
{
	return seconds;
}

bool Time::validateAndSet(size_t lowerBound, size_t upperBound, size_t currentValue, size_t newValue, size_t mult)
{
	if (newValue >= lowerBound && newValue <= upperBound)
	{
		(seconds -= (currentValue * mult)) += (newValue * mult);
		return true;
	}

	return false;
}

const int Time::getHours() const
{
	return seconds / SECONDS_IN_HOUR;
	// seconds / 60
}

const int Time::getMinutes() const
{
	return (seconds / SECONDS_IN_MINUTE) % SECONDS_IN_MINUTE;
	// (seconds / 60) % 60
}

const int Time::getSeconds() const
{
	return seconds % SECONDS_IN_MINUTE;
	// seconds % 60
}

bool Time::setHours(size_t hrs)
{
	return validateAndSet(0, 23, getHours(), hrs, SECONDS_IN_HOUR);
}

bool Time::setMinutes(size_t mins)
{
	return validateAndSet(0, 59, getMinutes(), mins, SECONDS_IN_MINUTE);
}

bool Time::setSeconds(size_t secs)
{
	return validateAndSet(0, 59, getSeconds(), secs, 1);
}

const size_t Time::getTimeTillMidnight() const
{
	return SECONDS_IN_DAY - seconds;
}

const int Time::isDinnerTime() const
{
	size_t lowerBound = (20 * SECONDS_IN_HOUR) + (30 * SECONDS_IN_MINUTE);
	size_t upperBound = 22 * SECONDS_IN_HOUR;

	return seconds >= lowerBound && seconds <= upperBound;
}

const bool Time::isPartyTime() const
{
	return getHours() >= 23 || getHours() <= 6;
}

Time Time::getDifference(const Time& time)
{
	Time t;

	t.setSeconds(myAbs(getSeconds() - time.getSeconds()));
	t.setMinutes(myAbs(getMinutes() - time.getMinutes()));
	t.setHours(myAbs(getHours() - time.getHours()));

	return t;
}

void Time::tick()
{
	(++seconds) %= SECONDS_IN_DAY;
}

void Time::print() const
{
	std::cout << std::setw(2) << std::setfill('0') << getHours() << ":"
		<< std::setw(2) << std::setfill('0') << getMinutes() << ":"
		<< std::setw(2) << std::setfill('0') << getSeconds();
}

const int compareTimes(const Time& lhs, const Time& rhs)
{
	if (lhs.getHours() < rhs.getHours())
		return -1;
	else if (lhs.getHours() > rhs.getHours())
		return 1;
	else
	{
		if (lhs.getMinutes() < rhs.getMinutes())
			return -1;
		else if (lhs.getMinutes() > rhs.getMinutes())
			return 1;
		else
		{
			if (lhs.getSeconds() < rhs.getSeconds())
				return -1;
			else if (lhs.getSeconds() > rhs.getSeconds())
				return 1;
			else
				return 0;
		}
	}
}