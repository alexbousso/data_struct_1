/*
 * list.h
 *
 *  Created on: Nov 15, 2014
 *      Author: alex
 */

#ifndef LIST_H_
#define LIST_H_

#include <iostream>
#include "exceptions.h"
#include <cassert>		// For assert

template<typename T>
class List {
	class Node;
	Node *first, *last;
	int listSize;

	// If the list is empty return ListIsEmpty() exception
	static void checkEmpty();

public:
	class Iterator;

	List();
	List(const List&);

	// QUESTION: Why do we need this??
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

	Iterator begin();
	Iterator end();

	// Returns the size of the list
	int size() const;
};

template<typename T>
class List<T>::Node {
	T data;
	typename List<T>::Node *next, *previous;

	friend class List;
	friend class Iterator;

	Node(T data) :
			data(data), next(NULL), previous(NULL) {
	}

	// QUESTION: Why do we need these??
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
	first->next = last;
	last->previous = first;
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
	while (listSize > 0) {
		popFront();
	}
	assert(last == first);
	delete last;
	last = first = NULL;
}

template<typename T>
void List<T>::popBack() {
	checkEmpty();
	assert(listSize > 0);

	List<T>::Node toDelete = last->previous;
	last->previous = last->previous->previous;
	last->previous->prevoius->next = last->previous->next;
	delete toDelete;
	listSize--;
}

template<typename T>
void List<T>::pushBack(const T& data) {
	List<T>::Node* newNode(new List<T>::Node(data));

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

	List<T>::Node toDelete = first->next;
	first = first->next;
	first->next->previous = NULL;
	delete toDelete;
	listSize--;
}

template<typename T>
void List<T>::pushFront(const T& data) {
	List<T>::Node* newNode(new List<T>::Node(data));

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
inline typename List<T>::Iterator List<T>::end() {
	return last;
}

template<typename T>
inline int List<T>::size() const {
	return listSize;
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
	if (!List<T>::Node::node->next) {
		throw IndexOutOfBounds();
	}
	node = List<T>::Node::node->next;
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

