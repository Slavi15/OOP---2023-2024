#pragma once

#include <iostream>
#include <fstream>

#include "ResultSet.hpp"
#include "SetFactory.hpp"

#define MAX_LENGTH 1024
#define TT template <typename T>

TT
class Engine
{
private:
	SetFactory<T> setFactory;
	ResultSet<T> resultSet;

	uint32_t readElementCount(std::ifstream& ifs) const;
	uint8_t readType(std::ifstream& ifs) const;

	uint8_t getAddType(uint8_t type) const;
	uint8_t getSetType(uint8_t type) const;

public:
	void run(const char* fileName);
};

TT
inline uint32_t Engine<T>::readElementCount(std::ifstream& ifs) const
{
	uint32_t elemCount = 0;
	ifs.read(reinterpret_cast<char*>(&elemCount), sizeof(uint32_t));
	return elemCount;
}

TT
inline uint8_t Engine<T>::readType(std::ifstream& ifs) const
{
	uint8_t type = 0;
	ifs.read(reinterpret_cast<char*>(&type), sizeof(uint8_t));
	return type;
}

TT
inline uint8_t Engine<T>::getAddType(uint8_t type) const
{
	type <<= 6;
	return (type >> 6);
}

TT
inline uint8_t Engine<T>::getSetType(uint8_t type) const
{
	return type >> 5; // най-старши 3 бита
}

TT
void Engine<T>::run(const char* fileName)
{
	if (!fileName) return;

	std::ifstream ifs(fileName, std::ios::in | std::ios::binary);

	if (!ifs.is_open()) return;

	char buff[MAX_LENGTH + 1]{};

	while (!ifs.eof())
	{
		ifs.getline(buff, MAX_LENGTH + 1, '\n');

		std::ifstream ifsFile(buff, std::ios::in | std::ios::binary);

		if (!ifsFile.is_open()) return;

		uint32_t elemCount = readElementCount(ifsFile);
		uint8_t type = readType(ifsFile);

		uint8_t setType = getSetType(type);
		uint8_t addType = getAddType(type);

		Set<T>* set = setFactory->readSet(ifsFile, elemCount, setType);
		resultSet.addSet(set, addType);

		ifsFile.close();
	}

	ifs.close();
}