/*
 * list.h
 *
 *  Created on: Nov 15, 2014
 *      Author: alex
 */

#ifndef LIST_H_
#define LIST_H_

#include "exceptions.h"
#include <cassert>		// For assert#include <iostream>

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
	/**
	 * WARNING: If a node is added or removed the iterator becomes invalid! For
	 * every change in the list one must build a new iterator.
	 */
	class Iterator;

	Iterator begin();
	Iterator end();

	List();
	List(const List&);
	List operator =(List&);
	~List();

	/*searching for a specific data in the list
	 * returns true if found and feels the ptr with the object
	 *  and false if not-then the ptrs' value isn't relevant
	 */
	bool find(T&, T*);



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
			data(), next(NULL), previous(NULL) {
	}

	Node(T data) :
			data(data), next(NULL), previous(NULL) {
	}

	//TODO
//	Node(const Node&);
//	Node operator =(const Node&);
};

/**
 * WARNING: If a node is added or removed the iterator becomes invalid! For
 * every change in the list one must build a new iterator.
 */
template<typename T>
class List<T>::Iterator {
	typename List<T>::Node *node;

public:
	Iterator(typename List<T>::Node* node) :
			node(node) {
	}
	typename List<T>::Iterator& operator ++();
	typename List<T>::Iterator operator ++(int);
	T& operator *() const;
	// QUESTION: Do we need this?
//	T* operator ->() const;
	bool operator ==(const Iterator&) const;
	bool operator !=(const Iterator&) const;
};

/*
 *						*****************************
 *						* FUNCTIONS IMPLEMENTATIONS *
 *						*****************************
 */

/*
 *								CLASS LIST
 */

template<typename T>
inline List<T>::List() :
		first(new List<T>::Node), last(first), listSize(0) {
	first->next = NULL;
	last->previous = NULL;
}

// FIXME: Check if this is right
template<typename T>
inline List<T>::List(const List& copy) :
		first(new List<T>::Node), last(first), listSize(0) {
	for (List<T>::Iterator it = begin(); it != end(); ++it) {
		pushBack(*it);
	}
}

// FIXME: Check if this is right
template<typename T>
List<T> List<T>::operator =(List& copy) {
	for (List<T>::Iterator it(copy.begin()); it != copy.end(); ++it) {
		pushBack(*it);
	}
	return *this;
}

template<typename T>
inline List<T>::~List() {
	reset();
	delete last;
	last = first = NULL;
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
	// QUESTION:Do we need this?
//	if (!data) {
//		throw InvalidInput();
//	}

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
	first->previous = NULL;
	delete toDelete;
	listSize--;
}

template<typename T>
void List<T>::pushFront(const T& data) {
	// QUESTION:Do we need this?
//	if (!data) {
//		throw InvalidInput();
//	}

	List<T>::Node* newNode(new List<T>::Node(data));

	if (listSize == 0) {
		pushFirstNode(newNode);
		return;
	}

	newNode->next = first;
	first->next->previous = newNode;
	newNode->previous = NULL;
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
	node->previous = NULL;
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

	return *it;
}

template<typename T>
void List<T>::reset() {
	while (listSize > 0) {
		popFront();
	}
	assert(last == first);
}

/*
 *								CLASS NODE
 */

// QUESTION: Why do we need this?
//template<typename T>
//inline Node Node<T>::operator =(const Node& other) {
//	data = other.data;
//	return *this;
//}
/*
 *								CLASS ITERATOR
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
inline T& List<T>::Iterator::operator *() const {
	return node->data;
}

// QUESTION: Do we need this?
//template<typename T>
//inline T* List<T>::Iterator::operator ->() const {
//	return &(node->data);
//}

template<typename T>
inline bool List<T>::Iterator::operator ==(const Iterator& it) const {
	return node == it.node;
}

template<typename T>
inline bool List<T>::Iterator::operator !=(const Iterator& it) const {
	return !(*this == it);
}

#endif /* LIST_H_ */

