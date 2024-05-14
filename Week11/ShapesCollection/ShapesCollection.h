#pragma once

#include "Shapes.h"

class ShapesCollection
{
private:
	Shapes** shapes = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	ShapesCollection(size_t newSize);

	const unsigned int getNextPowerOfTwo(unsigned int n) const;
	const unsigned int allocateCapacity(unsigned int size) const;

	void resize(size_t newCapacity);

	void copyFrom(const ShapesCollection& other);
	void moveFrom(ShapesCollection&& other) noexcept;
	void free();

public:
	ShapesCollection();

	ShapesCollection(const ShapesCollection& other);
	ShapesCollection& operator=(const ShapesCollection& other);

	ShapesCollection(ShapesCollection&& other) noexcept;
	ShapesCollection& operator=(ShapesCollection&& other) noexcept;

	const size_t getSize() const;
	const size_t getCapacity() const;

	void push_back(Shapes* shape);
	void push_back(Shapes*&& shape);

	void pop_back();

	~ShapesCollection() noexcept;
};