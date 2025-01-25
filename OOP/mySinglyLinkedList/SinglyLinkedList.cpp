#include <iostream>
#include <vector>
using namespace std;

template <class T>
struct Node {
	T data;
	Node* next = nullptr;
	Node(const T& data, Node* next = nullptr) : data(data), next(next) {}
};

template <class T>
class SinglyLinkedList {
private:
	Node<T>* head = nullptr;
	Node<T>* tail = nullptr;
public:
	SinglyLinkedList() = default;
	void push_back(const T& value);
	void pop_back();
	void pop_front();
	void push_front(const T& value);
	void print() const;
};

template<class T>
void SinglyLinkedList<T>::push_back(const T& value)
{
	Node<T>* newNode = new Node<T>(value);

	if (!this->head) {
		this->head = this->tail = newNode;
	}
	else {
		this->tail->next = newNode;
		this->tail = this->tail->next;
	}
}

template<class T>
void SinglyLinkedList<T>::pop_back()
{
	if (!head) {
		throw logic_error("Empty List!");
	}
	Node<T>* iter = head;
	Node<T>* prev = nullptr;
	while (iter->next) {
		prev = iter;
		iter = iter->next;
	}
	if (head != tail) {
		prev->next = nullptr;
		tail = prev;
	}
	else {
		head = tail = nullptr;
	}
	delete iter;
}

template<class T>
void SinglyLinkedList<T>::pop_front()
{
	if (!head) {
		throw logic_error("Empty list!");
	}
	Node<T>* first = head;
	head = head->next;
	delete first;
	if (!head) {
		tail = nullptr;
	}
}

template<class T>
void SinglyLinkedList<T>::push_front(const T& value)
{
	Node<T>* newNode = new Node<T>(value);
	if (!head) {
		head = tail = newNode;
	}
	else {
		newNode->next = head;
		head = newNode;
	}
}

template<class T>
void SinglyLinkedList<T>::print() const
{
	Node<T>* iter = head;
	while (iter) {
		std::cout << iter->data << ' ';
		iter = iter->next;
	}
	std::cout << '\n';
}

int main() {
	SinglyLinkedList<int> s;
	s.push_back(7);
	s.push_back(8);
	s.push_back(3);
	s.push_back(11);
	s.push_front(-2);
	s.push_front(-8);
	s.pop_front();
	s.pop_back();
	s.print();
}
