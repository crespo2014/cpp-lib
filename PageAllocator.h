/*
 * PageAllocator.h
 *
 *  Created on: 25 Oct 2013
 *      Author: lester
 */

#ifndef PAGEALLOCATOR_H_
#define PAGEALLOCATOR_H_

/*
 	 memory manager

 	 free block list.
 	 when a block is freeing then lock for previous free block and put block on list
 */

/*
 * object in memory
 */

#define PA_F_OBJ_USED	0x1		// this object is not free

struct _obj {
	unsigned char* flag;
	unsigned short size;	// size of structure + data, or next block pos
	unsigned int obj[1];
};

/*
 *  (page size - sizeof(_page)) / sizeof(int) + 1 = max integer
 */
struct _page
{
	_page *next;
	unsigned short max_idx;
	unsigned short free_obj_idx;
	unsigned int dt[1];
};

class PageAllocator
{
public:
	PageAllocator();
	virtual ~PageAllocator();
	void* get(unsigned short size);
private:
	_page	*first_page;
};

#endif /* PAGEALLOCATOR_H_ */
