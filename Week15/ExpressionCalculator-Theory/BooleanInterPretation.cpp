#include "BooleanInterPretation.h"

void BooleanInterPretation::set(char ch, bool value)
{
	assert(ch >= 'a' && ch <= 'z');
	values[ch - 'a'] = value;
}

bool BooleanInterPretation::operator()(char ch) const
{
	assert(ch >= 'a' && ch <= 'z');
	return values[ch - 'a'];
}

size_t BooleanInterPretation::getTrueCount() const
{
	size_t result = 0;

	for (size_t i = 0; i < BOOLEAN_ARRAY_LENGTH; i++)
		if (values[i])
			result++;

	return result;
}

void BooleanInterPretation::excludeValuesByMask(size_t mask)
{
	for (int i = 25; i >= 0; i--)
	{
		if (values[i])
		{
			if (mask % 2 == 0)
			{
				values[i] = false;
			}

			mask /= 2;
		}
	}
}
