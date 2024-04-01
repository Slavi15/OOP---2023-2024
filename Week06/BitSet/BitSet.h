#pragma once

#include <iostream>
#include <cstdint>

#define BYTE_LENGTH 8

class BitSet
{
private:
	uint8_t* buckets = nullptr;
	size_t N = 0;
	size_t bucketsCount = 0;

	void copyFrom(const BitSet& other);
	void free();

	const size_t getBucketIndex(size_t num) const;

public:
	BitSet(size_t N);
	
	BitSet(const BitSet& other);
	BitSet& operator=(const BitSet& other);

	void add(size_t num);
	void remove(size_t num);
	const bool contains(size_t num) const;

	friend BitSet getUnionSets(const BitSet& lhs, const BitSet& rhs);
	friend BitSet getIntersectionSets(const BitSet& lhs, const BitSet& rhs);

	void print() const;

	~BitSet();
};