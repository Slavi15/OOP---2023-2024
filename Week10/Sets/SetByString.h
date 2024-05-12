#pragma once

#include <sstream>

#include "BitSet.h"

class SetByString : private BitSet
{
private:
	char* str = nullptr;

	void copyFrom(const SetByString& other);
	void moveFrom(SetByString&& other) noexcept;
	void free();

	void extractNumbers();

public:
	SetByString();
	SetByString(const char* str, size_t N);

	SetByString(const SetByString& other);
	SetByString& operator=(const SetByString& other);

	SetByString(SetByString&& other) noexcept;
	SetByString& operator=(SetByString&& other) noexcept;

	void setText(const char* str);

	void setAt(size_t index, char ch);

	void print() const;

	~SetByString() noexcept;
};