 // sigc04.cpp: implementation of the CMessageEvent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LFC10C02.H"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMessageEvent::CMessageEvent()
{
	InitMessageEvent();
}

CMessageEvent::~CMessageEvent()
{
	delete m_MessageEvent;
}

int CMessageEvent::InitMessageEvent()
{
	m_MessageEvent =new S_MESSAGEEVENT;	
	m_MessageEvent->TimeOut=INFINITE;
	return true;
}

int CMessageEvent::WaitMessage(DWORD dwTimeout)
{
	return m_MessageEvent->SendEvent.Lock(dwTimeout);
}

int CMessageEvent::ReplyMessage(int pResult)
{
	if (m_MessageEvent->OnMessage)
	{
		m_MessageEvent->OnMessage=false;
		m_MessageEvent->Message.Result=pResult;
		return m_MessageEvent->ReplyEvent.SetEvent();
	}
	return false;
}

HANDLE CMessageEvent::GetSendEventHandle()
{
	return m_MessageEvent->SendEvent;
}

int CMessageEvent::PeekMessage(S_MESSAGE *pMessage)
{
	if (m_MessageEvent->OnMessage)
	{
		memcpy (pMessage,&m_MessageEvent->Message,sizeof(S_MESSAGE));
		return true;
	}
	return false;
}

int CMessageEvent::SendMessage(S_MESSAGE *pMessage)
{
	BOOL	Result;
	m_MessageEvent->CriticalSection.Lock();
	memcpy(&m_MessageEvent->Message,pMessage,sizeof(S_MESSAGE));
	m_MessageEvent->OnMessage=true;
	m_MessageEvent->SendEvent.SetEvent();
	Result=m_MessageEvent->ReplyEvent.Lock(m_MessageEvent->TimeOut);
	m_MessageEvent->CriticalSection.Unlock();
	return Result;	
}

