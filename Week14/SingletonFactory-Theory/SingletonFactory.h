#pragma once

#include <iostream>
#include <fstream>

class Base
{
public:
	virtual ~Base() noexcept = default;
};

class A : public Base {};
class B : public Base {};


class SingletonFactory
{
private:
	size_t* numbers = nullptr;
	size_t current = 0;
	size_t numSize = 0;

	SingletonFactory();
	~SingletonFactory() noexcept;

public:
	static SingletonFactory& getInstance();

	SingletonFactory(const SingletonFactory&) = delete;
	SingletonFactory& operator=(const SingletonFactory&) = delete;

	Base* create();
};