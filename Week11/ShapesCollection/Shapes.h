#pragma once

#include <iostream>

class Triangle;
class Rectangle;
class Circle;

class Shapes
{
protected:
	struct Point
	{
		int x = 0;
		int y = 0;

		Point() : x(0), y(0) {}
		Point(int x, int y) : x(x), y(y) {}

		double getDistance(const Point& other) const
		{
			double dx = x - other.x;
			double dy = y - other.y;

			return sqrt(dx * dx + dy * dy);
		}
	};

	const Point& getPointByIndex(size_t index) const;

private:
	Point* points = nullptr;
	size_t size = 0;

	void copyFrom(const Shapes& other);
	void moveFrom(Shapes&& other) noexcept;
	void free();

public:
	Shapes(size_t size);

	Shapes(const Shapes& other);
	Shapes& operator=(const Shapes& other);

	Shapes(Shapes&& other) noexcept;
	Shapes& operator=(Shapes&& other) noexcept;

	const size_t getSize() const;

	void addPoint(int x, int y, size_t index);
	void addPoint(const Point& p, size_t index);

	virtual double getArea() const = 0;
	virtual double getPerimeter() const;
	virtual bool isPointInside(int x, int y) const = 0;

	virtual Shapes* clone() const = 0;

	virtual bool intersectedWith(Shapes* other) = 0;

	virtual bool intersectedWithTriangle(Triangle* other) = 0;
	virtual bool intersectedWithRectangle(Rectangle* other) = 0;
	virtual bool intersectedWithCircle(Circle* other) = 0;

	virtual ~Shapes() noexcept;
};