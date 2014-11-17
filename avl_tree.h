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


template<typename T>
class AVLTree {

	class AVLNode;
	AVLNode* root;
	int treeSize;
	//inserting a new object to the tree under a specific root
	void insert(AVLNode*, T&);
	//searching for an object in a specific sub tree
	T& find(AVLNode*, T) const;

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
	T& find(T) const;

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

template <typename T>
void AVLTree<T>::insert(T& element){
	if(!element){
			throw InvalidInput();
	}
	if(root == NULL){
		root = new AVLNode(element);
		treeSize++;
		return;
	}
	else{
		insert(root, element);
	}
}


template <typename T>
void AVLTree<T>::insert(AVLTree<T>::AVLNode* currentRoot, T& element){
	if(!element){
			throw InvalidInput();
		}
		if(currentRoot == NULL){
			currentRoot = new AVLNode(element);
			treeSize++;
			return;
		}
		if(element > currentRoot->data){
			insert(currentRoot->right, element);
		}
		if(element < currentRoot->data){
			insert(currentRoot->left, element);
		}
		throw InputAlreadyExists();
}

//TODO complete this function!
//template <typename T>
//void AVLTree<T>::remove(T& element){


template <typename T>
typename T& AVLTree<T>::find(T element) const{
	if(root == NULL){
		throw DataDoesNotExist();
	}
	return find(root, element);
}

template <typename T>
typename T& AVLTree<T>::find(AVLTree<T>::AVLNode* currentRoot, T element) const{
	if(currentRoot == NULL){
		throw DataDoesNotExist();
	}
	if(currentRoot->data == element){
		return currentRoot->data;
	}
	if(currentRoot->data < element){
		find(currentRoot->right, element);
	}
	find(currentRoot->left, element);
}

template <typename T>
inline int AVLTree<T>::size() const{
	return treeSize;
}

template <typename T>
void AVLTree<T>::rotateRight(){
	if(root == NULL){
		//TODO throw exception
	}
	root = root->left;
	root->dad->left = root->right;
	root->right = root->dad;
	root->dad = NULL;
}

template <typename T>
void AVLTree<T>::rotateLeft(){
	if(root == NULL){
		//TODO throw exception
	}
	root = root->right;
	root->dad->right = root->left;
	root->left = root->dad;
	root->dad = NULL;
}

#endif /* AVL_TREE_H_ */
