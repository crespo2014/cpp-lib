// Dimension_AR.h: interface for the CDimension_AR class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIMENSION_AR_H__F9985B72_1CA0_4476_AA05_88CE19F4CC95__INCLUDED_)
#define AFX_DIMENSION_AR_H__F9985B72_1CA0_4476_AA05_88CE19F4CC95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\include\labdevice.h"

#define MAX_STR_POS	50

class CDimension_AR	: public CLabDevice
{
	//
	DWORD _stdcall ProcessData(BYTE *lpData, DWORD dwSize);
	DWORD ResetStatus();
	DWORD AddAnalysis();
	DWORD ProcessBlock();
		
	// 
	BYTE	m_status;
	BYTE	m_blockIndex;	// Indica en que separador esta 
	BYTE	m_strpos;		// proxima posicion del string a llenar
	char	m_str[MAX_STR_POS];
	BYTE	m_anacant;

public:
	CDimension_AR();
	virtual ~CDimension_AR();

};

#endif // !defined(AFX_DIMENSION_AR_H__F9985B72_1CA0_4476_AA05_88CE19F4CC95__INCLUDED_)
