#include "MultiSet.h"

MultiSet::MultiSet() = default;

MultiSet::MultiSet(size_t N, size_t K)
{
	setN(N);
	setK(K);
	setBucketsCount();

	this->_buckets = new uint8_t[_bucketsCount]{ 0 };
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

MultiSet::MultiSet(MultiSet&& other) noexcept
{
	moveFrom(std::move(other));
}

MultiSet& MultiSet::operator=(MultiSet&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

const size_t MultiSet::getN() const
{
	return this->_N;
}

const size_t MultiSet::getK() const
{
	return this->_K;
}

const size_t MultiSet::getBucketsCount() const
{
	return this->_bucketsCount;
}

void MultiSet::setN(size_t N)
{
	if (N < 0)
		throw std::out_of_range("The given number N should be higher than 0!");

	if (this->_N > 0)
		throw std::logic_error("The value N cannot be manipulated if it has already been set!");

	_N = N;
}

void MultiSet::setK(size_t K)
{
	if (K < MIN_BITS || K > MAX_BITS)
		throw std::out_of_range("The given K number of bits are out of range!");

	if (this->_K > 0)
		throw std::logic_error("The value K cannot be manipulated if it has already been set!");

	_K = K;
}

void MultiSet::setBucketsCount()
{
	size_t nextDivisibleByEight = getNextDivisibleByEight(this->_N * this->_K);
	this->_bucketsCount = ((this->_N * this->_K) % MAX_BITS == 0) ? nextDivisibleByEight / MAX_BITS + 1 : nextDivisibleByEight / MAX_BITS;
}

const size_t MultiSet::getBitBucketIndex(size_t bitIndex) const
{
	return bitIndex / MAX_BITS;
}

const size_t MultiSet::getBitPosition(size_t idx) const
{
	idx %= MAX_BITS;
	return MAX_BITS - idx - 1;
}

const size_t MultiSet::getOccurences(size_t num) const
{
	if (num > this->_N || num < 0)
		throw std::out_of_range("Number outside the range [0...N] cannot exist!");

	size_t occurences = 0;
	int startPosition = getStartPosition(num), endPosition = getEndPosition(num);

	for (int i = endPosition, bit = 0; i >= startPosition; i--, bit++)
		if (checkBit(this->_buckets[getBitBucketIndex(i)], getBitPosition(i)))
			occurences += powerOfTwo(bit);

	return occurences;
}

const int MultiSet::getStartPosition(size_t num) const
{
	return num * this->_K;
}

const int MultiSet::getEndPosition(size_t num) const
{
	return getStartPosition(num) + this->_K - 1;
}

void MultiSet::modifyBuckets(size_t num, size_t occurences)
{
	int endPosition = getEndPosition(num);
	size_t powerNumber = 0;

	while (occurences != getOccurences(num))
	{
		size_t index = getBitBucketIndex(endPosition);

		size_t bitPosition = getBitPosition(endPosition);
		bool bitValue = checkBit(this->_buckets[index], bitPosition);

		bitValue = occurences & powerOfTwo(powerNumber);

		if (checkBit(this->_buckets[index], bitPosition) != bitValue)
			this->_buckets[index] ^= powerOfTwo(bitPosition);

		endPosition--, powerNumber++;
	}
}

void MultiSet::add(size_t num)
{
	if (num > this->_N || num < 0)
		throw std::out_of_range("Number outside the range [0...N] cannot exist!");

	size_t occurences = getOccurences(num);

	if (occurences == powerOfTwo(this->_K)) return;
	//throw std::logic_error("Maximum number of occurences cannot be exceeded!");

	occurences++;
	modifyBuckets(num, occurences);
}

void MultiSet::remove(size_t num)
{
	if (num > this->_N || num < 0)
		throw std::out_of_range("Number outside the range [0...N] cannot exist!");

	size_t occurences = getOccurences(num);

	if (occurences == 0) return;
	//throw std::logic_error("The number of occurences cannot be a negative number!");

	occurences--;
	modifyBuckets(num, occurences);
}

const int MultiSet::contains(size_t num) const
{
	if (num > this->_N || num < 0)
		throw std::out_of_range("Number outside the range [0...N] cannot exist!");

	return getOccurences(num);
}

void MultiSet::addMultiple(size_t num, size_t occurences)
{
	for (size_t i = 0; i < occurences; i++)
		add(num);
}

void MultiSet::removeMultiple(size_t num, size_t occurences)
{
	for (size_t i = 0; i < occurences; i++)
		remove(num);
}

MultiSet getUnion(const MultiSet& lhs, const MultiSet& rhs)
{
	MultiSet multiset(std::max(lhs.getN(), rhs.getN()), std::max(lhs.getK(), rhs.getK()));

	size_t minN = std::min(lhs.getN(), rhs.getN());
	for (size_t i = 0; i <= minN; i++)
		multiset.addMultiple(i, std::max(lhs.contains(i), rhs.contains(i)));

	const MultiSet& biggerN = (lhs.getN() > rhs.getN()) ? lhs : rhs;
	for (size_t i = minN + 1; i <= multiset.getN(); i++)
		multiset.addMultiple(i, biggerN.contains(i));

	return multiset;
}

MultiSet getIntersection(const MultiSet& lhs, const MultiSet& rhs)
{
	MultiSet multiset(std::min(lhs.getN(), rhs.getN()), std::min(lhs.getK(), rhs.getK()));

	for (size_t i = 0; i <= multiset.getN(); i++)
		if (lhs.contains(i) && rhs.contains(i))
			multiset.addMultiple(i, std::min(lhs.contains(i), rhs.contains(i)));

	return multiset;
}

MultiSet getDifference(const MultiSet& lhs, const MultiSet& rhs)
{
	MultiSet multiset(lhs);

	size_t minN = std::min(multiset.getN(), rhs.getN());
	for (size_t i = 0; i <= minN; i++)
		if (multiset.contains(i))
			multiset.removeMultiple(i, rhs.contains(i));

	return multiset;
}

MultiSet getComplement(const MultiSet& other)
{
	MultiSet multiset(other.getN(), other.getK());

	for (size_t i = 0; i < other.getBucketsCount(); i++)
		multiset._buckets[i] = ~(other._buckets[i]);

	return multiset;
}

void MultiSet::readFromFile(std::ifstream& ifs)
{
	free(); // in case dynamic memory has already been allocated

	ifs.read((char*)&this->_N, sizeof(this->_N));
	ifs.read((char*)&this->_K, sizeof(this->_K));
	ifs.read((char*)&this->_bucketsCount, sizeof(this->_bucketsCount));

	this->_buckets = new uint8_t[_bucketsCount]{ 0 };
	ifs.read((char*)this->_buckets, this->_bucketsCount * sizeof(uint8_t));
}

void MultiSet::readFromFile(const char* fileName)
{
	if (!fileName)
		throw std::runtime_error("NULLPTR!");

	std::ifstream ifs(fileName, std::ios::in | std::ios::binary);
	if (!ifs.is_open()) throw std::runtime_error("File could not be opened!");

	return readFromFile(ifs);
}

void MultiSet::writeToFile(std::ofstream& ofs) const
{
	ofs.write((const char*)&this->_N, sizeof(this->_N));
	ofs.write((const char*)&this->_K, sizeof(this->_K));
	ofs.write((const char*)&this->_bucketsCount, sizeof(this->_bucketsCount));
	ofs.write((const char*)this->_buckets, this->_bucketsCount * sizeof(uint8_t));
}

void MultiSet::writeToFile(const char* fileName) const
{
	if (!fileName)
		throw std::runtime_error("NULLPTR!");

	std::ofstream ofs(fileName, std::ios::out | std::ios::binary);
	if (!ofs.is_open()) throw std::runtime_error("File could not be opened!");

	return writeToFile(ofs);
}

void MultiSet::printNumbersBucket(size_t num) const
{
	size_t occurences = contains(num);

	for (size_t j = 0; j < occurences; j++)
		std::cout << ' ' << num << ' ';
}

void MultiSet::printNumbers() const
{
	std::cout << "Decimal Representation: " << std::endl;
	std::cout << "{";

	for (size_t i = 0; i <= this->_N; i++)
		printNumbersBucket(i);

	std::cout << "}" << std::endl;
}

void MultiSet::printBinaryBucket(size_t bucketIdx) const
{
	std::cout << ' ';

	for (int j = MAX_BITS - 1; j >= 0; j--)
		std::cout << checkBit(this->_buckets[bucketIdx], j);

	std::cout << ' ';
}

void MultiSet::printBinary() const
{
	std::cout << "Binary Representation: " << std::endl;
	std::cout << "{";

	for (size_t i = 0; i < this->_bucketsCount; i++)
		printBinaryBucket(i);

	std::cout << "}" << std::endl;
}

MultiSet::~MultiSet()
{
	free();
}

void MultiSet::copyFrom(const MultiSet& other)
{
	this->_N = other._N;
	this->_K = other._K;
	this->_bucketsCount = other._bucketsCount;

	this->_buckets = new uint8_t[_bucketsCount]{ 0 };
	for (size_t i = 0; i < _bucketsCount; i++)
		this->_buckets[i] = other._buckets[i];
}

void MultiSet::moveFrom(MultiSet&& other) noexcept
{
	this->_N = other._N;
	this->_K = other._K;
	this->_bucketsCount = other._bucketsCount;
	this->_buckets = other._buckets;

	other._buckets = nullptr;
	other._bucketsCount = other._N = other._K = 0;
}

void MultiSet::free()
{
	delete[] _buckets;
	this->_buckets = nullptr;
	this->_bucketsCount = this->_N = this->_K = 0;
}

const bool MultiSet::checkBit(uint8_t num, size_t pos) const
{
	int mask = 1 << pos;
	return (num & mask) == mask;
}
