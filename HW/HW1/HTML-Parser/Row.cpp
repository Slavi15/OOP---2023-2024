#include "Row.h"

Row::Row() = default;

const size_t Row::getRowColumns() const
{
	return rowColumns;
}

const Cell& Row::getCell(size_t index) const
{
	return cells[index];
}

void Row::setRowColumns(size_t rowColumns)
{
	this->rowColumns = rowColumns;
}

void Row::setCell(const Cell& cell, size_t index)
{
	cells[index].setCellText(cell.getCellText());
	cells[index].setFlag(cell.getFlag());
}

void Row::printCell(const Cell& cell, size_t width) const
{
	cell.getFlag() ?
		std::cout << "*" << std::setw(width) << std::left << cell.getCellText() << "*" :
		std::cout << " " << std::setw(width) << std::left << cell.getCellText() << " ";
}