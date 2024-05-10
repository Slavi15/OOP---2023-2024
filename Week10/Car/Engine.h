#pragma once

#include <fstream>

#include "CarPart.h"

class Engine : public CarPart
{
private:
	size_t horsePower = 0;

public:
	Engine() = default;
	Engine(size_t horsePower, size_t ID, const char* manufacturer, const char* description);

	Engine(const Engine& other) = default;
	Engine& operator=(const Engine& other) = default;

	Engine(Engine&& other) = default;
	Engine& operator=(Engine&& other) = default;

	const size_t getHorsePower() const;
	void setHorsePower(size_t horsePower);

	friend std::ostream& operator<<(std::ostream& os, const Engine& engine);
};