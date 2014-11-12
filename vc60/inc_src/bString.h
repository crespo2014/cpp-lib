// bString.h: interface for the CbString class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BSTRING_H__B09F6461_009D_4E31_9704_E3414068CF3F__INCLUDED_)
#define AFX_BSTRING_H__B09F6461_009D_4E31_9704_E3414068CF3F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bObject.h"

class CbString : public CbObject  
{
public:
	BYTE* GetBuffer() { return (BYTE*)m_str; };
	void Release();
	DWORD SetStr(char* str);
	char	*str() { return m_str;};
	char* GetStr();
	DWORD NewStr(WORD size);
	CbString();
	virtual ~CbString();

private:	
	char	*m_str;
	WORD	m_len;

};

#endif // !defined(AFX_BSTRING_H__B09F6461_009D_4E31_9704_E3414068CF3F__INCLUDED_)
