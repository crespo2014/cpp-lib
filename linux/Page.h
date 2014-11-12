/*
 * Page.h
 *
 *  Created on: 1 Nov 2013
 *      Author: lester
 */

#ifndef PAGE_H_
#define PAGE_H_

#include <sys/mman.h>
#include <unistd.h>
#include "os.h"
#include "exception_base.h"

/*
 * This class is not actually a object.
 * it is use to handle access to a page in memory.
 *
 * memory will not release by this class on destruction
 */


class Page
{
protected:
	void release();

	// Initialize page structure
	void init(unsigned int psize);

	inline Page* getNext()
	{
		return next;
	}
	inline void setNext(Page* p)
	{
		next = p;
	}
	static Page* create(unsigned int size = 0);
	// create a new page and insert after this
	void InsertNew();

	Page* next;
	unsigned int size;
};

template<class T>
class BPage
{
public:
	// create a new memory page
	static T* create(unsigned int size = 4000)
	{
		unsigned int psize = getpagesize();
		size += sizeof(T);

		// adjust size to page boundary
		if (size > psize)
			psize = ((size + psize - 1) / psize) * psize;

		// create page
		T *p = (T*) mmap(0, psize, PROT_WRITE | PROT_READ, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
		if ( p == MAP_FAILED)
		{
			throw error_memory(ERROR_INFO());
		}
		p->BPage::reset(psize);
		p->reset();
		return p;
	}
	// release memory used by page
	void destroy()
	{
		if (this == 0)
			return;
		if (next)
			next->destroy();
		next = 0;
		if (munmap(this, size) == -1)
		{
			throw error_memory(ERROR_INFO());
		}
	}
	unsigned int getSize()
	{
		return size;
	}
	unsigned int getAvailable()
	{
		return (size - sizeof(T));
	}
	inline T* getNext()
	{
		return next;
	}
	inline void setNext(T* p)
	{
		next = p;
	}
protected:
	// Initialize page structure
	void reset(unsigned int psize)
	{
		next = 0;
		size = psize;
	}
	T* next;
	unsigned int size;
};

#endif /* PAGE_H_ */
