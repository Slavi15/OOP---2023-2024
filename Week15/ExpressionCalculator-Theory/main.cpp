#include <iostream>

#include "ExpressionHandler/ExpressionHandler.h"
#include "BooleanInterPretation.h"

int main()
{
	ExpressionHandler be("((p)|((q)&(t)))");
	BooleanInterPretation bi;
	bi.set('p', true);
	std::cout << be.evaluate(bi) << std::endl;
	ExpressionHandler be2("((p)|(!(p)))");
	std::cout << be2.isTautology() << std::endl;

	return 0;
}