#include "ExpressionFactory.h"

BooleanExpression* ExpressionFactory::expressionFactory(StringView str)
{
	str = str.substr(1, str.length() - 2);

	if (str.length() == 1)
		return new Var(str[0]);

	size_t count = 0;
	for (size_t i = 0; i < str.length(); i++)
	{
		if (str[i] == '(')
		{
			count++;
		}
		else if (str[i] == ')')
		{
			count--;
		}
		else if (count == 0)
		{
			switch (str[i])
			{
			case '!':
				return new Negation(expressionFactory(str.substr(i + 1, str.length() - i - 1)));
				break;
			case '&':
				return new Conjunction(expressionFactory(str.substr(0, i)), expressionFactory(str.substr(i + 1, str.length() - i - 1)));
				break;
			case '|':
				return new Disjunction(expressionFactory(str.substr(0, i)), expressionFactory(str.substr(i + 1, str.length() - i - 1)));
				break;
			case '>':
				return new Implication(expressionFactory(str.substr(0, i)), expressionFactory(str.substr(i + 1, str.length() - i - 1)));
				break;
			}
		}
	}
}
