#pragma once
#include <iostream>
template <typename T>
class myQueue {
private:
	T* data = nullptr;;
	size_t size = 0;
	size_t capacity = 4;
	size_t put = 0;
	size_t get = 0;
	void free();
	void copyFrom(const myQueue<T>& other);
	void moveFrom(myQueue<T>&& other);
	void resize();
public:
	myQueue();
	myQueue(const myQueue<T>& other);
	myQueue(myQueue<T>&& other);
	myQueue<T>& operator=(const myQueue<T>& other);
	myQueue<T>& operator=(myQueue<T>&& other);
	~myQueue();
	void push(const T& element);
	void push(T&& element);
	void pop();
	const T& peek() const;
	bool isEmpty() const;
	void print() const;
};

template<typename T>
inline void myQueue<T>::free()
{
	delete[] data;
	size = 0;
	capacity = 4;
	put = get = 0;
}

template<typename T>
inline void myQueue<T>::copyFrom(const myQueue<T>& other)
{
	size = other.size;
	capacity = other.capacity;
	put = other.put;
	get = other.get;
	data = new (std::nothrow) T[capacity];
	if (!data)throw std::logic_error("could not create data!");
	for (int i = 0;i < capacity;i++) {
		data[i] = other.data[i];
	}
}

template<typename T>
inline void myQueue<T>::moveFrom(myQueue<T>&& other)
{
	put = other.put;
	get = other.get;
	size = other.size;
	capacity = other.capacity;
	data = other.data;
	other.put = 0;
	other.get = 0;
	other.size = 0;
	other.capacity = 4;
	other.data = nullptr;
}

template<typename T>
inline void myQueue<T>::resize()
{
	T* newData = new (std::nothrow) T[capacity * 2];
	if (!newData)throw std::logic_error("could not create data!");
	for (int i = 0;i < capacity;i++) {
		newData[i] = data[get];
		(++get) %= capacity;
	}
	capacity *= 2;
	put = size;
	get = 0;
	delete[] data;
	data = newData;
}

template<typename T>
inline myQueue<T>::myQueue()
{
	put = get = 0;
	size = 0;
	capacity = 4;
	data = new (std::nothrow) T[capacity];
	if (!data)throw std::logic_error("could not create data!");
}

template<typename T>
inline myQueue<T>::myQueue(const myQueue<T>& other)
{
	copyFrom(other);
}

template<typename T>
inline myQueue<T>::myQueue(myQueue<T>&& other)
{
	moveFrom(std::move(other));
}

template<typename T>
inline myQueue<T>& myQueue<T>::operator=(const myQueue<T>& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

template<typename T>
inline myQueue<T>& myQueue<T>::operator=(myQueue<T>&& other)
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template<typename T>
inline myQueue<T>::~myQueue()
{
	free();
}

template<typename T>
inline void myQueue<T>::push(const T& element)
{
	if (size >= capacity)resize();
	data[put] = element;
	(++put) %= capacity;
	size++;
}

template<typename T>
inline void myQueue<T>::push(T&& element)
{
	if (size >= capacity)resize();
	data[put] = std::move(element);
	(++put) %= capacity;
	size++;
}

template<typename T>
inline void myQueue<T>::pop()
{
	if (size == 0)return;
	size--;
	(++get) %= capacity;
}

template<typename T>
inline const T& myQueue<T>::peek() const
{
	if (size == 0)throw std::logic_error("Queue is empty!");
	return data[get];
}

template<typename T>
inline bool myQueue<T>::isEmpty() const
{
	return size == 0;
}

template<typename T>
inline void myQueue<T>::print() const
{
	myQueue<T> toPrint(*this);
	for (int i = 0;i < size;i++) {
		std::cout << toPrint.peek();
		toPrint.pop();
	}
}
