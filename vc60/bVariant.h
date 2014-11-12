// bVariant.h: interface for the CbVariant class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BVARIANT_H__55BB716C_D4FD_410B_8215_4C9AB6FE758A__INCLUDED_)
#define AFX_BVARIANT_H__55BB716C_D4FD_410B_8215_4C9AB6FE758A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bObject.h"

class CbVariant : public CbObject  
{
public:
	DWORD GetCharString(char* str,WORD max_size);
	VARIANTARG* GetPtr();
	VARIANTARG* GetNewPtr();
	DWORD Release();
	CbVariant();
	virtual ~CbVariant();
	
private:
	VARIANTARG	m_var;
};

#endif // !defined(AFX_BVARIANT_H__55BB716C_D4FD_410B_8215_4C9AB6FE758A__INCLUDED_)
