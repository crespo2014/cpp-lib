// Axsym_.h: interface for the CAxsym class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AXSYM__H__95ACA4DD_15AC_4D41_8D38_27EC5324898A__INCLUDED_)
#define AFX_AXSYM__H__95ACA4DD_15AC_4D41_8D38_27EC5324898A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\include\labdevice.h"

class CAxsym  : public CLabDevice
{
	DWORD _stdcall ProcessData(BYTE *lpData, DWORD dwSize);
	DWORD ResetStatus();
	DWORD _stdcall AddAnalysis();
	DWORD ProcessBlock();
		
	//
	BYTE	m_frametype;
	BYTE	m_status;
	BYTE	m_blockIndex;
	BYTE	m_strPos;
	BYTE	m_lastByte;
	char	m_str[100];

public:
	CAxsym();
	virtual ~CAxsym();

};

#endif // !defined(AFX_AXSYM__H__95ACA4DD_15AC_4D41_8D38_27EC5324898A__INCLUDED_)
