#include "../operatingSystem.h"
#include "test_utils.h"
#include "../library1.h"
#include <string>

#define ASSERT_INVALID_INPUT(arg) ASSERT_EQUALS(arg, INVALID_INPUT)
#define ASSERT_FAILURE(arg) ASSERT_EQUALS(arg, FAILURE)
#define ASSERT_SUCCESS(arg) ASSERT_EQUALS(arg, SUCCESS)

std::string location;

static bool testAddVersion() {
	OS os;

	ASSERT_INVALID_INPUT(os.addVersion(0));
	ASSERT_INVALID_INPUT(os.addVersion(-10));

	ASSERT_SUCCESS(os.addVersion(5));
	ASSERT_FAILURE(os.addVersion(5));
	ASSERT_FAILURE(os.addVersion(3));
	ASSERT_SUCCESS(os.addVersion(8));

	return true;
}

static bool testAddApplication() {
	OS os;

	ASSERT_INVALID_INPUT(os.addApplication(0, 5, 10));
	ASSERT_INVALID_INPUT(os.addApplication(-1, 5, 10));
	ASSERT_INVALID_INPUT(os.addApplication(10, 0, 10));
	ASSERT_INVALID_INPUT(os.addApplication(10, -5, 10));
	ASSERT_INVALID_INPUT(os.addApplication(10, 5, -10));
	ASSERT_FAILURE(os.addApplication(10, 5, 10));

	ASSERT_SUCCESS(os.addVersion(5));
	ASSERT_INVALID_INPUT(os.addApplication(0, 5, 10));
	ASSERT_INVALID_INPUT(os.addApplication(-1, 5, 10));
	ASSERT_INVALID_INPUT(os.addApplication(10, 5, -10));

	ASSERT_SUCCESS(os.addApplication(10, 5, 10));

	ASSERT_FAILURE(os.addApplication(10, 6, 10));
	ASSERT_FAILURE(os.addApplication(10, 4, 10));

	ASSERT_SUCCESS(os.addApplication(15, 5, 20));
	ASSERT_SUCCESS(os.addApplication(2, 5, 10));

	ASSERT_SUCCESS(os.addVersion(8));
	ASSERT_SUCCESS(os.addApplication(4, 5, 0));
	ASSERT_FAILURE(os.addApplication(10, 8, 10));
	ASSERT_SUCCESS(os.addApplication(17, 8, 23));
	ASSERT_FAILURE(os.addApplication(17, 5, 1));

	return true;
}

static bool testRemoveApplication() {
	// TODO: Add tests

	return true;
}

static bool testIncreaseDownloads() {
	// TODO: Add tests

	return true;
}

static bool testUpgradeApplication() {
	// TODO: Add tests

	return true;
}

static bool testGetTopApp() {
	// TODO: Add tests

	return true;
}

static bool testGetAllAppsByDownloads() {
	// TODO: Add tests

	return true;
}

static bool testUpdateDownloads() {
	// TODO: Add tests

	return true;
}

int main() {
	RUN_TEST(testAddVersion);
	RUN_TEST(testAddApplication);
	RUN_TEST(testRemoveApplication);
	RUN_TEST(testIncreaseDownloads);
	RUN_TEST(testUpgradeApplication);
	RUN_TEST(testGetTopApp);
	RUN_TEST(testGetAllAppsByDownloads);
	RUN_TEST(testUpdateDownloads);

	return 0;
}
