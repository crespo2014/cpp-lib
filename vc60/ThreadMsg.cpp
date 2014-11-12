// ThreadMsg.cpp: implementation of the CThreadMsg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ThreadMsg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CThreadMsg::CThreadMsg()
{

}

CThreadMsg::~CThreadMsg()
{

}

DWORD CThreadMsg::WaitMessage(DWORD TimeOut)
{
	return 0;
}

DWORD GetSndEvent(LPHANDLE lpHandle)
{
	return 0;
}


DWORD ThreadGetMsg(S_THREADMSG **lpMessage)
{
	return 0;
}

DWORD CThreadMsg::SendMessage(S_THREADMSG *lpMessage, DWORD timeout)
{
	return 0;
}

DWORD CThreadMsg::ThreadReplyMsg()
{
	return 0;
}

DWORD CThreadMsg::Initialize()
{
	do 
	{
		m_hReplyEvent = ::CreateEvent(NULL,FALSE,FALSE,NULL);
		if (hReplyEvent == NULL) break;
		hSendEvent = ::CreateEvent(NULL,FALSE,FALSE,NULL);
		if (hSendEvent == NULL) break;
	}while(false);
	Release();
	return 1;

}

DWORD CThreadMsg::Release()
{
	Release();
}
