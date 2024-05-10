#pragma once

#include "Computer.h"

class GamingConsole : public Computer
{
public:
	const char* getComputerType() const override;
	const char* getGadgets() const override;
}