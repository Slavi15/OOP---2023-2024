#include <iostream>

#include "Fibbonacci.h"

unsigned int fibb(unsigned int n)
{
	if (n == 0 || n == 1)
		return 1;

	static Fibbonacci fibbCache(100, 0);

	if (fibbCache.contains(n))
		return fibbCache.getValue(n);
	else
	{
		unsigned result = fibb(n - 1) + fibb(n - 2);
		fibbCache.add(n, result);
		return result;
	}
}

int main()
{
	std::cout << fibb(42) << std::endl;

	return 0;
}