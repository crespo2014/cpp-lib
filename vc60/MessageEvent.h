// IMessageEvent.h: interface for the IMessageEvent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMESSAGEEVENT_H__4F25E8CB_EACF_408C_A8F3_2401D8FC8CCE__INCLUDED_)
#define AFX_IMESSAGEEVENT_H__4F25E8CB_EACF_408C_A8F3_2401D8FC8CCE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "windows.h"

typedef struct
{
	DWORD		lParam;
	DWORD		wParam;
	DWORD		Msg;
	LPVOID		ExtraData;
	int			Result;
} S_MESSAGE,*LP_MESSAGE;

#define MSG_TIMEOUT 1000

class CMessageEvent
{
protected:
	DWORD WaitMessage(DWORD TimeOut = INFINITE);
	DWORD GetSendEventHandle(LPHANDLE lpHandle);
	DWORD PeekMessage(LP_MESSAGE lpMessage);
	DWORD ReplyMessage(DWORD presult);
	DWORD SendMessage(LP_MESSAGE lpMessage);
	DWORD Initialize();
	CMessageEvent();
	~CMessageEvent();
private:
	HANDLE				hSendEvent;
	HANDLE				hReplyEvent;
	HANDLE				hBlockEvent;
	BOOL				OnMessage;
	int					TimeOut;
	S_MESSAGE			Message;
	BOOL OnInitialize;
};

#endif // !defined(AFX_IMESSAGEEVENT_H__4F25E8CB_EACF_408C_A8F3_2401D8FC8CCE__INCLUDED_)
