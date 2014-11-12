// lfc30c02.h: interface for the CShareMessage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LFC30C02_H__D9449AA9_0999_11D5_94E2_00D0093D4380__INCLUDED_)
#define AFX_LFC30C02_H__D9449AA9_0999_11D5_94E2_00D0093D4380__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "lfc30c01.h"   // CMessage

class CShareMessage  
{
public:
	DWORD Initialize();
	CShareMessage();
	~CShareMessage();
public:
	DWORD WaitMessage(DWORD dwTimeout);
	DWORD PeekMessage(S_MESSAGE *pMessage);
	DWORD SendMessage(S_MESSAGE *pMessage);
	DWORD SetMessageClass(CMessage* lpmessage);
	DWORD Release();
	/*
		Variables
	*/
	HANDLE		m_hSendEvent;
	HANDLE		m_hReplyEvent;
	HANDLE		m_hMutex;
	BOOL		m_OnInit;	
	CMessage*	m_lpmessage;

};

#endif // !defined(AFX_LFC30C02_H__D9449AA9_0999_11D5_94E2_00D0093D4380__INCLUDED_)
