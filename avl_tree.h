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
/*
 #define LARGER 1
 #define SMALLER -1
 #define EQUAL 0
 */

template<typename T, class Compare>
class AVLTree {

	class AVLNode;
	AVLNode* root;
	int treeSize;
	Compare compare;

	//inserting a new object to the tree under a specific root
	void insert(AVLNode*, const T&);

	//searching for an object in a specific sub tree
	AVLNode* find(AVLNode*, const T&) const;

	//removing an object from a specific subtree
	void remove(AVLNode*);

	//in case of removing a node with a single child' use this function
	void removeSingleChild(AVLNode*);

	//calculates the bf of a single node
	int calcBF(AVLNode*);

	//updates the BF after removing an item from the tree
	void updateBFAfterRemove(AVLNode*);

public:
	AVLTree(Compare func) :
			root(NULL), treeSize(0), compare(func) {
	}
	AVLTree(const AVLTree&);
	AVLTree operator=(const AVLTree&);
	~AVLTree();

	//inserting a new object to the tree
	void insert(const T&);

	//removing an object from the tree
	void remove(const T&);

	//finding a specific object in the tree
	bool find(const T&) const;

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
	void updateHight(AVLNode*, AVLNode*);

	//finding the next node with bad BF
	AVLNode* findBadBF(AVLNode*);

	//update balance factor of the first broken node from a specific start point
	AVLNode* updateBF(AVLNode*);
};

template<typename T, class Compare>
class AVLTree<T, Compare>::AVLNode {
	T data;
	AVLNode* left;
	AVLNode* right;
	AVLNode* dad;
	int hight;
	friend class AVLTree;
	friend class Iterator;

	AVLNode(T data) :
			data(data), left(NULL), right(NULL), dad(NULL), hight(0) {
	}
	AVLNode(const AVLNode&);
	AVLNode operator=(const AVLNode&);
};

/******************************
 * Functions and Classes Implementation
 ******************************/

