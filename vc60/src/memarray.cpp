// memarray.cpp: implementation of the Cpep class.
//
//////////////////////////////////////////////////////////////////////

#include "memarray.h"


#define _FILENAME_ "memarray.c"

//////////////////////////////////////////////////////////////////////
// CMemArray Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMemArray::CMemArray()
{
	ClearData();
	m_max_reserved = 1024*1024;
	m_ver = "Class CMemArray " CLASS_VER;
}

CMemArray::~CMemArray()
{
	Release();
}

DWORD CMemArray::SetSize(DWORD new_size)
{
	MEMORY_BASIC_INFORMATION	mbi;
	if (m_mem == NULL)
	{
		// reservar el rango de direcciones
		m_mem = (BYTE*)VirtualAlloc(NULL,m_max_reserved,MEM_RESERVE,PAGE_READWRITE);
		if (m_mem == NULL) return LOG_TW32_ERROR GetLastError(),ERR_API,"VirtualAlloc Reserve (%X)",m_max_reserved);
		::VirtualQuery(m_mem,&mbi,sizeof(mbi));
		m_max_reserved = mbi.RegionSize;
		m_max_commit = 0;
	}
	if (new_size > m_max_commit)
	{
		if (VirtualAlloc(m_mem,new_size,MEM_COMMIT,PAGE_READWRITE) == NULL) return LOG_TW32_ERROR GetLastError(),ERR_API,"VirtualAlloc Commit (%X)",new_size);
		::VirtualQuery(m_mem,&mbi,sizeof(mbi));
		m_max_commit = mbi.RegionSize;
	}
	m_mem_size = new_size;
	return ERR_OK;
}


DWORD CMemArray::SetMaxMemorySize(DWORD max_size)
{
	if (m_mem == NULL) m_max_reserved = max_size;
	return 0;
}

void* CMemArray::GetElementAt(WORD index)
{
	DWORD pos;
	pos = index*m_element_size;
	if (index >= m_element_count) return NULL;
	if (pos >= m_max_commit) return NULL;
	return &m_mem[pos];
}

DWORD CMemArray::Release()
{
	BOOL	br;

	if (m_mem == NULL) return ERR_OK;
	br = VirtualFree(m_mem,0,MEM_RELEASE);
	if (!br) return LOG_TW32_ERROR GetLastError(),ERR_API,"VirtualFree ");
	ClearData();
	return ERR_OK;
}

void CMemArray::ClearData()
{
	m_max_commit = 0;
	m_mem_size = 0;
	m_element_count = 0;
	m_element_size = 1;
	m_mem = NULL;
}


DWORD CMemArray::LoadFile(const char *file_path)
{
	HANDLE	hFile;
	BOOL	br;
	DWORD	fsize;
	DWORD	bread;

	hFile = CreateFile(file_path,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if (hFile == INVALID_HANDLE_VALUE) 
		return LOG_TW32_ERROR GetLastError(),ERR_API,"CreateFile (%s)",file_path);
	fsize = GetFileSize(hFile,NULL);
	Release();
	if (fsize == 0) return ERR_OK;
	SetMaxMemorySize(fsize+1);
	SetSize(fsize);

	br = ReadFile(hFile,m_mem,fsize,&bread,NULL);
	CloseHandle(hFile);
	if (!br) 
	{
		Release();
		return LOG_TW32_ERROR GetLastError(),ERR_API,"ReadFile (%d) ",fsize);
	}
	m_mem[bread] = 0;
	return ERR_OK;
}
