// Microscan2Way_.h: interface for the CMicroscan2Way class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MICROSCAN2WAY__H__AC082336_B2E0_4DDA_A3AF_C350D6594D64__INCLUDED_)
#define AFX_MICROSCAN2WAY__H__AC082336_B2E0_4DDA_A3AF_C350D6594D64__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\include\labdevice.h"

class CMicroscan2Way : public CLabDevice 
{
	
	//
	DWORD _stdcall ProcessData(BYTE *lpData, DWORD dwSize);
	DWORD ResetStatus();
	DWORD AddAnalysis();
	DWORD ProcessBlock();
	
	//
	BYTE	m_frametype;
	BYTE	m_status;
	BYTE	m_blockIndex;
	BYTE	m_strPos;
	BYTE	m_lastByte;
	char	m_str[100];

public:
	CMicroscan2Way();
	virtual ~CMicroscan2Way();

};

#endif // !defined(AFX_MICROSCAN2WAY__H__AC082336_B2E0_4DDA_A3AF_C350D6594D64__INCLUDED_)
