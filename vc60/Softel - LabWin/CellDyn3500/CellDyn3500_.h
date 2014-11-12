// CellDyn3500_.h: interface for the CCellDyn3500 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CELLDYN3500__H__586D9031_FD2A_44A8_A003_FC0715E507E5__INCLUDED_)
#define AFX_CELLDYN3500__H__586D9031_FD2A_44A8_A003_FC0715E507E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\include\labdevice.h"

#define MAX_STR_SIZE 100

class CCellDyn3500 : public CLabDevice
					
{
	//
	DWORD _stdcall ProcessData(BYTE *lpData, DWORD dwSize);
	DWORD ResetStatus();
	DWORD AddAnalysis();
	DWORD ProcessBlock();
		
	//
	BYTE	m_blockIndex;
	BYTE	m_strPos;
	BYTE	m_lastByte;
	char	m_str[MAX_STR_SIZE];
	BYTE	m_status;

public:
	CCellDyn3500();
	virtual ~CCellDyn3500();

};

#endif // !defined(AFX_CELLDYN3500__H__586D9031_FD2A_44A8_A003_FC0715E507E5__INCLUDED_)
