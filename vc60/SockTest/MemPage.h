// MemPage.h: interface for the CMemPage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMPAGE_H__876DB06C_30CD_4F14_A355_C674A9C70F89__INCLUDED_)
#define AFX_MEMPAGE_H__876DB06C_30CD_4F14_A355_C674A9C70F89__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMemPage  
{
public:
	DWORD Size() {return m_Allocated;};
	DWORD Free();
	DWORD Alloc(DWORD dwSize);
	DWORD Reserved(DWORD dwSize);
	CMemPage();
	virtual ~CMemPage();
	operator BYTE*()  const {return m_Page;};
	operator char*()  const {return (char*)m_Page;};
private:
	DWORD	m_Reserved;
	DWORD	m_Allocated;
	BYTE*	m_Page;
};

#endif // !defined(AFX_MEMPAGE_H__876DB06C_30CD_4F14_A355_C674A9C70F89__INCLUDED_)
