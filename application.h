/*
 * application.h
 *
 *  Created on: Nov 15, 2014
 *      Author: alex
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

class Application {
	const int appID;
	int versionCode;
	int downloadCount;

public:
	Application(const int appID, int versionCode, int downloadCount);

	/**
	 * Returns the application ID
	 */
	int getAppID() const;

	/**
	 * Returns the version code
	 */
	int getVersionCode() const;

	/**
	 * Returns the current download count
	 */
	int getDownloadCount() const;

	/**
	 * Increases the download count. If the argument is <= 0, then
	 * InvalidInput() exception is thrown
	 */
	void increaseDownloads(const int downloadIncrease);

	/**
	 * Upgrades the version code of the application. If the argument is less
	 * or equal to the current version, then BadVersionCode() exception is
	 * thrown.
	 */
	void upgradeApplication(const int newVersion);
};

#endif /* APPLICATION_H_ */
