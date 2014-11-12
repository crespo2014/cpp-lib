// lfc30c01.cpp: implementation of the CMessage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lfc30c01.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
 
CMessage::CMessage()
{
	ZeroMemory(this,sizeof(CMessage));
}

CMessage::~CMessage()
{
	Release();
}

DWORD CMessage::Initialize()
{
	if (m_OnInit!=0)
		return 0;
	// Todos los datos deben estar inicializados en cero
	// Crear los nombres de los eventos
	LFC30GetString(m_sename,0);
	LFC30GetString(m_rename,1);
	LFC30GetString(m_muname,2);

	SECURITY_ATTRIBUTES	sa;
	ZeroMemory(&sa,sizeof(sa));
	sa.nLength=sizeof(sa);
	sa.bInheritHandle=TRUE;
	m_hMutex=::CreateMutex(&sa,FALSE,m_muname);
	if (m_hMutex==NULL)
		goto failed;
	if (GetLastError()==ERROR_ALREADY_EXISTS)
		goto failed;
	m_hSendEvent=::CreateEvent(&sa,FALSE,FALSE,m_sename);
	if (m_hSendEvent==NULL)
		goto failed;
	if (GetLastError()==ERROR_ALREADY_EXISTS)
		goto failed;
	m_hReplyEvent=::CreateEvent(&sa,FALSE,FALSE,m_rename);
	if (m_hReplyEvent==NULL)
		goto failed;
	if (GetLastError()==ERROR_ALREADY_EXISTS)
		goto failed;
	m_OnInit=true;
	return 0;
failed:
	Release();
	return 1;
}

DWORD CMessage::Release()
{
	::CloseHandle(m_hMutex);
	::CloseHandle(m_hSendEvent);
	::CloseHandle(m_hReplyEvent);
	m_hMutex=NULL;
	m_hSendEvent=NULL;
	m_hReplyEvent=NULL;
	return 0;
}

DWORD CMessage::Lock(DWORD ptimeout)
{
	return 0;
}

DWORD CMessage::UnLock()
{
	return 0;
}

DWORD CMessage::SendMessage(S_MESSAGE *pMessage)
{
	if (::WaitForSingleObject(m_hMutex,INFINITE)!=WAIT_OBJECT_0)
		return 1;
	m_Message=*pMessage;
	m_OnMessage=true;
	::SetEvent(m_hSendEvent);
	::WaitForSingleObject(m_hReplyEvent,INFINITE);
	*pMessage=m_Message;
	m_OnMessage=false;
	::ReleaseMutex(m_hMutex);
	return 0;	
}

HANDLE CMessage::GetSendEvent()
{
	return m_hSendEvent;
}

DWORD CMessage::ReplyMessage()
{
	if (m_OnMessage==false)
		return 1;
	::SetEvent(m_hReplyEvent);
	return 0;
}

DWORD CMessage::WaitMessage(DWORD dwTimeout)
{
	WaitForSingleObject(m_hSendEvent,dwTimeout);
	return 0;
}

DWORD CMessage::PeekMessage(S_MESSAGE *pMessage)
{
	if (m_OnMessage==false)
		return 1;
	*pMessage=m_Message;
	return 0;
}
