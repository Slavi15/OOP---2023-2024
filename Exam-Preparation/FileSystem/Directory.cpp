#include "Directory.h"

Directory::Directory(const char* fileName) : File(fileName)
{
	this->size = 0;
	this->capacity = 8;
	this->files = new File * [this->capacity] {};
}

Directory::Directory(const File* const* files, size_t size, size_t capacity) : size(size), capacity(capacity)
{
	this->files = new File * [this->capacity] {};
	for (size_t i = 0; i < this->capacity; i++)
	{
		this->files[i] = files[i]->clone();
	}
}

Directory::Directory(size_t newSize) : size(0)
{
	this->capacity = allocateCapacity(newSize);
	this->files = new File * [this->capacity] {};
}

Directory::Directory(const Directory& other)
{
	copyFrom(other);
}

Directory& Directory::operator=(const Directory& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Directory::Directory(Directory&& other) noexcept
{
	moveFrom(std::move(other));
}

Directory& Directory::operator=(Directory&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

size_t Directory::getSize() const
{
	return this->size;
}

size_t Directory::getCapacity() const
{
	return this->capacity;
}

void Directory::add(const File& file)
{
	if (getSize() >= getCapacity())
		resize(getCapacity() * 2);

	this->files[size++] = file.clone();
}

void Directory::add(File* file)
{
	if (getSize() >= getCapacity())
		resize(getCapacity() * 2);

	this->files[size++] = file;
}

File* Directory::getFileByName(const char* fileName) const
{
	if (!fileName) return nullptr;

	for (size_t i = 0; i < getSize(); i++)
		if (strcmp(this->files[i]->getFileName(), fileName) == 0)
			return this->files[i];

	return nullptr;
}

bool Directory::contains(const char* fileName) const
{
	if (!fileName) return false;

	for (size_t i = 0; i < getSize(); i++)
		if (strcmp(this->files[i]->getFileName(), fileName) == 0)
			return true;

	return false;
}

void Directory::print() const
{
	printDirectory(0);
}

void Directory::printDirectory(size_t depth) const
{
	File::printDirectory(depth);

	for (size_t i = 0; i < getSize(); i++)
	{
		this->files[i]->printDirectory(depth + 1);
	}
}

File* Directory::clone() const
{
	return new Directory(*this);
}

Directory::~Directory() noexcept
{
	free();
}

unsigned int Directory::getNextPowerTwo(unsigned int n) const
{
	if (n == 0) return 1;

	while (n & (n - 1))
		n &= (n - 1);

	return n << 1;
}

unsigned int Directory::allocateCapacity(unsigned int n) const
{
	return std::max(getNextPowerTwo(n + 1), 8u);
}

void Directory::resize(size_t newCapacity)
{
	File** newFiles = new File * [newCapacity];
	for (size_t i = 0; i < this->size; i++)
	{
		newFiles[i] = this->files[i];
	}

	delete[] this->files;
	this->files = newFiles;
	this->capacity = newCapacity;
}

void Directory::copyFrom(const Directory& other)
{
	this->size = other.size;
	this->capacity = other.capacity;

	this->files = new File * [this->capacity];
	for (size_t i = 0; i < this->capacity; i++)
	{
		this->files[i] = other.files[i]->clone();
	}
}

void Directory::moveFrom(Directory&& other) noexcept
{
	this->files = other.files;
	this->size = other.size;
	this->capacity = other.capacity;

	other.files = nullptr;
	other.size = other.capacity = 0;
}

void Directory::free()
{
	for (size_t i = 0; i < this->size; i++)
		delete this->files[i];

	delete[] this->files;
	this->files = nullptr;
}
