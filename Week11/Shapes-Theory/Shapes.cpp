#include "Shapes.h"

Shapes::Shapes(size_t size) : size(size)
{
	this->points = new Point[this->size];
}

Shapes::Shapes(const Shapes& other)
{
	copyFrom(other);
}

Shapes& Shapes::operator=(const Shapes& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Shapes::Shapes(Shapes&& other) noexcept
{
	moveFrom(std::move(other));
}

Shapes& Shapes::operator=(Shapes&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

const size_t Shapes::getSize() const
{
	return this->size;
}

void Shapes::setPoint(int x, int y, size_t index)
{
	if (index >= getSize()) return;

	this->points[index].x = x;
	this->points[index].y = y;
}

void Shapes::setPoint(const Point& p, size_t index)
{
	if (index >= getSize()) return;

	this->points[index] = p;
}

double Shapes::getPerimeter() const
{
	assert(size >= 3);

	double perimeter = 0;
	for (size_t i = 0; i < getSize(); i++)
		perimeter += this->points[i].getDistance(this->points[i + 1]);

	return perimeter + this->points[0].getDistance(this->points[getSize() - 1]);
}

Shapes::~Shapes() noexcept
{
	free();
}

const Shapes::Point& Shapes::getPointAtIndex(size_t index) const
{
	return this->points[index];
}

void Shapes::copyFrom(const Shapes& other)
{
	this->size = other.size;

	this->points = new Point[this->size];
	for (size_t i = 0; i < this->size; i++)
		this->points[i] = other.points[i];
}

void Shapes::moveFrom(Shapes&& other) noexcept
{
	this->points = other.points;
	this->size = other.size;

	other.points = nullptr;
	other.size = 0;
}

void Shapes::free()
{
	delete[] this->points;

	this->points = nullptr;
	this->size = 0;
}
