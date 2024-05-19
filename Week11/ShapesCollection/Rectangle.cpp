#include "Rectangle.h"

Rectangle::Rectangle(int x1, int y1, int x3, int y3) : Shapes(4)
{
	addPoint(x1, y1, 0);
	addPoint(x3, y3, 2);

	addPoint(x3, y1, 1);
	addPoint(x1, y3, 3);
}

Rectangle::Rectangle(const Point& p1, const Point& p3) : Shapes(4)
{
	addPoint(p1, 0);
	addPoint(p3, 2);

	addPoint(p3.x, p1.y, 1);
	addPoint(p1.x, p3.y, 3);
}

double Rectangle::getArea() const
{
	double sideA = getPointByIndex(0).getDistance(getPointByIndex(1));
	double sideB = getPointByIndex(0).getDistance(getPointByIndex(3));

	return sideA * sideB;
}

bool Rectangle::isPointInside(int x, int y) const
{
	return x >= getPointByIndex(0).x && x <= getPointByIndex(1).x && y >= getPointByIndex(0).y && y <= getPointByIndex(3).y;
}

Shapes* Rectangle::clone() const
{
	return new Rectangle(*this);
}

bool Rectangle::intersectedWith(Shapes* other)
{
	return other->intersectedWithRectangle(this);
}

bool Rectangle::intersectedWithRectangle(Rectangle* other)
{
	std::cout << "Rectangle + Rectangle" << std::endl;
	return true;
}

bool Rectangle::intersectedWithCircle(Circle* other)
{
	std::cout << "Rectangle + Circle" << std::endl;
	return true;
}

bool Rectangle::intersectedWithTriangle(Triangle* other)
{
	std::cout << "Rectangle + Triangle" << std::endl;
	return true;
}
