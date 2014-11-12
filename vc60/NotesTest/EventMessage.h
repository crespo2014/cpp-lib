// EventMessage.h: interface for the CEventMessage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVENTMESSAGE_H__BCE81282_8770_465C_A7C7_7A8A6855B4B0__INCLUDED_)
#define AFX_EVENTMESSAGE_H__BCE81282_8770_465C_A7C7_7A8A6855B4B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bObject.h"

class CEventMessage : public CbObject  
{
public:
	void GetMessageEvent(HANDLE* hevent) { *hevent = m_hsndEvent;};
	DWORD ReplyMessage(DWORD result);
	DWORD GetMessage(DWORD* msg_id, DWORD* msg_param, void **msg_data,DWORD timeout = INFINITE);
	DWORD GetMessageResult(DWORD* msg_result);
	DWORD SendMessage(DWORD msg_id,DWORD msg_param,DWORD* msg_result = NULL,void* msg_data = NULL);
	void Release();
	DWORD Initialize();
	CEventMessage();
	virtual ~CEventMessage();

private:
	HANDLE	m_hsndEvent;	// evento de envio
	HANDLE	m_hrplEvent;	// evento de replica

	DWORD	m_sndTimeOut;	// timeout en el envio 
	BOOL	m_bInitialize;	// la clase ya ha sido inicializada
	
	// datos del mensaje enviado
	BOOL	m_bMessage;		// indica que un mensaje a sido enviado y no se ha obtendido respuesta
	DWORD	m_msg_id;	// mensaje enviado
	DWORD	m_msg_param;	// Prametro del mensaje
	DWORD	m_msg_result;	// Resultado devuelto por el mensaje, util cuando el procesamiento es inmediato
	void*	m_msg_pdata;	// Datos enviados por el mensaje

};

#endif // !defined(AFX_EVENTMESSAGE_H__BCE81282_8770_465C_A7C7_7A8A6855B4B0__INCLUDED_)
