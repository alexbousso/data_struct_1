
#include "../application.h"
#include "assert.h"
#include <string>

std::string location;

static bool testGetApplicationID() {
	Application app(1, 2, 3);
	ASSERT_EQUALS(app.getAppID(), 1);

	return true;
}

static bool testGetVersionCode() {
	Application app(1, 2, 3);
	ASSERT_EQUALS(app.getVersionCode(), 2);

	return true;
}

static bool testGetDownloadCount() {
	Application app(1, 2, 3);
	ASSERT_EQUALS(app.getDownloadCount(), 3);

	return true;
}

static bool testIncreaseDownloads() {
	Application app(1, 2, 3);
	ASSERT_NO_THROW(app.increaseDownloads(1));
	ASSERT_EQUALS(app.getDownloadCount(), 3);
	ASSERT_INVALID_INPUT(app.increaseDownloads(0));
	ASSERT_INVALID_INPUT(app.increaseDownloads(-10));
	ASSERT_EQUALS(app.getDownloadCount(), 3);

	return true;
}

static bool testUpgradeApplication() {
	Application app(1, 2, 3);
	ASSERT_NO_THROW(app.upgradeApplication(5));
	ASSERT_EQUALS(app.getVersionCode(), 5);
	ASSERT_BAD_VERSION_CODE(app.upgradeApplication(2));
	ASSERT_EQUALS(app.getVersionCode(), 5);

	return true;
}

int main() {
	RUN_TEST(testGetApplicationID);
	RUN_TEST(testGetVersionCode);
	RUN_TEST(testGetDownloadCount);
	RUN_TEST(testIncreaseDownloads);
	RUN_TEST(testUpgradeApplication);

	return 0;
}
