#include "Circle.h"

Circle::Circle(int x, int y, double radius) : Shapes(1)
{
	setRadius(radius);
	addPoint(x, y, 0);
}

Circle::Circle(const Point& p, double radius) : Shapes(1)
{
	setRadius(radius);
	addPoint(p, radius);
}

const double Circle::getRadius() const
{
	return this->radius;
}

void Circle::setRadius(double radius)
{
	if (radius <= 0) return;

	this->radius = radius;
}

double Circle::getArea() const
{
	return M_PI * getRadius() * getRadius();
}

double Circle::getPerimeter() const
{
	return 2 * M_PI * getRadius();
}

bool Circle::isPointInside(int x, int y) const
{
	Shapes::Point p(x, y);

	return getPointByIndex(0).getDistance(p) < getRadius();
}

Shapes* Circle::clone() const
{
	return new Circle(*this);
}

bool Circle::intersectedWith(Shapes* other)
{
	return other->intersectedWithCircle(this);
}

bool Circle::intersectedWithCircle(Circle* other)
{
	std::cout << "Circle + Circle" << std::endl;
	return true;
}

bool Circle::intersectedWithTriangle(Triangle* other)
{
	std::cout << "Circle + Triangle" << std::endl;
	return true;
}

bool Circle::intersectedWithRectangle(Rectangle* other)
{
	std::cout << "Circle + Rectangle" << std::endl;
	return true;
}
