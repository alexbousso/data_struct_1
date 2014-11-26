/*
 * version.h
 *
 *  Created on: Nov 15, 2014
 *      Author: Miri
 */

#ifndef VERSION_H_
#define VERSION_H_

#include "avl_tree.h"
#include "application.h"
#include "helper_classes.h"

class Version {
public:
	Version(): versionCode(-1){}
	Version(int versionCode) :
			versionCode(versionCode), apps(Compare(Compare::FIRST_BY_ID)), downloads(
					Compare(Compare::FIRST_BY_DOWNLOAD_COUNT)) {
		if (versionCode <= 0) {
			throw InvalidInput();
		}
	}

	/**
	 * Returns the number of the object's version.
	 */
	int getVersionCode() {
		return versionCode;
	}

	/**
	 * Adds an application to both trees.
	 * Exceptions this function might throw:
	 * 		BadVersionCode() if the version codes do not match
	 * 		InputAlreadyExists() if the already exists
	 */
	void addApp(Application);

	/**
	 * Finds an application in the tree by sending the application ID and
	 * and removes it from both trees. If the ID does not exist the exception
	 * DataDoesNotExist() will be thrown.
	 */
	void removeApp(int appID);

	/**
	 * Finds the right app in the tree and increases the download count in both
	 * trees.
	 * Exceptions this function might throw:
	 * 		DataDoesNotExist() if the application ID does not exist
	 * 		InvalidInput() if (appID <= 0) or (downloadIncrease <= 0)
	 */
	void increaseDownloads(int appID, int downloadIncrease);

	/**
	 * Returns an array initialized with malloc that contains every application
	 * ordered inverted by the download count.
	 */
	Application* getAllAppsByDownloads(int* numberOfApps);

	/*
	 * returns the ID of the app with the heighst amount of downloads
	 */
	int getTopApp();

	friend class OS;

private:
	const int versionCode;

	/**
	 * This tree is sorted by the application ID's.
	 */
	AVLTree<Application, Compare> apps;

	/**
	 * This tree is sorted by the applications downloads count. If they are
	 * the same, then they are sorted by they ID's.
	 */
	AVLTree<Application, Compare> downloads;

	/**
	 * Receives an application ID and returns the correct application from the
	 * trees.
	 */
	Application findApplication(int appID);
};

inline Application Version::findApplication(int appID) {
	// Sending an application with the ID that we want, the others parameters
	// are not relevant to the search. The return value will contain the real
	// values of the application.
	return apps.find(Application(appID, 1, 1));
}

#endif /* VERSION_H_ */
