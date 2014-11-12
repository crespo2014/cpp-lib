// MemShare.cpp: implementation of the CMemShare class.
//
//////////////////////////////////////////////////////////////////////

#include "MemShare.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMemShare::CMemShare()
{
	m_hfile = NULL;
	m_pmem = NULL;
	m_mem_size = 0;	
}

CMemShare::~CMemShare()
{
	Release();
}

DWORD CMemShare::Create(char *mem_name, DWORD mem_size)
{
	char	*fnc_name = "CMemShare::Create";
	DWORD	dwr;
	if (m_pmem != NULL) return LOG_TERROR ERR_FATAL,"Share mem is already open");
	m_mem_size = mem_size;
	m_hfile = CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,mem_size,mem_name);
	if (m_hfile == NULL) 
		return LOG_TW32_ERROR  GetLastError(),ERR_API,"CreateFileMapping (%s,%u) ",mem_name,mem_size);
	m_pmem = MapViewOfFile(m_hfile,FILE_MAP_ALL_ACCESS,0,0,0);
	if (m_pmem != NULL) return ERR_OK;
	dwr = GetLastError();
	Release();
	return LOG_TW32_ERROR  GetLastError(),ERR_API,"CMemShare::Create ... MapViewOfFile ");
}

void CMemShare::Release()
{
	char	*fnc_name = "CMemShare::Release";
	if (m_pmem != NULL) 
		if (!UnmapViewOfFile(m_pmem)) LOG_TW32_ERROR  GetLastError(),ERR_API,"UnmapViewOfFile");
	if (m_hfile != NULL)
		if (!CloseHandle(m_hfile)) LOG_TW32_ERROR  GetLastError(),ERR_API,"CloseHandle");
	m_hfile = NULL;
	m_pmem = NULL;
	m_mem_size = 0;
}

DWORD CMemShare::Open(char *mem_name)
{
	char	*fnc_name = "CMemShare::Open";
	DWORD	dwr;
	m_hfile = OpenFileMapping(FILE_MAP_ALL_ACCESS,FALSE,mem_name);
	if (m_hfile == NULL) 
		return LOG_TW32_ERROR  GetLastError(),ERR_API,"OpenFileMapping (%s) ",mem_name);
	m_pmem = MapViewOfFile(m_hfile,FILE_MAP_ALL_ACCESS,0,0,0);
	if (m_pmem != NULL) return ERR_OK;
	dwr = GetLastError();
	Release();
	return LOG_TW32_ERROR  GetLastError(),ERR_API,"MapViewOfFile ");

}

