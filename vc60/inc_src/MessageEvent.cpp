// CMessageEvent.cpp: implementation of the CMessageEvent class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MessageEvent.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMessageEvent::CMessageEvent()
{
	hReplyEvent = NULL;
	hSendEvent = NULL;
	OnMessage = FALSE;
	OnInitialize = FALSE;
}

CMessageEvent::~CMessageEvent()
{
	if (!OnInitialize)
		return;
	::CloseHandle(hBlockEvent);
	::CloseHandle(hSendEvent);
	::CloseHandle(hReplyEvent);
}

DWORD CMessageEvent::Initialize()
{
	if (OnInitialize == TRUE)
		return 0;
	// Creacion de todos los objetos utilizados
	hReplyEvent = ::CreateEvent(NULL,FALSE,FALSE,NULL);
	if (hReplyEvent == NULL) return 1;
	hSendEvent = ::CreateEvent(NULL,FALSE,FALSE,NULL);
	if (hSendEvent == NULL) goto failed_2;
	hBlockEvent = ::CreateEvent(NULL,FALSE,TRUE,NULL);
	if (hSendEvent == NULL) goto failed_3;
	OnInitialize = TRUE;
	return 0;
failed_3:
	CloseHandle(hSendEvent);
failed_2:
	CloseHandle(hReplyEvent);
	return 1;
}

DWORD CMessageEvent::SendMessage(LP_MESSAGE lpMessage)
{
	DWORD	result = 0;
	if (WaitForSingleObject(hBlockEvent,MSG_TIMEOUT) !=  WAIT_OBJECT_0)
		return 1;
	Message = *lpMessage;
	OnMessage = TRUE;
	::SetEvent(hSendEvent);
	if (::WaitForSingleObject(hReplyEvent,INFINITE) != WAIT_OBJECT_0)
		result = 1;
	SetEvent(hBlockEvent);
	return result;
}

DWORD CMessageEvent::ReplyMessage(DWORD presult)
{
	DWORD result=0;
	if (OnMessage == TRUE)
	{
		Message.Result = presult;
		if (!::SetEvent(hReplyEvent))
			result = 1;
		OnMessage = FALSE;
	}
	return result;
}

DWORD CMessageEvent::PeekMessage(LP_MESSAGE lpMessage)
{
	if (OnMessage == TRUE)
	{
		*lpMessage = Message;
		return 0;
	}
	return 1;
}

DWORD CMessageEvent::GetSendEventHandle(LPHANDLE lpHandle)
{
	*lpHandle = hSendEvent;
	if (hSendEvent == NULL)
		return 1;
	return 0;
}

DWORD CMessageEvent::WaitMessage(DWORD TimeOut)
{
	switch(WaitForSingleObject(hSendEvent,TimeOut))
	{
	case WAIT_OBJECT_0:
		return 0;
	case WAIT_TIMEOUT:
		return 2;
	default:
		return 1;
	}
}
