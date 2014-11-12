// HeapMem.h: interface for the CHeapMem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HEAPMEM_H__62913A5A_2401_4FDE_8539_D563B839877A__INCLUDED_)
#define AFX_HEAPMEM_H__62913A5A_2401_4FDE_8539_D563B839877A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bObject.h"

class CHeapMem  : public CbObject
{
public:
	DWORD setStr(char* str,DWORD size = 0);
	DWORD setData(void* pData,DWORD dwsize);
	DWORD Alloc(DWORD size);
	void Release();
	DWORD SetHeap(HANDLE hHeap);
	CHeapMem();
	virtual ~CHeapMem();
	BYTE*	getBytes()	{ return (BYTE*) m_ptr; };
	char*	getStr()	{ return (char*) m_ptr; };
	unsigned short*	getUShort() { return (unsigned short*) m_ptr; };
private:
	HANDLE	m_hHeap;
	DWORD	m_size;
	void*	m_ptr;
};

#endif // !defined(AFX_HEAPMEM_H__62913A5A_2401_4FDE_8539_D563B839877A__INCLUDED_)
