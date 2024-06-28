#include "File.h"

File::File() = default;

File::File(const char* fileName)
{
	setFileName(fileName);
}

File::File(const File& other)
{
	copyFrom(other);
}

File& File::operator=(const File& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

File::File(File&& other) noexcept
{
	moveFrom(std::move(other));
}

File& File::operator=(File&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

const char* File::getFileName() const
{
	return this->fileName;
}

void File::setFileName(const char* fileName)
{
	if (!fileName) return;

	delete[] this->fileName;
	this->fileName = new char[strlen(fileName) + 1];
	strcpy(this->fileName, fileName);
}

void File::printDirectory(size_t depth) const
{
	for (size_t i = 0; i < depth; i++)
		std::cout << '\t';

	std::cout << getFileName() << std::endl;
}

File::~File() noexcept
{
	free();
}

void File::copyFrom(const File& other)
{
	this->fileName = new char[strlen(other.fileName) + 1];
	strcpy(this->fileName, other.fileName);
}

void File::moveFrom(File&& other) noexcept
{
	this->fileName = other.fileName;
	other.fileName = nullptr;
}

void File::free()
{
	delete[] this->fileName;
	this->fileName = nullptr;
}
