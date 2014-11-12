/*
 * Mutex.h
 *
 *  Created on: Sep 10, 2013
 *      Author: lcrespo
 */


#ifndef MUTEX_H_
#define MUTEX_H_

/*
 This class will handle mutex functionality
 it can operate in three modes.
 total control
 */

#define FLAG_INITIALIZE 1

class Mutex
{
public:
	Mutex();
	virtual ~Mutex();
	void init();
	void lock();
	void unlock();
private:
	unsigned char flag;


};

#endif /* MUTEX_H_ */
