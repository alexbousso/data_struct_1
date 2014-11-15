/*
 * list.h
 *
 *  Created on: Nov 15, 2014
 *      Author: alex
 */

#ifndef LIST_H_
#define LIST_H_

#include <iostream>

template<typename T>
class List {
	class Node;
	Node *first, *last;
	int listSize;

public:
	class Iterator;

	List() :
			first(NULL), last(NULL), listSize(0) {
	}
	List(const List&);
	List operator =(const List&);
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
class Node {
	T data;
	Node *next;

	friend class List;
	friend class Iterator;

	Node(T data) :
			data(data), next(NULL) {
	}
	Node(const Node&);
	Node operator =(const Node&);
};

template<typename T>
class Iterator {
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

#endif /* LIST_H_ */

