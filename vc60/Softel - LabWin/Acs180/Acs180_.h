// Acs180_.h: interface for the CAcs180 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACS180__H__A9273101_C148_40FA_890E_A9E5FCFBB257__INCLUDED_)
#define AFX_ACS180__H__A9273101_C148_40FA_890E_A9E5FCFBB257__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\include\LabDevice.h"

class CAcs180 : public CLabDevice
{
	//
	DWORD _stdcall ProcessData(BYTE *lpData, DWORD dwSize);
	DWORD ResetStatus();
		
	//
	BYTE	m_frametype;
	BYTE	m_status;
	BYTE	m_blockIndex;
	BYTE	m_strPos;
	BYTE	m_lastByte;
	char	m_str[100];

public:
	virtual DWORD _stdcall ProcessField();
	CAcs180();
	virtual ~CAcs180();

};

#endif // !defined(AFX_ACS180__H__A9273101_C148_40FA_890E_A9E5FCFBB257__INCLUDED_)
