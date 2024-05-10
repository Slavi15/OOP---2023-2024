#pragma once
#include "Cell.h"

#include <iostream>
#include <iomanip>

#define MAX_CELL_COUNT 15
#define MAX_TEXT_LENGTH 1024

class Row
{
private:
	Cell cells[MAX_CELL_COUNT];
	size_t rowColumns = 0;

public:
	Row();

	const size_t getRowColumns() const;
	const Cell& getCell(size_t index) const;

	void setRowColumns(size_t rowColumns);
	void setCell(const Cell& cell, size_t index);

	void printCell(const Cell& cell, size_t width) const;
};