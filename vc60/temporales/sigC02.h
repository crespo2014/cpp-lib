// sigc04.h: interface for the CMessageEvent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIGC04_H__324A5D01_68C4_11D4_8632_00D0093D4380__INCLUDED_)
#define AFX_SIGC04_H__324A5D01_68C4_11D4_8632_00D0093D4380__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct
{
	LPARAM				lParam;
	WPARAM				wParam;
	UINT				Msg;
	LPVOID				ExtraData;
	int					Result;
} S_MESSAGE;

typedef struct
{
	CCriticalSection    CriticalSection;
	CEvent				SendEvent;
	CEvent				ReplyEvent;
	BOOL				OnMessage;
	int					TimeOut;
	S_MESSAGE			Message;
} S_MESSAGEEVENT;

class AFX_EXT_CLASS CMessageEvent : public CObject  
{
public:
	int SendMessage(S_MESSAGE *pMessage);
	int PeekMessage(S_MESSAGE* pMessage);
	HANDLE GetSendEventHandle();
	int ReplyMessage(int pResult);
	int WaitMessage( DWORD dwTimeout = INFINITE );
	S_MESSAGEEVENT* m_MessageEvent;
	int InitMessageEvent();
	CMessageEvent();
	virtual ~CMessageEvent();

};

#endif // !defined(AFX_SIGC04_H__324A5D01_68C4_11D4_8632_00D0093D4380__INCLUDED_)
