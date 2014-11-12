// Buffer.cpp: implementation of the CBuffer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Buffer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBuffer::CBuffer()
{
	m_dwEnd = 0;
	m_dwStart = 0;
	m_pBuffer = NULL;
	m_dwSize = 0;
}

CBuffer::~CBuffer()
{
	if (m_pBuffer) VirtualFree(m_pBuffer,0,MEM_RELEASE);
}

DWORD CBuffer::AddBuffer(BYTE *pBuffer, DWORD dwSize, DWORD *pdwPos)
{

}

DWORD CBuffer::GetWritePos(DWORD *pdwPos)
{

}

DWORD CBuffer::GetWriteBuffer(BYTE **ppbBuffer, DWORD *dwSize)
{

}

DWORD CBuffer::SetSize(DWORD dwSize)
{
	if (m_pBuffer) VirtualFree(m_pBuffer,0,MEM_RELEASE);
	MEMORY_BASIC_INFORMATION	mbi;
	m_pBuffer = (BYTE*)VirtualAlloc(NULL,dwSize,MEM_COMMIT,PAGE_READWRITE);
	if (m_pBuffer == NULL) 
	{
		//m_LastError = GetLastError();
		return ERR_NOMEMORY;
	}
	::VirtualQuery(m_MemBuffer,&mbi,sizeof(mbi));
	m_dwSize= mbi.RegionSize;
	return ERR_NONE;
}
