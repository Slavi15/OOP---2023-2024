#pragma once
#pragma warning (disable : 4996)

#include "TextFile.h"
#include "Directory.h"

class FileSystem
{
private:
	Directory* root = nullptr;

	char* getLastFileName(const char* path) const;
	char* getFirstFileName(const char* path) const;

	void createSubDirectory(Directory* directory, const char* path);

	File* getFileSubDirectory(Directory* directory, const char* path) const;

	void copyFrom(const FileSystem& other);
	void moveFrom(FileSystem&& other) noexcept;
	void free();

public:
	FileSystem();

	FileSystem(const FileSystem& other);
	FileSystem& operator=(const FileSystem& other);

	FileSystem(FileSystem&& other) noexcept;
	FileSystem& operator=(FileSystem && other) noexcept;

	void createTextFile(const char* path, const char* content);
	void createDirectory(const char* path);

	File* getFile(const char* path) const;

	~FileSystem() noexcept;
};