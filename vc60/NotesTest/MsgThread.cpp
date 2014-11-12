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
	m_bms_initialize = false;
}

CMsgThread::~CMsgThread()
{

}

DWORD CMsgThread::Initialize()
{
	DWORD	dwr;
	if (m_bms_initialize) return ERR_OK;
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
	if (m_hthread != NULL)
	{
		SendMessage(TH_MSG_KILL,0);
		if (WaitForSingleObject(m_hthread,1000) != WAIT_OBJECT_0) TerminateThread(m_hthread,0);
		CloseHandle(m_hthread);
	}
	m_hthread = NULL;
	m_bms_initialize = false;
	CEventMessage::Release();
}

UINT CMsgThread::ThreadProc(LPVOID pParam)
{
	return ((CMsgThread*)pParam)->Thread();
}

// metodo virtual que representa el hilo de ejecucion
UINT CMsgThread::Thread()
{
	DWORD	thr;	//thread result
	DWORD	dwr;
	DWORD	msg_id;
	DWORD	msg_param;
	void*	msg_pdata;
	m_plog->_log(LOG_ERROR,"Thread Start ...");
	thr	= ERR_OK;
	for (;;)
	{
		status = TH_ST_NONE;
		dwr = GetMessage(&msg_id,&msg_param,&msg_pdata);
		if (dwr != ERR_OK)
		{
			thr = ERR_FATAL;			
			break;
		}
		status = TH_ST_BUSY;
		if ((msg_id == TH_MSG_KILL) ||
			(msg_id == TH_MSG_EXIT))
		{
			ReplyMessage(ERR_OK);
			thr = ERR_OK;
			break;
		}
		switch(msg_id)
		{
		case TH_MSG_TEST:
			{
				m_plog->_log(LOG_ERROR,"Thread with id = 0x%X is OK",GetCurrentThreadId());
				break;
			}
		default:
			{
				ReplyMessage(ERR_OP);continue;
			}
		}
		ReplyMessage(ERR_OK);
	}
	status = TH_ST_NONE;
	m_plog->_log(LOG_ERROR,"Thread End ...");
	return thr;
}
