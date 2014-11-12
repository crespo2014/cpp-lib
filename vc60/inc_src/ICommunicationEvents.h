// ICommunicationEvents.h: interface for the ICommunicationEvents class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ICOMMUNICATIONEVENTS_H__FC729657_1F43_493A_807F_F49376473B5C__INCLUDED_)
#define AFX_ICOMMUNICATIONEVENTS_H__FC729657_1F43_493A_807F_F49376473B5C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MessageEvent.h"

class ICommunicationEvents  
{
public:
	virtual DWORD _stdcall OnReceivedData(BYTE* Buffer,DWORD cant)=0;
	virtual DWORD _stdcall OnCommEvent(DWORD pEventMask)=0;
	virtual DWORD _stdcall OnSendBytes(BYTE* Buffer,DWORD BytesWritten)=0;
	virtual DWORD _stdcall OnProcessMessage(LP_MESSAGE lpMessage)=0;
	virtual DWORD _stdcall OnWaitTimeOut()=0;
};

typedef ICommunicationEvents* LPCOMMUNICATIONEVENTS;


#endif // !defined(AFX_ICOMMUNICATIONEVENTS_H__FC729657_1F43_493A_807F_F49376473B5C__INCLUDED_)
