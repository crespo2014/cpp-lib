/*
 * Page.cpp
 *
 *  Created on: 1 Nov 2013
 *      Author: lester
 */

#include "Page.h"
#include <sys/mman.h>
#include <unistd.h>
#include "errno.h"
#include "log.h"

void Page::init(unsigned int psize)
{
	next = 0;
	size = psize;
}

void Page::release()
{
	if (next != 0)
		next->release();
	if (munmap(this,size) != 0)
	{
		throw error_api(ERROR_INFO());
	}
}

void Page::InsertNew()
{
	Page *p = create();
	p->setNext(next);
	next = p;
}

Page* Page::create(unsigned int size)
{
	unsigned int psize = getpagesize();
	size += sizeof(Page);

	// adjust size to page boundary
	if (size > psize)
		psize = ((size + psize - 1)/psize)*psize;

	// create page
	Page *p= (Page*)mmap(0, psize, PROT_WRITE | PROT_READ, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

	//CHECK_API_RET_CODE(p != MAP_FAILED,0);
	p->init(psize);
	return p;
}


