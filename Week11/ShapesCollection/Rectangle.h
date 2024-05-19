#pragma once

#include "Shapes.h"

class Rectangle : public Shapes
{
public:
	Rectangle(int x1, int y1, int x3, int y3);
	Rectangle(const Point& p1, const Point& p3);

	double getArea() const override;
	bool isPointInside(int x, int y) const override;

	Shapes* clone() const override;

	bool intersectedWith(Shapes* other) override;

	bool intersectedWithRectangle(Rectangle* other) override;
	bool intersectedWithCircle(Circle* other) override;
	bool intersectedWithTriangle(Triangle* other) override;
};