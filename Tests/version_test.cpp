#include "../version.h"
#include "../application.h"
#include "assert.h"
#include <string>
#include <stdlib.h>

std::string location;

static bool testGetVersionCode() {
	Version ver(1);
	ASSERT_EQUALS(ver.getVersionCode(), 1);

	return true;
}

static bool testAddApp() {
	Version ver(1);
	Application goodApp1(100, 1, 10);
	Application goodApp2(20, 1, 0);
	Application badApp1(101, 2, 10);
	Application badApp2(100, 1, 20);

	ASSERT_NO_THROW(ver.addApp(goodApp1));
	ASSERT_NO_THROW(ver.addApp(goodApp2));
	ASSERT_BAD_VERSION_CODE(ver.addApp(badApp1));
	ASSERT_INPUT_ALREADY_EXISTS(ver.addApp(badApp2));

	return true;
}

static bool testRemoveApp() {
	Version ver(1);
	Application app1(100, 1, 10);
	Application app2(200, 1, 10);

	ASSERT_INVALID_INPUT(ver.removeApp(0));
	ASSERT_INVALID_INPUT(ver.removeApp(-100));

	ASSERT_DATA_DOES_NOT_EXIST(ver.removeApp(100));
	ASSERT_NO_THROW(ver.addApp(app1));
	ASSERT_DATA_DOES_NOT_EXIST(ver.removeApp(10));
	ASSERT_NO_THROW(ver.removeApp(100));
	ASSERT_DATA_DOES_NOT_EXIST(ver.removeApp(100));

	ASSERT_NO_THROW(ver.addApp(app1));
	ASSERT_NO_THROW(ver.addApp(app2));
	ASSERT_NO_THROW(ver.removeApp(100));
	ASSERT_DATA_DOES_NOT_EXIST(ver.removeApp(100));
	ASSERT_NO_THROW(ver.removeApp(200));

	return true;
}

static bool testIncreaseDownloads() {
	Version ver(1);
	Application app1(100, 1, 10);

	ASSERT_INVALID_INPUT(ver.increaseDownloads(0, 10));
	ASSERT_INVALID_INPUT(ver.increaseDownloads(100, 0));

	ASSERT_DATA_DOES_NOT_EXIST(ver.increaseDownloads(100, 10));

	ASSERT_NO_THROW(ver.addApp(app1));
	ASSERT_NO_THROW(ver.increaseDownloads(100, 10));
	ASSERT_NO_THROW(ver.increaseDownloads(100, 10));
	ASSERT_INPUT_ALREADY_EXISTS(ver.addApp(app1));

	return true;
}

//static bool operator ==(Application app1, Application app2) {
//	return app1.getAppID() == app2.getAppID()
//			&& app1.getDownloadCount() == app2.getDownloadCount()
//			&& app1.getVersionCode() == app2.getVersionCode();
//}

static bool testGetAllAppsByDownloads() {
	Version ver(1);
	Application app1(100, 1, 6);
	Application app2(200, 1, 12);
	Application app3(150, 1, 16);
	int numOfApps;

	ASSERT_EQUALS(ver.getAllAppsByDownloads(&numOfApps), NULL);
	ASSERT_EQUALS(numOfApps, 0);

	ASSERT_NO_THROW(ver.addApp(app1));
	ASSERT_NO_THROW(ver.addApp(app2));
	ASSERT_NO_THROW(ver.addApp(app3));
	Application* apps(ver.getAllAppsByDownloads(&numOfApps));
	ASSERT_EQUALS(numOfApps, 3);

	ASSERT_EQUALS(apps[0], app1);
	ASSERT_EQUALS(apps[1], app2);
	ASSERT_EQUALS(apps[2], app3);

	free(apps);
	return true;
}

int main() {
	RUN_TEST(testGetVersionCode);
	RUN_TEST(testAddApp);
	RUN_TEST(testRemoveApp);
	RUN_TEST(testIncreaseDownloads);
	RUN_TEST(testGetAllAppsByDownloads);

	return 0;
}
