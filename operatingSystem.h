/*
 * operatingSystem.h
 *
 *  Created on: Nov 23, 2014
 *      Author: Miri
 */

#ifndef OPERATINGSYSTEM_H_
#define OPERATINGSYSTEM_H_

#include "list.h"
#include "avl_tree.h"
#include "version.h"
#include "application.h"
#include "library1.h"
#include "helper_classes.h"

class OS {
	List<Version> versions;
	AVLTree<Application, Compare> applications;
	AVLTree<Application, Compare> downloads;

public:
	OS() :
			versions(), applications(Compare(Compare::FIRST_BY_ID)), downloads(
					Compare(Compare::FIRST_BY_DOWNLOAD_COUNT)) {
	}
	~OS() {
	}

	//adds a new version
	StatusType addVersion(int versionCode);

	//adds a new app to a specific version
	StatusType addApplication(int appID, int versionCode, int downloadCount);

	StatusType removeApplication(int appID);

	//increases the download count on a specific app in the specified version
	StatusType increaseDownloads(int appID, int downloadIncrease);

	//upgrades an application to a newer version
	StatusType upgradeApplication(int appID);

	// TODO: Add description
	StatusType getTopApp(int versionCode, int* appID);

	//returns all the apps in a specified version by their downloads
	//TODO any other input needed here? should it be const function?!
	StatusType getAllAppsByDownloads(int versionCode, int **apps,
			int *numOfApps);

	//updates the downloads of a certain group of apps
	StatusType updateDownloads(int groupBase, int multiplyFactor);

	//returns true if a version with the given code is found in the list and false otherwise
	bool findVersion(int);

	//if a version with the given code is found-return a reference to it
	Version& getVersion(int);

	// TODO: Add description
	void printTreeDownloads(int versionCode);
	void printTreeApplications(int versionCode);
};

#endif /* OPERATINGSYSTEM_H_ */
