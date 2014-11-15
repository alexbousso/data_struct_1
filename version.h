/*
 * version.h
 *
 *  Created on: Nov 15, 2014
 *      Author: Miri
 */

#ifndef VERSION_H_
#define VERSION_H_

#include <memory>
#include "avl_tree.h"
#include "application.h"

using std::shared_ptr;

class Version{
	int versionCode;
	AVLTree< shared_ptr< Application > > appsTree;
	AVLTree< shared_ptr< Application > > downloadsTree;

public:
	Version(int code) : versionCode(code), appsTree(), downloadsTree(){}

	int getCode(){
		return versionCode;
	}

};



#endif /* VERSION_H_ */
