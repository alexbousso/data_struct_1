/*
 * list.h
 *
 *  Created on: Nov 15, 2014
 *      Author: alex
 */

#ifndef LIST_H_
#define LIST_H_

#include "exceptions.h"
#include <cassert>		// For assert

template<typename T>
class List {
	class Node;
	Node *first, *last;
	int listSize;

	// If the list is empty return ListIsEmpty() exception
	void checkEmpty();

	// Pushes the first node in the list
	void pushFirstNode(List<T>::Node*);

public:
	class Iterator;

	Iterator begin();
	Iterator end();

	List();
	List(const List&);
	// TODO
//	List operator =(const List&);
	~List();

	// Remove last element from list
	void popBack();

	// Add element to the end of the list
	void pushBack(const T& data);

	// Remove first element from list
	void popFront();

	// Add element to the front of the list
	void pushFront(const T& data);

	// Returns the data at the given index
	T& at(const int index) const;
	T& operator [](const int index) const;

	// Returns the size of the list
	int size() const;

	// Resets the entire list
	void reset();

private:
	Iterator begin() const;
};

template<typename T>
class List<T>::Node {
	T data;
	typename List<T>::Node *next, *previous;

	friend class List;
	friend class Iterator;

	Node() :
			data(), next(nullptr), previous(nullptr) {
	}

	Node(T data) :
			data(data), next(nullptr), previous(nullptr) {
	}

	//TODO
//	Node(const Node&);
//	Node operator =(const Node&);
};

template<typename T>
class List<T>::Iterator {
	typename List<T>::Node *node;

public:
	Iterator(typename List<T>::Node* node) :
			node(node) {
	}
	typename List<T>::Iterator& operator ++();
	typename List<T>::Iterator operator ++(int);
	typename List<T>::Node& operator *() const;
	typename List<T>::Node* operator ->() const;
	bool operator ==(const Iterator&) const;
	bool operator !=(const Iterator&) const;
};

/*****************************
 * FUNCTIONS IMPLEMENTATIONS *
 *****************************/

/**
 * CLASS LIST
 */

template<typename T>
inline List<T>::List() :
		first(new List<T>::Node), last(first), listSize(0) {
	first->next = nullptr;
	last->previous = nullptr;
}

template<typename T>
inline List<T>::List(const List& copy) :
		List() {
	for (auto it = begin(); it != end(); ++it) {
		pushBack(it->node->data);
	}
}

template<typename T>
inline List<T>::~List() {
	reset();
	delete last;
	last = first = nullptr;
}

template<typename T>
void List<T>::popBack() {
	checkEmpty();
	assert(listSize > 0);

	List<T>::Node* toDelete(last->previous);
	last->previous = last->previous->previous;
	listSize == 1 ? first = last : last->previous->next = last;
	delete toDelete;
	listSize--;
}

template<typename T>
void List<T>::pushBack(const T& data) {
	List<T>::Node* newNode(new List<T>::Node(data));

	if (listSize == 0) {
		pushFirstNode(newNode);
		return;
	}

	assert(listSize > 0);
	last->previous->next = newNode;
	newNode->previous = last->previous;
	newNode->next = last;
	last->previous = newNode;
	listSize++;
}

template<typename T>
void List<T>::popFront() {
	checkEmpty();
	assert(listSize > 0);

	List<T>::Node* toDelete(first);
	first = first->next;
	first->previous = nullptr;
	delete toDelete;
	listSize--;
}

template<typename T>
void List<T>::pushFront(const T& data) {
	List<T>::Node* newNode(new List<T>::Node(data));

	if (listSize == 0) {
		pushFirstNode(newNode);
		return;
	}

	newNode->next = first;
	first->next->previous = newNode;
	newNode->previous = nullptr;
	first = newNode;
	listSize++;
}

template<typename T>
inline typename List<T>::Iterator List<T>::begin() {
	return first;
}

template<typename T>
inline typename List<T>::Iterator List<T>::begin() const {
	return first;
}

template<typename T>
inline typename List<T>::Iterator List<T>::end() {
	return last;
}

template<typename T>
inline int List<T>::size() const {
	return listSize;
}

template<typename T>
inline void List<T>::checkEmpty() {
	if (first == last) {
		throw ListIsEmpty();
	}
}

template<typename T>
inline void List<T>::pushFirstNode(List<T>::Node* node) {
	assert(first == last && listSize == 0);

	first = node;
	node->previous = nullptr;
	node->next = last;
	last->previous = node;
	listSize++;
}

template<typename T>
T& List<T>::at(const int index) const {
	if (index < 0 || index > listSize - 1) {
		throw IndexOutOfBounds();
	}

	return (*this)[index];
}

template<typename T>
T& List<T>::operator [](const int index) const {
	List<T>::Iterator it(begin());

	for (int i(0); i < index; ++i) {
		++it;
	}

	return it->data;
}

template<typename T>
void List<T>::reset() {
	while (listSize > 0) {
		popFront();
	}
	assert(last == first);
}

/**
 * CLASS NODE
 */

// QUESTION: Why do we need this?
//template<typename T>
//inline Node Node<T>::operator =(const Node& other) {
//	data = other.data;
//	return *this;
//}
/**
 * CLASS ITERATOR
 */

template<typename T>
inline typename List<T>::Iterator& List<T>::Iterator::operator ++() {
	if (!node->next) {
		throw IndexOutOfBounds();
	}
	node = node->next;
	return *this;
}

template<typename T>
inline typename List<T>::Iterator List<T>::Iterator::operator ++(int) {
	Iterator temp(node);
	++(*this);
	return temp;
}

template<typename T>
inline typename List<T>::Node& List<T>::Iterator::operator *() const {
	return *node;
}

template<typename T>
inline typename List<T>::Node* List<T>::Iterator::operator ->() const {
	return node;
}

template<typename T>
inline bool List<T>::Iterator::operator ==(const Iterator& it) const {
	return List<T>::Node::node == &(*it);
}

template<typename T>
inline bool List<T>::Iterator::operator !=(const Iterator& it) const {
	return !(*this == it);
}

#endif /* LIST_H_ */

