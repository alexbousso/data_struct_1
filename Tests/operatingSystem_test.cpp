#include "../operatingSystem.h"
#include "test_utils.h"
#include "../library1.h"
#include <string>
#include <stdlib.h>

#define ASSERT_INVALID_INPUT(arg) ASSERT_EQUALS(arg, INVALID_INPUT)
#define ASSERT_FAILURE(arg) ASSERT_EQUALS(arg, FAILURE)
#define ASSERT_SUCCESS(arg) ASSERT_EQUALS(arg, SUCCESS)

std::string location;

static const int NUMBER_OF_APPS(12);

static void setUp(OS& os) {
	os.addVersion(2);
	os.addVersion(5);
	os.addVersion(8);

	os.addApplication(14, 8, 1);
	os.addApplication(10, 2, 10);
	os.addApplication(11, 2, 0);
	os.addApplication(1, 5, 15);
	os.addApplication(110, 2, 210);
	os.addApplication(2, 8, 4);
	os.addApplication(3, 2, 109);
	os.addApplication(30, 5, 42);
	os.addApplication(33, 5, 42);
	os.addApplication(31, 5, 42);
	os.addApplication(32, 5, 42);
	os.addApplication(15, 2, 10);
}

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
	OS os;

	ASSERT_INVALID_INPUT(os.removeApplication(0));
	ASSERT_INVALID_INPUT(os.removeApplication(-10));

	ASSERT_FAILURE(os.removeApplication(10));

	setUp(os);
/*
	ASSERT_INVALID_INPUT(os.removeApplication(0));

	ASSERT_FAILURE(os.removeApplication(18));
	ASSERT_SUCCESS(os.removeApplication(10));
	ASSERT_FAILURE(os.removeApplication(10));
	ASSERT_SUCCESS(os.addApplication(10, 5, 3));

	ASSERT_SUCCESS(os.removeApplication(110));
	ASSERT_SUCCESS(os.removeApplication(2));
	ASSERT_SUCCESS(os.removeApplication(31));
	ASSERT_SUCCESS(os.removeApplication(30));
	ASSERT_SUCCESS(os.removeApplication(14));

	ASSERT_SUCCESS(os.addApplication(2, 8, 3));
*/
	return true;
}

static bool testIncreaseDownloads() {
	OS os;

	ASSERT_INVALID_INPUT(os.increaseDownloads(0, 10));
	ASSERT_INVALID_INPUT(os.increaseDownloads(-1, 10));
	ASSERT_INVALID_INPUT(os.increaseDownloads(5, 0));
	ASSERT_INVALID_INPUT(os.increaseDownloads(3, -1));
	ASSERT_FAILURE(os.increaseDownloads(1, 10));

	setUp(os);

	ASSERT_INVALID_INPUT(os.increaseDownloads(0, 10));
	ASSERT_INVALID_INPUT(os.increaseDownloads(-1, 10));
	ASSERT_INVALID_INPUT(os.increaseDownloads(2, 0));
	ASSERT_INVALID_INPUT(os.increaseDownloads(2, -1));

	ASSERT_FAILURE(os.increaseDownloads(29, 1));
	ASSERT_SUCCESS(os.increaseDownloads(110, 1000));

	return true;
}

static bool testUpgradeApplication() {
	OS os;

	ASSERT_INVALID_INPUT(os.upgradeApplication(0));
	ASSERT_INVALID_INPUT(os.upgradeApplication(-1));

	setUp(os);

	ASSERT_FAILURE(os.upgradeApplication(14));
	ASSERT_FAILURE(os.upgradeApplication(29));
	ASSERT_SUCCESS(os.upgradeApplication(30));

	ASSERT_SUCCESS(os.addVersion(10));
	ASSERT_SUCCESS(os.upgradeApplication(14));

	return true;
}

