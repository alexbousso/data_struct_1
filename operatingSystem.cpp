/*
 * operatingSystem.cpp
 *
 *  Created on: Nov 23, 2014
 *      Author: Miri
 */
#include "list.h"
#include "avl_tree.h"
#include "version.h"
#include "application.h"
#include "library1.h"
#include "operatingSystem.h"

StatusType OS::addVersion(int versionCode) {
	if (versionCode <= 0) {
		return INVALID_INPUT;
	}
	if (versionCode <= versions[0].getVersionCode()) {
		return FAILURE;
	}
	try {
		Version newVer(versionCode);
		versions.pushFront(newVer);
	} catch (std::bad_alloc& ba) {
		return ALLOCATION_ERROR;
	}

	return SUCCESS;
}

StatusType OS::addApplication(int appID, int versionCode, int downloadCount) {
	if (appID <= 0 || versionCode <= 0 || downloadCount <= 0) {
		return INVALID_INPUT;
	}
	try {
		Version ver(versionCode);
		Version* verPtr;
		Application app(appID, versionCode, downloadCount);
		if (versions.find(ver, verPtr) == false
				|| applications.find(app) == true) { //if the app exists or there's no such version
			return FAILURE;
		}
		verPtr->addApp(app);		//add the app to the version (both trees)
		applications.insert(app);	//add the app to the OS tree
	} catch (std::bad_alloc& ba) {
		return ALLOCATION_ERROR;
	} catch (...) {
		//TODO what to do here?!?!? (could catch BadVersionCode)
	}

	return SUCCESS;
}

StatusType OS::removeApplication(int appID) {

	if (appID <= 0) {
		return INVALID_INPUT;
	}
	try {
		Application app(appID);
		if (applications.find(app) == false) {	//if the app doesnt exist
			return FAILURE;
		}
		app = applications.find(app);
		Version *ver(app.getVersionCode());
		applications.remove(app);	//remove from the OD tree
		versions.find(*ver, ver);
//TODO finish this!!!

	} catch (std::bad_alloc& e) {
		return ALLOCATION_ERROR;
	}

	return SUCCESS;
}
