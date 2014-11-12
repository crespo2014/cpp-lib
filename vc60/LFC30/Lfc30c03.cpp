// Lfc30c03.cpp: implementation of the CEventMessage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Lfc30c03.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEventMessage::CEventMessage()
{
	on_init=false;
	hmutex=NULL;
	hreply_event=NULL;
	hsend_event=NULL;
	on_message=false;
}

CEventMessage::~CEventMessage()
{
	Release();
}

DWORD CEventMessage::Initialize()
{
	if (on_init)
		return 0;
	hmutex=::CreateMutex(NULL,FALSE,NULL);
	if (hmutex==NULL)
		goto failed;
	hsend_event=::CreateEvent(NULL,FALSE,FALSE,NULL);
	if (hsend_event==NULL)
		goto failed;
	hreply_event=::CreateEvent(NULL,FALSE,FALSE,NULL);
	if (hreply_event==NULL)
		goto failed;
	on_init=true;
	return 0;
failed:
	Release();
	return 1;
}

DWORD CEventMessage::Release()
{
	on_init=false;
	CloseHandle(hreply_event);
	CloseHandle(hsend_event);
	CloseHandle(hmutex);
	return 0;
}

DWORD CEventMessage::GetMessage(S_MESSAGE *pMessage)
{
	if (on_message==false)
		return 1;
	*pMessage=message;
	return 0;
}

DWORD CEventMessage::WaitMessage(DWORD dwTimeout)
{
	DWORD re=WaitForSingleObject(hsend_event,dwTimeout);
	switch (re)
	{
	case WAIT_OBJECT_0:
		return 0;
	case WAIT_TIMEOUT:
		return 2;
	default:
		return 1;
	}
}

DWORD CEventMessage::Reply()
{
	if (on_message==false)
		return 1;
	if (::SetEvent(hreply_event))
		return 0;
	return 2;
}

DWORD CEventMessage::GetSendEventHandle(HANDLE *handle)
{
	if (!on_init)
		return 1;
	*handle = hsend_event;
	return 0;
}

DWORD CEventMessage::SendMessage(S_MESSAGE *pmessage)
{
	if (::WaitForSingleObject(hmutex,INFINITE)!=WAIT_OBJECT_0)
		return 1;
	message=*pmessage;
	on_message=true;
	::SetEvent(hsend_event);
	::WaitForSingleObject(hreply_event,INFINITE);
	*pmessage=message;
	on_message=false;
	::ReleaseMutex(hmutex);
	return 0;	
}
