#pragma once
#pragma warning (disable : 4996)

#include <iostream>

class File
{
private:
	char* fileName = nullptr;

	void copyFrom(const File& other);
	void moveFrom(File&& other) noexcept;
	void free();

public:
	File();
	File(const char* fileName);

	File(const File& other);
	File& operator=(const File& other);

	File(File&& other) noexcept;
	File& operator=(File&& other) noexcept;

	const char* getFileName() const;
	void setFileName(const char* fileName);

	virtual void print() const = 0;
	virtual void printDirectory(size_t depth) const;

	virtual File* clone() const = 0;

	virtual ~File() noexcept;
};