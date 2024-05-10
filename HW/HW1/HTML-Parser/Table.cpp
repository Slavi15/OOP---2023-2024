#include "Table.h"

Table::Table() = default;

const size_t Table::getTableRows() const
{
	return tableRows;
}

const size_t Table::getTableColumns() const
{
	return tableColumns;
}

const Row& Table::getRow(size_t index) const
{
	return rows[index];
}

void Table::setTableRows(size_t tableRows)
{
	this->tableRows = tableRows;
}

void Table::setTableColumns(size_t tableColumns)
{
	if (tableColumns > this->tableColumns)
		this->tableColumns = tableColumns;
}

void Table::add(const Row& row, size_t rowNumber)
{
	if (tableRows >= MAX_ROWS_COUNT) return;

	if (rowNumber > 0 && rowNumber <= tableRows)
	{
		for (int i = tableRows; i >= rowNumber; i--)
			setRow(getRow(i - 1), i, false);

		setRow(row, rowNumber - 1, true);
	}
	else
	{
		setRow(row, tableRows, true);
	}

	tableRows++;

	if (row.getRowColumns() > tableColumns)
		tableColumns = row.getRowColumns();
}

void Table::edit(size_t rowNumber, size_t colNumber, const char* newValue)
{
	if (!newValue) return;

	if (rowNumber > 0 && rowNumber <= tableRows && colNumber > 0 && colNumber <= tableColumns)
	{
		Cell& cell = (Cell&)getRow(rowNumber - 1).getCell(colNumber - 1);
		cell.setCellText(newValue);

		Row& row = (Row&)getRow(rowNumber - 1);
		row.setCell(cell, colNumber - 1);

		if (colNumber > row.getRowColumns())
			row.setRowColumns(colNumber);

		setRow(row, rowNumber - 1, false);
	}
}

void Table::remove(size_t rowNumber)
{
	if (rowNumber > 0 && rowNumber <= tableRows)
	{
		for (size_t i = rowNumber - 1; i < tableRows; i++)
			setRow(getRow(i + 1), i, false);

		tableRows--;
		tableColumns = getMaxColumns();
	}
}

const size_t Table::getLongestCell(size_t colIndex) const
{
	size_t result = 0;

	for (size_t i = 0; i < tableRows; i++)
	{
		size_t length = strlen(rows[i].getCell(colIndex).getCellText());

		if (length > result)
			result = length;
	}

	return result;
}

const size_t Table::getMaxColumns() const
{
	size_t result = 0;

	for (size_t i = 0; i < tableRows; i++)
		if (rows[i].getRowColumns() > result)
			result = rows[i].getRowColumns();

	return result;
}

void Table::setRow(const Row& row, size_t rowIndex, bool newRow)
{
	if (newRow)
	{
		for (size_t i = 0; i < row.getRowColumns() && i < MAX_CELL_COUNT; i++)
			rows[rowIndex].setCell(row.getCell(i), i);
	}
	else
	{
		for (size_t i = 0; i < tableColumns; i++)
			rows[rowIndex].setCell(row.getCell(i), i);
	}

	rows[rowIndex].setRowColumns(row.getRowColumns());
}

void Table::printRow(size_t index) const
{
	for (size_t j = 0; j < tableColumns; j++)
	{
		size_t width = getLongestCell(j);
		rows[index].printCell(rows[index].getCell(j), width);

		std::cout << '|';
	}
}

void Table::print() const
{
	for (size_t i = 0; i < tableRows; i++)
	{
		std::cout << '|';
		printRow(i);
		std::cout << std::endl;
	}
}