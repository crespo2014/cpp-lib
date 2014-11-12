// MemShare.h: interface for the CMemShare class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMSHARE_H__ED43D91B_AD08_41BF_A5C3_91E260941268__INCLUDED_)
#define AFX_MEMSHARE_H__ED43D91B_AD08_41BF_A5C3_91E260941268__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bobject.h"

class CMemShare : public CbObject  
{
public:
	void* GetMem() { return m_pmem; };
	DWORD Open(char* mem_name);
	void Release();
	DWORD Create(char* mem_name,DWORD mem_size);
	CMemShare();
	virtual ~CMemShare();

private:
	void*	m_pmem;
	DWORD	m_mem_size;
	HANDLE	m_hfile;

};

#endif // !defined(AFX_MEMSHARE_H__ED43D91B_AD08_41BF_A5C3_91E260941268__INCLUDED_)
