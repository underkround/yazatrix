#ifndef __SINGLETON_H__
#define __SINGLETON_H__
/**
 * Singleton.h
 *
 * $Revision$
 * $Id$
 *
 * Curiously Recurring Template Pattern aka the Meyers singleton
 * http://en.wikipedia.org/wiki/Singleton_pattern#C.2B.2B
 *
 */

template<typename T> class Singleton {

public:
  static T& getInstance() {
    static T theSingleInstance;  // assumes T has a protected default constructor
    return theSingleInstance;
  }

};

#endif // __SINGLETON_H__
