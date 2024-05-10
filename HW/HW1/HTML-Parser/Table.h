#pragma once
#include "Row.h"

#include <iostream>
#include <cstring>

#define MAX_ROWS_COUNT 100

class Table
{
private:
	Row rows[MAX_ROWS_COUNT];
	size_t tableRows = 0;
	size_t tableColumns = 0;

public:
	Table();

	const size_t getTableRows() const;
	const size_t getTableColumns() const;
	const Row& getRow(size_t index) const;
	const size_t getLongestCell(size_t colIndex) const;
	const size_t getMaxColumns() const;

	void setTableRows(size_t tableRows);
	void setTableColumns(size_t tableColumns);
	void setRow(const Row& row, size_t rowIndex, bool newRow);

	void add(const Row& row, size_t rowNumber);
	void edit(size_t rowNumber, size_t colNumber, const char* newValue);
	void remove(size_t rowNumber);

	void printRow(size_t index) const;
	void print() const;
};