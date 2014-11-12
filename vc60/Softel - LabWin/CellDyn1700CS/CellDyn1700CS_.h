// CellDyn1700CS_.h: interface for the CCellDyn1700CS class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CELLDYN1700CS__H__88D50960_32AD_45B1_A5B9_64B7DC0112BF__INCLUDED_)
#define AFX_CELLDYN1700CS__H__88D50960_32AD_45B1_A5B9_64B7DC0112BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\include\labdevice.h"

#define MAX_STR_SIZE 100

class CCellDyn1700CS  : public CLabDevice
{
	//
	DWORD _stdcall ProcessData(BYTE *lpData, DWORD dwSize);
	DWORD ResetStatus();
	DWORD AddAnalysis();
	DWORD ProcessBlock();
		
	BYTE	m_blockIndex;
	BYTE	m_strPos;
	BYTE	m_lastByte;
	char	m_str[MAX_STR_SIZE];
	BOOL	m_onstr;			//se esta procesando un string
	BYTE	m_status;

public:
	CCellDyn1700CS();
	virtual ~CCellDyn1700CS();

};

#endif // !defined(AFX_CELLDYN1700CS__H__88D50960_32AD_45B1_A5B9_64B7DC0112BF__INCLUDED_)
