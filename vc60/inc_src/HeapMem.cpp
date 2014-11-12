// HeapMem.cpp: implementation of the CHeapMem class.
//
//////////////////////////////////////////////////////////////////////

#include "HeapMem.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHeapMem::CHeapMem()
{
	m_hHeap = NULL;
	m_ptr = NULL;
	m_size = 0;
}

CHeapMem::~CHeapMem()
{
	Release();
}

DWORD CHeapMem::SetHeap(HANDLE hHeap)
{
	Release();
	m_hHeap = hHeap;
	return ERR_OK;
}

void CHeapMem::Release()
{
	if (m_ptr != NULL) HeapFree(m_hHeap,0,m_ptr);
	m_ptr = NULL;
	m_size = 0;
}

DWORD CHeapMem::Alloc(DWORD size)
{
	char	*fnc_name = "CHeapMem::Alloc";
	Release();
	if (m_hHeap == NULL) m_hHeap = GetProcessHeap();
	m_ptr = HeapAlloc(m_hHeap,0,size);
	if (m_ptr == NULL)
	{
		return log_w32error GetLastError(),ERR_API,"HeapAlloc (%d) ",size);
	}
	return ERR_OK;
}

DWORD CHeapMem::setData(void *pData, DWORD dwsize)
{
	char	*fnc_name = "CHeapMem::setData";
	if (Alloc(dwsize) != ERR_OK) return LOG_TSTACK;
	memcpy(m_ptr,pData,dwsize);
	return ERR_OK;
}

DWORD CHeapMem::setStr(char *str, DWORD size)
{
	char	*fnc_name = "CHeapMem::setStr";
	if (size == 0) size = strlen(str);
	if (str == NULL) return LOG_TERROR ERR_PARAM,"null pointer error");
	if (Alloc(size+1) != ERR_OK) return LOG_TSTACK;
	memcpy(m_ptr,str,size);
	((char*)m_ptr)[size] = 0;
	return ERR_OK;	
}
