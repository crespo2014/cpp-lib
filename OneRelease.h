/*
 * OneRelease.h
 *
 *  Created on: 31 Oct 2013
 *      Author: lester
 */

#ifndef ONERELEASE_H_
#define ONERELEASE_H_

#include "LinearAlloc.h"
#include "string.h"

class OneRelease
{
public:
	OneRelease();
	~OneRelease()
	{
		release();
	}
	// store a string
	void alloc(const char *str, unsigned int len, char * &new_str);

	void alloc(const char *str,char * &new_str)
	{
		return alloc(str,strlen(str),new_str);
	}

	void* alloc(unsigned int size);
	inline void free(void* p)
	{
	}
	static bool inline canFree()
	{
		return false;
	}
	void release();
private:
	LinearAlloc* first;
	/*
	 * disable copy constructor
	 */
private:
	OneRelease(const OneRelease&);     // do not give these a body
	OneRelease& operator =(const OneRelease&);
};

#endif /* ONERELEASE_H_ */
