// MsgThread.h: interface for the CMsgThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGTHREAD_H__7C229C84_2C09_4871_8F31_EC9DC948EF41__INCLUDED_)
#define AFX_MSGTHREAD_H__7C229C84_2C09_4871_8F31_EC9DC948EF41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bObject.h"
#include "EventMessage.h"

#define TH_MSG_NONE		0
#define TH_MSG_TEST		1
#define TH_MSG_KILL		2
#define TH_MSG_EXIT		3
#define TH_MSG_LAST		1000	//mensajes disponibles al usuario

#define TH_ST_NONE		0	// el hilo no se esta ejecutando ni ha sido creado
#define TH_ST_BUSY		1	// el hilo esta en una operacion que le toma algun tiempo no enviar mensajes en este caso
#define	TH_ST_OK		2	// el hilo esta esperando un mensaje

/*
	Hilo con soporte de mensajeria a traves de eventos
*/

class CMsgThread : public CEventMessage 
{
public:
	void Release();
	DWORD Initialize();
	CMsgThread();
	virtual ~CMsgThread();

	WORD	status;

private:
	HANDLE	m_hthread;
	BOOL	m_bms_initialize;		// msgthread initialize
	virtual UINT Thread();
	static	UINT ThreadProc(LPVOID pParam);
};

#endif // !defined(AFX_MSGTHREAD_H__7C229C84_2C09_4871_8F31_EC9DC948EF41__INCLUDED_)
