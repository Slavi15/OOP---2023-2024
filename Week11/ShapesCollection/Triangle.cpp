#include "Triangle.h"

Triangle::Triangle(int x1, int y1, int x2, int y2, int x3, int y3) : Shapes(3)
{
	addPoint(x1, y1, 0);
	addPoint(x2, y2, 1);
	addPoint(x3, y3, 2);
}

Triangle::Triangle(const Point& p1, const Point& p2, const Point& p3) : Shapes(3)
{
	addPoint(p1, 0);
	addPoint(p2, 1);
	addPoint(p3, 2);
}

double Triangle::getArea() const
{
	// Hero's Formula
	/*double halfPerimeter = getPerimeter() / 2;

	double sideA = getPointAtIndex(0).getDistance(getPointAtIndex(1));
	double sideB = getPointAtIndex(1).getDistance(getPointAtIndex(2));
	double sideC = getPointAtIndex(0).getDistance(getPointAtIndex(2));

	return sqrt(halfPerimeter * (halfPerimeter - sideA) * (halfPerimeter - sideB) * (halfPerimeter - sideC));*/
	// Hero's Formula

	// Determinant
	const Point& p1 = getPointByIndex(0);
	const Point& p2 = getPointByIndex(1);
	const Point& p3 = getPointByIndex(2);

	return abs(p1.x * p2.y + p2.x * p3.y + p3.x * p1.y - p1.y * p2.x - p2.y * p3.x - p3.y * p1.x) / 2;
	// Determinant
}

bool Triangle::isPointInside(int x, int y) const
{
	Point p(x, y);

	Triangle t1(getPointByIndex(0), getPointByIndex(1), p);
	Triangle t2(getPointByIndex(0), getPointByIndex(2), p);
	Triangle t3(getPointByIndex(1), getPointByIndex(2), p);

	return (t1.getArea() + t2.getArea() + t3.getArea() - getArea()) <= std::numeric_limits<double>::epsilon();
}

Shapes* Triangle::clone() const
{
	return new Triangle(*this);
}

bool Triangle::intersectedWith(Shapes* other)
{
	return other->intersectedWithTriangle(this);
}

bool Triangle::intersectedWithTriangle(Triangle* other)
{
	std::cout << "Triangle + Triangle" << std::endl;
	return true;
}

bool Triangle::intersectedWithRectangle(Rectangle* other)
{
	std::cout << "Triangle + Rectangle" << std::endl;
	return true;
}

bool Triangle::intersectedWithCircle(Circle* other)
{
	std::cout << "Triangle + Circle" << std::endl;
	return true;
}
