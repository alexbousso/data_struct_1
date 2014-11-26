#include "../avl_tree.h"
#include "assert.h"
#include <string>

std::string location;

class CompareInt {
public:
	int operator ()(int a, int b) const {
		return a - b;
	}
};
/*
static const int NUMBER_OF_ELEMENTS(6);

static void setUp(AVLTree<int, CompareInt>& tree) {
	tree.insert(4);
	tree.insert(5);
	tree.insert(2);
	tree.insert(3);
	tree.insert(1);
	tree.insert(6);
}
*/
static bool testAVLTreeInsert() {

	CompareInt func;
	AVLTree<int, CompareInt> tree(func);

	ASSERT_NO_THROW(tree.insert(4));
	ASSERT_NO_THROW(tree.insert(5));
	ASSERT_NO_THROW(tree.insert(2));
	ASSERT_NO_THROW(tree.insert(3));

	ASSERT_INPUT_ALREADY_EXISTS(tree.insert(2));
	ASSERT_INPUT_ALREADY_EXISTS(tree.insert(4));

	ASSERT_NO_THROW(tree.remove(5));
	ASSERT_NO_THROW(tree.insert(5));
	ASSERT_INPUT_ALREADY_EXISTS(tree.insert(3));
	//tree.printTree();
	ASSERT_EQUALS(tree.size(), 4);

	ASSERT_NO_THROW(tree.insert(10));
	ASSERT_EQUALS(10, tree.getMax());

	ASSERT_NO_THROW(tree.remove(2));
	ASSERT_EQUALS(3, tree.getMin());
	ASSERT_NO_THROW(tree.insert(1));
	ASSERT_NO_THROW(tree.remove(3));

	ASSERT_NO_THROW(tree.insert(6));
	ASSERT_NO_THROW(tree.remove(10));
	ASSERT_EQUALS(true, tree.checkTree());
	tree.printTree();
	return true;
}
/*
static bool testAVLTreeRemove() {
	CompareInt func;
	AVLTree<int, CompareInt> tree(func);
	//FIXME what wrong with the line above

	ASSERT_DATA_DOES_NOT_EXIST(tree.remove(2));
	setUp(tree);

	ASSERT_NO_THROW(tree.remove(3));
	ASSERT_DATA_DOES_NOT_EXIST(tree.remove(3));

	ASSERT_DATA_DOES_NOT_EXIST(tree.remove(42));
	ASSERT_EQUALS(tree.size(), NUMBER_OF_ELEMENTS - 1);

	return true;
}

static bool testAVLTreeMin() {
	CompareInt func;
	AVLTree<int, CompareInt> tree(func);
	//FIXME what wrong with the line above

	setUp(tree);

	ASSERT_EQUALS(1, tree.getMin());
	ASSERT_NO_THROW(tree.remove(1));
	ASSERT_NO_THROW(tree.remove(2));
	ASSERT_EQUALS(3, tree.getMin());

	ASSERT_NO_THROW(tree.insert(2));
	ASSERT_EQUALS(2, tree.getMin());

	return true;
}

static bool testAVLTreeMax() {
	CompareInt func;
	AVLTree<int, CompareInt> tree(func);
	//FIXME what wrong with the line above

	setUp(tree);
	//tree.printTree();

	ASSERT_EQUALS(6, tree.getMax());
	ASSERT_NO_THROW(tree.remove(6));
	ASSERT_EQUALS(5, tree.getMax());

	ASSERT_NO_THROW(tree.insert(7));
	ASSERT_EQUALS(7, tree.getMax());
	//tree.printTree();
	ASSERT_NO_THROW(tree.checkTree());
	return true;
}
*/
/*
static bool testAVLTreeFind() {
	CompareInt func;
	AVLTree<int, CompareInt> tree(func);

	ASSERT_FALSE(tree.find(42));
	setUp(tree);

	ASSERT_TRUE(tree.find(3));
	ASSERT_TRUE(tree.find(2));

	ASSERT_FALSE(tree.find(42));
	ASSERT_NO_THROW(tree.remove(3));
	ASSERT_FALSE(tree.find(3));

	return true;
}
*//*
static bool testAVLTreeSize() {
	CompareInt func;
	AVLTree<int, CompareInt> tree(func);

	ASSERT_EQUALS(tree.size(), 0);
	setUp(tree);

	for (int i(NUMBER_OF_ELEMENTS); i > 2; --i) {
		//tree.printTree();
		ASSERT_EQUALS(tree.size(), i);
		ASSERT_NO_THROW(tree.remove(i));
	}

	ASSERT_NO_THROW(tree.insert(3));
	ASSERT_EQUALS(tree.size(), 3);
	tree.printTree();

	for (int i(3); i > 0; --i) {
		ASSERT_EQUALS(tree.size(), i);
		ASSERT_NO_THROW(tree.remove(i));
	}

	ASSERT_EQUALS(tree.size(), 0);

	return true;
}*/

int main() {
	RUN_TEST(testAVLTreeInsert);
	/*RUN_TEST(testAVLTreeRemove);
	RUN_TEST(testAVLTreeMin);
	RUN_TEST(testAVLTreeMax);*/
	//RUN_TEST(testAVLTreeFind);
	//RUN_TEST(testAVLTreeSize);

	return 0;
}
