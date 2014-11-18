
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

static bool testListPopBack() {
	List<int> list;

	ASSERT_LIST_IS_EMPTY(list.popBack());

	setUp(list);

	list.popBack();
	ASSERT_EQUALS(list.size(), NUMBER_OF_ELEMENTS - 1);
	ASSERT_EQUALS(list[0], 3);
	ASSERT_EQUALS(list[NUMBER_OF_ELEMENTS - 2], 4);

	while (list.size() > 0) {
		ASSERT_NO_THROW(list.popBack());
	}
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

	while (list.size() > 0) {
		ASSERT_NO_THROW(list.popFront());
	}
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
	// TODO: Add tests

	return true;
}

static bool testListReset() {
	// TODO: Add tests

	return true;
}

static bool testListIterator() {
	// TODO: Add tests

	return true;
}

int main() {
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
