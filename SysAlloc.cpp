/*
 * SysAlloc.cpp
 *
 *  Created on: 9 Nov 2013
 *      Author: lester
 */

#include "SysAlloc.h"

SysAlloc::SysAlloc()
{

}

SysAlloc::~SysAlloc()
{
}

#ifdef _TEST
static unsigned int tot = 0;
#endif

void* SysAlloc::alloc(unsigned short size)
{
#ifdef _TEST
	char *p = new char[size + sizeof(int)];
	*((int*)p) = size;
	tot += size;
	log_e(",mem,%d", tot,p);
	p += sizeof(int);
	return p;
#else
	return new char[size];
#endif
}

void SysAlloc::free(void* p)
{
#ifdef _TEST
	char *i = (char*)p;
	i-= sizeof(int);
	tot -= ((int*)i)[0];
	log_e(",mem,%d", tot,i);
	delete[] i;
#else
	char *i = (char*)p;
	delete[] i;
#endif
}
