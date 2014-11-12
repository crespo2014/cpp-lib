 // sigc04.cpp: implementation of the CMessageEvent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LFC2C05.H"

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
	ZeroMemory(this,sizeof(CMessageEvent));
	m_OnConstructor=true;	
}

CMessageEvent::~CMessageEvent()
{
	Release();	
}

int CMessageEvent::WaitMessage(DWORD dwTimeout)
{
	if (::WaitForSingleObject(hSendEvent,dwTimeout)==
		WAIT_OBJECT_0)
		return true;
	return false;
}

int CMessageEvent::ReplyMessage(int pResult)
{
	if (OnMessage)
	{
		OnMessage=false;
		Message.Result=pResult;
		return ::SetEvent(hReplyEvent);
	}
	return false;
}

HANDLE CMessageEvent::GetSendEventHandle()
{
	return hSendEvent;
}

int CMessageEvent::PeekMessage(S_MESSAGE *pMessage)
{
	if (OnMessage)
	{
		memcpy (pMessage,&Message,sizeof(S_MESSAGE));
		return true;
	}
	return false;
}

int CMessageEvent::SendMessage(S_MESSAGE *pMessage)
{
	if (::WaitForSingleObject(hMutex,INFINITE)!=WAIT_OBJECT_0)
		return false;
	memcpy(&Message,pMessage,sizeof(S_MESSAGE));
	OnMessage=true;
	::SetEvent(hSendEvent);
	::WaitForSingleObject(hReplyEvent,TimeOut);
	::ReleaseMutex(hMutex);
	return true;	
}


DWORD CMessageEvent::Initialize()
{
	if (m_OnInitialize)
		return 1;
	SECURITY_ATTRIBUTES	sa;
	ZeroMemory(&sa,sizeof(sa));
	sa.nLength=sizeof(sa);
	sa.bInheritHandle=TRUE;
	hMutex=::CreateMutex(&sa,FALSE,NULL);
	if (!hMutex)
		goto failed;
	hSendEvent=::CreateEvent(&sa,FALSE,FALSE,"evento");
	if (hSendEvent==NULL)
		goto failed;
	hReplyEvent=::CreateEvent(&sa,FALSE,FALSE,NULL);
	if (hReplyEvent==NULL)
		goto failed;
	m_OnInitialize=true;
	TimeOut=INFINITE;
	return 0;
failed:
	Release();
	return 1;
}

DWORD CMessageEvent::Release()
{
	::CloseHandle(hMutex);
	::CloseHandle(hSendEvent);
	::CloseHandle(hReplyEvent);
	hMutex=NULL;
	hSendEvent=NULL;
	hReplyEvent=NULL;
	return 0;
}
