#pragma once

#include <iostream>
#include <iomanip>

#define SECONDS_IN_HOUR 3600
#define SECONDS_IN_MINUTE 60
#define SECONDS_IN_DAY 24 * 3600

#define myAbs(a) a > 0 ? a : -a

class Time
{
private:
	size_t seconds = 0;

	bool validateAndSet(size_t lowerBound, size_t upperBound, size_t currentValue, size_t newValue, size_t mult);

public:
	Time();
	Time(size_t hrs, size_t mins, size_t secs);

	const size_t getTime() const;

	const int getHours() const;
	const int getMinutes() const;
	const int getSeconds() const;

	bool setHours(size_t hrs);
	bool setMinutes(size_t mins);
	bool setSeconds(size_t secs);

	void tick();
	
	const size_t getTimeTillMidnight() const;
	const int isDinnerTime() const;
	const bool isPartyTime() const;

	Time getDifference(const Time& time);

	void print() const;
};

const int compareTimes(const Time& lhs, const Time& rhs);