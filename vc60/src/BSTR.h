// BSTR.h: interface for the CBSTR class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BSTR_H__E13D29BB_BAA4_4C67_8C79_98785A8B75D6__INCLUDED_)
#define AFX_BSTR_H__E13D29BB_BAA4_4C67_8C79_98785A8B75D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/*
	Necesito un imen para guardar los datos que me solicitan.

*/

#include "bObject.h"
#include "imem.h"

class CbBSTR : public CbObject  
{
public:
	WCHAR* getWCHAR(IMem* mem);
	static LPWSTR toUnicode(char* str,IMem* mem);
	static char* toChar(LPWSTR str,DWORD cbMultiByte,IMem* mem);
	
	char* getASCII(IMem* mem);

	BSTR* GetNewPtr();
	DWORD SetWCharString(WCHAR* wchar);
	
	BSTR	_BSTR()  { return m_bstr; };
	WCHAR*	_WCHAR() { return m_bstr; };
	DWORD	SetCharString(char* str);
	char*	GetChar();
	DWORD	GetCharString(char* cstr, WORD maxsize);
	void	Release();
	BSTR	Dettach();
	void	Attach(BSTR bstr);
	DWORD	getSize() { return m_bstr_size; }

	CbBSTR(char* cstr);
	CbBSTR(WCHAR* wchar);
	CbBSTR();
	virtual ~CbBSTR();
private:
	BSTR	m_bstr;
	UINT	m_bstr_size;	
	char	m_cstr[255];	// temporal

};

#endif // !defined(AFX_BSTR_H__E13D29BB_BAA4_4C67_8C79_98785A8B75D6__INCLUDED_)
