#include <iostream>

#define TT template <typename T, size_t N>

TT
class Stack
{
private:
	T data[N];
	size_t size = 0;

public:
	size_t getSize() const;

	void push_back(const T& element);
	void push_back(T&& element);

	void pop();

	const T& peek() const;

	bool isEmpty() const;
};

TT
size_t Stack<T, N>::getSize() const
{
	return this->size;
}

TT
void Stack<T, N>::push_back(const T& element)
{
	if (getSize() >= N)
		return;

	data[this->size++] = element;
}

TT
void Stack<T, N>::push_back(T&& element)
{
	if (getSize() >= N)
		return;

	data[this->size++] = std::move(element);
}

TT
void Stack<T, N>::pop()
{
	if (isEmpty())
		throw std::out_of_range("Error!");

	this->size--;
}

TT
const T& Stack<T, N>::peek() const
{
	if (isEmpty())
		throw std::out_of_range("Error!");

	return data[this->size - 1];
}

TT
bool Stack<T, N>::isEmpty() const
{
	return this->size == 0;
}