static bool testGetTopApp() {
	OS os;
	int appID;

	ASSERT_INVALID_INPUT(os.getTopApp(10, NULL));
	ASSERT_INVALID_INPUT(os.getTopApp(0, &appID));
	// QUESTION: We need to do this?
//	ASSERT_EQUALS(appID, -1);

	ASSERT_FAILURE(os.getTopApp(2, &appID));
	// QUESTION: We need to do this?
//	ASSERT_EQUALS(appID, -1);
	// QUESTION: The return value shall be success or failure?
	ASSERT_SUCCESS(os.getTopApp(-25, &appID));
	// QUESTION: We need to do this?
	ASSERT_EQUALS(appID, -1);

	ASSERT_SUCCESS(os.addVersion(1));
	// QUESTION: The return value shall be success or failure?
	ASSERT_SUCCESS(os.getTopApp(1, &appID));
	ASSERT_EQUALS(appID, -1);
	// QUESTION: The return value shall be success or failure?
	ASSERT_SUCCESS(os.getTopApp(-1, &appID));
	ASSERT_EQUALS(appID, -1);

	ASSERT_SUCCESS(os.addApplication(1, 1, 1));
	ASSERT_SUCCESS(os.getTopApp(1, &appID));
	ASSERT_EQUALS(appID, 1);
	ASSERT_SUCCESS(os.removeApplication(1));
	// QUESTION: The return value shall be success or failure?
	ASSERT_SUCCESS(os.getTopApp(1, &appID));
	ASSERT_EQUALS(appID, -1);

	setUp(os);

	ASSERT_SUCCESS(os.getTopApp(-1, &appID));
	ASSERT_EQUALS(appID, 110);

	ASSERT_FAILURE(os.getTopApp(3, &appID));
	// QUESTION: We need to do this?
//	ASSERT_EQUALS(appID, -1);

	ASSERT_SUCCESS(os.getTopApp(8, &appID));
	ASSERT_EQUALS(appID, 2);

	ASSERT_SUCCESS(os.getTopApp(5, &appID));
	ASSERT_EQUALS(appID, 30);

	ASSERT_SUCCESS(os.increaseDownloads(11, 1000));
	ASSERT_SUCCESS(os.getTopApp(2, &appID));
	ASSERT_EQUALS(appID, 11);

	ASSERT_SUCCESS(os.removeApplication(31));
	ASSERT_SUCCESS(os.addApplication(31, 5, 100));
	ASSERT_SUCCESS(os.getTopApp(5, &appID));
	ASSERT_EQUALS(appID, 31);
	ASSERT_SUCCESS(os.removeApplication(31));
	ASSERT_SUCCESS(os.getTopApp(5, &appID));
	ASSERT_EQUALS(appID, 30);

	ASSERT_SUCCESS(os.upgradeApplication(110));
	ASSERT_SUCCESS(os.getTopApp(5, &appID));
	ASSERT_EQUALS(appID, 110);

	ASSERT_SUCCESS(os.getTopApp(-57, &appID));
	ASSERT_EQUALS(appID, 11);

	return true;
}

