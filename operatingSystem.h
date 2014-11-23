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


class OS{
	List<Version> versions;
	class MainSorter;
	AVLTree <Application, MainSorter> applications;
public:
	OS(): versions(), applications(MainSorter()){}
	~OS();

	//adds a new version
	StatusType addVersion(int);

	//adds a new app to a specific version
	StatusType addApplication(int, int, int);

	StatusType removeApplication(int);

	//increses the download count on a specific app in the specified version
	void increseDownloads(int, int);

	//upgrades an application to a newer version
	void upgradeApplication(int);

	//returns all the apps in a specified version by their downloads
	//TODO any other input needed here?
	void getAllAppsByDownloads(int);

	//updates the downloads of a certain group of apps
	void updateDownloads(int, int);

};



#endif /* OPERATINGSYSTEM_H_ */
