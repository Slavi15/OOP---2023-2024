#pragma once
#pragma warning (disable : 4996)

#include "File.h"

class TextFile : public File
{
private:
	char* fileContent = nullptr;

	void copyFrom(const TextFile& other);
	void moveFrom(TextFile&& other) noexcept;
	void free();

public:
	TextFile();
	TextFile(const char* fileName, const char* fileContent);

	TextFile(const TextFile& other);
	TextFile& operator=(const TextFile& other);

	TextFile(TextFile&& other) noexcept;
	TextFile& operator=(TextFile&& other) noexcept;

	const char* getContent() const;
	void setContent(const char* fileContent);

	void print() const override;
	File* clone() const override;

	~TextFile() noexcept;
};