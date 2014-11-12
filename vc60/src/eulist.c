#include "eulist.h"


DWORD	eu_list_init(struct _EU_LIST *pthis,void* pmem,DWORD size)
{
	const char	*fnc_name = "eu_list_init";

	memset(pthis,0,sizeof(struct _EU_LIST));
	pthis->first = NULL;
	pthis->last = NULL;
	pthis->stack = pmem;
	if (MemStack_Init(pthis->stack,size) != ERR_OK) return LOG_TSTACK;
	return ERR_OK;
}