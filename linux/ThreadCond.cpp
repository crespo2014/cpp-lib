/*
 * ThreadCond.cpp
 *
 *  Created on: 21 Aug 2013
 *      Author: lester
 */


#include "ThreadCond.h"
#include <sys/time.h>
#include "errno.h"
#include "log.h"

#define FLAG_INITIALIZE 1

ThreadCond::ThreadCond()
{
	if (pthread_cond_init(&cond, NULL) != 0)
	{
		throw uexception::error_api(ERROR_INFO());
	}
}

ThreadCond::~ThreadCond()
{
	pthread_cond_destroy(&cond);
}

/*
	wait for condition.
	return
	true condition is done
	false timeout

 */
bool ThreadCond::wait(Mutex &mutex, unsigned int mseconds)
{
	struct timespec ts;
	//struct timeval tp;

	clock_gettime(CLOCK_REALTIME, &ts);

	/*
	 gettimeofday(&tp, NULL);

	 ts.tv_sec = tp.tv_sec + mseconds / 1000;
	 ts.tv_nsec = (tp.tv_usec * 1000) + mseconds % 1000 * 1000000;
	 */

	ts.tv_sec += (mseconds / 1000);
	ts.tv_nsec += (mseconds % 1000) * 1000 * 1000;
	if (ts.tv_nsec > 1000000000)
	{
		ts.tv_sec++;
		ts.tv_nsec -= 1000000000;
	}

	int ir = pthread_cond_timedwait(&cond, mutex, &ts);
	if (ir == 0)
		return true;
	if (ir == ETIMEDOUT)
		return false;
	throw uexception::error_api(ERROR_INFO(),ir);

}

void ThreadCond::wait(Mutex &mutex)
{
	int ir = pthread_cond_wait(&cond, mutex);
	if (ir != 0)
		throw uexception::error_api(ERROR_INFO(),ir);
}



