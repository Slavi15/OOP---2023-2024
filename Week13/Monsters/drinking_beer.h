#pragma once

#include <iostream>

class drinking_beer : public std::logic_error
{
public:
	drinking_beer(const char* errorMessage);
};