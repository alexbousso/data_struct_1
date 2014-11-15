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

	int getAppID() const;
	int getVersionCode() const;
	int getDownloadCount() const;
	void increaseDownloads(const int downloadIncrease);
	void upgradeApplication(const int newVersion);
};

#endif /* APPLICATION_H_ */
