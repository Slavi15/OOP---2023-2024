#include "Singleton.h"

Singleton::Singleton(char ch) : ch(ch) {}

bool Singleton::isElementIn(const Element& el) const
{
	return el.get(ch);
}

SetExpression* Singleton::clone() const
{
	return new Singleton(*this);
}
