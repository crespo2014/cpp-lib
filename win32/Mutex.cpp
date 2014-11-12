/*
 * Mutex.cpp
 *
 *  Created on: Sep 10, 2013
 *      Author: lcrespo
 */

#ifdef _WIN32

#include "Mutex.h"
#include "os.h"
#include "log.h"

/*
 * Mutex must be initialize on ctor, use flag to indicate lock status
 */
Mutex::Mutex()
{
	flag = 0;
}

Mutex::~Mutex()
{
	if (flag & FLAG_INITIALIZE)
	{
		unlock();
		//pthread_mutex_destroy(&mutex);
	}
}

void Mutex::init()
{
	if (!(flag & FLAG_INITIALIZE))
	{
		//CHECK_API_RET(pthread_mutex_init(&mutex, NULL) == 0);
	}
	flag |= FLAG_INITIALIZE;
}

/*
 Lock mutex
 */
void Mutex::lock()
{
	//CHECK_RET_CODE(flag & FLAG_INITIALIZE, ERR_CLOSE);
	//CHECK_API_RET(pthread_mutex_lock(&mutex) == 0);

}

void Mutex::unlock()
{
	//CHECK_RET_CODE(flag & FLAG_INITIALIZE, ERR_CLOSE);
	//CHECK_API_RET(pthread_mutex_unlock(&mutex) == 0);

}

#endif
