#include "TextFile.h"

TextFile::TextFile() = default;

TextFile::TextFile(const char* fileName, const char* fileContent) : File(fileName)
{
	setContent(fileContent);
}

TextFile::TextFile(const TextFile& other)
{
	copyFrom(other);
}

TextFile& TextFile::operator=(const TextFile& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

TextFile::TextFile(TextFile&& other) noexcept
{
	moveFrom(std::move(other));
}

TextFile& TextFile::operator=(TextFile&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

const char* TextFile::getContent() const
{
	return this->fileContent;
}

void TextFile::setContent(const char* fileContent)
{
	if (!fileContent) return;

	delete[] this->fileContent;
	this->fileContent = new char[strlen(fileContent) + 1];
	strcpy(this->fileContent, fileContent);
}

void TextFile::print() const
{
	std::cout << getFileName() << ": " << getContent() << std::endl;
}

File* TextFile::clone() const
{
	return new TextFile(*this);
}

TextFile::~TextFile() noexcept
{
	free();
}

void TextFile::copyFrom(const TextFile& other)
{
	this->fileContent = new char[strlen(other.fileContent) + 1];
	strcpy(this->fileContent, other.fileContent);
}

void TextFile::moveFrom(TextFile&& other) noexcept
{
	this->fileContent = other.fileContent;
	other.fileContent = nullptr;
}

void TextFile::free()
{
	delete[] this->fileContent;
	this->fileContent = nullptr;
}
