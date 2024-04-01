#pragma once

#include <iostream>
#include <cstdint>

#define SHORT_BYTE_LENGTH 4

class MultiSet
{
private:
	uint8_t* buckets = nullptr;
	size_t bucketsCount = 0;
	size_t N = 0;

	void copyFrom(const MultiSet& other);
	void free();

	const size_t getBucketIndex(size_t num) const;
	const bool checkBit(uint8_t num, size_t pos) const;

public:
	MultiSet(size_t N);

	MultiSet(const MultiSet& other);
	MultiSet& operator=(const MultiSet& other);

	void add(size_t num);
	void remove(size_t num);
	const int contains(size_t num) const;

	friend MultiSet getUnionMultiSets(const MultiSet& lhs, const MultiSet& rhs);
	friend MultiSet getIntersectionMultiSets(const MultiSet& lhs, const MultiSet& rhs);

	void print() const;

	~MultiSet();
};