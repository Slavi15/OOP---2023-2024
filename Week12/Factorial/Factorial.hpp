#pragma once

#define TT template <unsigned int N>

TT
class Factorial
{
public:
	enum { number = N * Factorial<N - 1>::number };
};

template <>
class Factorial<0>
{
public:
	enum { number = 1 };
};
