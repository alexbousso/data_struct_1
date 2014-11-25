/*
 * helper_classes.h
 *
 *  Created on: Nov 25, 2014
 *      Author: alex
 */

#ifndef HELPER_CLASSES_H_
#define HELPER_CLASSES_H_

#include "list.h"

/**
 * Class that functions as a function object. It is used for explore the tree
 * and copy every application on it to a list defined in the class.
 */
class AppsToList {
public:
	AppsToList() :
			apps() {
	}
	void copyIDToArray(int** array) {
		int i(0);
		for (List<Application>::Iterator it(apps.begin()); it != apps.end();
				++it, ++i) {
			(*array)[i] = it->getAppID();
		}
	}
	List<Application> getListOfApps() {
		return apps;
	}
	void operator ()(Application app) {
		apps.pushBack(app);
	}

private:
	List<Application> apps;
};

/**
 * This class is used to compare two applications either by their download
 * count or by their ID.
 */
class Compare {
public:
	enum TypeOfComparison {
		FIRST_BY_ID, FIRST_BY_DOWNLOAD_COUNT
	};
	Compare(): type(FIRST_BY_ID){}
	Compare(TypeOfComparison type) :
			type(type) {
	}
	int operator ()(Application app1, Application app2) const;

private:
	TypeOfComparison type;
};

int Compare::operator ()(Application app1, Application app2) const {
	if (type == FIRST_BY_DOWNLOAD_COUNT) {
		int downloadsDifference = app2.getDownloadCount()
				- app1.getDownloadCount();
		if (downloadsDifference != 0) {
			return downloadsDifference;
		}
	}
	return app1.getAppID() - app2.getAppID();
}

#endif /* HELPER_CLASSES_H_ */
