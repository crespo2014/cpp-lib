/*
 * MemManager.cpp
 *
 *  Created on: 5 Sep 2013
 *      Author: lester
 */

#include "MemManager.h"
#include "string.h"
#include "log.h"

//#define log_e(...)

// align to the next integer
#define ALIGN_NEXT(x)  x = (x + (sizeof(int) - 1) )  & ~(sizeof(int) - 1);

MemManager::MemManager()
{
	mem = 0;
	size = 0;
	wr_pos = 0;
	flag = 0;
}
MemManager::MemManager(void* mem, unsigned short size) : mem(mem) , size(size), wr_pos(0), flag(0)
{

}

MemManager::~MemManager()
{

}

void MemManager::AddString(const char *str, int len, char **ppBuffer)
{
	if (!str)
	{
		*ppBuffer = 0;
		return;
	}
	char *cptr;
	if (len == 0)
		len = strlen(str);
	Get(len + 1, (void**) &cptr, false);
	if (ppBuffer) *ppBuffer = cptr;
	if (str != NULL)
	{
		memcpy(cptr, str, len);
		cptr[len] = 0;
	}
}

void MemManager::Get(int size, void **ppBuffer, bool align)
{
	if (flag & MM_F_LOCK)
	{
		throw error_api(ERROR_INFO(),api_error::get_locked());
	}
	if (align)
	{
		wr_pos = (wr_pos + sizeof(int) -1) & ~(sizeof(int) - 1);
	}
	if (wr_pos + size >= this->size)
	{
		throw error_api(ERROR_INFO(),api_error::get_not_enough_memory());
	}
	*ppBuffer = &((unsigned char*) mem)[wr_pos];
	wr_pos += size;
}

void MemManager::lockRemained(void* &buffer, unsigned short &size)
{
	ALIGN_NEXT(wr_pos);
	flag |= MM_F_LOCK;
	buffer = &((unsigned char*) mem)[wr_pos];
	size = this->size - wr_pos;
}

void	MemManager::lockConsolidation(unsigned short size)
{
	//FIX

}
