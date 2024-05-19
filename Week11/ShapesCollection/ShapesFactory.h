#pragma once

#include "Shapes.h"

// FACTORY based on user input
class ShapesFactory
{
public:
	Shapes* createShape();
};