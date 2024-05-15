#include "StudentCollection.h"

StudentCollection::StudentCollection() : StudentCollection(4) {}

StudentCollection::StudentCollection(size_t newSize) : size(newSize)
{
	this->capacity = allocateCapacity(newSize);
	this->students = new Student * [this->capacity] { nullptr };
}

StudentCollection::StudentCollection(const StudentCollection& other)
{
	copyFrom(other);
}

StudentCollection& StudentCollection::operator=(const StudentCollection& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

StudentCollection::StudentCollection(StudentCollection&& other) noexcept
{
	moveFrom(std::move(other));
}

StudentCollection& StudentCollection::operator=(StudentCollection&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

const size_t StudentCollection::getSize() const
{
	return this->size;
}

const size_t StudentCollection::getCapacity() const
{
	return this->capacity;
}

void StudentCollection::addAtFirstFreeIndex(const Student& student)
{
	if (getSize() >= getCapacity())
		resize(getCapacity() * 2);

	int index = getFirstFreeIndex();

	if (index == -1)
		throw std::out_of_range("No free spaces left!");

	this->students[index] = new Student(student);
}

void StudentCollection::addAtFirstFreeIndex(Student&& student)
{
	if (getSize() >= getCapacity())
		resize(getCapacity() * 2);

	int index = getFirstFreeIndex();

	if (index == -1)
		throw std::out_of_range("No free spaces left!");

	this->students[index] = new Student(std::move(student));
}

void StudentCollection::insert(const Student& student, size_t index)
{
	if (index >= getCapacity())
		resize(getCapacity() * 2);

	if (this->students[index] == nullptr)
		this->students[index] = new Student(student);
	else
		*this->students[index] = student;

	this->size++;
}

void StudentCollection::insert(Student&& student, size_t index)
{
	if (index >= getCapacity())
		resize(getCapacity() * 2);

	if (this->students[index] == nullptr)
		this->students[index] = new Student(std::move(student));
	else
		*this->students[index] = std::move(student);

	this->size++;
}

const bool StudentCollection::contains(size_t index) const
{
	if (index >= getCapacity())
		throw std::out_of_range("Invalid index!");

	return this->students[index] != nullptr;
}

void StudentCollection::remove(size_t index)
{
	if (index >= getCapacity())
		throw std::out_of_range("Invalid index!");

	if (getSize())
		this->size--;
	else
		throw std::invalid_argument("Already empty!");

	delete this->students[index];
	this->students[index] = nullptr;

	if ((getSize() * 4) <= getCapacity() && getCapacity() > 1)
		resize(getCapacity() / 2);
}

const size_t StudentCollection::getNumberInClass(const char* name) const
{
	if (!name)
		throw std::runtime_error("NULLPTR!");

	for (size_t i = 0; i < getCapacity(); i++)
		if (this->students[i] != nullptr && strcmp(this->students[i]->getName(), name) == 0)
			return i + 1;

	throw std::invalid_argument("Invalid student!");
}

StudentCollection::~StudentCollection() noexcept
{
	free();
}

void StudentCollection::resize(size_t newCapacity)
{
	Student** newStudents = new Student * [newCapacity] { nullptr };

	for (size_t i = 0; i < getSize(); i++)
		newStudents[i] = this->students[i];

	delete[] this->students;

	this->students = newStudents;
	this->capacity = newCapacity;
}

void StudentCollection::copyFrom(const StudentCollection& other)
{
	this->size = other.size;
	this->capacity = other.capacity;

	this->students = new Student * [this->capacity];
	for (size_t i = 0; i < this->capacity; i++)
		if (other.students[i] == nullptr)
			this->students[i] = nullptr;
		else
			this->students[i] = new Student(*other.students[i]);
}

void StudentCollection::moveFrom(StudentCollection&& other) noexcept
{
	this->students = other.students;
	this->size = other.size;
	this->capacity = other.capacity;

	other.students = nullptr;
	other.size = other.capacity = 0;
}

void StudentCollection::free()
{
	for (size_t i = 0; i < this->capacity; i++)
		delete this->students[i];

	delete[] this->students;
}

const int StudentCollection::getFirstFreeIndex() const
{
	for (size_t i = 0; i < getCapacity(); i++)
		if (this->students[i] == nullptr)
			return i;

	return -1;
}

const unsigned int StudentCollection::getNextPowerOfTwo(unsigned int n) const
{
	if (n == 0) return 1;

	while (n & (n - 1))
		n &= (n - 1);

	return n << 1;
}

const unsigned int StudentCollection::allocateCapacity(unsigned int size) const
{
	return std::max(getNextPowerOfTwo(size + 1), 8u);
}
