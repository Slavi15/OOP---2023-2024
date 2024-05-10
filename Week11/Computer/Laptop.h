#pragma once

#include "Computer.h"

class Laptop : public Computer
{
public:
	const char* getComputerType() const override;
	const char* getGadgets() const override;
}