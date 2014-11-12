/*
 * StrList.cpp
 *
 *  Created on: 13 Aug 2013
 *      Author: lester
 */

#include "StrList.h"
#include "string.h"
#include "os.h"
#include "log.h"

StrList::StrList(MemPage* mem)
{
	this->mem = mem;
	this->f_node = 0;
	save_space = 0;
	waste_space = 0;
	string_count = 0;
}

StrList::~StrList()
{

}

void StrList::clear()
{
	f_node = 0;
}

/*!
 get a new node to store a string of size = size
 */

struct _str_node* StrList::newNode(struct _str_node* next, const char* val, unsigned short size)
{
	struct _str_node* p;
	waste_space += (sizeof(*p) - sizeof(p->c));	// by overhead string with structure

	mem->Get(sizeof(*p) - sizeof(p->c) + size + 1, (void**) &p);
	p->next = next;
	p->size = size;
	*p->c = 0;
	strncat(p->c, val, size);
	return p;
}

/*!
 always compare with the next node
 */

void StrList::push(const char* val, unsigned short size, char* &str)
{
	int ir;
	struct _str_node *node, *n;

	string_count++;
	n = 0;
	str = 0;
	// compare with first node
	// check size
	if (f_node)
	{
		if (size == f_node->size)
			ir = strncmp(f_node->c, val, size);
		else if (size < f_node->size)
			ir = 1;
		else
			ir = -1;
	} else
		ir = 1;

	// there is not first node or  new value is below order than first node
	if ((!f_node) || (ir > 0))
	{
		n = newNode(f_node, val, size);
		f_node = n;
	} else if (ir == 0)
	{
		// string has been found
		save_space+= (size +1);		// but reusing string
		n = f_node;
	} else
	{
		// compare with other nodes
		for (node = f_node; node->next; node = node->next)
		{
			if (node->next->size == size)
			{
				if ((ir = strncmp(node->next->c, val, size)) == 0)
				{
					// string has been found
					save_space+= (size +1); 	// but reusing string
					n = node->next;
					break;
				}
				if (ir > 0)
					break;
			} else if (size < node->next->size)
				break;
		}
		// end of list reached or node is below in list
		if (!n)
		{
			n = newNode(node->next, val, size);
			node->next = n;
		}

	}
	str = n->c;
}

void StrList::Print()
{
	log_d("Pushed %d strings, wasted %d bytes, saved %d bytes",string_count,waste_space,save_space);
	struct _str_node *node;
	for (node = f_node; node; node = node->next)
	{
		//printf("%s\n",node->c);
	}
}

