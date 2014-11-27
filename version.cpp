#include "version.h"
#include "exceptions.h"
#include "list.h"
#include "helper_classes.h"
#include <stdlib.h>
#include <iostream>

using std::ostream;
using std::endl;

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

int Version::getTopApp() {
	return downloads.getMax().getAppID();
}

void Version::increaseDownloads(int appID, int downloadIncrease) {
	if (downloadIncrease <= 0 || appID <= 0) {
		throw InvalidInput();
	}

	Application app(findApplication(appID));
	app.increaseDownloads(downloadIncrease);
}

int* Version::getAllAppsByDownloads(int* numberOfApps) {
	if (apps.size() == 0) {
		*numberOfApps = 0;
		return NULL;
	}

	int* appsByDownloads = (int *) malloc(
			sizeof(*appsByDownloads) * downloads.size());
	if (!appsByDownloads) {
		throw std::bad_alloc();
	}

	AppsToList getApps;
	downloads.inOrder<AppsToList>(getApps);
	getApps.copyIDToArray(&appsByDownloads);

	*numberOfApps = downloads.size();

	return appsByDownloads;
}

ostream& operator <<(ostream& os, const Version& ver) {
	os << "Version: " << ver.versionCode;
	os << "\tapps tree:      ";
	ver.apps.printTree();
	os << endl;
	os << "\tdownloads tree: ";
	ver.downloads.printTree();
	os << endl;
	return os;
}
