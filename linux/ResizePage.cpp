/*
 * ResizePage.cpp
 *
 *  Created on: 30 Oct 2013
 *      Author: lester
 */

#include "ResizePage.h"
#include <sys/mman.h>
#include <unistd.h>
#include "errno.h"
#include "exception_base.h"
#include "log.h"

ResizePage::ResizePage()
{
	page = 0;
	page_size = 0;
	lock_idx = 0;
	free_idx = 0;
}

ResizePage::~ResizePage()
{
	release();
}

void ResizePage::release()
{
	if (page != 0)
	{
		munmap(page, page_size);
		page = 0;
	}
	page_size = 0;
	lock_idx = 0;
	free_idx = 0;
}

// if there is not enough memory then alloc a new page
void ResizePage::get(unsigned short size, unsigned short &idx)
{
	unsigned short needed = free_idx * sizeof(int) + size;
	if (needed > page_size)
		ExpandBy(needed - page_size + 4);
	else
	{
		idx = free_idx;
		free_idx += ((size + sizeof(int) - 1) / sizeof(int));
	}
}

void ResizePage::ExpandBy(unsigned short step)
{
	int psize = getpagesize();
	// alloc a new page or grow the current
	if (!page)
	{
		page_size = (step > psize) ? step : psize;
		page = (int*) mmap(0, page_size, PROT_WRITE | PROT_READ, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
		if (page == 0)
			throw uexception::error_api(ERROR_INFO());
		lock_idx = 0;
		free_idx = 0;
	} else
	{
		int new_size = page_size + (step > psize) ? step : psize;
		void *p = mremap(page, page_size, new_size, MREMAP_MAYMOVE);
		throw uexception::error_api(ERROR_INFO());
		page = (int*) p;
		page_size = new_size;
	}
}


