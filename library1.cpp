#include "library1.h"
#include "operatingSystem.h"

#define CHECK_NULL(arg) if (!(arg)) return INVALID_INPUT

void* Init() {
	try {
		OS *os(new OS());
		return (void *) os;
	} catch (std::bad_alloc& e) {
		return NULL;
	}
}

StatusType AddVersion(void *DS, int versionCode) {
	CHECK_NULL(DS);
	return (static_cast<OS *>(DS))->addVersion(versionCode);
}

StatusType AddApplication(void *DS, int appID, int versionCode,
		int downloadCount) {
	CHECK_NULL(DS);
	return (static_cast<OS *>(DS))->addApplication(appID, versionCode,
			downloadCount);
}

StatusType RemoveApplication(void *DS, int appID) {
	CHECK_NULL(DS);
	return (static_cast<OS *>(DS))->removeApplication(appID);
}

StatusType IncreaseDownloads(void *DS, int appID, int downloadIncrease) {
	CHECK_NULL(DS);
	return (static_cast<OS *>(DS))->increaseDownloads(appID, downloadIncrease);
}

StatusType UpgradeApplication(void *DS, int appID) {
	CHECK_NULL(DS);
	return (static_cast<OS *>(DS))->upgradeApplication(appID);
}

StatusType GetTopApp(void *DS, int versionCode, int *appID) {
	if (!DS) {
		*appID = -1;
		return INVALID_INPUT;
	}
	return (static_cast<OS *>(DS))->getTopApp(versionCode, appID);
}

StatusType GetAllAppsByDownloads(void *DS, int versionCode, int **apps,
		int *numOfApps) {
	if (!DS) {
		*numOfApps = -1;
		apps = NULL;
		return INVALID_INPUT;
	}
	return (static_cast<OS *>(DS))->getAllAppsByDownloads(versionCode, apps,
			numOfApps);
}

StatusType UpdateDownloads(void *DS, int groupBase, int multiplyFactor) {
	CHECK_NULL(DS);
	return (static_cast<OS *>(DS))->updateDownloads(groupBase, multiplyFactor);
}

void Quit(void** DS) {
	if (!DS) {
		return;
	}
	delete static_cast<OS *>(*DS);
	*DS = NULL;
}
