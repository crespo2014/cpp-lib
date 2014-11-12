// lfc30c02.cpp: implementation of the CShareMessage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lfc30c02.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShareMessage::CShareMessage()
{
	ZeroMemory(this,sizeof(CShareMessage));
}

CShareMessage::~CShareMessage()
{
	Release();
}

DWORD CShareMessage::Initialize()
{
	//Antes de inicializar esta clase hay
	//que pasarle un ptr a la clase CMessage
	//que se esta compartiendo
	if (m_OnInit!=0)
		return 0;
	if (m_lpmessage==NULL)
		return 1;
	// Crear todos los objetos compartidos
	m_hMutex=::OpenMutex(SYNCHRONIZE|MUTEX_ALL_ACCESS,TRUE,m_lpmessage->m_muname);
	if (m_hMutex==NULL)
		goto failed;
	m_hSendEvent=::OpenEvent(EVENT_ALL_ACCESS,TRUE,m_lpmessage->m_sename);
	if (m_hSendEvent==NULL)
		goto failed;
	m_hReplyEvent=::OpenEvent(EVENT_ALL_ACCESS,TRUE,m_lpmessage->m_rename);
	if (m_hReplyEvent==NULL)
		goto failed;
	m_OnInit=TRUE;
	return 0;
failed:
	Release();
	return 1;
}

DWORD CShareMessage::Release()
{
	::CloseHandle(m_hMutex);
	::CloseHandle(m_hSendEvent);
	::CloseHandle(m_hReplyEvent);
	m_hMutex=NULL;
	m_hSendEvent=NULL;
	m_hReplyEvent=NULL;
	return 0;
}

DWORD CShareMessage::SetMessageClass(CMessage *lpmessage)
{
	m_lpmessage=lpmessage;
	return 0;
}

DWORD CShareMessage::SendMessage(S_MESSAGE *pMessage)
{
	if (::WaitForSingleObject(m_hMutex,INFINITE)!=WAIT_OBJECT_0)
		return 1;
	m_lpmessage->m_Message=*pMessage;
	m_lpmessage->m_OnMessage=true;
	::SetEvent(m_hSendEvent);
	::WaitForSingleObject(m_hReplyEvent,INFINITE);
	*pMessage=m_lpmessage->m_Message;
	m_lpmessage->m_OnMessage=false;
	::ReleaseMutex(m_hMutex);
	return 0;
}

DWORD CShareMessage::PeekMessage(S_MESSAGE *pMessage)
{
	if (m_lpmessage->m_OnMessage==false)
		return 1;
	*pMessage=m_lpmessage->m_Message;
	return 0;
}

DWORD CShareMessage::WaitMessage(DWORD dwTimeout)
{
	WaitForSingleObject(m_hSendEvent,dwTimeout);
	return 0;
}

