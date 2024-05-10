#pragma once

#include "Computer.h"

class PC : public Computer
{
public:
	const char* getComputerType() const override;
	const char* getGadgets() const override;
};