/*
 * Mutex.h
 *
 *  Created on: Sep 10, 2013
 *      Author: lcrespo
 */

#ifndef MUTEX_H_
#define MUTEX_H_

#include <pthread.h>

/*
 This class will handle mutex functionality
 it can operate in three modes.
 total control
 */

#include "exception_base.h"

class Mutex
{
public:
	Mutex()
	{
		if (pthread_mutex_init(&mutex, NULL) != 0)
		{
			throw error_api(ERROR_INFO());
		}
	}
	virtual ~Mutex()
	{
		unlock();
		pthread_mutex_destroy(&mutex);
	}
	void lock()
	{
		if (pthread_mutex_lock(&mutex) != 0)
		{
			throw error_api(ERROR_INFO());
		}
	}
	void unlock()
	{
		if (pthread_mutex_unlock(&mutex) != 0)
		{
			throw error_api(ERROR_INFO());
		}
	}
	inline operator pthread_mutex_t*()
	{
		return &mutex;
	}
private:
	unsigned char flag = 0;
	pthread_mutex_t mutex;

};


#endif /* MUTEX_H_ */
