#include "StringView.h"

StringView::StringView(const char* begin, const char* end) : begin(begin), end(end) {}

StringView::StringView(const char* str) : StringView(str, str + strlen(str)) {}

//StringView::StringView(const char* str) : begin(str), end(str + strlen(str)) {}

StringView::StringView(const String& string) : StringView(string.c_str()) {}

size_t StringView::length() const
{
	return this->end - this->begin;
}

const char& StringView::operator[](size_t index) const
{
	return begin[index];
}

StringView StringView::substr(size_t from, size_t howMany) const
{
	if (begin + from + howMany > end)
		throw std::out_of_range("Substr, out of range!");

	return StringView(begin + from, begin + from + howMany);
}

std::ostream& operator<<(std::ostream& os, const StringView& ref)
{
	const char* iter = ref.begin;

	while (iter != ref.end)
	{
		os << *iter;
		iter++;
	}

	return os;
}
