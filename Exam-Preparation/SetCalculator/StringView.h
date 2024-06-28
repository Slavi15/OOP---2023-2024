#pragma once

#include "String.h"

class StringView
{
private:
	const char* begin;
	const char* end;

public:
	StringView(const char* begin, const char* end);
	StringView(const char* str);
	StringView(const String& string);

	size_t length() const;

	const char& operator[](size_t index) const;

	StringView substr(size_t from, size_t howMany) const;

	friend std::ostream& operator<<(std::ostream& os, const StringView& ref);
};