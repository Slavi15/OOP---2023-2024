#pragma once

#include <iostream>
#include <cassert>

enum class ShapesType { NONE, TRIANGLE, RECTANGLE, CIRCLE };

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

	const Point& getPointAtIndex(size_t index) const;

private:
	Point* points = nullptr;
	size_t size = 0;
	ShapesType type = ShapesType::NONE;

	void copyFrom(const Shapes& other);
	void moveFrom(Shapes&& other) noexcept;
	void free();

public:
	Shapes(size_t size, ShapesType type);

	Shapes(const Shapes& other);
	Shapes& operator=(const Shapes& other);

	Shapes(Shapes&& other) noexcept;
	Shapes& operator=(Shapes&& other) noexcept;

	const size_t getSize() const;

	void setPoint(int x, int y, size_t index);
	void setPoint(const Point& p, size_t index);

	virtual double getArea() const = 0;

	virtual double getPerimeter() const; // non-pure virtual function because the calculation of the perimeter for every is almost the same

	virtual bool isPointInside(int x, int y) const = 0;

	virtual Shapes* clone() const = 0;

	virtual ~Shapes() noexcept;
};