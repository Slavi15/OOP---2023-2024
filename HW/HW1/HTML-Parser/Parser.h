#pragma once
#include "Table.h"

#include <cstring>
#include <fstream>
#include <sstream>

#define LEFT_SEPARATOR '<'
#define RIGHT_SEPARATOR '>'
#define END_TAG_SEPARATOR '/'

bool hasRowEnded(std::ifstream& ifs);

int strToNumUnsigned(const char* str);
int strToNum(const char* str);

class Parser
{
private:
	const char* fileName = nullptr;
	Table table;

	const char* getBuffer(std::stringstream& ss) const;

public:
	Parser(const char* fileName, const Table& table);

	const char* getFileName() const;
	const Table& getTable() const;

	const Row& parseRow(std::ifstream& ifs) const;
	void readFromFile(std::ifstream& ifs);
	void readFromFile();

	void writeCell(std::ofstream& ofs, const Cell& cell) const;
	void writeRow(std::ofstream& ofs, size_t rowIndex) const;
	void writeToFile(std::ofstream& ofs) const;
	void writeToFile() const;

	void getInput();
};