
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
	setUp(list);

	list.popBack();
	ASSERT_EQUALS(list.size(), NUMBER_OF_ELEMENTS - 1);
	ASSERT_EQUALS(list[0], 3);
	ASSERT_EQUALS(list[NUMBER_OF_ELEMENTS - 1], 4);

	return true;
}

int main() {
	RUN_TEST(testListPopBack);

	return 0;
}
