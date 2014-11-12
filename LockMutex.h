/*
 * LockMutex.h
 *
 *  Created on: 14 Aug 2013
 *      Author: lester
 */

#ifndef LOCKMUTEX_H_
#define LOCKMUTEX_H_

#include "Mutex.h"

/*
 this class will lock a mutex object
 and will unlock on destructor
 */
class LockMutex
{
public:
	LockMutex(Mutex &mutex);
	virtual ~LockMutex()
	{
		if (status) unlock();
	}
	//
	void lock();
	//
	void unlock();
	Mutex *mutex;

private:
	bool status;
};

#endif /* LOCKMUTEX_H_ */
