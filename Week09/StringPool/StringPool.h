#pragma once
#pragma warning (disable : 4996)

#include <iostream>

class StringPool
{
private:
	struct StringNode
	{
		char* data = nullptr;
		size_t refCount = 0;

		void allocateData(const char* data);
	};

	StringNode* nodes;
	size_t size = 0;
	size_t capacity = 0;

	explicit StringPool(size_t newSize);

	const unsigned int getNextPowerOfTwo(unsigned int n) const;
	const unsigned int allocateCapacity(unsigned int size) const;

	void resize(size_t newCapacity);

	int binarySearch(const char* str, bool& found) const;
	const char* insert(const char* str, size_t index);
	void removeInternal(size_t index);

public:
	StringPool();

	StringPool(const StringPool& other) = delete;
	StringPool& operator=(const StringPool& other) = delete;

	const size_t getSize() const;
	const size_t getCapacity() const;

	const char* getString(const char* str);
	void removeString(const char* str);

	~StringPool() noexcept;
};