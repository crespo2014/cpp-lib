/*
 * LockMutex.cpp
 *
 *  Created on: 14 Aug 2013
 *      Author: lester
 */

#include "LockMutex.h"
#include "stdio.h"

LockMutex::LockMutex(Mutex &mutex)
{
	status = false;
	this->mutex = &mutex;
}

/*
 lock the mutex and return current status
 */
void LockMutex::lock()
{
	status = true;
	mutex->lock();
}

/*
 unlock the mutex and return current status
 */
void LockMutex::unlock()
{
	status = false;
	mutex->unlock();
}

