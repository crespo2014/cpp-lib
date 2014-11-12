/*
 * PageAllocator.cpp
 *
 *  Created on: 25 Oct 2013
 *      Author: lester
 */

#include "PageAllocator.h"
#include <stdlib.h>
#include "log.h"

PageAllocator::PageAllocator()
{
	first_page = 0;

}

PageAllocator::~PageAllocator()
{
}

void* PageAllocator::get(unsigned short size)
{
	//CHECK_RET_CODE(size < 4000, 0);
	// get a available page and look for size.
	_page *page = first_page;
	_obj *obj;
	unsigned short idx;

	//look free page or create one
	for (;;)
	{
		// create page if it is not exits
		if (!page)
		{
			page = (_page*) malloc(4028);
			page->free_obj_idx = 0;
			page->max_idx = (4028 - sizeof(_page)) / sizeof(int) + 1;
			obj = (_obj*) &page->dt[0];
			obj->flag = 0;
			obj->size = page->max_idx;
			if (!first_page)
			{
				first_page = page;
				page->next = 0;
			} else
			{
				page->next = first_page;
				first_page = page;
			}
		}
		// find a obj with enough space, if the object is free then data will point to next free object
		//
		// look for free space
		unsigned short isize = (size + sizeof(_obj) - sizeof(obj->obj)) / sizeof(obj->obj);

		for (idx = page->free_obj_idx; idx < page->max_idx;)
		{
			obj = (_obj*) &page->dt[idx];

			// if there is not enough space go to next free block
			if (obj->size < isize)
			{
				idx = obj->obj[0];
				continue;
			}
			// if remain space is enough to store next node
			if (obj->size > isize + sizeof(_obj)/sizeof(obj->obj))
			{
				_obj* nxt_obj = (_obj*)obj->obj[idx + isize];
				nxt_obj->size = obj->size - isize;
				//nxt_obj

			}
			if (obj->size >= isize)
			{
				// there space here

				_obj* nxt_obj = (_obj*)obj->obj[isize];
				nxt_obj->size = obj->size - isize;
				/*
				obj->flag |= PA_F_OBJ_USED;
				obj->size = (size + sizeof(_obj) - sizeof(obj->obj)) / sizeof(obj->obj);
				void* r = &obj->obj;
				*/

				// create next empty object
				obj = (_obj*)obj->obj[obj->size];
			}
		}
		page = page->next;
	}
	while (page)
	{
		// lok for enough room
		for (idx = page->free_obj_idx; idx < page->max_idx; idx += ((_obj*) &page->dt[idx])->size)
		{
			obj = (_obj*) &page->dt[idx];
			/*
			if (obj->flag & PA_F_OBJ_USED)
				continue;
				*/
		}

	}

	while (!page)
	{
		if (page)
		{

		}
		page = (_page*) malloc(4028);
		page->free_obj_idx = 0;
		page->max_idx = (4028 - sizeof(_page)) / sizeof(int) + 1;
		obj = (_obj*) &page->dt[0];
		obj->flag = 0;
		obj->size = page->max_idx;
		if (!first_page)
		{
			first_page = page;
			page->next = 0;
		} else
		{
			page->next = first_page;
			first_page = page;
		}
		// check space in this page
	}
}

