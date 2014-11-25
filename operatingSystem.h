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

// TODO: Delete
//class AppSorter{
//public:
//	int operator()(const Application& app1, const Application& app2) const{
//		return app1.getAppID()-app2.getAppID();
//	}
//};

class OS {
	List<Version> versions;

	AVLTree<Application, Compare> applications;

	// TODO: Notice me!!!
	AVLTree<Application, Compare> downloads;

public:
	OS() :
			versions(), applications(Compare(Compare::FIRST_BY_ID)), downloads(
					Compare(Compare::FIRST_BY_DOWNLOAD_COUNT)) {
	}
	~OS();

	//adds a new version
	StatusType addVersion(int);

	//adds a new app to a specific version
	StatusType addApplication(int, int, int);

	StatusType removeApplication(int);

	//increases the download count on a specific app in the specified version
	StatusType increseDownloads(int, int);

	//upgrades an application to a newer version
	StatusType upgradeApplication(int);

	StatusType getTopApp(int, int*);

	//returns all the apps in a specified version by their downloads
	//TODO any other input needed here? should it be const function?!
	StatusType getAllAppsByDownloads(int, int**, int*);

	//updates the downloads of a certain group of apps
	StatusType updateDownloads(int, int);

	// QUESTION: Why not private?
	//returns true if a version with the given code is found in the list and false otherwise
	bool findVersion(int);

	// QUESTION: Why not private?
	//if a version with the given code is found-return a reference to it
	Version& getVersion(int);
};

#endif /* OPERATINGSYSTEM_H_ */
