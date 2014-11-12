// g30c05.h: interface for the CDXMaterial class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_G30C05_H__F6975481_1574_11D5_8D01_00D0093D4380__INCLUDED_)
#define AFX_G30C05_H__F6975481_1574_11D5_8D01_00D0093D4380__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDXMaterial  
{
public:
	DWORD Release();
	DWORD Initialize();
	CDXMaterial();
	virtual ~CDXMaterial();
	CDXMaterial	*m_next,*m_prev;

};

#endif // !defined(AFX_G30C05_H__F6975481_1574_11D5_8D01_00D0093D4380__INCLUDED_)
