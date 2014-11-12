// BFA_.h: interface for the CBFA class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BFA__H__8F7CD150_4231_4184_8037_0B981721E99F__INCLUDED_)
#define AFX_BFA__H__8F7CD150_4231_4184_8037_0B981721E99F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\include\labdevice.h"


#define MAX_STR_SIZE 100

class CBFA : public CLabDevice
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
	CBFA();
	virtual ~CBFA();

};

#endif // !defined(AFX_BFA__H__8F7CD150_4231_4184_8037_0B981721E99F__INCLUDED_)
