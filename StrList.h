/*
 * StrList.h
 *
 *  Created on: 13 Aug 2013
 *      Author: lester
 */

#ifndef STRLIST_H_
#define STRLIST_H_

#include "MemPage.h"

/*!
 char* values will be store on nodes.
 the nodes will on a list
 use sizeof - sizeof (a)
 */

struct _str_node
{
	struct _str_node* next;
	unsigned short size;
	char c[2];
};
/*!

 Alphabetical ordered string list
 this object store char* ordered alphabetically
 main idea is save memory reusing similar strings values.
 JSON objects have this characteristic
 */

class StrList
{
public:
	StrList(MemPage* mem);
	virtual ~StrList();
	void push(const char* val, unsigned short size, char* &str);
	void clear();
	void Print();
private:
	MemPage *mem;
	struct _str_node* f_node;    // first node
	struct _str_node*newNode(struct _str_node* next, const char* val, unsigned short size);
	unsigned int save_space;
	unsigned int waste_space;
	unsigned int string_count;    // how many string has been push
};

/*
 * TODO ; string iterators
 * zstring iterator end = (null) compare (a==b) or (*a == 0) && (b==null)
 * lstring iterator easy way
 */

class zstring
{
	class iterator
	{
		iterator() :
				ptr(0)
		{
		}
		iterator(char * p) :
				ptr(p)
		{

		}
		iterator(const iterator& it) : ptr(it.ptr){

		}
		bool operator==(const iterator& it)
		{
			return ((ptr == it.ptr) || ((ptr == 0) && (*it.ptr == 0)));
		}
		bool operator>(const iterator& it)
		{
			return ((ptr == 0) || (ptr > it.ptr));
		}
		bool operator<(const iterator& it)
		{
			return ((ptr != 0) && (ptr < it.ptr));
		}
		void operator++()
		{
			++ptr;
		}
		iterator operator++(int)
		{
			return (*this).ptr++;
			/*
			iterator i = *this;
			ptr++;
			return i;
			*/
		}
	char* ptr;
};
};

#endif /* STRLIST_H_ */
