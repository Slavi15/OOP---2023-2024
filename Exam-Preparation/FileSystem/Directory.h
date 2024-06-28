#pragma once

#include "File.h"

class Directory : public File
{
private:
	File** files = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	Directory(size_t newSize);

	unsigned int getNextPowerTwo(unsigned int n) const;
	unsigned int allocateCapacity(unsigned int n) const;

	void resize(size_t newCapacity);

	void copyFrom(const Directory& other);
	void moveFrom(Directory&& other) noexcept;
	void free();

public:
	Directory(const char* fileName);
	Directory(const File* const* files, size_t size, size_t capacity);

	Directory(const Directory& other);
	Directory& operator=(const Directory& other);

	Directory(Directory&& other) noexcept;
	Directory& operator=(Directory&& other) noexcept;

	size_t getSize() const;
	size_t getCapacity() const;

	void add(const File& file);
	void add(File* file);

	File* getFileByName(const char* fileName) const;
	bool contains(const char* fileName) const;

	void print() const override;
	void printDirectory(size_t depth) const override;

	File* clone() const override;

	~Directory() noexcept;
};