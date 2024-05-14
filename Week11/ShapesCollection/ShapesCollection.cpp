#include "ShapesCollection.h"

ShapesCollection::ShapesCollection() : ShapesCollection(4) {}

ShapesCollection::ShapesCollection(size_t newSize) : size(newSize)
{
	this->capacity = allocateCapacity(newSize);
	this->shapes = new Shapes * [this->capacity] { nullptr };
}

ShapesCollection::ShapesCollection(const ShapesCollection& other)
{
	copyFrom(other);
}

ShapesCollection& ShapesCollection::operator=(const ShapesCollection& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

ShapesCollection::ShapesCollection(ShapesCollection&& other) noexcept
{
	moveFrom(std::move(other));
}

ShapesCollection& ShapesCollection::operator=(ShapesCollection&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

const size_t ShapesCollection::getSize() const
{
	return this->size;
}

const size_t ShapesCollection::getCapacity() const
{
	return this->capacity;
}

void ShapesCollection::push_back(Shapes* shape)
{
	if (getSize() >= getCapacity())
		resize(getCapacity() * 2);

	this->shapes[this->size++] = shape;
}

void ShapesCollection::push_back(Shapes*&& shape)
{
	if (getSize() >= getCapacity())
		resize(getCapacity() * 2);

	this->shapes[this->size++] = std::move(shape);
}

void ShapesCollection::pop_back()
{
	if (getSize())
		this->size--;
	else
		return;

	delete this->shapes[getSize()];
	this->shapes[getSize()] = nullptr;

	if ((getSize() * 4) <= getCapacity() && getCapacity() > 1)
		resize(getCapacity() / 2);
}

ShapesCollection::~ShapesCollection() noexcept	
{
	free();
}

const unsigned int ShapesCollection::getNextPowerOfTwo(unsigned int n) const
{
	if (n == 0) return 1;

	while (n & (n - 1))
		n &= (n - 1);

	return n << 1;
}

const unsigned int ShapesCollection::allocateCapacity(unsigned int size) const
{
	return std::max(getNextPowerOfTwo(size + 1), 8u);
}

void ShapesCollection::resize(size_t newCapacity)
{
	Shapes** newShapes = new Shapes * [newCapacity];
	for (size_t i = 0; i < getSize(); i++)
		newShapes[i] = this->shapes[i]; // !!! no cloning !!! only in copyFrom !!!

	delete[] this->shapes;
	this->shapes = newShapes;
	this->capacity = newCapacity;
}

void ShapesCollection::copyFrom(const ShapesCollection& other)
{
	this->size = other.size;
	this->capacity = other.capacity;

	this->shapes = new Shapes * [this->capacity];
	for (size_t i = 0; i < this->capacity; i++)
	{
		Shapes* cloned = other.shapes[i]->clone();

		if (cloned)
			this->shapes[i] = cloned;
	}
}

void ShapesCollection::moveFrom(ShapesCollection&& other) noexcept
{
	this->shapes = other.shapes;
	this->size = other.size;
	this->capacity = other.capacity;

	other.shapes = nullptr;
	other.size = other.capacity = 0;
}

void ShapesCollection::free()
{
	for (size_t i = 0; i < this->capacity; i++)
		delete this->shapes[i];

	delete[] this->shapes;
}