template<typename T, class Compare>
void AVLTree<T, Compare>::insert(const T& element) {
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

template<typename T, class Compare>
void AVLTree<T, Compare>::insert(AVLTree<T, Compare>::AVLNode* currentRoot,
		const T& element) {
	if (!element) {
		throw InvalidInput();
	}

	//TODO is the next code block required?! been taken care of in the casic unsert func!
	/*if (currentRoot == NULL) {
	 currentRoot = new AVLNode(element);
	 treeSize++;
	 return;
	 }*/

	if (compare(element > currentRoot->data) > 0) {	//if the data is larger then the roots'
		if (currentRoot->right == NULL) {		//check if the right son is free
			currentRoot->right = new AVLNode(element); //if it is, then set the right son to be the new node
			currentRoot->right->dad = currentRoot;
			treeSize++;
			updateHight(currentRoot, root);
			updateBF(currentRoot);
			updateHight(currentRoot, root);	//after the rolls, update heights again
			return;
		}
		insert(currentRoot->right, element);//if it isn't, look for a space in the right subtree
	}
	if (compare(element, currentRoot->data) < 0) {//if the data is smaller then the roots'
		if (currentRoot->left == NULL) {		//check if the left son is free
			currentRoot->left = new AVLNode(element); //if it is, then set the left son to be the new node
			currentRoot->left->dad = currentRoot;
			treeSize++;
			updateHight(currentRoot, root);
			updateBF(currentRoot);
			updateHight(currentRoot, root);	//after the rolls, update heights again
			return;
		}
		insert(currentRoot->left, element);	//if it isn't, look for a space in the left subtree
	}
	throw InputAlreadyExists();
}

template<typename T, class Compare>
bool AVLTree<T, Compare>::find(const T& element) const {
	if (root == NULL) {
		return false;
	}
	return find(root, element) ? true : false;
}

template<typename T, class Compare>
typename AVLTree<T, Compare>::AVLNode* AVLTree<T, Compare>::find(
		AVLTree<T, Compare>::AVLNode* currentRoot, const T& element) const {
	if (currentRoot == NULL) {
		return NULL;
	}
	if (compare(currentRoot->data, element) == 0) { //if it's the same object
		return currentRoot;
	}
	if (compare(currentRoot->data, element) < 0) { //if the current is smaller, go to the right subtree
		find(currentRoot->right, element);
	}
	find(currentRoot->left, element); //else: the current is larger-search the left subtree
}

template<typename T, class Compare>
inline int AVLTree<T, Compare>::size() const {
	return treeSize;
}

template<typename T, class Compare>
void AVLTree<T, Compare>::rotateRight(
		AVLTree<T, Compare>::AVLNode* currentRoot) {
	if (currentRoot == NULL) {
		//TODO throw exception
	}
	currentRoot = currentRoot->left;
	currentRoot->dad->left = currentRoot->right;
	currentRoot->right = currentRoot->dad;
	currentRoot->dad = NULL;
}

template<typename T, class Compare>
void AVLTree<T, Compare>::rotateLeft(
		AVLTree<T, Compare>::AVLNode* currentRoot) {
	if (currentRoot == NULL) {
		//TODO throw exception
	}
	currentRoot = currentRoot->right;
	currentRoot->dad->right = currentRoot->left;
	currentRoot->left = currentRoot->dad;
	currentRoot->dad = NULL;
}

template<typename T, class Compare>
void AVLTree<T, Compare>::rotateRL(AVLTree<T, Compare>::AVLNode* currentRoot) {
	rotateRight(currentRoot->right);
	rotateLeft(currentRoot);
}

template<typename T, class Compare>
void AVLTree<T, Compare>::rotateLR(AVLTree<T, Compare>::AVLNode* currentRoot) {
	rotateRight(currentRoot->left);
	rotateLeft(currentRoot);
}

template<typename T, class Compare>
void AVLTree<T, Compare>::removeSingleChild(
		AVLTree<T, Compare>::AVLNode* currentRoot) {
	if (currentRoot->left != NULL && currentRoot->right == NULL) { //if current has only a left child
		if (compare(currentRoot->dad->left->data, currentRoot->data) == 0) { //if current is it's dads' left child
			currentRoot->dad->left = currentRoot->left;		//
			currentRoot->left->dad = currentRoot->dad;
		} else {					//else-current is it's dads right child
			currentRoot->dad->right = currentRoot->left;
			currentRoot->right->dad = currentRoot->dad;
		}
	} else {	//else-current has only a right child (or no children at all)
		if (compare(currentRoot->dad->left->data, currentRoot->data) == 0) {//if current is it's dads' left child
			currentRoot->dad->left = currentRoot->right;
			currentRoot->right->dad = currentRoot->dad;
		} else {					//else-current is it's dads right child
			currentRoot->dad->right = currentRoot->right;
			currentRoot->right->dad = currentRoot->dad;
		}
	}
	updateBFAfterRemove(currentRoot->dad);
	delete(currentRoot);
}

template<typename T, class Compare>
void AVLTree<T, Compare>::remove(AVLTree<T, Compare>::AVLNode* currentRoot) {
	if (currentRoot == NULL) {
		throw DataDoesNotExist();
	}

	if (currentRoot->left == NULL && currentRoot->right == NULL) {//if current has no offsprings
		AVLNode* tempDad = currentRoot->dad;
		if (tempDad->right == currentRoot){		//if current is it's dads right son.
			tempDad->right = NULL;
		}
		else{		//current is it's dads left son
			assert(tempDad->left == currentRoot);

			tempDad->left = NULL;
		}
		delete (currentRoot);
		updateHight(tempDad, root);
		updateBFAfterRemove(tempDad);
		return;
	}
	if ((currentRoot->left != NULL && currentRoot->right == NULL)
			|| (currentRoot->right != NULL && currentRoot->left == NULL)) {	//if current has only one child

		removeSingleChild(currentRoot);

	} else {								//current has both children

		assert(currentRoot->left != NULL && currentRoot->right != NULL);

		AVLNode* successor = currentRoot->right;
		while (successor->left != NULL) {		//find the successor
			successor = successor->left;
		}
		currentRoot->data = successor->data;	//swap data
		removeSingleChild(successor);
	}
}

template<typename T, class Compare>
void AVLTree<T, Compare>::remove(const T& element) {
	AVLNode* toRemove = find(root, element);
	remove(toRemove);
}

template<typename T, class Compare>
void AVLTree<T, Compare>::updateHight(AVLTree<T, Compare>::AVLNode* start,
		AVLTree<T, Compare>::AVLNode* end) {
	int lH = start->left == NULL ? -1 : start->left->hight, rH =//calc the subtrees heights
			start->right == NULL ? -1 : start->left->hight;

	if (start == end) {						//if we are at the root/stop point
		end->hight = 1 + (lH > rH ? lH : rH);
		return;
	}
	start->hight = 1 + (lH > rH ? lH : rH);	//take the max between both subs and add 1
	updateHight(start = start->dad, end);		//update the rest of the tree
}

template<typename T, class Compare>
AVLTree<T, Compare>::AVLNode* AVLTree<T, Compare>::updateBF(AVLTree<T, Compare>::AVLNode* start) {

	AVLNode* toFix = findBadBF(start);
	if (toFix == NULL) {
		return NULL;
	}

	int bf = calcBF(toFix);				//calc the BF
	if (bf > 1) {					//if the left side is heavier
		if (calcBF(toFix->left) > 0) {//if in the left subtree-the left side is heavier
			assert(bf >= 2);
			rotateLeft(toFix);
		}
		if (calcBF(toFix->left) < 0) {//if in the left subtree-the right side is heavier
			assert(bf >= 2);
			rotateLR(toFix);
		}
	}
	if (bf < -1) {						//if the right subtree is heavier
		if (calcBF(toFix->right) < 0) {	//if in the right subtree- the right side  is heavier
			assert(bf <= -2);
			rotateRight(toFix);
		}
		if (calcBF(toFix->right) > 0) {	//if in the right subtree- the left side  is heavier
			assert(bf <= -2);
			rotateRL(toFix);
		}
	}
	updateHight(toFix, root);			//fix the heights after the rolls
	return toFix;
}

template<typename T, class Compare>
AVLTree<T, Compare>::AVLNode* AVLTree<T, Compare>::findBadBF(
		AVLTree<T, Compare>::AVLNode* currentRoot) {

	int bf = calcBF(currentRoot);		//calc the BF

	if (compare(currentRoot->data, root->data) == 0) { //if you are the root
		if (bf < -1 || bf > 1) {			//check if the roots BF is broken
			return currentRoot;		//if it is, send the root as the node to fix
		}
		return NULL;		//else-there are no more nodes to fix-return null.
	}
	if (bf < -1 || bf > 1) {
		return currentRoot;
	}
	assert(bf >= -1 && bf <= 1);
	findBadBF(currentRoot->dad);

}

template<typename T, class Compare>
int AVLTree<T, Compare>::calcBF(AVLTree<T, Compare>::AVLNode* node) {
	if (node == NULL) {
		throw InvalidInput();
	}
	int leftH = node->left == NULL ? -1 : node->left->hight, rightH =
			node->right == NULL ? -1 : node->right->hignt;
	return leftH - rightH;
}


template<typename T, class Compare>
void AVLTree<T, Compare>::updateBFAfterRemove(AVLTree<T, Compare>::AVLNode* currentRoot){
	while (currentRoot != NULL){
		currentRoot = updateBF(currentRoot); //the new root will be the node that was recently fixed
	}
}



#endif /* AVL_TREE_H_ */
