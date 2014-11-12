// VirtualMem.cpp: implementation of the CVirtualMem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VirtualMem.h"
#include "errorcodes.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVirtualMem::CVirtualMem()
{
	m_Commit = 0;
	m_LastError = 0;
	m_MaxSize = 0;
	m_MemBuffer = NULL;
	m_Size = 0;
}

CVirtualMem::~CVirtualMem()
{
	Release();
}

DWORD CVirtualMem::SetMaxSize(DWORD dwMaxSize)
{
	if (m_MemBuffer) Free();
	m_MaxSize = dwMaxSize;
	return 0;
}

DWORD CVirtualMem::Free()
{
	// Liberar toda la memoria
	if (m_MemBuffer)
		VirtualFree(m_MemBuffer,0,MEM_RELEASE);
	m_MemBuffer = NULL;
	m_Size = 0;
	m_Commit = 0;
	return 0;
}

DWORD CVirtualMem::AddBuffer(BYTE *lpBuffer, DWORD dwSize)
{
	// adicionar un buffer de datos
	DWORD Size = m_Size;
	DWORD dr;
	dr = SetSize(m_Size+dwSize);
	if (dr != 0) return dr;
	memcpy(&m_MemBuffer[Size],lpBuffer,dwSize);
	return ERR_NONE;
}

DWORD CVirtualMem::IncSize(DWORD dwOffset)
{
	// Incrementar el tamaño de la memoria
	return SetSize(m_Size+dwOffset);
}

DWORD CVirtualMem::SetSize(DWORD dwSize)
{
	// Poner el tamaño de la memoria
	m_LastError = 0;
	if (dwSize == 0) return Free();
	if (dwSize > m_MaxSize) return ERR_NOMEMORY;
	if ((dwSize > m_Size)&&(dwSize < m_Commit))
	{
		m_Size = dwSize;
		return ERR_NONE;
	}
	MEMORY_BASIC_INFORMATION	mbi;
	if (m_MemBuffer == NULL) 
	{
		m_MemBuffer = (BYTE*)VirtualAlloc(NULL,m_MaxSize,MEM_RESERVE,PAGE_READWRITE);
		if (m_MemBuffer == NULL) 
		{
			m_LastError = GetLastError();
			return ERR_NOMEMORY;
		}
		::VirtualQuery(m_MemBuffer,&mbi,sizeof(mbi));
		m_MaxSize = mbi.RegionSize;
	}
	DWORD request;
	if (m_MaxSize - m_Commit > 1024*1024) 
		request = m_Commit + 1024*1024;		//reservar de 1M en 1M
	else 
		request = dwSize;
	if (::VirtualAlloc(m_MemBuffer,request,MEM_COMMIT,PAGE_READWRITE)== NULL)
	{
		m_Size = 0;
		m_LastError = GetLastError();
		return ERR_NOMEMORY;
	}
	::VirtualQuery(m_MemBuffer,&mbi,sizeof(mbi));
	m_Size = dwSize;
	m_Commit = mbi.RegionSize;
	return ERR_NONE;
}


DWORD CVirtualMem::Release()
{
	Free();
	return 0;
}

