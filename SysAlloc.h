/*
 * SysAlloc.h
 *
 *  Created on: 9 Nov 2013
 *      Author: lester
 */

#ifndef SYSALLOC_H_
#define SYSALLOC_H_

/*
 * Memory allocator using standard system functions new and delete
 */
class SysAlloc
{
public:
	SysAlloc();
	virtual ~SysAlloc();
	void* alloc(unsigned short size);
	void free(void* p);
	/*
	 * return false to avoid call to free function
	 */
	static bool inline canFree()
	{
		return true;
	}
};

#endif /* SYSALLOC_H_ */
