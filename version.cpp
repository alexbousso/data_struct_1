#include "version.h"
#include "exceptions.h"
#include "list.h"
#include <stdlib.h>

void Version::addApp(Application app) {
	if (app.getVersionCode() != versionCode) {
		throw BadVersionCode();
	}

	apps.insert(app);
	downloads.insert(app);
}

void Version::removeApp(int appID) {
	if (appID <= 0) {
		throw InvalidInput();
	}

	Application app(findApplication(appID));

	apps.remove(app);
	downloads.remove(app);
}

int Version::getTopApp(){
	return downloads.getMax().getAppID();
}

void Version::increaseDownloads(int appID, int downloadIncrease) {
	if (downloadIncrease <= 0 || appID <= 0) {
		throw InvalidInput();
	}

	Application app(findApplication(appID));
	app.increaseDownloads(downloadIncrease);
}

/**
 * Class that functions as a function object. It is used for explore the tree
 * and copy every application on it to a list defined in the class.
 */
class GetAllAppsByDownloads {
public:
	GetAllAppsByDownloads() :
			apps() {
	}
	void copyAppsToArray(Application** array) {
		int i(0);
		for (List<Application>::Iterator it(apps.begin()); it != apps.end();
				++it, ++i) {
			(*array)[i] = *it;
		}
	}
	void operator ()(Application app) {
		apps.pushBack(app);
	}

private:
	List<Application> apps;
};

int Compare::operator ()(Application app1, Application app2) const {
	if (type == FIRST_BY_DOWNLOAD_COUNT) {
		int downloadsDifference = app2.getDownloadCount()
				- app1.getDownloadCount();
		if (downloadsDifference != 0) {
			return downloadsDifference;
		}
	}
	return app1.getAppID() - app2.getAppID();
}

Application* Version::getAllAppsByDownloads(int* numberOfApps) {
	if (apps.size() == 0) {
		numberOfApps = 0;
		return NULL;
	}

	Application* appsByDownloads = (Application *)malloc(
			sizeof(*appsByDownloads) * apps.size());
	if (!appsByDownloads) {
		throw std::bad_alloc();
	}

	GetAllAppsByDownloads getApps;
	apps.inOrder<GetAllAppsByDownloads>(getApps);
	getApps.copyAppsToArray(&appsByDownloads);

	return appsByDownloads;
}

