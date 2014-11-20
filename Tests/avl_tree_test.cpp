#include "../avl_tree.h"
#include "assert.h"
#include <string>

std::string location;

class CompareInt {
	int a, b;

public:
	CompareInt(const int a, const int b) :
			a(a), b(b) {
	}
	int operator ()(int a, int b) {
		return a - b;
	}
};

static const int NUMBER_OF_ELEMENTS(6);

static void setUp(AVLTree<int, CompareInt>& tree) {
	tree.insert(4);
	tree.insert(5);
	tree.insert(2);
	tree.insert(3);
	tree.insert(1);
	tree.insert(7);
}

static bool testAVLTreeInsert() {
	AVLTree<int, CompareInt> tree;

	ASSERT_NO_THROW(tree.insert(4));
	ASSERT_NO_THROW(tree.insert(5));
	ASSERT_NO_THROW(tree.insert(2));
	ASSERT_NO_THROW(tree.insert(3));

	ASSERT_INPUT_ALREADY_EXISTS(tree.insert(2));
	ASSERT_INPUT_ALREADY_EXISTS(tree.insert(4));

	ASSERT_NO_THROW(tree.remove(5));
	ASSERT_NO_THROW(tree.insert(5));
	ASSERT_INPUT_ALREADY_EXISTS(tree.insert(3));
	ASSERT_EQUALS(tree.size(), 4);

	return true;
}

static bool testAVLTreeRemove() {
	AVLTree<int, CompareInt> tree;

	ASSERT_DATA_DOES_NOT_EXIST(tree.remove(2));
	setUp(tree);

	ASSERT_NO_THROW(tree.remove(3));
	ASSERT_DATA_DOES_NOT_EXIST(tree.remove(3));

	ASSERT_DATA_DOES_NOT_EXIST(tree.remove(42));
	ASSERT_EQUALS(tree.size(), NUMBER_OF_ELEMENTS - 1);

	return true;
}

static bool testAVLTreeFind() {
	AVLTree<int, CompareInt> tree;

	ASSERT_FALSE(tree.find(42));
	setUp(tree);

	ASSERT_TRUE(tree.find(3));
	ASSERT_TRUE(tree.find(2));

	ASSERT_FALSE(tree.find(42));
	ASSERT_NO_THROW(tree.remove(3));
	ASSERT_FALSE(tree.find(3));

	return true;
}

static bool testAVLTreeSize() {
	// TODO: Add tests

	return true;
}

int main() {
	RUN_TEST(testAVLTreeInsert);
	RUN_TEST(testAVLTreeRemove);
	RUN_TEST(testAVLTreeFind);
	RUN_TEST(testAVLTreeSize);

	return 0;
}
