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

/**
 * This class is used to compare two applications either by their download
 * count or by their ID.
 */
class Compare {
public:
	enum TypeOfComparison {
		FIRST_BY_ID, FIRST_BY_DOWNLOAD_COUNT
	};
	Compare(TypeOfComparison type) :
			type(type) {
	}
	int operator ()(Application app1, Application app2) const;

private:
	TypeOfComparison type;
};

class Version {
public:
	Version(int versionCode) :
			versionCode(versionCode), apps(Compare(Compare::FIRST_BY_ID)), downloads(
					Compare(Compare::FIRST_BY_DOWNLOAD_COUNT)) {
	}

	int getVersionCode() {
		return versionCode;
	}

	/**
	 * Adds an application to both trees.
	 */
	void addApp(Application);

	/**
	 * Finds an application in the tree by sending the application ID and
	 * and removes it from both trees.
	 */
	void removeApp(int appID);

	/**
	 * Finds the right app in the tree and increases the download count in both
	 * trees. If the application ID does not exist, then the exception
	 * DataDoesNotExist() is thrown.
	 */
	void increaseDownloads(int appID, int downloadIncrease);

	/**
	 * Returns an array initialized with malloc that contains every application
	 * ordered inversed by the download count.
	 */
	Application* getAllAppsByDownloads(int* numberOfApps);

	//TODO: think of more funcs

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
	 * Receives an application ID and returns the correct application
	 */
	Application findApplication(int appID);
};

inline Application Version::findApplication(int appID) {
	// Sending an application with the ID that we want, the others parameters
	// are not relevant to the search. The return value will contain the real
	// values of the application.
	return apps.find(Application(appID, 0, 0));
}

#endif /* VERSION_H_ */
