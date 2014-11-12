// Lfc30c03.h: interface for the CEventMessage class.
//
//////////////////////////////////////////////////////////////////////

/*
	Esta clase es usada para enviar mensajes a un hilo
	No tiene soporte de memoria compartida
Funciones miembros:
	Initialize:
		Crea todos los objetos que usara la clase entre ellos se encuentran
		los eventos y el mutex
		Valor devuelto
			0 : Todas las variables han sido inicializadas
			1 : Hubo un error en la inicializacion
		Nota:
			Si una variable no pudo ser inicializada entonces las que ya lo estaban
			dejaran de estarlo
	Release:
		Se destruyen todos los objetos y variables de la clase
	GetMessage
		Toma la informacion del mensaje que se envio.
	IsMessage:
		Indica si hay algun mensaje esperando a ser procesado
	Reply:
		Permite que el hilo que envio el mensaje continue su ejecucion
	WaitMessage:
		Espera un tiempo determinado por la llegada de un mensaje.
		Valor devuelto:
			0 : Se recivio un mensaje
			1 : No se recivio ningun mensage
			2 : Ocurrio un error en la funcion
	GethEvent:
		Devuelve el handle del evento usado para esperar un mensaje


Variables miembro:
{
	hmutex		: Mutex usado para soporte multihilo
	hreply_event: Evento usado para 
	hsend_event : Evento usado para enviar el mensaje
	message		: Contiene la informacion del mensaje enviado
	on_init		: Indica que ya la clase ha sido inicializada.
	on_message	: Indica que ha sido enviado un mensaje y debe ser procesado
}
	
*/

#if !defined(AFX_LFC30C03_H__B9C57120_16D4_11D5_8D01_00D0093D4380__INCLUDED_)
#define AFX_LFC30C03_H__B9C57120_16D4_11D5_8D01_00D0093D4380__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "lfc30def.h"

class CEventMessage  
{
public:
	DWORD SendMessage(S_MESSAGE *pmessage);
	DWORD GetSendEventHandle(HANDLE* handle);
	DWORD Reply();
	DWORD WaitMessage(DWORD dwTimeout);
	DWORD GetMessage(S_MESSAGE *pMessage);
	BOOL		on_init;
	HANDLE		hsend_event;
	HANDLE		hreply_event;
	BOOL		on_message;
	S_MESSAGE	message;
	HANDLE		hmutex;
	DWORD Release();
	DWORD Initialize();
	CEventMessage();
	virtual ~CEventMessage();

};

#endif // !defined(AFX_LFC30C03_H__B9C57120_16D4_11D5_8D01_00D0093D4380__INCLUDED_)
