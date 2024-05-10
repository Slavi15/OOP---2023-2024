#include "BitSet.h"

BitSet::BitSet(size_t N) : N(N)
{
	this->bucketsCount = N / BYTE_LENGTH + 1;
	this->buckets = new uint8_t[bucketsCount]{ 0 };
}

const size_t BitSet::getBucketIndex(size_t num) const
{
	return num / BYTE_LENGTH;
}

BitSet::BitSet(const BitSet& other)
{
	copyFrom(other);
}

BitSet& BitSet::operator=(const BitSet& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

BitSet::BitSet(BitSet&& other) noexcept
{
	moveFrom(std::move(other));
}

BitSet& BitSet::operator=(BitSet&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

const size_t BitSet::getN() const
{
	return N;
}

const size_t BitSet::getBucketsCount() const
{
	return bucketsCount;
}

const uint16_t BitSet::getNumbersCount() const
{
	return numbersCount;
}

void BitSet::add(size_t num)
{
	if (num > N) return;

	size_t idx = getBucketIndex(num);
	numbersCount++;

	num %= BYTE_LENGTH;
	uint8_t mask = 1 << num;

	buckets[idx] |= mask;
}

void BitSet::invert(size_t num)
{
	if (num > N) return;

	size_t index = getBucketIndex(num);
	numbersCount--;

	num %= BYTE_LENGTH;
	int mask = 1 << num;

	buckets[index] ^= mask;
}

void BitSet::remove(size_t num)
{
	if (num > N) return;

	size_t idx = getBucketIndex(num);
	num %= BYTE_LENGTH;
	uint8_t mask = ~(1 << num);

	buckets[idx] &= mask;
}

const bool BitSet::contains(size_t num) const
{
	if (num > N) return false;

	size_t idx = getBucketIndex(num);
	num %= BYTE_LENGTH;
	uint8_t mask = 1 << num;

	return (buckets[idx] & mask) == mask;
}

BitSet getUnionSets(const BitSet& lhs, const BitSet& rhs)
{
	BitSet bitset(std::max(lhs.N, rhs.N));

	size_t minBucketsCount = std::min(lhs.bucketsCount, rhs.bucketsCount);
	for (size_t i = 0; i < minBucketsCount; i++)
		bitset.buckets[i] = (lhs.buckets[i] | rhs.buckets[i]);

	const BitSet& biggerN = (lhs.bucketsCount > rhs.bucketsCount) ? lhs : rhs;
	for (size_t i = minBucketsCount; i < biggerN.bucketsCount; i++)
		bitset.buckets[i] |= biggerN.buckets[i];

	return bitset;
}

BitSet getIntersectionSets(const BitSet& lhs, const BitSet& rhs)
{
	BitSet bitset(std::min(lhs.N, rhs.N));

	size_t minBucketsCount = std::min(lhs.bucketsCount, rhs.bucketsCount);
	for (size_t i = 0; i < minBucketsCount; i++)
		bitset.buckets[i] = (lhs.buckets[i] & rhs.buckets[i]);

	return bitset;
}

void BitSet::print() const
{
	std::cout << "{ ";

	for (size_t i = 0; i < N; i++)
		if (contains(i)) std::cout << i << " ";

	std::cout << "}" << std::endl;
}

BitSet::~BitSet()
{
	free();
}

void BitSet::copyFrom(const BitSet& other)
{
	this->N = other.N;
	this->bucketsCount = other.bucketsCount;
	this->numbersCount = other.numbersCount;

	this->buckets = new uint8_t[bucketsCount]{ 0 };
	for (size_t i = 0; i < bucketsCount; i++)
		this->buckets[i] = other.buckets[i];
}

void BitSet::moveFrom(BitSet&& other) noexcept
{
	buckets = other.buckets;
	N = other.N;
	bucketsCount = other.bucketsCount;
	numbersCount = other.numbersCount;

	other.buckets = nullptr;
	other.N = other.bucketsCount = other.numbersCount = 0;
}

void BitSet::free()
{
	delete[] buckets;

	buckets = nullptr;
	N = bucketsCount = numbersCount = 0;
}
