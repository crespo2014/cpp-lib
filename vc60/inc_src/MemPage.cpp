// MemPage.cpp: implementation of the CMemPage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MemPage.h"
#include "errorcodes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMemPage::CMemPage()
{
	m_Allocated = 0;
	m_Page = NULL;
	m_Reserved = 0;
}

CMemPage::~CMemPage()
{

}

DWORD CMemPage::Reserved(DWORD dwSize)
{
	Free();
	MEMORY_BASIC_INFORMATION	mbi;
	m_Page = (BYTE*)VirtualAlloc(NULL,dwSize,MEM_RESERVE,PAGE_READWRITE);
	if (m_Page == NULL) return ERR_NOMEMORY;
		
	::VirtualQuery(m_Page,&mbi,sizeof(mbi));
	m_Reserved = mbi.RegionSize;
	m_Allocated = 0;
	return ERR_NONE;
}

DWORD CMemPage::Alloc(DWORD dwSize)
{
	// Usar memoria reservada
	DWORD dr = ERR_NONE;
	MEMORY_BASIC_INFORMATION	mbi;
	if (m_Page == NULL) dr = Reserved(dwSize);
	if (dr != ERR_NONE) return dr;
	if (dwSize > m_Reserved) return ERR_NOMEMORY;	// No hay suficiente memoria reservada
	if (dwSize <= m_Allocated) return ERR_NONE;		// Ya dicha memoria fue localizada
	if (::VirtualAlloc(m_Page,dwSize,MEM_COMMIT,PAGE_READWRITE)== NULL) return ERR_NOMEMORY;
	::VirtualQuery(m_Page,&mbi,sizeof(mbi));
	m_Allocated = mbi.RegionSize;
	return ERR_NONE;
}

DWORD CMemPage::Free()
{
	if (m_Page != NULL) VirtualFree(m_Page,0,MEM_RELEASE);
	m_Page = NULL;
	m_Allocated = 0;
	m_Reserved = 0;
	return ERR_NONE;
}

