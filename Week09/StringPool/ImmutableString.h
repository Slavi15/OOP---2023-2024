#pragma once

#include <iostream>
#include <fstream>

#include "StringPool.h"

class ImmutableString
{
private:
	char* data = nullptr;
	size_t size = 0;

	void copyFrom(const ImmutableString& other);
	void moveFrom(ImmutableString&& other) noexcept;
	void free();

	static StringPool pool;

public:
	ImmutableString();
	ImmutableString(const char* data);

	ImmutableString(const ImmutableString& other);
	ImmutableString(ImmutableString&& other) noexcept;

	const char* c_str() const;
	const size_t getSize() const;

	const char& operator[](size_t index) const;

	friend const bool operator==(const ImmutableString& lhs, const ImmutableString& rhs);
	friend const bool operator!=(const ImmutableString& lhs, const ImmutableString& rhs);

	friend std::ostream& operator<<(std::ostream& os, const ImmutableString& ref);

	~ImmutableString() noexcept;
};