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


class OS{
	List<Version> versions;
public:
	OS(): versions(){}
	~OS();

	//adds a new version
	void addVersion(int);

	//adds a new app to a specific version
	void addApplication(int, int, int);

	//removes an app from a specified version
	void removeApplication(int);

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
