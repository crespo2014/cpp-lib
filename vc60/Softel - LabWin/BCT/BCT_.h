// BCT_.h: interface for the CBCT class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BCT__H__9AD60E38_C915_4E50_992E_77DD32E2BE1D__INCLUDED_)
#define AFX_BCT__H__9AD60E38_C915_4E50_992E_77DD32E2BE1D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\include\labdevice.h"

#define MAX_STR_SIZE 100

class CBCT : public CLabDevice
{
	DWORD _stdcall ProcessData(BYTE *lpData, DWORD dwSize);
	DWORD ResetStatus();
	DWORD _stdcall AddAnalysis();
	DWORD ProcessBlock();

	//
	BYTE	m_status;
	BYTE	m_frameType;
	BYTE	m_frameIndex;
	BYTE	m_frameTopIndex;
	BYTE	m_strPos;
	BYTE	m_lastByte;
	char	m_str[MAX_STR_SIZE];

public:
	CBCT();
	virtual ~CBCT();

};

#endif // !defined(AFX_BCT__H__9AD60E38_C915_4E50_992E_77DD32E2BE1D__INCLUDED_)
