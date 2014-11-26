#include "library1.h"
#include "operatingSystem.h"

// TODO: Add checks to DS

void* Init() {
	OS *os(new OS());
	return (void *) os;
}

StatusType AddVersion(void *DS, int versionCode) {
	return (static_cast<OS *>(DS))->addVersion(versionCode);
}

StatusType AddApplication(void *DS, int appID, int versionCode,
		int downloadCount) {
	return (static_cast<OS *>(DS))->addApplication(appID, versionCode,
			downloadCount);
}

StatusType RemoveApplication(void *DS, int appID) {
	return (static_cast<OS *>(DS))->removeApplication(appID);
}

StatusType IncreaseDownloads(void *DS, int appID, int downloadIncrease) {
	return (static_cast<OS *>(DS))->increaseDownloads(appID, downloadIncrease);
}

StatusType UpgradeApplication(void *DS, int appID) {
	return (static_cast<OS *>(DS))->upgradeApplication(appID);
}

StatusType GetTopApp(void *DS, int versionCode, int *appID) {
	return (static_cast<OS *>(DS))->getTopApp(versionCode, appID);
}

StatusType GetAllAppsByDownloads(void *DS, int versionCode, int **apps,
		int *numOfApps) {
	return (static_cast<OS *>(DS))->getAllAppsByDownloads(versionCode, apps,
			numOfApps);
}

void Quit(void** DS) {
	delete static_cast<OS *>(*DS);
}
