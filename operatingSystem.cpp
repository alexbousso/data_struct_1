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

bool OS::findVersion(int versionCode) {
	for (List<Version>::Iterator it = versions.begin(); it != versions.end();
			++it) {
		if ((*it).getVersionCode() == versionCode) {
			return true;
		}
	}
	return false;
}

Version& OS::getVersion(int versionCode) {
	for (List<Version>::Iterator it = versions.begin(); it != versions.end();
			++it) {
		if ((*it).getVersionCode() == versionCode) {
			return *it;
		}
	}
	throw DataDoesNotExist("list");
}

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
		//Version ver(versionCode);
		Application app(appID, versionCode, downloadCount);
		if (findVersion(versionCode) == false
				|| applications.find(app) == true) { //if the app exists or there's no such version
			return FAILURE;
		}
		Version ver = getVersion(versionCode);
		ver.addApp(app);		//add the app to the version (both trees)
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
		Application app(appID, 1, 1);
		if (applications.find(app) == false) {	//if the app doesnt exist
			return FAILURE;
		}

		//Application toRemove = (Application)applications.find(app);
		//Version ver(app.getVersionCode());

		Application toRemove = applications.getData(app);

		applications.remove(toRemove);	//remove from the OS tree

		Version ver = getVersion(toRemove.getVersionCode());

		ver.removeApp(toRemove.getAppID());	//remove app from both trees in the version.

	} catch (std::bad_alloc& e) {
		return ALLOCATION_ERROR;
	}

	return SUCCESS;
}

StatusType OS::increseDownloads(int appID, int downloadIncrease) {

	if (appID <= 0 || downloadIncrease <= 0) {
		return INVALID_INPUT;
	}


	try {
		Application tempApp(appID, 1, 1);
		if(applications.find(tempApp) == false){
			return FAILURE;
		}
		Application toRemove = applications.getData(tempApp);
		applications.remove(toRemove);//remove the relevant app from the OS tree
		Version containing = getVersion(toRemove.getVersionCode()); //find the version containing this app
		containing.removeApp(appID);

		Application updatedApp(appID, toRemove.getDownloadCount(),
				toRemove.getVersionCode());	//creates a new app, the same as old
		updatedApp.increaseDownloads(downloadIncrease);	//updates the relevant info
		applications.insert(updatedApp);	//add to the OS tree
		containing.addApp(updatedApp);	//add to both version trees
	} catch (std::bad_alloc& ba) {
		return ALLOCATION_ERROR;
	}

	return SUCCESS;
}
