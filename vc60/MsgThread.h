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

#define TH_ST_NULL		0	// el hilo no se esta ejecutando 
#define TH_ST_BUSY		1	// el hilo esta en una operacion que le toma algun tiempo no enviar mensajes en este caso
#define	TH_ST_OK		2	// el hilo esta esperando un mensaje
#define TH_ST_END		4	// el hilo se esta liberando
#define TH_ST_FAILED	3	// el hilo a terminado debido a un fallo desconocido
#define TH_ST_LAST		5

/*
	Hilo con soporte de mensajeria a traves de eventos
*/

class CMsgThread  : public CEventMessage 
{
public:
	void Kill();
	BOOL ProcessMessage(DWORD msg_id,DWORD msg_param,void* msg_data);
	void Release();
	DWORD Initialize();
	CMsgThread();
	virtual ~CMsgThread();

	WORD	m_thread_st;

private:
	HANDLE	m_hthread;
	virtual UINT Thread();
	static	UINT ThreadProc(LPVOID pParam);
};

#endif // !defined(AFX_MSGTHREAD_H__7C229C84_2C09_4871_8F31_EC9DC948EF41__INCLUDED_)
