
#include "stdafx.h"
#include "errorcodes.h"
#include "_IUnknown.h"


DWORD _stdcall DLLCreateInstance(void** lpInstance,void* lpClass,DWORD wClassSize)
{
	HANDLE hHeap = GetProcessHeap();
	if (hHeap == NULL)
	{
		return ERR_APIFAIL;
	}
	*lpInstance = (_IUnknown*)HeapAlloc(hHeap,HEAP_ZERO_MEMORY,wClassSize);
	DWORD test = HeapSize(hHeap,0,*lpInstance);
	if (*lpInstance == NULL) return ERR_APIFAIL;
	// Tabla de funciones virtuales
	memcpy(*lpInstance,lpClass,wClassSize);
	return ERR_NONE;
}

DWORD _stdcall DLLDestroyInstance(void* lpInstance)
{
	HANDLE hHeap = GetProcessHeap();
	if (hHeap == NULL)
	{
		return ERR_APIFAIL;
	}
	if (!HeapFree(hHeap,0,lpInstance))
		return ERR_APIFAIL;
	return ERR_NONE;
}