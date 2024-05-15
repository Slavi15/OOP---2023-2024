#pragma once

#include "Subject.h"

#include "DIS.h"
#include "OOP.h"

class SubjectsContainer
{
private:
	Subject** subjects = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	SubjectsContainer(size_t newSize);
	void resize(size_t newCapacity);

	const unsigned int getNextPowerOfTwo(unsigned int n) const;
	const unsigned int allocateCapacity(unsigned int size) const;

	void copyFrom(const SubjectsContainer& other);
	void moveFrom(SubjectsContainer&& other) noexcept;
	void free();

	void addSubject(Subject* subject);

public:
	SubjectsContainer();

	SubjectsContainer(const SubjectsContainer& other);
	SubjectsContainer& operator=(const SubjectsContainer& other);

	SubjectsContainer(SubjectsContainer&& other) noexcept;
	SubjectsContainer& operator=(SubjectsContainer&& other) noexcept;

	const size_t getSize() const;
	const size_t getCapacity() const;

	void addDIS(const char* subject, const char* lecturer, const char* const* asistents, size_t length, size_t neededPoints);
	void addOOP(const char* subject, const char* lecturer, const char* const* asistents, size_t length, size_t neededPoints, size_t bonusPoints);

	void remove(size_t index);

	const size_t getSubjectOccurences(const char* subject) const;
	const size_t getMaxOccurences() const;

	~SubjectsContainer() noexcept;
};