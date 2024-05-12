#pragma once

#include "Student.h"

class StudentCollection
{
private:
	Student** students = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	explicit StudentCollection(size_t newSize);

	const unsigned int getNextPowerOfTwo(unsigned int n) const;
	const unsigned int allocateCapacity(unsigned int size) const;

	void resize(size_t newCapacity);

	void copyFrom(const StudentCollection& other);
	void moveFrom(StudentCollection&& other) noexcept;
	void free();

	const int getFirstFreeIndex() const;

public:
	StudentCollection();

	StudentCollection(const StudentCollection& other);
	StudentCollection& operator=(const StudentCollection& other);

	StudentCollection(StudentCollection&& other) noexcept;
	StudentCollection& operator=(StudentCollection&& other) noexcept;

	const size_t getSize() const;
	const size_t getCapacity() const;

	void addAtFirstFreeIndex(const Student& student);
	void addAtFirstFreeIndex(Student&& student);

	void insert(const Student& student, size_t index);
	void insert(Student&& student, size_t index);

	const bool contains(size_t index) const;

	void remove(size_t index);

	const size_t getNumberInClass(const char* name) const;

	~StudentCollection() noexcept;
};