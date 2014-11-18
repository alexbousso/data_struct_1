/*
 * avl_tree.h
 *
 *  Created on: Nov 15, 2014
 *      Author: Miri
 */

#ifndef AVL_TREE_H_
#define AVL_TREE_H_

#include <iostream>
#include "exceptions.h"
#include <cassert>

template<typename T>
class AVLTree {

	class AVLNode;
	AVLNode* root;
	int treeSize;
	//inserting a new object to the tree under a specific root
	void insert(AVLNode*, T&);
	//searching for an object in a specific sub tree
	AVLNode* find(AVLNode*, T) const;
	//removing an object from a specific subtree
	void remove(AVLNode*);
	//in case of removing a node with a single child' use this function
	void removeSingleChild(AVLNode*);

public:
	AVLTree() :
			root(NULL), treeSize(0) {
	}
	AVLTree(const AVLTree&);
	AVLTree operator=(const AVLTree&);
	~AVLTree();

	/*class Iterator {
	 AVLNode* node;

	 public:
	 Iterator(AVLNode<T>* node) :
	 node(node) {
	 }
	 Iterator& operator ++();
	 Iterator operator ++(int);
	 AVLNode<T>& operator *() const;
	 AVLNode<T>* operator ->() const;
	 bool operator ==(const Iterator&) const;
	 bool operator !=(const Iterator&) const;
	 };

	 Iterator begin();
	 Iterator end();
	 */
	//inserting a new object to the tree
	void insert(T&);

	//removing an object from the tree
	void remove(T&);

	//finding a specific object in the tree
	bool find(T) const;

	//returning the current size of the tree
	int size() const;

	//rotating right
	void rotateRight();

	//rotating left
	void rotateLeft();
};

template<typename T>
class AVLTree<T>::AVLNode {
	T data;
	AVLNode* left;
	AVLNode* right;
	AVLNode* dad;
	friend class AVLTree;
	friend class Iterator;

	AVLNode(T data) :
			data(data), left(NULL), right(NULL), dad(NULL) {
	}
	AVLNode(const AVLNode&);
	AVLNode operator=(const AVLNode&);
};

/******************************
 * Functions and Classes Implementation
 ******************************/

template<typename T>
void AVLTree<T>::insert(T& element) {
	if (!element) {
		throw InvalidInput();
	}
	if (root == NULL) {
		root = new AVLNode(element);
		treeSize++;
		return;
	} else {
		insert(root, element);
	}
}

template<typename T>
void AVLTree<T>::insert(AVLTree<T>::AVLNode* currentRoot, T& element) {
	if (!element) {
		throw InvalidInput();
	}
	if (currentRoot == NULL) {
		currentRoot = new AVLNode(element);
		treeSize++;
		return;
	}
	if (element > currentRoot->data) {
		insert(currentRoot->right, element);
	}
	if (element < currentRoot->data) {
		insert(currentRoot->left, element);
	}
	throw InputAlreadyExists();
}

//TODO complete this function!
//template <typename T>
//void AVLTree<T>::remove(T& element){

template<typename T>
bool AVLTree<T>::find(T element) const {
	if (root == NULL) {
		return false;
	}
	return find(root, element) ? true : false;
}

template<typename T>
typename AVLTree<T>::AVLNode* AVLTree<T>::find(AVLTree<T>::AVLNode* currentRoot,
		T element) const {
	if (currentRoot == NULL) {
		return NULL;
	}
	if (currentRoot->data == element) {
		return currentRoot;
	}
	if (currentRoot->data < element) {
		find(currentRoot->right, element);
	}
	find(currentRoot->left, element);
}

template<typename T>
inline int AVLTree<T>::size() const {
	return treeSize;
}

template<typename T>
void AVLTree<T>::rotateRight() {
	if (root == NULL) {
		//TODO throw exception
	}
	root = root->left;
	root->dad->left = root->right;
	root->right = root->dad;
	root->dad = NULL;
}

template<typename T>
void AVLTree<T>::rotateLeft() {
	if (root == NULL) {
		//TODO throw exception
	}
	root = root->right;
	root->dad->right = root->left;
	root->left = root->dad;
	root->dad = NULL;
}

template<typename T>
void AVLTree<T>::removeSingleChild(AVLTree<T>::AVLNode* currentRoot) {
	if (currentRoot->left != NULL && currentRoot->right == NULL) { //if current has only a left child
		if (currentRoot->dad->left->data == currentRoot->data) { //if current is it's dads' left child
			currentRoot->dad->left = currentRoot->left;
		} else {					//else-current is it's dads right child
			currentRoot->dad->right = currentRoot->left;
		}
	} else {					//else-current has only a right child (or no children at all)
		if (currentRoot->dad->left->data == currentRoot->data) {//if current is it's dads' left child
			currentRoot->dad->left = currentRoot->right;
		} else {					//else-current is it's dads right child
			currentRoot->dad->right = currentRoot->right;
		}
	}
}

template<typename T>
void AVLTree<T>::remove(AVLNode* currentRoot) {
	if (currentRoot == NULL) {
		//throw DataDoesNotExist();
		//TODO check if should throw or return without doing anything!
		return;
	}
	if (currentRoot->left == NULL && currentRoot->right == NULL) {//if current has no offsprings
		delete (currentRoot);
	}
	if ((currentRoot->left != NULL && currentRoot->right == NULL)
			|| (currentRoot->right != NULL && currentRoot->left == NULL)) {	//if current has only one child
		removeSingleChild(currentRoot);
	} else {								//current has both children
		AVLNode* successor = currentRoot->right;
		while (successor->left != NULL) {		//find the successor
			successor = successor->left;
		}
		currentRoot->data = successor->data;	//swap data
		removeSingleChild(successor);
	}
}

template<typename T>
void AVLTree<T>::remove(T& element){
	AVLNode* toRemove = find(root, element);
	remove(toRemove);
}


#endif /* AVL_TREE_H_ */
