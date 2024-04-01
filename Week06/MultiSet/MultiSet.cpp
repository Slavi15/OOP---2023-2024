#include "MultiSet.h"

MultiSet::MultiSet(size_t N) : N(N)
{
	this->bucketsCount = N / 4 + 1;
	this->buckets = new uint8_t[bucketsCount]{ 0 };
}

MultiSet::MultiSet(const MultiSet& other)
{
	copyFrom(other);
}

MultiSet& MultiSet::operator=(const MultiSet& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

void MultiSet::add(size_t num)
{
	if (num > N) return;

	size_t index = getBucketIndex(num);

	num %= SHORT_BYTE_LENGTH;
	size_t pos1 = num * 2;
	size_t pos2 = (num * 2) + 1;

	bool value1 = checkBit(buckets[index], pos1);
	bool value2 = checkBit(buckets[index], pos2);

	size_t occurences = (2 * value1) + value2;

	if (occurences == 3) return;
	occurences++;

	value1 = occurences & 0b10;
	value2 = occurences & 0b01;

	if (((buckets[index] & (1 << pos1)) > 0) != value1)
		buckets[index] ^= (1 << pos1);

	if (((buckets[index] & (1 << pos2)) > 0) != value2)
		buckets[index] ^= (1 << pos2);
}

void MultiSet::remove(size_t num)
{
	if (num > N) return;

	size_t index = getBucketIndex(num);

	num %= SHORT_BYTE_LENGTH;
	size_t pos1 = num * 2;
	size_t pos2 = (num * 2) + 1;

	bool value1 = checkBit(buckets[index], pos1);
	bool value2 = checkBit(buckets[index], pos2);

	size_t occurences = (2 * value1) + value2;

	if (occurences == 0) return;
	occurences--;

	value1 = occurences & 0b10;
	value2 = occurences & 0b01;

	if (((buckets[index] & (1 << pos1)) > 0) != value1)
		buckets[index] ^= (1 << pos1);

	if (((buckets[index] & (1 << pos2)) > 0) != value2)
		buckets[index] ^= (1 << pos2);
}

const int MultiSet::contains(size_t num) const
{
	if (num > N) return -1;

	size_t index = getBucketIndex(num);

	num %= SHORT_BYTE_LENGTH;
	size_t pos1 = num * 2;
	size_t pos2 = (num * 2) + 1;

	bool value1 = checkBit(buckets[index], pos1);
	bool value2 = checkBit(buckets[index], pos2);

	size_t occurences = (2 * value1) + value2;
	return occurences;
}

MultiSet getUnionMultiSets(const MultiSet& lhs, const MultiSet& rhs)
{
	MultiSet m(std::max(lhs.N, rhs.N));

	size_t minBucketsCount = std::min(lhs.bucketsCount, rhs.bucketsCount);
	for (size_t i = 0; i < minBucketsCount; i++)
		m.buckets[i] = (lhs.buckets[i] | rhs.buckets[i]);

	const MultiSet& biggerSet = (lhs.N > rhs.N) ? lhs : rhs;
	for (size_t i = minBucketsCount; i < biggerSet.bucketsCount; i++)
		m.buckets[i] |= biggerSet.buckets[i];

	return m;
}

MultiSet getIntersectionMultiSets(const MultiSet& lhs, const MultiSet& rhs)
{
	MultiSet m(std::min(lhs.N, rhs.N));

	size_t minBucketsCount = std::min(lhs.bucketsCount, rhs.bucketsCount);
	for (size_t i = 0; i < minBucketsCount; i++)
		m.buckets[i] = (lhs.buckets[i] & rhs.buckets[i]);

	return m;
}

void MultiSet::print() const
{
	std::cout << "{ ";

	for (size_t i = 0; i <= N; i++) // [0 ... N]
	{
		int occurences = contains(i);
		for (size_t j = 0; j < occurences; j++)
			std::cout << i << " ";
	}

	std::cout << "}" << std::endl;
}

MultiSet::~MultiSet()
{
	free();
}

void MultiSet::copyFrom(const MultiSet& other)
{
	N = other.N;
	bucketsCount = other.bucketsCount;

	buckets = new uint8_t[bucketsCount];
	for (size_t i = 0; i < bucketsCount; i++)
		buckets[i] = other.buckets[i];
}

void MultiSet::free()
{
	delete[] buckets;

	buckets = nullptr;
	bucketsCount = 0;
	N = 0;
}

const size_t MultiSet::getBucketIndex(size_t num) const
{
	if (num > N) return 0;

	return num / 4;
}

const bool MultiSet::checkBit(uint8_t num, size_t pos) const
{
	int mask = 1;
	mask <<= pos;
	return (num & mask) == mask;
}