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

	class AVLNode;
	AVLNode* root;
	int treeSize;
	//inserting a new object to the tree under a specific root
	void insert(AVLNode*, T&);

public:
	AVLTree() :
			root(NULL), treeSize(0) {
	}
	AVLTree(const AVLTree&);
	AVLTree operator=(const AVLTree&);
	~AVLTree();

	class Iterator {
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

	//inserting a new object to the tree
	void insert(T&);


	//removing an object from the tree
	void remove(T&);

	//finding a specific object in the tree
	template <typename T>
	Iterator find(T) const;

	//returning the current size of the tree
	int size() const;
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
		AVLNode(const Node&);
		AVLNode operator=(const Node&);
};


/******************************
 * Functions and Classes Implementation
 ******************************/

template <typename T>
void AVLTree<T>::insert(T& element){
	if(!element){
			//TODO: throw exception
	}
	if(root == NULL){
		root = new AVLNode(element);
		return;
	}
	else{
		insert(root, element);
	}
}


template <typename T>
void AVLTree<T>::insert(AVLTree<T>::AVLNode* currentRoot, T& element){
	if(!element){
			//TODO: throw exception
		}
		if(currentRoot == NULL){
			currentRoot = new AVLNode(element);
			return;
		}
		if(element > currentRoot->data){
			insert(currentRoot->right, element);
		}
		if(element < currentRoot->data){
			insert(currentRoot->left, element);
		}
		//TODO throw exception
}

//template <typename T>
//void AVLTree<T>::remove(T& element){

}


#endif /* AVL_TREE_H_ */
