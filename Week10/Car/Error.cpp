#include "Error.h"

insufficient_fuel_error::insufficient_fuel_error(const char* errorMessage) : std::logic_error(errorMessage) {}