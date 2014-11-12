// MsgThread.cpp: implementation of the CMsgThread class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MsgThread.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMsgThread::CMsgThread()
{
	m_hthread = NULL;
	SetTimeout(1000);	// solo un segundo el tiempo de espera por operacion
}

CMsgThread::~CMsgThread()
{

}

DWORD CMsgThread::Initialize()
{
	DWORD	dwr;
	// chequear el hilo a ver si sigue corriendo
	if (m_hthread != NULL) return ERR_OK;
	dwr = CEventMessage::Initialize();if (dwr != ERR_OK) return dwr;
	for (;;)
	{
		m_hthread = ::CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ThreadProc,this,0,0);if (m_hthread == NULL) break;
		return ERR_OK;
	}
	SetError_Add_W32_code_msg(true,ERR_API,GetLastError(),"CMsgThread::Initialize ... failed to create thread ");
	Release();
	return ERR_API;
}

void CMsgThread::Release()
{
	Kill();
	CEventMessage::Release();
	/*
	if (m_hthread != NULL)
	{
		SendMessage(TH_MSG_KILL,0);
		if (m_thread_st != TH_ST_NULL)
			if (WaitForSingleObject(m_hthread,1000) != WAIT_OBJECT_0) TerminateThread(m_hthread,0);
		CloseHandle(m_hthread);
	}
	m_hthread = NULL;
	*/
	
}

UINT CMsgThread::ThreadProc(LPVOID pParam)
{
//	UINT		rs;
	CMsgThread*	pthread = (CMsgThread*)pParam;

	return pthread->Thread();
}

// metodo virtual que representa el hilo de ejecucion
UINT CMsgThread::Thread()
{
	DWORD	thr;	//thread result
//	DWORD	dwr;
	DWORD	msg_id;
	DWORD	msg_param;
	void*	msg_pdata;
	m_plog->_log(LOG_ERROR,"Thread Start ...");
	thr	= ERR_OK;
	for (;;)
	{
		m_thread_st = TH_ST_OK;
		if (GetMessage(&msg_id,&msg_param,&msg_pdata) != ERR_OK) break;
		if (!ProcessMessage(msg_id,msg_param,msg_pdata)) break;
	}
	m_plog->_log(LOG_ERROR,"Thread End ...");
	m_thread_st = TH_ST_NULL;
	return thr;
}

BOOL CMsgThread::ProcessMessage(DWORD msg_id, DWORD msg_param, void *msg_data)
{
	DWORD msg_r;	// resultado del mensaje
	BOOL  br;		// resultado booleano
	
	msg_r = ERR_OK;
	br	= true;
	switch(msg_id)
	{
	case TH_MSG_KILL:
	case TH_MSG_EXIT:
		{
			br = false;
			break;
		}
	case TH_MSG_TEST:
		{
			m_plog->_log(LOG_ERROR,"Thread with id = 0x%X is OK",GetCurrentThreadId());
			break;
		}
	}
	ReplyMessage(msg_r);
	return msg_r;
}

void CMsgThread::Kill()
{
	if (m_hthread != NULL)
	{
		SendMessage(TH_MSG_KILL,0);
		if (m_thread_st != TH_ST_NULL)
			if (WaitForSingleObject(m_hthread,1000) != WAIT_OBJECT_0) TerminateThread(m_hthread,0);
		CloseHandle(m_hthread);
	}
	m_hthread = NULL;
}
