/*
 * assert.h
 *
 *  Created on: Nov 15, 2014
 *      Author: alex
 */

#ifndef ASSERT_H_
#define ASSERT_H_

#include "test_utils.h"
#include "../exceptions.h"

#define ASSERT_INVALID_INPUT(arg) \
	ASSERT_THROWS(InvalidInput, arg)

#define ASSERT_APP_ID_EXISTS(arg) \
	ASSERT_THROWS(AppIDExists, arg)

#define ASSERT_BAD_VERSION_CODE(arg) \
	ASSERT_THROWS(BadVersionCode, arg)

#define ASSERT_VERSION_CODE_DOESNT_EXISTS(arg) \
	ASSERT_THROWS(VersionCodeDoesntExsists, arg)

#define ASSERT_APP_ID_DOESNT_EXISTS(arg) \
	ASSERT_THROWS(AppIDDoesentExists, arg)

#define ASSERT_LIST_IS_EMPTY(arg) \
	ASSERT_THROWS(ListIsEmpty, arg)

#define ASSERT_INDEX_OUT_OF_BOUNDS(arg) \
	ASSERT_THROWS(IndexOutOfBounds, arg)

#endif /* ASSERT_H_ */
