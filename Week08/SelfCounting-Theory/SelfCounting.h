#pragma once

class SelfCounting
{
private:
	const int const_val; // constant value can only be set through initializer list

	static size_t liveObjects;
	static size_t createdObjects;

public:
	SelfCounting();
	SelfCounting(int val);

	SelfCounting(const SelfCounting& other);

	static size_t getLiveObjects();
	static size_t getCreatedObjects();

	~SelfCounting() noexcept;
};