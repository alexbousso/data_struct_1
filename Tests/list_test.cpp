
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

int main() {
	RUN_TEST(testListPopBack);
	RUN_TEST(testListPushBack);
	RUN_TEST(testListPopFront);

	return 0;
}
