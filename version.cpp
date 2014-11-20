#include "version.h"
#include "exceptions.h"
#include "list.h"

void Version::addApp(Application app) {
	// QUESTION: Can app be NULL?

	if (app.getVersionCode() != versionCode) {
		throw BadVersionCode();
	}

	apps.insert(app);
	downloads.insert(app);
}

void Version::removeApp(int appID) {
	Application app(findApplication(appID));

	apps.remove(app);
	downloads.remove(app);
}

void Version::increaseDownloads(int appID, int downloadIncrease) {
	if (downloadIncrease <= 0) {
		throw InvalidInput();
	}

	Application app(findApplication(appID));
	app.increaseDownloads(downloadIncrease);
}

class GetAllAppsByDownloads {
	List<Application> apps;

public:
	GetAllAppsByDownloads() :
			apps() {
	}
	void operator ()(Application app) {
		apps.pushBack(app);
	}
};

//Application* Version::getAllAppsByDownloads(int* numberOfApps) {
//	if (apps.size() == 0) {
//		numberOfApps = 0;
//		return NULL;
//	}
//	// TODO: Complete
//
//}

int Compare::operator ()(Application app1, Application app2) const {
	// QUESTION: Can app be NULL?

	if (type == FIRST_BY_DOWNLOAD_COUNT) {
		int downloadsDifference = app2.getDownloadCount()
				- app1.getDownloadCount();
		if (downloadsDifference != 0) {
			return downloadsDifference;
		}
	}
	return app1.getAppID() - app2.getAppID();
}

