#include "library1.h"
#include "operatingSystem.h"

// TODO: Add checks to DS

void* Init() {
	OS *os(new OS());
	return (void *) os;
}

StatusType AddVersion(void *DS, int versionCode) {
	return ((OS*)DS)->addVersion(versionCode);
}

StatusType AddApplication(void *DS, int appID, int versionCode,
		int downloadCount) {
	return ((OS*)DS)->addApplication(appID, versionCode, downloadCount);
}

StatusType RemoveApplication(void *DS, int appID) {
	return ((OS*)DS)->removeApplication(appID);
}

StatusType IncreaseDownloads(void *DS, int appID, int downloadIncrease) {
	return ((OS*)DS)->increaseDownloads(appID, downloadIncrease);
}

StatusType UpgradeApplication(void *DS, int appID) {
	return ((OS*)DS)->upgradeApplication(appID);
}

StatusType GetTopApp(void *DS, int versionCode, int *appID) {
	return ((OS*)DS)->getTopApp(versionCode, appID);
}

StatusType GetAllAppsByDownloads(void *DS, int versionCode, int **apps,
		int *numOfApps) {
	return ((OS*)DS)->getAllAppsByDownloads(versionCode, apps, numOfApps);
}

void Quit(void** DS) {
	delete *((OS*)DS);
}
