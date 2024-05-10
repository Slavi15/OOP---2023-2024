#pragma once
#pragma warning (disable : 4996)

#include <iostream>
#include <fstream>

class CarPart
{
private:
	size_t ID = 0;
	char* manufacturer = nullptr;
	char* description = nullptr;

	void copyFrom(const CarPart& other);
	void moveFrom(CarPart&& other) noexcept;
	void free();

public:
	CarPart();
	CarPart(size_t ID, const char* manufacturer, const char* description);

	CarPart(const CarPart& other);
	CarPart& operator=(const CarPart& other);

	CarPart(CarPart&& other) noexcept;
	CarPart& operator=(CarPart&& other) noexcept;

	const size_t getID() const;
	const char* getManufacturer() const;
	const char* getDescription() const;

	void setID(size_t ID);
	void setManufacturer(const char* manufacturer);
	void setDescription(const char* description);

	friend std::ostream& operator<<(std::ostream& os, const CarPart& carPart);

	~CarPart() noexcept;
};