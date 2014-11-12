/*
 * Page.cpp
 *
 *  Created on: 19 Jun 2014
 *      Author: lester.crespo
 */

#ifdef _WIN32

#include <Page.h>

Page::Page()
{
	// TODO Auto-generated constructor stub

}

Page::~Page()
{
	// TODO Auto-generated destructor stub
}

void Page::release()
{
	if (next != 0)
		next->release();
	//CHECK_TRACE_API(munmap(this,size) == 0);
}

#endif
