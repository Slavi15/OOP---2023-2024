#include "StringPool.h"

StringPool::StringPool() : StringPool(4) {}

StringPool::StringPool(size_t newSize) : size(newSize)
{
	this->capacity = allocateCapacity(newSize);
	this->nodes = new StringNode[this->capacity];
}

const unsigned int StringPool::getNextPowerOfTwo(unsigned int n) const
{
	if (n == 0) return 1;

	while (n & (n - 1))
		n &= (n - 1);

	return n << 1;
}

const unsigned int StringPool::allocateCapacity(unsigned int size) const
{
	return std::max(getNextPowerOfTwo(size + 1), 8u);
}

int StringPool::binarySearch(const char* str, bool& found) const
{
	if (!str)
		throw std::runtime_error("NULLPTR!");

	size_t left = 0;
	size_t right = this->size - 1;

	while (left <= right)
	{
		size_t mid = left + (right - left) / 2;
		int cmp = strcmp(str, this->nodes[mid].data);

		if (cmp == 0)
		{
			found = true;
			return mid;
		}
		else if (cmp > 0)
		{
			left = mid + 1;
		}
		else
		{
			right = mid - 1;
		}
	}

	found = false;
	return left;
}

void StringPool::resize(size_t newCapacity)
{
	if (this->capacity >= newCapacity)
		return;

	StringNode* newNodes = new StringNode[newCapacity]{};
	for (size_t i = 0; i < this->size; i++)
		newNodes[i] = this->nodes[i];

	delete[] this->nodes;
	this->nodes = newNodes;
	this->capacity = newCapacity;
}

const char* StringPool::insert(const char* str, size_t index)
{
	if (index >= getSize())
		throw std::out_of_range("StringPool::insert invalid index!");

	if (getSize() >= getCapacity())
		resize(getCapacity() * 2);

	for (int i = getSize() - 1; i >= (int)index; i--)
		this->nodes[i + 1] = this->nodes[i];

	this->nodes[index].allocateData(str);
	this->nodes[index].refCount = 1;

	this->size++;
	return this->nodes[index].data;
}

void StringPool::removeInternal(size_t index)
{
	if (index >= getSize())
		throw std::out_of_range("StringPool::removeInternal invalid index!");

	if (getSize())
		this->size--;
	else
		throw std::logic_error("Alerady empty!");

	delete[] this->nodes[index].data;

	for (size_t i = index; i < getSize(); i++)
		this->nodes[i] = this->nodes[i + 1];

	this->nodes[getSize() - 1].data = nullptr;
	this->nodes[getSize() - 1].refCount = 0;

	if ((getSize() * 4) <= getCapacity() && getCapacity() >= 1)
		resize(getCapacity() / 2);
}

const size_t StringPool::getSize() const
{
	return this->size;
}

const size_t StringPool::getCapacity() const
{
	return this->capacity;
}

const char* StringPool::getString(const char* str)
{
	if (!str)
		throw std::runtime_error("NULLPTR!");

	bool found = false;
	size_t currentIndex = binarySearch(str, found);

	if (found)
	{
		this->nodes[currentIndex].refCount++;
		return this->nodes[currentIndex].data;
	}

	return insert(str, currentIndex);
}

void StringPool::removeString(const char* str)
{
	if (!str)
		throw std::runtime_error("NULLPTR!");

	bool found = false;
	size_t currentIndex = binarySearch(str, found);

	if (!found) return;

	if (this->nodes[currentIndex].refCount == 1)
		removeInternal(currentIndex);
	else
		this->nodes[currentIndex].refCount--;
}

StringPool::~StringPool() noexcept
{
	for (size_t i = 0; i < getSize(); i++)
		delete[] this->nodes[i].data;

	delete[] this->nodes;
}

void StringPool::StringNode::allocateData(const char* str)
{
	if (!str)
		throw std::runtime_error("NULLPTR!");

	this->data = new char[strlen(str) + 1] {};
	strcpy(this->data, str);
}