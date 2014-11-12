// MemStack.h: interface for the CMemStack class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMSTACK_H__AADF43D0_E3E5_442F_9FF1_2DD1E2AB2BFF__INCLUDED_)
#define AFX_MEMSTACK_H__AADF43D0_E3E5_442F_9FF1_2DD1E2AB2BFF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bObject.h"

class CMemStack : public CbObject
{
public:
	DWORD Get(int size,void** ppBuffer,int align32);
	DWORD AddString(char* str,int len,char** ppBuffer);
	void Init();
	DWORD Initialize(void* stack,DWORD size);
	CMemStack();
	virtual ~CMemStack();

private:
	int		m_binit;
	char	*m_wptr;
	DWORD	m_maxlen;
	char	*m_data_ptr;
};

#endif // !defined(AFX_MEMSTACK_H__AADF43D0_E3E5_442F_9FF1_2DD1E2AB2BFF__INCLUDED_)
