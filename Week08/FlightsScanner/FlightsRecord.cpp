#include "FlightsRecord.h"

FlightsRecord::FlightsRecord() : FlightsRecord("", "", 0) {}

FlightsRecord::FlightsRecord(const char* origin, const char* destination, size_t prize)
{
	if (!origin || !destination)
		throw std::runtime_error("NULLPTR!");

	setOrigin(origin);
	setDestination(destination);
	setPrize(prize);
}

FlightsRecord::FlightsRecord(const FlightsRecord& other)
{
	copyFrom(other);
}

FlightsRecord& FlightsRecord::operator=(const FlightsRecord& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

FlightsRecord::FlightsRecord(FlightsRecord&& other) noexcept
{
	moveFrom(std::move(other));
}

FlightsRecord& FlightsRecord::operator=(FlightsRecord&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

const char* FlightsRecord::getOrigin() const
{
	return this->origin;
}

const char* FlightsRecord::getDestination() const
{
	return this->destination;
}

const size_t FlightsRecord::getPrize() const
{
	return this->prize;
}

void FlightsRecord::setOrigin(const char* origin)
{
	if (!origin)
		throw std::runtime_error("NULLPTR!");

	this->origin = new (std::nothrow) char[strlen(origin) + 1];
	strcpy(this->origin, origin);
}

void FlightsRecord::setDestination(const char* destination)
{
	if (!destination)
		throw std::runtime_error("NULLPTR!");

	this->destination = new (std::nothrow) char[strlen(destination) + 1];
	strcpy(this->destination, destination);
}

void FlightsRecord::setPrize(size_t prize)
{
	this->prize = prize;
}

FlightsRecord::~FlightsRecord() noexcept
{
	free();
}

void FlightsRecord::copyFrom(const FlightsRecord& other)
{
	this->origin = new char[strlen(other.origin) + 1];
	strcpy(this->origin, other.origin);

	this->destination = new char[strlen(other.destination) + 1];
	strcpy(this->destination, other.destination);

	this->prize = other.prize;
}

void FlightsRecord::moveFrom(FlightsRecord&& other) noexcept
{
	this->origin = other.origin;
	this->destination = other.destination;
	this->prize = other.prize;

	other.origin = nullptr;
	other.destination = nullptr;
	other.prize = 0;
}

void FlightsRecord::free()
{
	delete[] this->origin;
	delete[] this->destination;

	this->origin = nullptr;
	this->destination = nullptr;
	this->prize = 0;
}