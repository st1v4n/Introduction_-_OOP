#pragma once
#include <iostream>
//a class that i wrote during Practicum course
//found a good usage of it
namespace vectorConstants {
	const size_t capacityMultiplier = 2;
};
using namespace vectorConstants;
template <typename T>
class myVector {
private:
	T* collection = nullptr;
	size_t size = 0;
	size_t capacity = 0;
	void free();
	void resize();
	void copyFrom(const myVector<T>& other);
	void moveFrom(myVector<T>&& other);
	void swap(T& lhs, T& rhs);
public:
	myVector();
	myVector(const myVector<T>& other);
	myVector(myVector<T>&& other);
	myVector<T>& operator=(const myVector<T>& other);
	myVector<T>& operator=(myVector<T>&& other);
	~myVector();
	void print() const;
	void push_back(const T& element);
	void pop_back();
	void insert(const T& element, size_t index);
	void insertWithSwaps(const T& element, size_t index);
	void erase(size_t index);
	void clear();
	const T& operator[](size_t index) const;
	T& operator[](size_t index);
	bool isEmpty() const;
	size_t getSize() const;
	template <typename T>
	friend std::ostream& operator<<(std::ostream& os, const myVector<T>& vect);
};

template<typename T>
inline void myVector<T>::free()
{
	delete[] collection;
	size = 0;
	capacity = 0;
}

template<typename T>
inline void myVector<T>::resize()
{
	T* helpResize = new (std::nothrow) T[capacity];
	if (!helpResize) {
		throw - 1;
	}
	for (int i = 0;i < size;i++) {
		helpResize[i] = collection[i];
	}
	delete[] collection;
	capacity *= capacityMultiplier;
	collection = new (std::nothrow) T[capacity];
	if (!collection) {
		delete[] helpResize;
		throw - 1;
	}
	for (int i = 0;i < size;i++) {
		collection[i] = helpResize[i];
	}
	delete[] helpResize;
}

template<typename T>
inline void myVector<T>::copyFrom(const myVector<T>& other)
{
	size = other.size;
	capacity = other.capacity;
	collection = new (std::nothrow) T[capacity];
	if (!collection) {
		throw - 1;
	}
	for (int i = 0;i < size;i++) {
		collection[i] = other.collection[i];
	}
}

template<typename T>
inline void myVector<T>::moveFrom(myVector<T>&& other)
{
	size = other.size;
	other.size = 0;
	capacity = other.capacity;
	other.capacity = 0;
	collection = other.collection;
	other.collection = nullptr;
}

template<typename T>
inline void myVector<T>::swap(T& lhs, T& rhs)
{
	T temp = lhs;
	lhs = rhs;
	rhs = temp;
}

template<typename T>
inline myVector<T>::myVector()
{
	size = 0;
	capacity = 4;
	collection = new (std::nothrow) T[capacity];
}

template<typename T>
inline myVector<T>::myVector(const myVector<T>& other)
{
	copyFrom(other);
}

template<typename T>
inline myVector<T>::myVector(myVector<T>&& other)
{
	moveFrom(std::move(other));
}

template<typename T>
inline myVector<T>& myVector<T>::operator=(const myVector<T>& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

template<typename T>
inline myVector<T>& myVector<T>::operator=(myVector<T>&& other)
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template<typename T>
inline myVector<T>::~myVector()
{
	free();
}

template<typename T>
inline void myVector<T>::print() const
{
	for (int i = 0;i < size;i++) {
		std::cout << collection[i] << " ";
	}
	std::cout << '\n';
}

template<typename T>
inline void myVector<T>::push_back(const T& element)
{
	if (size == capacity)resize();
	collection[size++] = element;
}

template<typename T>
inline void myVector<T>::pop_back()
{
	size--;
}

template<typename T>
inline void myVector<T>::insert(const T& element, size_t index)
{
	if (index > size) {
		std::cout << "Invalid index!";
		return;
	}
	else if (index == size) {
		if (size == capacity)resize();
		size++;
	}
	collection[index] = element;
}

template<typename T>
inline void myVector<T>::insertWithSwaps(const T& element, size_t index)
{
	if (index > size) {
		std::cout << "Invalid index!";
		return;
	}
	if (size == capacity)resize();
	size++;
	for (int i = size;i > index;i--) {
		swap(collection[i], collection[i - 1]);
	}
	collection[index] = element;
}

template<typename T>
inline void myVector<T>::erase(size_t index)
{
	if (index >= size) {
		std::cout << "Invalid index!";
		return;
	}
	for (int i = index;i < size - 1;i++) {
		swap(collection[i], collection[i + 1]);
	}
	size--;
}

template<typename T>
inline void myVector<T>::clear()
{
	size = 0;
	capacity = 4;
}

template<typename T>
inline const T& myVector<T>::operator[](size_t index) const
{
	if (index >= size) {
		throw std::out_of_range("Invalid index!");
	}
	return collection[index];
}
template<typename T>
inline T& myVector<T>::operator[](size_t index)
{
	if (index >= size) {
		throw std::out_of_range("Invalid index!");
	}
	return collection[index];
}

template<typename T>
inline bool myVector<T>::isEmpty() const
{
	return (size == 0);
}

template<typename T>
inline size_t myVector<T>::getSize() const
{
	return size;
}
template <typename T>
std::ostream& operator<<(std::ostream& os, const myVector<T>& vect) {
	for (size_t i = 0;i < vect.size;i++) {
		os << vect[i] << ' ';
	}
	return os;
}

