#include "../list.h"
#include "assert.h"
#include <string>

std::string location;

static const int NUMBER_OF_ELEMENTS(6);

static void setUp(List<int>& list) {
	list.pushBack(3);
	list.pushBack(3);
	list.pushBack(2);
	list.pushBack(3);
	list.pushBack(4);
	list.pushBack(5);
}

static bool testListCopyConstructor() {
	List<int> list, copy;
	setUp(list);

	copy = list;
	list[2] = 0;
	ASSERT_EQUALS(copy[2], 2);
	copy[3] = 0;
	ASSERT_EQUALS(list[3], 3);

	return true;
}

static bool testListPopBack() {
	List<int> list;

	ASSERT_LIST_IS_EMPTY(list.popBack());

	setUp(list);

	list.popBack();
	ASSERT_EQUALS(list.size(), NUMBER_OF_ELEMENTS - 1);
	ASSERT_EQUALS(list[0], 3);
	ASSERT_EQUALS(list[NUMBER_OF_ELEMENTS - 2], 4);

	list.reset();
	ASSERT_LIST_IS_EMPTY(list.popBack());

	return true;
}

static bool testListPushBack() {
	List<int> list;

	list.pushBack(2);
	ASSERT_EQUALS(list[0], 2);
	list.pushBack(3);
	ASSERT_EQUALS(list[0], 2);
	ASSERT_EQUALS(list[1], 3);

	return true;
}

static bool testListPopFront() {
	List<int> list;

	ASSERT_LIST_IS_EMPTY(list.popFront());

	setUp(list);

	list.popFront();
	ASSERT_EQUALS(list.size(), NUMBER_OF_ELEMENTS - 1);
	ASSERT_EQUALS(list[0], 3);
	ASSERT_EQUALS(list[NUMBER_OF_ELEMENTS - 2], 5);
	list.popFront();
	ASSERT_EQUALS(list[0], 2);

	list.reset();
	ASSERT_LIST_IS_EMPTY(list.popFront());

	return true;
}

static bool testListPushFront() {
	List<int> list;

	list.pushFront(2);
	ASSERT_EQUALS(list[0], 2);
	list.pushFront(3);
	ASSERT_EQUALS(list[1], 2);
	ASSERT_EQUALS(list[0], 3);

	return true;
}

static bool testListAt() {
	List<int> list;

	ASSERT_INDEX_OUT_OF_BOUNDS(list.at(0));
	ASSERT_NO_THROW(list[0]);

	setUp(list);

	ASSERT_EQUALS(list[3], 3);
	ASSERT_EQUALS(list.at(5), 5);
	ASSERT_INDEX_OUT_OF_BOUNDS(list.at(6));
	ASSERT_INDEX_OUT_OF_BOUNDS(list.at(-1));
	ASSERT_NO_THROW(list[6]);
	ASSERT_NO_THROW(list[-1]);

	return true;
}

static bool testListSize() {
	List<int> list;

	ASSERT_EQUALS(list.size(), 0);
	setUp(list);
	ASSERT_EQUALS(list.size(), NUMBER_OF_ELEMENTS);

	return true;
}

static bool testListReset() {
	List<int> list;

	ASSERT_NO_THROW(list.reset());
	ASSERT_EQUALS(list.size(), 0);
	setUp(list);
	ASSERT_NO_THROW(list.reset());
	ASSERT_EQUALS(list.size(), 0);

	return true;
}

static bool testListIterator() {
	List<int> list;

	// Checking empty list
	for (List<int>::Iterator it(list.begin()); it != list.end(); ++it)
		;

	// Checking the iterator's path
	int array[] = {3, 3, 2, 3, 4 ,5};
	setUp(list);
	int i(0);
	for (List<int>::Iterator it(list.begin()); it != list.end(); ++it, ++i) {
		ASSERT_EQUALS(*it, array[i]);
	}

	// Checking operators
	List<int>::Iterator it(list.begin());
	ASSERT_EQUALS(*(++it), list[1]);
	ASSERT_EQUALS(*(it++), list[1]);
	ASSERT_FALSE(*it == *list.end());
	it = list.begin();
	ASSERT_FALSE(*it != *list.begin());

	*it = 1;
	ASSERT_EQUALS(list[0], 1);

	return true;
}

int main() {
	RUN_TEST(testListCopyConstructor);
	RUN_TEST(testListPopBack);
	RUN_TEST(testListPushBack);
	RUN_TEST(testListPopFront);
	RUN_TEST(testListPushFront);
	RUN_TEST(testListAt);
	RUN_TEST(testListSize);
	RUN_TEST(testListReset);
	RUN_TEST(testListIterator);

	return 0;
}
