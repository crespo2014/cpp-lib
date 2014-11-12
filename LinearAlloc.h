/*
 * LinearAlloc.h
 *
 *  Created on: 1 Nov 2013
 *      Author: lester
 */

#ifndef LINEARALLOC_H_
#define LINEARALLOC_H_

#include "Page.h"

/*
 this class is not a object is a wrapper for linear allocation of memory over a page
 */

class LinearAlloc: private Page
{
public:
	// create a page to store some content
	static LinearAlloc* create(unsigned int size = 0)
	{
		LinearAlloc* p = (LinearAlloc*) Page::create(size + sizeof(LinearAlloc) - sizeof(Page));
		p->init();
		return p;
	}
	inline LinearAlloc** getnext()
	{
		return (LinearAlloc**) &next;
	}

	inline void init()
	{
		pos = 0;
	}
	// return null if there is not memory
	inline void* get(unsigned int size)
	{
		unsigned short idx = pos;
		pos += ((size + sizeof(*dt) -1)/sizeof(*dt));
		return &dt[idx];
	}
	// get free space
	inline unsigned int getFree()
	{
		return (pos == 0xFFFF) ? (0) : (size - sizeof(*this) - pos * sizeof(*dt) + sizeof(dt));
	}
	// store a string
	void AddString(const char *str, unsigned int len, char * &mem);
	// release memory
	void release()
	{
		Page::release();
	}
	/*
	 * get remained free space on memory
	 * return pointer index and size
	 * this memory can be reduce, but it can't be grow
	 */
	void* lock(unsigned short &size, unsigned int &idx)
	{
		size = getFree();
		idx = pos;
		pos = 0xFFFF;
		return &dt[idx];
	}
	/*
	 * Change size of this block on memory
	 */
	void unlock(unsigned int idx,unsigned int size)
	{

	}
private:
	unsigned int pos;		// current free pos
	// data go here
	int dt[1];
};

#endif /* LINEARALLOC_H_ */
