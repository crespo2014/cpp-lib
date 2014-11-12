/*
 * ThreadCond.h
 *
 *  Created on: 21 Aug 2013
 *      Author: lester
 */

#ifndef THREADCOND_H_
#define THREADCOND_H_

#include "pthread.h"
#include "Mutex.h"

/*
 class implementing a event object.
 mutex and condition
 */
class ThreadCond
{
public:
	ThreadCond();
	~ThreadCond();
	bool wait(Mutex &mutex, unsigned int mseconds);
	void wait(Mutex &mutex);
	void broadcast()
	{
		if (pthread_cond_broadcast(&cond) == 0) throw uexception::error_api(ERROR_INFO());
	}
	void signal()
	{
		if (pthread_cond_signal(&cond) != 0) throw uexception::error_api(ERROR_INFO());
	}
private:
	pthread_cond_t cond;
	unsigned char flag;
};

#endif /* THREADCOND_H_ */
