#include "SubjectsContainer.h"

SubjectsContainer::SubjectsContainer() : SubjectsContainer(4) {}

SubjectsContainer::SubjectsContainer(size_t newSize) : size(0)
{
	this->capacity = allocateCapacity(newSize);
	this->subjects = new Subject * [this->capacity];
}

SubjectsContainer::SubjectsContainer(const SubjectsContainer& other)
{
	copyFrom(other);
}

SubjectsContainer& SubjectsContainer::operator=(const SubjectsContainer& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

SubjectsContainer::SubjectsContainer(SubjectsContainer&& other) noexcept
{
	moveFrom(std::move(other));
}

SubjectsContainer& SubjectsContainer::operator=(SubjectsContainer&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

const size_t SubjectsContainer::getSize() const
{
	return this->size;
}

const size_t SubjectsContainer::getCapacity() const
{
	return this->capacity;
}

void SubjectsContainer::addSubject(Subject* subject)
{
	if (getSize() >= getCapacity())
		resize(getCapacity() * 2);

	this->subjects[this->size++] = subject;
}

void SubjectsContainer::addDIS(const char* subject, const char* lecturer, const char* const* asistents, size_t length, size_t neededPoints)
{
	if (!subject || !lecturer || !asistents) return;

	DIS* dis = new DIS(subject, lecturer, asistents, length, neededPoints);
	addSubject(dis);
}

void SubjectsContainer::addOOP(const char* subject, const char* lecturer, const char* const* asistents, size_t length, size_t neededPoints, size_t bonusPoints)
{
	if (!subject || !lecturer || !asistents) return;

	OOP* oop = new OOP(subject, lecturer, asistents, length, neededPoints, bonusPoints);
	addSubject(oop);
}

void SubjectsContainer::remove(size_t index)
{
	if (index >= getSize()) return;

	if (getSize())
		this->size--;
	else
		return;

	std::swap(this->subjects[index], this->subjects[getSize()]);

	if (getSize() * 4 <= getCapacity() && getCapacity() > 1)
		resize(getCapacity() / 2);
}

const size_t SubjectsContainer::getSubjectOccurences(const char* subject) const
{
	if (!subject) return 0;

	size_t occurences = 0;

	for (size_t i = 0; i < getSize(); i++)
		if (strcmp(subject, this->subjects[i]->getSubjectName()) == 0)
			occurences++;

	return occurences;
}

const size_t SubjectsContainer::getMaxOccurences() const
{
	return std::max(getSubjectOccurences("DIS"), getSubjectOccurences("OOP"));
}

SubjectsContainer::~SubjectsContainer() noexcept
{
	free();
}

void SubjectsContainer::resize(size_t newCapacity)
{
	Subject** newSubjects = new Subject * [newCapacity];
	for (size_t i = 0; i < getSize(); i++)
		newSubjects[i] = this->subjects[i];

	delete[] this->subjects;
	this->subjects = newSubjects;
	this->capacity = newCapacity;
}

const unsigned int SubjectsContainer::getNextPowerOfTwo(unsigned int n) const
{
	if (n == 0) return 1;

	while (n & (n - 1))
		n &= (n - 1);

	return n << 1;
}

const unsigned int SubjectsContainer::allocateCapacity(unsigned int size) const
{
	return std::max(getNextPowerOfTwo(size + 1), 8u);
}

void SubjectsContainer::copyFrom(const SubjectsContainer& other)
{
	this->size = other.size;
	this->capacity = other.capacity;

	this->subjects = new Subject * [this->capacity];
	for (size_t i = 0; i < this->capacity; i++)
		this->subjects[i] = other.subjects[i]->clone();
}

void SubjectsContainer::moveFrom(SubjectsContainer&& other) noexcept
{
	this->subjects = other.subjects;
	this->size = other.size;
	this->capacity = other.capacity;

	other.subjects = nullptr;
	other.size = other.capacity = 0;
}

void SubjectsContainer::free()
{
	for (size_t i = 0; i < this->size; i++)
		delete this->subjects[i];

	delete[] this->subjects;

	this->subjects = nullptr;
	this->size = this->capacity = 0;
}
