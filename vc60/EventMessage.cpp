// EventMessage.cpp: implementation of the CEventMessage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EventMessage.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEventMessage::CEventMessage()
{
	m_sndTimeOut	= 5000;		//5 segundos es lo mas que se espera por un mensaje
	m_bMessage		= false;
	m_bInitialize	= false;
	m_hrplEvent		= NULL;
	m_hsndEvent		= NULL;
}

CEventMessage::~CEventMessage()
{
	Release();
}


DWORD CEventMessage::Initialize()
{
	// inicilizar todas las estructuras y datos
	DWORD	ec;		//error code
	if (m_bInitialize) return ERR_OK;
	for(;;)
	{
		ec = 1;
		m_hrplEvent = ::CreateEvent(NULL,FALSE,FALSE,NULL);if (m_hrplEvent == NULL) break;
		m_hsndEvent = ::CreateEvent(NULL,FALSE,FALSE,NULL);if (m_hsndEvent == NULL) break;
		m_bInitialize = true;
		return ERR_OK;
	}
	Release();
	switch (ec)
	{
	case 1:
		return SetError_Add_W32_code_msg(true,ERR_API,GetLastError(),"CEventMessage::Initialize -> CreateEvent .... failed ");
	}
	return ERR_FATAL;
}

void CEventMessage::Release()
{
	if (m_hrplEvent != NULL) CloseHandle(m_hrplEvent);
	if (m_hsndEvent != NULL) CloseHandle(m_hsndEvent);
	m_hrplEvent		= NULL;
	m_hsndEvent		= NULL;
	m_bInitialize	= false;
	m_bMessage		= false;
}

DWORD CEventMessage::SendMessage(DWORD msg_id, DWORD msg_param, DWORD *msg_result, void *msg_data)
{
	DWORD	dwr;
	if (m_bMessage) return SetError(true,ERR_FATAL,"CEventMessage::SendMessage .. failed because there is a pending message");
	m_msg_id	= msg_id;
	m_msg_param	= msg_param;
	m_msg_pdata	= msg_data;

	if (!::SetEvent(m_hsndEvent)) return SetError_Add_W32_code_msg(true,ERR_API,GetLastError(),"CEventMessage::SendMessage -> SetEvent .. failed ");
	m_bMessage = true;
	dwr = ::WaitForSingleObject(m_hrplEvent,m_sndTimeOut);
	switch (dwr)
	{
	case WAIT_OBJECT_0:
		{
			if (msg_result != NULL) *msg_result = m_msg_result;
			m_bMessage = false;
			return ERR_OK;
		}
	case WAIT_TIMEOUT:		return SetError(true,ERR_TIMEOUT,"CEventMessage::SendMessage .... timeout of %u ms waiting for response",m_sndTimeOut);
	case WAIT_ABANDONED:	return SetError(true,ERR_FATAL,"CEventMessage::SendMessage .... object abandoned waiting for response");
	case WAIT_FAILED:  
	default:
			return SetError_Add_W32_code_msg(true,ERR_API,GetLastError(),"CEventMessage::SendMessage -> WaitForSingleObject .. failed ");
	}
	return ERR_FATAL;
}

DWORD CEventMessage::GetMessageResult(DWORD *msg_result)
{
	DWORD	dwr;
	if (!m_bMessage) return SetError(true,ERR_FATAL,"CEventMessage::SendMessage .. failed because there is not any pending message");
	dwr = ::WaitForSingleObject(m_hrplEvent,m_sndTimeOut);
	switch (dwr)
	{
	case WAIT_OBJECT_0:
		{
			*msg_result = m_msg_result;
			m_bMessage = false;
			return ERR_OK;
		}
	case WAIT_TIMEOUT:		return SetError(true,ERR_TIMEOUT,"CEventMessage::GetMessageResult .... timeout of %u ms waiting for response",m_sndTimeOut);
	case WAIT_ABANDONED:	return SetError(true,ERR_FATAL,"CEventMessage::GetMessageResult .... object abandoned waiting for response");
	case WAIT_FAILED:  
	default:
			return SetError_Add_W32_code_msg(true,ERR_API,GetLastError(),"CEventMessage::GetMessageResult -> WaitForSingleObject .. failed ");
	}
	return ERR_FATAL;
}

DWORD CEventMessage::GetMessage(DWORD *msg_id, DWORD *msg_param, void **msg_data, DWORD timeout)
{
	DWORD	dwr;

	dwr = WaitForSingleObject(m_hsndEvent,timeout);
	switch(dwr)
	{
	case WAIT_OBJECT_0:
		{
			*msg_id		= m_msg_id;
			*msg_param	= m_msg_param;
			*msg_data	= m_msg_pdata;
			return ERR_OK;
		}
	case WAIT_TIMEOUT: return ERR_TIMEOUT;
//	default:	return ERR_API;
	}
	glog._log(LOG_ERROR,"CEventMessage::GetMessage ... failed %u with code %u",dwr,GetLastError());
	return ERR_FATAL;
}

DWORD CEventMessage::ReplyMessage(DWORD result)
{
	if (!m_bMessage) return ERR_FATAL;
	m_msg_result = result;
	if (::SetEvent(m_hrplEvent)) return ERR_OK;
	glog._log(LOG_ERROR,"CEventMessage::ReplyMessage ... failed with code %u",GetLastError());
	return ERR_OK;
	
}

DWORD CEventMessage::PeekMessage(DWORD *msg_id, DWORD *msg_param, void **msg_data)
{
	if (!m_bMessage) return ERR_FATAL;
	*msg_id		= m_msg_id;
	*msg_param	= m_msg_param;
	*msg_data	= m_msg_pdata;
	return ERR_OK;
}
