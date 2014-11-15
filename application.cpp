/*
 * application.cpp
 *
 *  Created on: Nov 15, 2014
 *      Author: alex
 */

#include "application.h"
#include "exceptions.h"

inline Application::Application(const int appID, int versionCode, int downloadCount) :
		appID(appID), versionCode(versionCode), downloadCount(downloadCount) {
	if (appID <= 0 || versionCode <= 0 || downloadCount < 0) {
		throw (InvalidInput());
	}
}

inline int Application::getAppID() const {
	return appID;
}

inline int Application::getVersionCode() const {
	return versionCode;
}

inline int Application::getDownloadCount() const {
	return downloadCount;
}

inline void Application::increaseDownloads(const int downloadIncrease) {
	if (downloadIncrease <= 0) {
		throw (InvalidInput());
	}
	downloadCount += downloadIncrease;
}

inline void Application::upgradeApplication(const int newVersion) {
	if (newVersion <= versionCode) {
		throw (BadVersionCode());
	}
	versionCode = newVersion;
}
