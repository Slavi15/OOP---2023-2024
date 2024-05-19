#include "ShapesContainer.h"

#include "Triangle.h"
#include "Rectangle.h"
#include "Circle.h"

ShapesContainer::ShapesContainer() : ShapesContainer(4) {}

ShapesContainer::ShapesContainer(size_t newSize) : size(0)
{
	this->capacity = allocateCapacity(newSize);
	this->container = new Shapes * [this->capacity];
}

ShapesContainer::ShapesContainer(const ShapesContainer& other)
{
	copyFrom(other);
}

ShapesContainer& ShapesContainer::operator=(const ShapesContainer& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

ShapesContainer::ShapesContainer(ShapesContainer&& other) noexcept
{
	moveFrom(std::move(other));
}

ShapesContainer& ShapesContainer::operator=(ShapesContainer&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

const size_t ShapesContainer::getSize() const
{
	return this->size;
}

const size_t ShapesContainer::getCapacity() const
{
	return this->capacity;
}

void ShapesContainer::addShape(Shapes* shape)
{
	if (getSize() >= getCapacity())
		resize(getCapacity() * 2);

	this->container[this->size++] = shape;
	shape = nullptr;
}

void ShapesContainer::addTriangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
	Triangle* newTriangle = new Triangle(x1, y1, x2, y2, x3, y3);
	addShape(newTriangle);
}

void ShapesContainer::addRectangle(int x1, int y1, int x3, int y3)
{
	Rectangle* newRectangle = new Rectangle(x1, y1, x3, y3);
	addShape(newRectangle);
}

void ShapesContainer::addCircle(int x, int y, double radius)
{
	Circle* newCircle = new Circle(x, y, radius);
	addShape(newCircle);
}

void ShapesContainer::remove(size_t index)
{
	if (index >= getSize()) return;

	if (getSize())
		this->size--;
	else
		return;

	std::swap(this->container[index], this->container[getSize()]);

	if (getSize() * 4 <= getCapacity() && getCapacity() > 1)
		resize(getCapacity() / 2);
}

double ShapesContainer::getAreaByIndex(size_t index) const
{
	if (index >= getSize()) return 0;

	return this->container[index]->getArea();
}

double ShapesContainer::getPerimeterByIndex(size_t index) const
{
	if (index >= getSize()) return 0;

	return this->container[index]->getPerimeter();
}

bool ShapesContainer::isPointInsideByIndex(size_t index, int x, int y) const
{
	if (index >= getSize()) return false;

	return this->container[index]->isPointInside(x, y);
}

const Shapes* ShapesContainer::operator[](size_t index) const
{
	return this->container[index];
}

Shapes* ShapesContainer::operator[](size_t index)
{
	return this->container[index];
}

void ShapesContainer::printAreas() const
{
	for (size_t i = 0; i < getSize(); i++)
		std::cout << this->container[i]->getArea() << std::endl;
}

void ShapesContainer::printPerimeters() const
{
	for (size_t i = 0; i < getSize(); i++)
		std::cout << this->container[i]->getPerimeter() << std::endl;
}

ShapesContainer::~ShapesContainer() noexcept
{
	free();
}

void ShapesContainer::resize(size_t newCapacity)
{
	Shapes** newShapes = new Shapes * [newCapacity];
	for (size_t i = 0; i < getSize(); i++)
		newShapes[i] = this->container[i];

	delete[] this->container;
	this->container = newShapes;
	this->capacity = newCapacity;
}

const unsigned int ShapesContainer::getNextPowerOfTwo(unsigned int n) const
{
	if (n == 0) return 1;

	while (n & (n - 1))
		n &= (n - 1);

	return n << 1;
}

const unsigned int ShapesContainer::allocateCapacity(unsigned int size) const
{
	return std::max(getNextPowerOfTwo(size + 1), 8u);
}

void ShapesContainer::copyFrom(const ShapesContainer& other)
{
	this->size = other.size;
	this->capacity = other.capacity;

	this->container = new Shapes * [this->capacity];
	for (size_t i = 0; i < this->capacity; i++)
		this->container[i] = other.container[i]->clone();
}

void ShapesContainer::moveFrom(ShapesContainer&& other) noexcept
{
	this->container = other.container;
	this->size = other.size;
	this->capacity = other.capacity;

	other.container = nullptr;
	other.size = other.capacity = 0;
}

void ShapesContainer::free()
{
	delete[] this->container;

	this->container = nullptr;
	this->size = this->capacity = 0;
}
