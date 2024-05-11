#include "SelfCounting.h"

size_t SelfCounting::liveObjects = 0;

size_t SelfCounting::createdObjects = 0;

SelfCounting::SelfCounting() : SelfCounting(42) {}

SelfCounting::SelfCounting(int val) : const_val(val) // constant value can only be set through initializer list
{
	liveObjects++;
	createdObjects++;
}

SelfCounting::SelfCounting(const SelfCounting& other) : const_val(other.const_val) // constant value can only be set through initializer list
{
	liveObjects++;
	createdObjects++;
}

size_t SelfCounting::getLiveObjects()
{
	return liveObjects;
}

size_t SelfCounting::getCreatedObjects()
{
	return createdObjects;
}

SelfCounting::~SelfCounting()
{
	liveObjects--;
}