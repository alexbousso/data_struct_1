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

	// TODO: Why do we need this??
//	List operator =(const List&);

	~List();

	// Remove last element from list
	void popBack();

	// Add element to the end of the list
	void pushBack(const T&);

	// Remove first element from list
	void popFront();

	// Add element to the front of the list
	void pushFront(const T&);

	Iterator begin();
	Iterator end();

	// Returns the size of the list
	int size() const;
};

template<typename T>
class List<T>::Node {
	T data;
	Node *next;

	friend class List;
	friend class Iterator;

	Node(T data) :
			data(data), next(NULL) {
	}

	// TODO: Why do we need this??
//	Node(const Node&);

	Node operator =(const Node&);
};

template<typename T>
class List<T>::Iterator {
	Node *node;

public:
	Iterator(Node<T>* node) :
			node(node) {
	}
	Iterator& operator ++();
	Iterator operator ++(int);
	Node<T>& operator *() const;
	Node<T>* operator ->() const;
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
		first(NULL), last(NULL), listSize(0) {
}

template<typename T>
inline List<T>::List(const List& copy) :
		List() {
	for (auto it = begin(); it != end(); ++it) {
		pushFront(it->node->data);
	}
}

template<typename T>
inline List<T>::~List() {
	for (auto it(begin()); it != end(); ++it) {
		delete &(*it);
	}
}

template<typename T>
inline void List<T>::popBack() {
	checkEmpty();
	for (auto it(begin()); it != end; ++it) {
		if (it->next == last) {
			delete last;
			it->next = NULL;
			last = &(*it);
			return;
		}
	}
}

/**
 * CLASS NODE
 */

template<typename T>
Node Node<T>::operator =(const Node& other) {
	data = other.data;
	return *this;
}

/**
 * CLASS ITERATOR
 */

#endif /* LIST_H_ */

