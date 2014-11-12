/*
 * StrBuffer.h
 *
 *  Created on: 31 Oct 2013
 *      Author: lester
 */

#ifndef STRBUFFER_H_
#define STRBUFFER_H_



/*
 * Create a buffer using a simple link list with element of size 50.
 * send list to output port using iterator.
 * when finish release everything.
 *
 */

template<class A = OneRelease>
class StrNode
{
public:

	/*
	 * Write node content to string
	 */
	inline unsigned short pop(char *&str, unsigned short &max)
	{
		CHECK_RET_CODE(pos <= max, ERR_MEMORY);
		memcpy(str, this->data, this->pos);
		str += this->pos;
		max -= this->pos;
		return NO_ERR;
	}
	/*
	 * Try to put content on node
	 * pointer and size are actualized
	 */
	void push(const char* &str, unsigned short &str_size, A *mem)
	{
		unsigned short count = MIN(size - pos, str_size);
		if (count == 0)
			return;
		memcpy(&data[pos], str, count);
		pos += count;
		str_size -= count;
		str += count;
	}
	unsigned short getUse()
	{
		return pos;
	}
	unsigned short getFree()
	{
		return (size - pos);
	}
	inline StrNode<A>* getNext()
	{
		return next;
	}

	/*
	 * Get length of string from this segment
	 */
	unsigned short getLength()
	{
		unsigned short len = 0;
		StrNode *n = this;
		while (n)
		{
			len += n->getUse();
			n = n->next;
		}
		return len;
	}

	/*
	 * Create a node to store the required size.
	 * 100 is a minimum size,
	 */
	static StrNode *create(unsigned short size, A *mem)
	{
		StrNode *n;
		size += 100;
		n = (StrNode *) mem->alloc(sizeof(StrNode<A> ) + size);
		CHECK_RET_CODE(n != 0, 0);
		n->init();
		n->setSize(size);
		return n;
	}
	/*
	 * Add a new node after  this
	 */
	unsigned int add(unsigned short size, A *mem)
	{
		if (this == 0)
			return ERR_WRONG_PARAM;
		StrNode *n = create(size, mem);
		CHECK_RET_CODE(n != 0, ERR_MEMORY);
		n->next = next;
		next = n;
		return NO_ERR;
	}

	inline void release(A *mem)
	{
		if (A::canFree())
		{
			if (this == 0)
				return;
			if (next)
				next->release(mem);
			mem->free(this);
		}
	}
private:
	void init()
	{
		next = 0;
		size = 0;
		pos = 0;
	}
	inline void setSize(unsigned short s)
	{
		size = s;
	}
	StrNode<A>* next;
	unsigned char size;	// size
	unsigned char pos;	// write pos
	char data[1];		// string data
};

template<class A = OneRelease>
class StrBuffer
{
public:
	StrBuffer(A &mem)
	{
		this->mem = &mem;
		first = 0;
		last = 0;
	}
	inline void release()
	{
		first->release(mem);
	}
	~StrBuffer()
	{
		release();
	}
	inline unsigned short push(const char* str)
	{
		return push(str, strlen(str));
	}
	unsigned short push(const char* str, unsigned short size)
	{
		if (first == 0)
		{
			first = first->create(size, mem);
			CHECK_RET_CODE(first != 0, ERR_MEMORY);
			last = first;
		}
		while (size)
		{
			last->push(str, size, mem);
			if (size)
			{
				CHECK_ERR_RET(last->add(size,mem));
				last = last->getNext();
			}
		}
		return NO_ERR;
	}
	unsigned short getSize()
	{
		return first->getLength();
	}
	/*
	 * Get all on a buffer
	 * null terminate character will be include
	 */
	unsigned short pop(char* str, unsigned short max_size)
	{
		StrNode<A> *n = first;
		// loop all nodes and copy string
		while (n)
		{
			RET_ON_ERROR(n->pop(str, max_size));
			n = n->getNext();
		}
		CHECK_RET_CODE(max_size, ERR_MEMORY);
		*str = 0;
		return NO_ERR;
	}
	/*
	 * get entire string
	 * a zero is add at the end of string
	 * return size of string no including null terminate
	 */
	unsigned short pop(char* &str, unsigned short &size, A &lmem)
	{
		if (first == 0)
		{
			str = 0;
			size = 0;
			return NO_ERR;
		}
		size = first->getLength() + 1;
		str = (char*) lmem.alloc(size);
		CHECK_ERR_RET(pop(str, size));
		size--;
		return NO_ERR;
	}
private:
	A *mem;
	StrNode<A>* first, *last;
};

#endif /* STRBUFFER_H_ */
