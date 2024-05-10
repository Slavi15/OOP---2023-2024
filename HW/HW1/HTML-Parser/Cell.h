#pragma once

#define MAX_CELL_TEXT_LENGTH 50
#define isDigit(ch) ch >= '0' && ch <= '9'
#define charToDigit(ch) ch - '0'

#define EMPTY_CHAR ' '
#define NEW_LINE '\n'
#define TAB '\t'

class Cell
{
private:
	char cell[MAX_CELL_TEXT_LENGTH + 1] = { '\0' };
	bool flag = false;

	void trim(char* str);
	void convertSpecialCharacters(char* str);

public:
	Cell();
	Cell(const char* cell, bool flag);

	const char* getCellText() const;
	const bool getFlag() const;

	void setCellText(const char* cell);
	void setFlag(bool flag);
};