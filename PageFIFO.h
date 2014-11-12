/*
 * PageFIFO.h
 *
 *  Created on: 20 Nov 2013
 *      Author: lester
 */

#ifndef PAGEFIFO_H_
#define PAGEFIFO_H_

#include "Page.h"

#include "string.h"
/*
 * Create a fifo using memory pages
 * to store elements of variable size
 *
 * when read position reach end of page the page is free after clear next element
 *
 * when max size is reach an a new page create and the first is release.
 * better to put the first page at the end and reuse.
 *
 */

class Element
{
public:
	/*
	 * size of element or next
	 * 0xFFFF is use when remained space of page it was not enough to store a new one
	 * then wr_pos will be 0xFFFF and the last element will be invalidate
	 */
	unsigned int size;
};
/*
 * If wr_pos == sizeof(element) then a zero size element is the last on the list
 */
class FIFOPage: public BPage<FIFOPage>
{
public:
	/*
	 * get memory for a a new element. use of this function is not allowed in multithread
	 */
	unsigned short alloc(unsigned short esize, void* &data)
	{
		// check available space
		if (wr_pos + esize + sizeof(Element) > size)
		{
			wr_pos += sizeof(Element);
			return ERR_MEMORY;
		}
		// copy element
		Element* e = (Element*) ((unsigned char*) &this[1] + wr_pos);
		e->size = esize;
		data = &e[1];
		// go to next position
		wr_pos += (sizeof(*e) + esize + sizeof(int) - 1);
		wr_pos &= ~(sizeof(int) - 1);
		return NO_ERR;
	}

	/*
	 * Add element
	 * return ERR_MEMORY if there is not room
	 * If there is not space enough at this segment then
	 * write pointer will leave space for a zeero size element
	 */
	unsigned short push(const void* data, unsigned short esize)
	{
		void *p;
		CHECK_ERR_RET_CODE(alloc(esize, p), ERR_MEMORY);
		memcpy(p, data, esize);
		return NO_ERR;
	}
	/*
	 * Pop element from begin
	 * return
	 * NO_MORE if write pointer is equal to rd pointer
	 * EOF when the page is clear
	 */
	unsigned short pop(void* &p, unsigned short &size)
	{
		if (wr_pos == rd_pos)
			return ERR_NO_MORE;
		if (rd_pos + sizeof(Element) == wr_pos)
			return ERR_EOF;
		Element* e = (Element*) ((unsigned char*) &this[1] + rd_pos);

		// move to next
		rd_pos += (sizeof(*e) + e->size + sizeof(int) - 1);
		rd_pos &= ~(sizeof(int) - 1);

		p = &e[1];
		size = e->size;
		return NO_ERR;
	}
	// this page will be reuse
	void reset()
	{
		wr_pos = 0;
		rd_pos = 0;
	}
	unsigned short getFree() const
	{
		return (wr_pos + sizeof(Element) > size) ? 0 : size - wr_pos - sizeof(Element);
	}
private:
	FIFOPage();
	// read pos
	unsigned short rd_pos;
	unsigned short wr_pos;
	// data wil be store on this[1]
};

class PageFIFO
{
public:
	PageFIFO()
	{
		first = 0;
		last = 0;
		maxSize = 0;
		currentSize = 0;
	}
	PageFIFO(unsigned maxSize) :
			first(0), last(0), maxSize(maxSize), currentSize(0)
	{

	}
	~PageFIFO()
	{
		first->destroy();
	}
	unsigned short pop(void* &p, unsigned short &size)
	{
		for (;;)
		{
			// try to get from first element
			if (first == 0)
				return ERR_EOF;
			unsigned short sr = first->pop(p, size);
			if (sr == NO_ERR)
				return NO_ERR;
			// release block because rd have reached wr or rd have passed end of block
			FIFOPage* f = first;
			first = first->getNext();
			f->setNext(0);
			currentSize -= f->getSize();
			f->destroy();
			if (last == f)
				last = 0;
		}
		return NO_ERR;
	}
	/*
	 * Insert a new element and get pointer
	 */
	unsigned short alloc(unsigned short size, void* &p)
	{
		if (last == 0)
		{
			last = last->create(size);
			currentSize += last->getSize();
			if (first == 0)
				first = last;
		}
		// insert in last page if it is possible
		if (last->alloc(size, p) == NO_ERR)
			return NO_ERR;
		// create a new one
		if ((currentSize < maxSize) || (last == first))
		{
			last->setNext(last->create(size));
			CHECK_RET_CODE(last->getNext() != 0, ERR_MEMORY);
			last = last->getNext();
			currentSize += last->getSize();
		} else
		{
			// reuse the first page
			last->setNext(first);
			first = first->getNext();
			last = last->getNext();
			last->setNext(0);
			last->reset();
		}
		CHECK_ERR_RET_CODE(last->alloc(size, p), ERR_MEMORY);
		return NO_ERR;
	}
	/*
	 * Get space for a new element and copy its data
	 */
	unsigned short push(const void* p, unsigned short size)
	{
		void *t;
		unsigned short sr = alloc(size, t);
		CHECK_ERR_RET_CODE(sr, sr);
		memcpy(t, p, size);
		return NO_ERR;
	}
	/*
	 * Define max memory size to use
	 */
	void setMaxSize(unsigned int size)
	{
		maxSize = size;
	}
	unsigned short getUsed() const
	{
		if (last == 0)
			return 0;
		return (currentSize - last->getFree());
	}
	unsigned short getAllocatedSize() const
	{
		return currentSize;
	}
private:
	FIFOPage* first, *last;
	unsigned int maxSize;
	unsigned int currentSize;
};

#endif /* PAGEFIFO_H_ */
