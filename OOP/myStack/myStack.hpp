#pragma once
#include <iostream>
// template class Stack with fixed capacity (in the template)
template <typename T, const size_t N>
class myStack {
private:
	T data[N];
	size_t index = 0;
public:
	void push(const T& element);
	void push(T&& element);
	void pop();
	const T& peek() const;
	bool isEmpty() const;
};

template<typename T, size_t N>
inline void myStack<T, N>::push(const T& element)
{
	if (index >= N) return;
	data[index++] = element;
}

template<typename T, size_t N>
inline void myStack<T, N>::push(T&& element)
{
	if (index >= N) return;
	data[index++] = std::move(element);
}

template<typename T, size_t N>
inline void myStack<T, N>::pop()
{
	if (index <= 0)return;
	index--;
}

template<typename T, size_t N>
inline const T& myStack<T, N>::peek() const
{
	if (index == 0)throw std::logic_error("Stack is empty!");
	return data[index-1];
}

template<typename T, size_t N>
inline bool myStack<T, N>::isEmpty() const
{
	return index == 0;
}
