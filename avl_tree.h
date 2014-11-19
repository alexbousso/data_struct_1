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
	void rotateRight(AVLNode*);

	//rotating left
	void rotateLeft(AVLNode*);

	//rotating RL
	void rotateRL(AVLNode*);

	//rotating LR
	void rotateLR(AVLNode*);

	//updating all the heights in a subtree
	void updateHight(AVLNode*, AVLNode*, int);

	//Recursively update balance factor from a specific start point
	void updateBF(AVLNode*, AVLNode*);
};

template<typename T>
class AVLTree<T>::AVLNode {
	T data;
	AVLNode* left;
	AVLNode* right;
	AVLNode* dad;
	int hight;
	int bf;
	friend class AVLTree;
	friend class Iterator;

	AVLNode(T data) :
			data(data), left(NULL), right(NULL), dad(NULL), hight(0), bf(0) {
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
	//TODO is the next code block required?! been taken care of in the casic unsert func!
	/*if (currentRoot == NULL) {
		currentRoot = new AVLNode(element);
		treeSize++;
		return;
	}*/
	if (element > currentRoot->data) {		//if the data is larger then the roots'
		if(currentRoot->right == NULL){		//check if the right son is free
			currentRoot->right = new AVLNode(element); 		//if it is, then set the right son to be the new node
			currentRoot->right->dad = currentRoot;
			int hightDiff = currentRoot->hight >= 1 ? 0 : 1;
			updateHight(currentRoot, root, hightDiff);
			treeSize++;
			return;
		}
		insert(currentRoot->right, element);	//if it isn't, look for a space in the right subtree
	}
	if (element < currentRoot->data) {			//if the data is smaller then the roots'
		if(currentRoot->left == NULL){		//check if the left son is free
			currentRoot->left = new AVLNode(element); 		//if it is, then set the left son to be the new node
			currentRoot->left->dad = currentRoot;
			int hightDiff = currentRoot->hight >= 1 ? 0 : 1;
			updateHight(currentRoot, root, hightDiff);
			treeSize++;
			return;
		}
		insert(currentRoot->left, element);		//if it isn't, look for a space in the left subtree
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
void AVLTree<T>::rotateRight(AVLTree<T>::AVLNode* currentRoot) {
	if (currentRoot == NULL) {
		//TODO throw exception
	}
	currentRoot = currentRoot->left;
	currentRoot->dad->left = currentRoot->right;
	currentRoot->right = currentRoot->dad;
	currentRoot->dad = NULL;
}

template<typename T>
void AVLTree<T>::rotateLeft(AVLTree<T>::AVLNode* currentRoot) {
	if (currentRoot == NULL) {
		//TODO throw exception
	}
	currentRoot = currentRoot->right;
	currentRoot->dad->right = currentRoot->left;
	currentRoot->left = currentRoot->dad;
	currentRoot->dad = NULL;
}

template <typename T>
void AVLTree<T>::rotateRL(AVLNode* currentRoot){
	rotateRight(currentRoot->right);
	rotateLeft(currentRoot);
}

template <typename T>
void AVLTree<T>::rotateLR(AVLNode* currentRoot){
	rotateRight(currentRoot->left);
	rotateLeft(currentRoot);
}


template <typename T>
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
void AVLTree<T>::remove(AVLTree<T>::AVLNode* currentRoot) {
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

template<typename T>
void AVLTree<T>::updateHight(AVLTree<T>::AVLNode* start, AVLTree<T>::AVLNode* end, int diff){
	if(start == end){
		end->hight += diff;
		return;
	}
	start->hight += diff;
	start = start->dad;
}

template<typename T>
void AVLTree<T>::updateBF(AVLTree<T>::AVLNode* start, AVLTree<T>::AVLNode* end){

	//TODO stop condition!!!!!!!

	int hL = -1, hR = -1;
	if(start->left != NULL){
		hL = start->left->hight;
	}
	if(start->right != NULL){
		hL = start->right->hight;
	}
	int bf = hL - hR;
	if (bf >= -1 && bf <= 1){		//if the balance
		updateBF(start->dad, end);
	}
	if(bf < -1){
		//
	}
}

#endif /* AVL_TREE_H_ */
