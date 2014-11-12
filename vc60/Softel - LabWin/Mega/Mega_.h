// Mega_.h: interface for the CMega class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEGA__H__36C5E90E_501B_4EFF_AA06_393AE701C6E2__INCLUDED_)
#define AFX_MEGA__H__36C5E90E_501B_4EFF_AA06_393AE701C6E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\include\labdevice.h"

#define MAX_STR_SIZE 100

class CMega  : public CLabDevice
{
	//
	DWORD _stdcall ProcessData(BYTE *lpData, DWORD dwSize);
	DWORD ResetStatus();
	DWORD AddAnalysis();
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
	CMega();
	virtual ~CMega();

};

#endif // !defined(AFX_MEGA__H__36C5E90E_501B_4EFF_AA06_393AE701C6E2__INCLUDED_)
