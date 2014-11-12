// Selectra_.h: interface for the CSelectra class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SELECTRA__H__D50A0196_568D_4A9A_8D94_3F58DF4D3FB3__INCLUDED_)
#define AFX_SELECTRA__H__D50A0196_568D_4A9A_8D94_3F58DF4D3FB3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\include\labdevice.h"

#define MAX_STR_SIZE 100

class CSelectra :	public CLabDevice 
{
	DWORD _stdcall ProcessData(BYTE *lpData, DWORD dwSize);
	DWORD ResetStatus();
	DWORD AddAnalysis();
	DWORD ProcessBlock();
		
	//
	BYTE	m_status;
	BYTE	m_blockIndex;
	BYTE	m_strPos;
	BYTE	m_lastByte;
	char	m_str[MAX_STR_SIZE];

public:
	CSelectra();
	virtual ~CSelectra();

};

#endif // !defined(AFX_SELECTRA__H__D50A0196_568D_4A9A_8D94_3F58DF4D3FB3__INCLUDED_)
