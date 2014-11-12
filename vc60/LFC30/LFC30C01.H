// lfc30c01.h: interface for the CMessage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LFC30C01_H__4FA91FB5_078F_11D5_94DA_00D0093D4380__INCLUDED_)
#define AFX_LFC30C01_H__4FA91FB5_078F_11D5_94DA_00D0093D4380__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "lfc30def.h"

class LFC30_API CMessage  
{
public:
	DWORD Release();
	DWORD Initialize();
	CMessage();
	virtual ~CMessage();
public:
	DWORD PeekMessage(S_MESSAGE *pMessage);
	DWORD WaitMessage(DWORD dwTimeout);
	HANDLE GetSendEvent();
	DWORD SendMessage(S_MESSAGE *pMessage);
	DWORD UnLock();
	DWORD Lock(DWORD ptimeout);
	DWORD ReplyMessage();
	/*
		Member variables
	*/
	char		m_sename[SHARE_MAXLEN];
	char		m_rename[SHARE_MAXLEN];
	char		m_muname[SHARE_MAXLEN];
	HANDLE		m_hSendEvent;
	HANDLE		m_hReplyEvent;
	BOOL		m_OnMessage;
	S_MESSAGE	m_Message;
	HANDLE		m_hMutex;
	BOOL		m_OnInit;	

};

#endif // !defined(AFX_LFC30C01_H__4FA91FB5_078F_11D5_94DA_00D0093D4380__INCLUDED_)
