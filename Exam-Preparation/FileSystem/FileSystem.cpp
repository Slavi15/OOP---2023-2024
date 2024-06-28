#include "FileSystem.h"

FileSystem::FileSystem()
{
	root = new Directory("root");
}

void FileSystem::createTextFile(const char* path, const char* content)
{
	if (!path || !content) return;

	char* fileName = getLastFileName(path);
	if (fileName == nullptr) // no slash has been found <--
		return;

	size_t dirnameLength = strlen(path) - strlen(fileName);
	char* dirPath = new char[dirnameLength + 1] {};
	dirPath[dirnameLength] = '\0';

	strncpy(dirPath, path, dirnameLength);

	createDirectory(dirPath);

	Directory* dir = static_cast<Directory*>(getFile(dirPath));
	delete[] dirPath;

	dir->add(new TextFile(fileName, content));
}

void FileSystem::createDirectory(const char* path)
{
	if (!path) return;

	char* fileName = getFirstFileName(path);
	if (fileName == nullptr)
	{
		if (strcmp(path, root->getFileName()) == 0)
			return;

		throw std::runtime_error("error!");
	}

	if (strcmp(fileName, root->getFileName()) != 0)
		throw std::runtime_error("error!");

	const char* subpath = path + strlen(fileName) + 1;
	delete[] fileName;

	return createSubDirectory(root, subpath);
}

void FileSystem::createSubDirectory(Directory* directory, const char* path)
{
	if (!directory || !path) return;

	char* fileName = getFirstFileName(path);
	if (fileName == nullptr)
	{
		if (directory->contains(path))
		{
			Directory* subDirectory = static_cast<Directory*>(directory->getFileByName(path));

			if (subDirectory == nullptr)
				throw std::runtime_error("file already exists!");

			return;
		}

		directory->add(new Directory(path));
		return;
	}

	Directory* subfolder = static_cast<Directory*>(directory->getFileByName(fileName));

	if (subfolder == nullptr)
	{
		if (directory->contains(fileName))
			throw std::runtime_error("file already exists!");

		subfolder = new Directory(fileName);
		directory->add(subfolder);
	}

	const char* subpath = path + strlen(fileName) + 1;
	delete[] fileName;
	return createSubDirectory(subfolder, subpath);
}

File* FileSystem::getFile(const char* path) const
{
	if (!path) return nullptr;

	char* fileName = getFirstFileName(path);
	if (fileName == nullptr)
	{
		if (strcmp(path, root->getFileName()) == 0)
			return root;

		throw std::runtime_error("error!");
	}

	if (strcmp(fileName, root->getFileName()) != 0)
		throw std::runtime_error("error!");

	const char* subpath = path + strlen(fileName) + 1;
	delete[] fileName;

	return getFileSubDirectory(root, subpath);
}

File* FileSystem::getFileSubDirectory(Directory* directory, const char* path) const
{
	if (!directory || !path) return nullptr;

	char* fileName = getFirstFileName(path);
	if (fileName == nullptr)
	{
		return directory->getFileByName(path);
	}

	Directory* subfolder = static_cast<Directory*>(directory->getFileByName(fileName));
	
	const char* subpath = path + strlen(fileName) + 1;
	delete[] fileName;
	return getFileSubDirectory(subfolder, subpath);
}

char* FileSystem::getLastFileName(const char* path) const
{
	if (!path) return nullptr;

	int lastSlash = -1;
	for (int i = strlen(path) - 1; i >= 0; i--)
	{
		if (path[i] == '/')
		{
			lastSlash = i;
			break;
		}
	}

	if (lastSlash == -1) return nullptr;

	size_t lastFileLength = strlen(path) - lastSlash;
	char* lastFile = new char[lastFileLength + 1] {};
	lastFile[lastFileLength] = '\0';

	strncpy(lastFile, path + lastSlash + 1, lastFileLength);
	return lastFile;
}

char* FileSystem::getFirstFileName(const char* path) const
{
	if (!path) return nullptr;

	int lastSlash = -1;

	size_t pathLength = strlen(path);
	for (size_t i = 0; i < pathLength; i++)
	{
		if (path[i] == '/')
		{
			lastSlash = i;
			break;
		}
	}

	if (lastSlash == -1) return nullptr;

	char* firstFile = new char[lastSlash + 1] {};
	firstFile[lastSlash] = '\0';

	strncpy(firstFile, path, lastSlash);
	return firstFile;
}

FileSystem::FileSystem(const FileSystem& other)
{
	copyFrom(other);
}

FileSystem& FileSystem::operator=(const FileSystem& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

FileSystem::FileSystem(FileSystem&& other) noexcept
{
	moveFrom(std::move(other));
}

FileSystem& FileSystem::operator=(FileSystem&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

FileSystem::~FileSystem() noexcept
{
	free();
}

void FileSystem::copyFrom(const FileSystem& other)
{
	root = other.root;
}

void FileSystem::moveFrom(FileSystem&& other) noexcept
{
	root = other.root;
	other.root = nullptr;
}

void FileSystem::free()
{
	delete root;
	root = nullptr;
}
