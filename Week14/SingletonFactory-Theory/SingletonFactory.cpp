#include "SingletonFactory.h"

SingletonFactory::SingletonFactory()
{
	std::ifstream ifs("file.txt", std::ios::in);

	if (!ifs.is_open())
		throw std::runtime_error("Could not open file!");

	ifs >> numSize;
	this->numbers = new size_t[numSize] { };

	size_t index = 0;
	while (!ifs.eof())
	{
		ifs >> numbers[index++];
	}
}

SingletonFactory& SingletonFactory::getInstance()
{
	static SingletonFactory instance;
	return instance;
}

Base* SingletonFactory::create()
{
	if (current >= numSize)
		return nullptr;

	if (numbers[current++] % 2 == 0)
		return new A();
	else
		return new B();
}

SingletonFactory::~SingletonFactory() noexcept
{
	delete[] this->numbers;
	this->numbers = nullptr;
}
