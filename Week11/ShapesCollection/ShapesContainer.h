#pragma once

#include "Shapes.h"

class ShapesContainer
{
private:
	Shapes** container = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	ShapesContainer(size_t newSize);
	void resize(size_t newCapacity);

	const unsigned int getNextPowerOfTwo(unsigned int n) const;
	const unsigned int allocateCapacity(unsigned int size) const;

	void copyFrom(const ShapesContainer& other);
	void moveFrom(ShapesContainer&& other) noexcept;
	void free();

	void addShape(Shapes* shape);

public:
	ShapesContainer();

	ShapesContainer(const ShapesContainer& other);
	ShapesContainer& operator=(const ShapesContainer& other);

	ShapesContainer(ShapesContainer&& other) noexcept;
	ShapesContainer& operator=(ShapesContainer&& other) noexcept;

	const size_t getSize() const;
	const size_t getCapacity() const;

	void addTriangle(int x1, int y1, int x2, int y2, int x3, int y3);
	void addRectangle(int x1, int y1, int x3, int y3);
	void addCircle(int x, int y, double radius);

	void remove(size_t index);

	double getAreaByIndex(size_t index) const;
	double getPerimeterByIndex(size_t index) const;
	bool isPointInsideByIndex(size_t index, int x, int y) const;

	const Shapes* operator[](size_t index) const;
	Shapes* operator[](size_t index);

	void printAreas() const;
	void printPerimeters() const;

	~ShapesContainer() noexcept;
};