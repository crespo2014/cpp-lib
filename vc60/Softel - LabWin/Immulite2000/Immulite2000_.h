// Immulite2000_.h: interface for the CImmulite2000 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMMULITE2000__H__AE24EBDB_013B_47C4_8420_87EC9FDCBD90__INCLUDED_)
#define AFX_IMMULITE2000__H__AE24EBDB_013B_47C4_8420_87EC9FDCBD90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\include\labdevice.h"

#define MAX_STR_SIZE 100

class CImmulite2000  : public CLabDevice
{
	
	DWORD _stdcall ProcessData(BYTE *lpData, DWORD dwSize);
	DWORD ResetStatus();
	DWORD AddAnalysis();
	DWORD ProcessBlock();
		
	//
	BYTE	m_blockIndex;
	BYTE	m_strPos;
	BYTE	m_lastByte;
	char	m_str[MAX_STR_SIZE];

public:
	CImmulite2000();
	virtual ~CImmulite2000();

};

#endif // !defined(AFX_IMMULITE2000__H__AE24EBDB_013B_47C4_8420_87EC9FDCBD90__INCLUDED_)
