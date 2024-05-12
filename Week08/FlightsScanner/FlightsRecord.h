#pragma once
#pragma warning (disable : 4996)

#include <iostream>

class FlightsRecord
{
private:
	void copyFrom(const FlightsRecord& other);
	void moveFrom(FlightsRecord&& other) noexcept;
	void free();

protected:
	char* origin = nullptr;
	char* destination = nullptr;
	size_t prize = 0;

public:
	FlightsRecord();
	FlightsRecord(const char* origin, const char* destination, size_t prize);

	FlightsRecord(const FlightsRecord& other);
	FlightsRecord& operator=(const FlightsRecord& other);

	FlightsRecord(FlightsRecord&& other) noexcept;
	FlightsRecord& operator=(FlightsRecord&& other) noexcept;

	const char* getOrigin() const;
	const char* getDestination() const;
	const size_t getPrize() const;

	void setOrigin(const char* origin);
	void setDestination(const char* destination);
	void setPrize(size_t prize);

	~FlightsRecord() noexcept;
};