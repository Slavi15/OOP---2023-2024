#pragma once

#include "../String and StringView/StringView.h"

#include "../BooleanExpression.h"

#include "../Variable/Var.h"
#include "../Unary/Negation.h"
#include "../Binary/Conjunction.h"
#include "../Binary/Disjunction.h"
#include "../Binary/Implication.h"

class ExpressionFactory
{
public:
	static BooleanExpression* expressionFactory(StringView str);
};