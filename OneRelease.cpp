/*
 * OneRelease.cpp
 *
 *  Created on: 31 Oct 2013
 *      Author: lester
 */

#include "OneRelease.h"
#include "log.h"

OneRelease::OneRelease()
{
	first = 0;
}

void OneRelease::release()
{
	if (first != 0)
	{
		first->release();
		first = 0;
	}
#ifdef _TEST
	log_e(",mem,0");
#endif
}

// store a string
void OneRelease::alloc(const char *str, unsigned int len, char * &new_str)
{
	LinearAlloc **allocator = &first;
	for (;;)
	{
		if (*allocator == 0)
		{
			*allocator = LinearAlloc::create(len + 1);
			break;
		}
		if ((*allocator)->getFree() >= (len + 1))
			break;
		allocator = (*allocator)->getnext();

	}
	(*allocator)->AddString(str, len, new_str);
}
/*
 * reading file more than 65KB it does not work
 */
void* OneRelease::alloc(unsigned int size)
{
#ifdef _TEST
	static unsigned int tot = 0;
	tot += size;
	log_e(",mem,%d", tot);
#endif

	LinearAlloc **allocator = &first;
	for (;;)
	{
		if (*allocator == 0)
		{
			*allocator = LinearAlloc::create(size);
			break;
		}
		if ((*allocator)->getFree() >= size)
			break;
		allocator = (*allocator)->getnext();
	}
	return (*allocator)->get(size);
}

