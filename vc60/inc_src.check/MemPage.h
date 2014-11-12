// MemPage.h: interface for the CMemPage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMPAGE_H__536655F1_70B1_458B_96B9_82B078877598__INCLUDED_)
#define AFX_MEMPAGE_H__536655F1_70B1_458B_96B9_82B078877598__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "windows.h"
#include "bobject.h"

class CMemPage  : public CbObject
{
public:
	DWORD LoadFile(const char *file_path);
	DWORD AddStr(char *str,char** pos, DWORD len = 0);
	void Release();
	void* CreatePage(DWORD* maxsize);
	DWORD	GetSize() { return m_page_size; };
	BYTE*	GetPage() { return m_page; };
	BYTE*	GetPtr()  { return m_page_ptr; };
	void SetPtr(BYTE* bptr) { m_page_ptr = bptr; };
	CMemPage();
	virtual ~CMemPage();
	
private:
	BYTE*	m_page;
	DWORD	m_page_size;
	BYTE*	m_page_ptr;	//puntero que indica donde se estan adicionando datos
};

#endif // !defined(AFX_MEMPAGE_H__536655F1_70B1_458B_96B9_82B078877598__INCLUDED_)
