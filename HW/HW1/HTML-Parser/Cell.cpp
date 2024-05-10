#include "Cell.h"
#pragma warning (disable: 4996)

#include <cstring>

Cell::Cell() = default;

Cell::Cell(const char* cell, bool flag) : flag(flag)
{
	setCellText(cell);
}

const char* Cell::getCellText() const
{
	return cell;
}

const bool Cell::getFlag() const
{
	return flag;
}

void Cell::setCellText(const char* cell)
{
	if (!cell) return;

	convertSpecialCharacters((char*)cell);

	if (strlen(cell) <= MAX_CELL_TEXT_LENGTH)
	{
		trim((char*)cell);
		strcpy(this->cell, cell);
	}
}

void Cell::setFlag(bool flag)
{
	this->flag = flag;
}

void Cell::trim(char* str)
{
	if (!str) return;

	int len = strlen(str);
	int start = 0;
	int end = len - 1;

	while (start < len && (str[start] == EMPTY_CHAR || str[start] == NEW_LINE || str[start] == TAB))
		start++;

	while (end >= 0 && (str[end] == EMPTY_CHAR || str[end] == NEW_LINE || str[end] == TAB))
		end--;

	if (start > end)
	{
		str[0] = '\0';
		return;
	}

	for (int i = start; i <= end; i++)
		(str[i] == NEW_LINE || str[i] == TAB) ? str[i - start] = EMPTY_CHAR : str[i - start] = str[i];

	str[end - start + 1] = '\0';
}

void Cell::convertSpecialCharacters(char* str)
{
	if (!str) return;

	char* p = str;
	char* q = str;

	while (*p)
	{
		if (*p == '&' && *(p + 1) == '#' && isDigit(*(p + 2)))
		{
			int num = 0;
			char* r = p + 2;

			while (isDigit(*r))
			{
				(num *= 10) += charToDigit(*r);
				r++;
			}

			*q = char(num);
			q++;
			p = r;
		}
		else
		{
			*q = *p;
			q++;
			p++;
		}
	}

	*q = '\0';
}