/*
 * helper_classes.h
 *
 *  Created on: Nov 25, 2014
 *      Author: alex
 */

#ifndef HELPER_CLASSES_H_
#define HELPER_CLASSES_H_

#include "list.h"
#include <cassert>

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

	/**
	 * ATENTION: The function gets the object in reverse order.
	 */
	void operator ()(Application app) {
		apps.pushFront(app);
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
	Compare() :
			type(FIRST_BY_ID) {
	}
	Compare(TypeOfComparison type) :
			type(type) {
	}
	int operator ()(Application app1, Application app2) const;

private:
	TypeOfComparison type;
};

int Compare::operator ()(Application app1, Application app2) const {
	if (type == FIRST_BY_DOWNLOAD_COUNT) {
		int downloadsDifference = app1.getDownloadCount()
				- app2.getDownloadCount();
		if (downloadsDifference != 0) {
			return downloadsDifference;
		}
	}
	return app1.getAppID() - app2.getAppID();
}

/**
 * This class updates the download counter of the desired application on a
 * given tree
 */
class TreeDownloadsUpdater {
public:
	TreeDownloadsUpdater(AVLTree<Application, Compare>& tree, int groupBase,
			int multiplyFactor) :
			tree(tree), apps(), moduloEqualsZero(), moduloNotZero(), groupBase(
					groupBase), multiplyFactor(multiplyFactor) {
	}

	void updateTree() {
		AppsToList getApps;
		tree.inOrder<AppsToList>(getApps);
		apps(getApps.getListOfApps());

		splitBetweenLists();
		multiplyModuloEqualsZero();
		mergeLists();
		pushListToTree();

		apps.reset();
		moduloEqualsZero.reset();
		moduloNotZero.reset();
	}

private:
	AVLTree<Application, Compare>& tree;
	List<Application> apps, moduloEqualsZero, moduloNotZero;
	int groupBase, multiplyFactor;

	/**
	 * TODO: Description
	 */
	void splitBetweenLists() {
		for (List<Application>::Iterator it(apps.begin()); it != apps.end();
				++it) {
			if (it->getAppID() % groupBase == 0) {
				moduloEqualsZero.pushBack(*it);
			} else {
				moduloNotZero.pushBack(*it);
			}
		}
	}

	/**
	 * TODO: Description
	 */
	void multiplyModuloEqualsZero() {
		for (List<Application>::Iterator it(moduloEqualsZero.begin());
				it != moduloEqualsZero.end(); ++it) {
			it->increaseDownloads(
					it->getDownloadCount() * (multiplyFactor - 1));
		}
	}

	/**
	 * Resets the list apps and merges the lists moduloEqualsZero and
	 * moduloNotZero into the list apps. This function also reverses the order
	 * of the list, because the function AppsToList.operator ()() reverses
	 * the order of the list while getting it from the tree.
	 */
	void mergeLists() {
		apps.reset();

		List<Application>::Iterator itModZero(moduloEqualsZero.begin());
		List<Application>::Iterator itModNotZero(moduloNotZero.begin());

		while (itModZero != moduloEqualsZero.end()
				&& itModNotZero != moduloNotZero.end()) {
			assert(tree.compareElements(*itModZero, *itModNotZero) != 0);
			if (tree.compareElements(*itModZero, *itModNotZero) > 0) {
				apps.pushFront(*itModZero);
				++itModZero;
			} else {
				assert(tree.compareElements(*itModZero, *itModNotZero) < 0);
				apps.pushFront(*itModNotZero);
				++itModNotZero;
			}
			while (itModZero != moduloEqualsZero.end()) {
				apps.pushFront(*itModZero);
				++itModZero;
			}
			while (itModNotZero != moduloNotZero.end()) {
				apps.pushFront(*itModNotZero);
				++itModNotZero;
			}
			assert(
					itModZero == moduloEqualsZero.end()
							&& itModNotZero == moduloNotZero.end());
		}
	}

	/**
	 * TODO: Description
	 */
	class InsertAppsToTree {
	public:
		InsertAppsToTree() :
				it(TreeDownloadsUpdater::apps.begin()) {
		}
		void operator ()(Application &app) {
			app.appID = it->appID;
			app.downloadCount = it->downloadCount;
			app.versionCode = it->versionCode;
			++it;
		}

	private:
		List<Application>::Iterator it;
	};

	/**
	 * TODO: Description
	 */
	void pushListToTree() {
		InsertAppsToTree insertAppsToTree;
		tree.inOrder<InsertAppsToTree>(insertAppsToTree);
	}
};

#endif /* HELPER_CLASSES_H_ */

