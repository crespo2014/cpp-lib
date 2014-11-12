// Clases1.cpp: implementation of the CMessageClass class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Clases1.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMessageClass::CMessageClass()
{
	m_OnMessage=false;
}

CMessageClass::~CMessageClass()
{

}

int CMessageClass::SendMessage(UINT Msg, WPARAM wParam, LPARAM lParam)
{
	m_CriticalSection.Lock();
	m_Msg=Msg;
	m_wParam=wParam;
	m_lParam=lParam;
	m_OnMessage=true;
	m_SendEvent.SetEvent();
	m_ReceiveEvent.Lock();
	m_OnMessage=false;
	m_CriticalSection.Unlock();
	return true;
}

int CMessageClass::ReplyMessage()
{
	if (m_OnMessage)
	{
		return m_ReceiveEvent.SetEvent();
	}
	return false;
}

CEvent* CMessageClass::GetMessageEvent()
{
	return &m_SendEvent;
}

int CMessageClass::IsMessage()
{
	return m_OnMessage;
}

int CMessageClass::GetMesage(UINT *Msg, WPARAM *wParam, LPARAM *lParam)
{
	if (m_OnMessage)
	{
		*Msg=m_Msg;
		*wParam=m_wParam;
		*lParam=m_lParam;
		return true;
	}
	return false;
}

int CMessageClass::WaitMessage()
{
	return m_SendEvent.Lock();
}
