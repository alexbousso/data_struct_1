/*
 * application.h
 *
 *  Created on: Nov 15, 2014
 *      Author: alex
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "exceptions.h"

class Application {
	const int appID;
	int versionCode;
	int downloadCount;

public:
	Application();
	Application(int appID, int versionCode, int downloadCount);
	Application(const Application&);
	Application operator =(Application&);

	/**
	 * Returns the application ID
	 */
	int getAppID() const;

	/**
	 * Returns the version code
	 */
	int getVersionCode() const;

	/**
	 * Returns the current download count
	 */
	int getDownloadCount() const;

	/**
	 * Increases the download count. If the argument is <= 0, then
	 * InvalidInput() exception is thrown
	 */
	void increaseDownloads(const int downloadIncrease);

	/**
	 * Upgrades the version code of the application. If the argument is less
	 * or equal to the current version, then BadVersionCode() exception is
	 * thrown.
	 */
	void upgradeApplication(const int newVersion);
};

/*						****************************
 *						* FUNCTION IMPLEMENTATIONS *
 *						****************************
 * All functions are implemented here because they are defined inline.
 */

inline Application::Application() :
		appID(0), versionCode(0), downloadCount(0) {
}

inline Application::Application(int appID, int versionCode, int downloadCount) :
		appID(appID), versionCode(versionCode), downloadCount(downloadCount) {
	// TODO: Add tests for this function
	if (appID <= 0 || versionCode <= 0 || downloadCount < 0) {
		throw InvalidInput();
	}
}

// TODO: Add tests
inline Application::Application(const Application& copy) :
		appID(copy.appID), versionCode(copy.versionCode), downloadCount(
				copy.downloadCount) {
}

// TODO: Add tests
inline Application Application::operator =(Application & copy) {
	return Application(copy.appID, copy.downloadCount, copy.versionCode);
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
		throw InvalidInput();
	}
	downloadCount += downloadIncrease;
}

inline void Application::upgradeApplication(const int newVersion) {
	if (newVersion <= versionCode) {
		throw BadVersionCode();
	}
	versionCode = newVersion;
}

#endif /* APPLICATION_H_ */
