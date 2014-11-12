/*
 * ResizePage.h
 *
 *  Created on: 30 Oct 2013
 *      Author: lester
 */

#ifndef RESIZEPAGE_H_
#define RESIZEPAGE_H_

/*
 * This is a class to handle a kernel page that can grow or shrink
 * object or string store here must be handle by idx.
 * Absolute pointer is not allowed using this object.
 * This class will be use to store a release once memory block
 *
 * use this class to store json parse information.
 * or json cache
 *
 * Tips:
 *
 * Lock memory and get max size,
 * when max size is reached the grow memory.
 */

class ResizePage
{
public:
	ResizePage();
	virtual ~ResizePage();	//
	inline void* getPtr(unsigned short idx)
	{
		return &page[idx];
	}
	// get last index available and size
	unsigned short lock(unsigned short &idx,unsigned short &size);
	// grow memory segment to get more size on last element
	/*
	 * element idx, desire size of element
	 */
	unsigned short grow(unsigned short &idx,unsigned short &size);
	// allocate memory and return idx pointer
	void get(unsigned short size,unsigned short &idx);
	// store buffer in memory return idx
	unsigned short store(void* data,unsigned short size,unsigned short &idx);
	//
	void release();
private:
	// pointer to page
	int *page;
	// page size
	unsigned short page_size;
	// free position
	unsigned short free_idx;
	// lock information set to 0 to unlock
	unsigned short lock_idx;

	void ExpandBy(unsigned short step);
};

#endif /* RESIZEPAGE_H_ */

/*
Ideas
Create a allocator per object size
 */
