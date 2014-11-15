/*
 * avl_tree.h
 *
 *  Created on: Nov 15, 2014
 *      Author: Miri
 */

#ifndef AVL_TREE_H_
#define AVL_TREE_H_

#include <iostream>

template<typename T>
class AVLTree {
	class Node;
	Node* root;
	int treeSize;

public:
	AVLTree() :
			root(NULL), treeSize(0) {
	}
	AVLTree(const AVLTree&);
	AVLTree operator=(const AVLTree&);
	~AVLTree();

	class Iterator;
	Iterator begin();
	Iterator end();

	//inserting a new object to the tree
	void insert(T&);

	//removing an object from the tree
	void remove(Iterator);

	//finding a specific object in the tree
	Iterator find(T) const;

	//returning the current size of the tree
	int size() const;
};

template<typename T>
class Node {
	T data;
	Node* left;
	Node* right;
	Node* dad;
	friend class AVLTree;
	friend class Iterator;

	Node(T data) :
			data(data), left(NULL), right(NULL), dad(NULL) {
	}
	Node(const Node&);
	Node operator=(const Node&);
};

template<typename T>
class Iterator {
	Node* node;

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

#endif /* AVL_TREE_H_ */
