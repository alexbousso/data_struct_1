/*
 * exceptions.h
 *
 *  Created on: Nov 15, 2014
 *      Author: alex
 */

#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <exception>

// TODO Documentation to exceptions

class AllocationError: public std::exception {
};

class InvalidInput: public std::exception {
};

class AppIDExists: public std::exception {
};

class BadVersionCode: public std::exception {
};

class VersionCodeDoesntExsists: public std::exception {
};

class AppIDDoesentExists: public std::exception {
};

class ListIsEmpty: public std::exception {
};

class IndexOutOfBounds: public std::exception {
};

#endif /* EXCEPTIONS_H_ */
