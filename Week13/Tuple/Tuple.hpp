#include <iostream>

#define TT template<typename T, size_t N>

TT
class Tuple
{
private:
	T data[N];

public:
	const size_t getSize() const;

	const T& operator[](size_t index) const;
	T& operator[](size_t index);
};

TT
const size_t Tuple<T, N>::getSize() const
{
	return N;
}

TT
const T& Tuple<T, N>::operator[](size_t index) const
{
	return this->data[index];
}

TT
T& Tuple<T, N>::operator[](size_t index)
{
	return this->data[index];
}