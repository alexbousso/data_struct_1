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
#include "helper_classes.h"
#include <stdlib.h>

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
	if (appID <= 0 || versionCode <= 0 || downloadCount < 0) {
		return INVALID_INPUT;
	}
	try {

		Application app(appID, versionCode, downloadCount);
		if (findVersion(versionCode) == false
				|| applications.findIsIn(app) == true) { //if the app exists or there's no such version
			return FAILURE;
		}
		Version& ver = getVersion(versionCode);
		ver.addApp(app);		//add the app to the version (both trees)
		applications.insert(app);	//add the app to the OS apps tree
		downloads.insert(app);	//add to the OS downloads tree
	} catch (std::bad_alloc& ba) {
		return ALLOCATION_ERROR;
	} /*catch (...) {
	 //TODO what to do here?!?!? (could catch BadVersionCode)
	 }*/

	return SUCCESS;
}

StatusType OS::removeApplication(int appID) {

	if (appID <= 0) {
		return INVALID_INPUT;
	}
	try {
		Application app(appID, 1, 1);
		if (applications.findIsIn(app) == false) {	//if the app doesnt exist
			return FAILURE;
		}

		Application toRemove = applications.getData(app); //find the app we need to remove with all it's data

		applications.remove(toRemove);	//remove from the OS app tree
		downloads.remove(toRemove);		//remove from OS downloads tree

		Version& ver = getVersion(toRemove.getVersionCode()); //find in the version containing the app we're removing

		ver.removeApp(toRemove.getAppID());	//remove app from both trees in the version.

	} catch (std::bad_alloc& e) {
		return ALLOCATION_ERROR;
	}

	return SUCCESS;
}

StatusType OS::increaseDownloads(int appID, int downloadIncrease) {

	if (appID <= 0 || downloadIncrease <= 0) {
		return INVALID_INPUT;
	}

	try {
		Application tempApp(appID, 1, 1);
		if (applications.findIsIn(tempApp) == false) { //if an app with such ID doesn't exist
			return FAILURE;
		}
		Application toRemove = applications.getData(tempApp);
		applications.remove(toRemove); //remove the relevant app from the OS app tree
		downloads.remove(toRemove);	//remove the app from the OS downloads tree
		Version& containing = getVersion(toRemove.getVersionCode()); //find the version containing this app
		containing.removeApp(appID); //remove the app from the version

		//now' we'll create a new app with the updated info and insert it to all trees

		Application updatedApp(appID, toRemove.getVersionCode(),
				toRemove.getDownloadCount());//creates a new app, the same as old
		updatedApp.increaseDownloads(downloadIncrease);	//updates the relevant info
		applications.insert(updatedApp);	//add to the OS app tree
		downloads.insert((updatedApp));		//add to the OS downloads tree
		containing.addApp(updatedApp);		 //add to both version trees
	} catch (std::bad_alloc& ba) {
		return ALLOCATION_ERROR;
	}

	return SUCCESS;
}

StatusType OS::upgradeApplication(int appID) {

	if (appID <= 0) {
		return INVALID_INPUT;
	}

	try {
		Application tempApp(appID, 1, 1);
		if (applications.findIsIn(tempApp) == false) {//if such app doesn't exist
			return FAILURE;
		}
		Application oldApp = applications.getData(tempApp); //get the real app with the real data
		Version& oldVer = getVersion(oldApp.getVersionCode());
		if (oldVer.getVersionCode() == versions[0].getVersionCode()) { //if the version this app is in is the newest
			return FAILURE;
		}
		//if you survived till now, then remove from old, find the next version and upgrade the app
		oldVer.removeApp(tempApp.getAppID());
		applications.remove(oldApp);
		downloads.remove(oldApp);

		int index = 0;
		//now we'll find the index of the current version to use to find the index of the following one.
		for (List<Version>::Iterator it = versions.begin();
				(*it).getVersionCode() != oldVer.getVersionCode(); ++it) {
			index++;
		}
		Version& newVer = versions[index - 1];
		oldApp.upgradeApplication(newVer.getVersionCode());
		newVer.addApp(oldApp);		//add to the newer version
		applications.insert(oldApp);	//add to the app tree in the OS
		downloads.insert(oldApp);		//add to the downloads tree in the OS

	} catch (std::bad_alloc& ba) {
		return ALLOCATION_ERROR;
	}

	return SUCCESS;
}

StatusType OS::getTopApp(int versionCode, int* appID) {

	if (appID == NULL || versionCode == 0) {
		return INVALID_INPUT;
	}

	if (versionCode < 0) {	//if wer'e asked for the max in all the OS
		if (downloads.size() == 0) {
			*appID = -1;
		} else {
			*appID = downloads.getMax().getAppID();
		}
		return SUCCESS;
	}

	if (findVersion(versionCode) == false) { //if there's no such version
		return FAILURE;
	}
	try { //this is the case where: versionCode > 0
		Version& containing = getVersion(versionCode);
		if (containing.downloads.size() == 0) {
			*appID = -1;
		} else {
			*appID = containing.getTopApp();
		}

	} catch (std::bad_alloc& ba) {
		return ALLOCATION_ERROR;
	}
	return SUCCESS;
}

StatusType OS::getAllAppsByDownloads(int versionCode, int **apps,
		int *numOfApps) {
	if (!apps || !numOfApps || versionCode == 0) {
		if (apps) {
			apps = NULL;
		}
		if (numOfApps) {
			*numOfApps = -1;
		}
		return INVALID_INPUT;
	}
	if (versionCode > 0 && !findVersion(versionCode)) {
		// TODO: Is this right?
		apps = NULL;
		*numOfApps = -1;
		return FAILURE;
	}

	if (versionCode < 0) {
		if (downloads.size() == 0) {
			*numOfApps = 0;
			apps = NULL;
			// TODO: Is this right?
			return SUCCESS;
		}

		*apps = (int *) malloc(sizeof(*apps) * downloads.size());
		if (!apps) {
			*numOfApps = -1;
			return ALLOCATION_ERROR;
		}

		AppsToList getApps;
		downloads.inOrder<AppsToList>(getApps);
		getApps.copyIDToArray(apps);
	} else {
		assert(versionCode > 0);
		Version& version(getVersion(versionCode));
		assert(version.getVersionCode() == versionCode);
		try {
			*apps = version.getAllAppsByDownloads(numOfApps);
		} catch (std::bad_alloc& e) {
			apps = NULL;
			*numOfApps = -1;
			return ALLOCATION_ERROR;
		}
	}
	return SUCCESS;
}

StatusType OS::updateDownloads(int groupBase, int multiplyFactor) {
	if (multiplyFactor <= 0 || groupBase < 1) {
		return INVALID_INPUT;
	}

	try {
		TreeDownloadsUpdater updateApplications(applications, groupBase,
				multiplyFactor);
		updateApplications.updateTree();
		TreeDownloadsUpdater updateDownloads(downloads, groupBase,
				multiplyFactor);
		updateDownloads.updateTree();
		for (List<Version>::Iterator it(versions.begin()); it != versions.end();
				++it) {
			TreeDownloadsUpdater updateApplications(it->apps, groupBase,
					multiplyFactor);
			updateApplications.updateTree();
			TreeDownloadsUpdater updateDownloads(it->downloads, groupBase,
					multiplyFactor);
			updateDownloads.updateTree();
		}

	} catch (std::bad_alloc& e) {
		return ALLOCATION_ERROR;
	}
	return SUCCESS;
}

