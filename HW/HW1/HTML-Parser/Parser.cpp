#include "Parser.h"
#pragma warning (disable: 4996)

Parser::Parser(const char* fileName, const Table& table) : fileName(fileName), table(table) {}

const char* Parser::getFileName() const
{
	return fileName;
}

const Table& Parser::getTable() const
{
	return table;
}

const Row& Parser::parseRow(std::ifstream& ifs) const
{
	Row row;
	Cell cell;

	char buff[MAX_TEXT_LENGTH + 1];

	while (true)
	{
		ifs.getline(buff, MAX_TEXT_LENGTH + 1, LEFT_SEPARATOR);
		if (hasRowEnded(ifs)) break;
		ifs.getline(buff, MAX_TEXT_LENGTH + 1, RIGHT_SEPARATOR);

		if (strcmp(buff, "th") == 0)
			cell.setFlag(true);

		ifs.getline(buff, MAX_TEXT_LENGTH + 1, END_TAG_SEPARATOR);
		buff[strlen(buff) - 1] = '\0';

		cell.setCellText(buff);

		row.setCell(cell, row.getRowColumns());
		row.setRowColumns(row.getRowColumns() + 1);

		ifs.getline(buff, MAX_TEXT_LENGTH + 1, RIGHT_SEPARATOR);
	}

	return row;
}

void Parser::readFromFile(std::ifstream& ifs)
{
	while (!ifs.eof())
	{
		char buff[MAX_TEXT_LENGTH + 1];

		ifs.getline(buff, MAX_TEXT_LENGTH + 1, LEFT_SEPARATOR);
		ifs.getline(buff, MAX_TEXT_LENGTH + 1, RIGHT_SEPARATOR);

		if (strcmp(buff, "tr") == 0)
		{
			Row row = parseRow(ifs);
			table.setTableColumns(row.getRowColumns());
			table.setRow(row, table.getTableRows(), true);
			table.setTableRows(table.getTableRows() + 1);
		}
	}
}

void Parser::readFromFile()
{
	if (!fileName) return;

	std::ifstream ifs(fileName, std::ios::in);
	if (!ifs.is_open()) return;

	return readFromFile(ifs);
}

void Parser::writeCell(std::ofstream& ofs, const Cell& cell) const
{
	cell.getFlag() ?
		ofs << "<th>" << cell.getCellText() << "</th>" << std::endl :
		ofs << "<td>" << cell.getCellText() << "</td>" << std::endl;
}

void Parser::writeRow(std::ofstream& ofs, size_t rowIndex) const
{
	size_t rowColumns = table.getRow(rowIndex).getRowColumns();

	for (size_t j = 0; j < rowColumns; j++)
		writeCell(ofs, table.getRow(rowIndex).getCell(j));
}

void Parser::writeToFile(std::ofstream& ofs) const
{
	ofs << "<table>" << std::endl;

	size_t tableRows = table.getTableRows();
	for (size_t i = 0; i < tableRows; i++)
	{
		ofs << "<tr>" << std::endl;
		writeRow(ofs, i);
		ofs << "</tr>" << std::endl;
	}

	ofs << "</table>";
}

void Parser::writeToFile() const
{
	if (!fileName) return;

	std::ofstream ofs(fileName, std::ios::out);
	if (!ofs.is_open()) return;

	return writeToFile(ofs);
}

void Parser::getInput()
{
	char command[MAX_TEXT_LENGTH + 1] = { '\0' };

	while (std::cin.getline(command, MAX_TEXT_LENGTH + 1))
	{
		std::stringstream ss(command);

		char buff[MAX_TEXT_LENGTH + 1];
		ss.getline(buff, MAX_TEXT_LENGTH + 1, EMPTY_CHAR);

		if (strcmp(buff, "add") == 0)
		{
			strcpy(buff, getBuffer(ss));
			size_t rowNumber = strToNum(buff);

			Row row;

			ss.getline(buff, MAX_TEXT_LENGTH + 1, LEFT_SEPARATOR);
			while (ss.getline(buff, MAX_TEXT_LENGTH + 1, RIGHT_SEPARATOR))
			{
				Cell cell;

				cell.setCellText(buff);
				row.setCell(cell, row.getRowColumns());

				row.setRowColumns(row.getRowColumns() + 1);

				if (ss.peek() == NEW_LINE) break;
				ss.getline(buff, MAX_TEXT_LENGTH + 1, LEFT_SEPARATOR);
			}

			table.add(row, rowNumber);
		}
		else if (strcmp(buff, "remove") == 0)
		{
			strcpy(buff, getBuffer(ss));
			size_t rowNumber = strToNum(buff);

			table.remove(rowNumber);
		}
		else if (strcmp(buff, "edit") == 0)
		{
			strcpy(buff, getBuffer(ss));
			size_t rowNumber = strToNum(buff);

			strcpy(buff, getBuffer(ss));
			size_t colNumber = strToNum(buff);

			strcpy(buff, getBuffer(ss));
			table.edit(rowNumber, colNumber, buff);
		}
		else if (strcmp(buff, "print") == 0)
		{
			table.print();
		}
		else if (strcmp(buff, "exit") == 0)
		{
			return;
		};
	};
}

const char* Parser::getBuffer(std::stringstream& ss) const
{
	char buff[MAX_TEXT_LENGTH + 1];

	ss.getline(buff, MAX_TEXT_LENGTH + 1, LEFT_SEPARATOR);
	ss.getline(buff, MAX_TEXT_LENGTH + 1, RIGHT_SEPARATOR);

	return buff;
}

int strToNumUnsigned(const char* str)
{
	if (!str) return 0;

	int result = 0;

	while (*str)
	{
		(result *= 10) += charToDigit(*str);
		str++;
	}

	return result;
}

int strToNum(const char* str)
{
	if (!str) return 0;

	if (*str == '-')
		return (-1) * strToNumUnsigned(str);
	else
		return strToNumUnsigned(str);
}

bool hasRowEnded(std::ifstream& ifs)
{
	char buff[MAX_TEXT_LENGTH + 1];

	size_t currentPos = ifs.tellg();
	ifs.getline(buff, MAX_TEXT_LENGTH + 1, RIGHT_SEPARATOR);
	ifs.seekg(currentPos);

	return strcmp(buff, "/tr") == 0 || strcmp(buff, "/table") == 0;
}