static bool testGetAllAppsByDownloads() {
	OS os;
	int *apps, numOfApps;

	ASSERT_INVALID_INPUT(os.getAllAppsByDownloads(0, &apps, &numOfApps));
	// QUESTION: We need to do this?
	ASSERT_EQUALS(numOfApps, -1);
	ASSERT_EQUALS(apps, NULL);
	ASSERT_INVALID_INPUT(os.getAllAppsByDownloads(5, NULL, &numOfApps));
	// QUESTION: We need to do this?
	ASSERT_EQUALS(numOfApps, -1);
	ASSERT_INVALID_INPUT(os.getAllAppsByDownloads(5, &apps, NULL));
	// QUESTION: We need to do this?
	ASSERT_EQUALS(apps, NULL);

	ASSERT_FAILURE(os.getAllAppsByDownloads(1, &apps, &numOfApps));
	// QUESTION: We need to do this?
	ASSERT_EQUALS(numOfApps, -1);
	ASSERT_EQUALS(apps, NULL);

	ASSERT_SUCCESS(os.addVersion(1));
	ASSERT_SUCCESS(os.getAllAppsByDownloads(1, &apps, &numOfApps));
	// QUESTION: Are those right?
	ASSERT_EQUALS(numOfApps, 0);
	ASSERT_EQUALS(apps, NULL);

	setUp(os);

	ASSERT_SUCCESS(os.getAllAppsByDownloads(-12, &apps, &numOfApps));
	ASSERT_EQUALS(numOfApps, NUMBER_OF_APPS);
	ASSERT_EQUALS(apps[0], 110);
	ASSERT_EQUALS(apps[NUMBER_OF_APPS - 1], 11);
	ASSERT_EQUALS(apps[3], 31);
	free(apps);

	ASSERT_SUCCESS(os.getAllAppsByDownloads(8, &apps, &numOfApps));
	ASSERT_EQUALS(apps[0], 2);
	ASSERT_EQUALS(apps[1], 14);
	ASSERT_EQUALS(numOfApps, 2);
	free(apps);

	ASSERT_SUCCESS(os.getAllAppsByDownloads(5, &apps, &numOfApps));
	ASSERT_EQUALS(apps[0], 30);
	ASSERT_EQUALS(apps[2], 32);
	ASSERT_EQUALS(apps[4], 1);
	ASSERT_EQUALS(numOfApps, 5);
	free(apps);

	ASSERT_SUCCESS(os.upgradeApplication(31));
	ASSERT_SUCCESS(os.getAllAppsByDownloads(5, &apps, &numOfApps));
	ASSERT_EQUALS(apps[0], 30);
	ASSERT_EQUALS(apps[1], 32);
	ASSERT_EQUALS(apps[3], 1);
	ASSERT_EQUALS(numOfApps, 4);
	free(apps);

	ASSERT_SUCCESS(os.increaseDownloads(32, 100));
	ASSERT_SUCCESS(os.getAllAppsByDownloads(5, &apps, &numOfApps));
	ASSERT_EQUALS(apps[0], 32);
	ASSERT_EQUALS(apps[1], 30);
	ASSERT_EQUALS(apps[3], 1);
	ASSERT_EQUALS(numOfApps, 4);
	free(apps);

	ASSERT_SUCCESS(os.increaseDownloads(11, 10));
	ASSERT_SUCCESS(os.increaseDownloads(14, 3));
	ASSERT_SUCCESS(os.getAllAppsByDownloads(-1, &apps, &numOfApps));
	ASSERT_EQUALS(numOfApps, NUMBER_OF_APPS);
	ASSERT_EQUALS(apps[1], 32);
	ASSERT_EQUALS(apps[NUMBER_OF_APPS - 1], 14);
	free(apps);

	return true;
}

static bool testUpdateDownloads() {
	OS os;
	int *apps, numOfApps;

	ASSERT_INVALID_INPUT(os.updateDownloads(0, 3));
	ASSERT_INVALID_INPUT(os.updateDownloads(-2, 2));
	ASSERT_INVALID_INPUT(os.updateDownloads(3, 0));

	ASSERT_SUCCESS(os.updateDownloads(2, 2));

	setUp(os);

	ASSERT_SUCCESS(os.updateDownloads(11, 3));
	ASSERT_SUCCESS(os.getAllAppsByDownloads(-1, &apps, &numOfApps));
	ASSERT_EQUALS(apps[0], 110);
	ASSERT_EQUALS(apps[1], 33);
	ASSERT_EQUALS(apps[NUMBER_OF_APPS - 1], 11);
	free(apps);

	ASSERT_SUCCESS(os.updateDownloads(10, 10));
	ASSERT_SUCCESS(os.getAllAppsByDownloads(-1, &apps, &numOfApps));
	ASSERT_EQUALS(apps[0], 110);
	ASSERT_EQUALS(apps[1], 30);
	ASSERT_EQUALS(apps[4], 10);
	ASSERT_EQUALS(apps[NUMBER_OF_APPS - 1], 11);
	free(apps);

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
