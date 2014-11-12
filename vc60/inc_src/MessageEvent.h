// IMessageEvent.h: interface for the IMessageEvent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMESSAGEEVENT_H__4F25E8CB_EACF_408C_A8F3_2401D8FC8CCE__INCLUDED_)
#define AFX_IMESSAGEEVENT_H__4F25E8CB_EACF_408C_A8F3_2401D8FC8CCE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "lockevent.h"

typedef struct 
{
	DWORD		lParam;
	DWORD		wParam;
	DWORD		Msg;
	LPVOID		ExtraData;
	DWORD		Result;
	int			ErrorCode;
} S_MESSAGE,*LP_MESSAGE;

#define MSG_TIMEOUT 10000

class CMessageEvent : private CLockEvent
{
public:
	//DWORD Release();
	DWORD Initialize();
protected:
	DWORD WaitMessage(DWORD TimeOut = INFINITE);
	DWORD GetSendEventHandle(LPHANDLE lpHandle);
	DWORD PeekMessage(LP_MESSAGE lpMessage);
	DWORD ReplyMessage(DWORD presult);
	DWORD SendMessage(LP_MESSAGE lpMessage);
	CMessageEvent();
	~CMessageEvent();
private:
	HANDLE				hSendEvent;
	HANDLE				hReplyEvent;
	HANDLE				hBlockEvent;
	BOOL				OnMessage;
	BOOL				OnInitialize;
	int					TimeOut;
	S_MESSAGE			Message;
	BOOL m_OnMsgInit;
};

#endif // !defined(AFX_IMESSAGEEVENT_H__4F25E8CB_EACF_408C_A8F3_2401D8FC8CCE__INCLUDED_)
