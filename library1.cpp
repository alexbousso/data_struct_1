#include "library1.h"
#include "operatingSystem.h"

void* Init() {
	OS *os(new OS());
	return (void *) os;
}

StatusType AddVersion(void *DS, int versionCode) {
	return DS->addVersion(versionCode);
}

StatusType AddApplication(void *DS, int appID, int versionCode,
		int downloadCount) {
	return DS->addApplicaation(appID, versionCode, downloadCount);
}

StatusType RemoveApplication(void *DS, int appID) {
	return DS->removeApplication(appID);
}

StatusType IncreaseDownloads(void *DS, int appID, int downloadIncrease) {
	return DS->increseDownloads(appID, downloadIncrease);
}

StatusType UpgradeApplication(void *DS, int appID) {
	return DS->upgradeApplication(appID);
}

StatusType GetTopApp(void *DS, int versionCode, int *appID) {
	return DS->getTopApp(versionCode, appID);
}

StatusType GetAllAppsByDownloads(void *DS, int versionCode, int **apps,
		int *numOfApps) {
	return getAllAppsByDownloads(versionCode, apps, numOfApps);
}

void Quit(void** DS) {
	delete *DS;
}
