#pragma once

#include <iostream>
#include <cstdint>
#include <fstream>
#include <stdexcept>

#define MAX_BITS 8
#define MIN_BITS 1

#define powerOfTwo(n) (1 << n)

inline size_t getNextDivisibleByEight(size_t num)
{
	size_t bits = num & (MAX_BITS - 1);
	return bits == 0 ? num : num + (MAX_BITS - bits);
}

class MultiSet
{
private:
	uint8_t* _buckets = nullptr;
	size_t _bucketsCount = 0;
	size_t _N = 0;
	size_t _K = 0;

	void copyFrom(const MultiSet& other);
	void moveFrom(MultiSet&& other) noexcept;
	void free();

	const bool checkBit(uint8_t num, size_t pos) const;

	const size_t getBitBucketIndex(size_t idx) const;
	const size_t getBitPosition(size_t idx) const;
	const size_t getOccurences(size_t num) const;

	void readFromFile(std::ifstream& ifs);
	void writeToFile(std::ofstream& ofs) const;

	const int getStartPosition(size_t num) const;
	const int getEndPosition(size_t num) const;

public:
	MultiSet();
	MultiSet(size_t N, size_t K);

	MultiSet(const MultiSet& other);
	MultiSet& operator=(const MultiSet& other);

	MultiSet(MultiSet&& other) noexcept;
	MultiSet& operator=(MultiSet&& other) noexcept;

	const size_t getN() const;
	const size_t getK() const;
	const size_t getBucketsCount() const;

	void setN(size_t N);
	void setK(size_t K);
	void setBucketsCount();

	void add(size_t num);
	void remove(size_t num);
	const int contains(size_t num) const;

	void addMultiple(size_t num, size_t occurences);
	void removeMultiple(size_t num, size_t occurences);
	void modifyBuckets(size_t num, size_t occurences);

	friend MultiSet getUnion(const MultiSet& lhs, const MultiSet& rhs);
	friend MultiSet getIntersection(const MultiSet& lhs, const MultiSet& rhs);

	friend MultiSet getDifference(const MultiSet& lhs, const MultiSet& rhs);

	friend MultiSet getComplement(const MultiSet& other);

	void readFromFile(const char* fileName);
	void writeToFile(const char* fileName) const;

	void printNumbersBucket(size_t num) const;
	void printNumbers() const;

	void printBinaryBucket(size_t bucketIdx) const;
	void printBinary() const;

	~MultiSet();
};