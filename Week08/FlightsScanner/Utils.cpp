#include "Utils.h"

bool isDigit(char ch)
{
	return ch >= '0' && ch <= '9';
}

bool isLower(char ch)
{
	return ch >= 'a' && ch <= 'z';
}

void toUpper(char* str)
{
	if (!str)
		throw std::runtime_error("NULLPTR!");

	while (*str)
	{
		if (isLower(*str))
			*str -= ('a' - 'A');

		str++;
	}
}

size_t charToDigit(char ch)
{
	if (ch < '0' || ch > '9')
		throw std::bad_cast();

	return ch - '0';
}

size_t convertToNum(const char* str)
{
	size_t res = 0;

	while (*str)
	{
		(res *= 10) += charToDigit(*str);
		str++;
	}

	return res;
}
