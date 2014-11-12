// LogPipe.h: interface for the CLogPipe class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGPIPE_H__6F372048_82BF_4205_8058_CCA39195FF80__INCLUDED_)
#define AFX_LOGPIPE_H__6F372048_82BF_4205_8058_CCA39195FF80__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MessageEvent.h"

/*
#ifndef LOGEVENT_PIPE
#define LOGEVENT_PIPE	"logpipe"
#endif
*/

class CLogPipe :  private CMessageEvent
{
public:
	void Pipe_SetName(char* pname);
	DWORD SendMsg(char* msg);
	DWORD CreatePipe(char* pipe_name);
	DWORD Pipe_ProcessRead();
	DWORD Pipe_SetupRead();
	
	void PipeClose();
	DWORD Initialize();
	void ClosePipe();
	void OpenPipe();
	void CheckEvent();
	char*	GetErrorMsg(){return m_err_msg;}
	CLogPipe();
	virtual ~CLogPipe();
	
private:
	BOOL ThreadProcessMessage();
	UINT Thread();
	DWORD ThreadCreatePipe(char* pipe_name);
	DWORD Thread_Pipe_Read();

	HANDLE		m_hpipe_event;	// handle del evento usado para habilitar el pipe
	BOOL		m_bpipe_status;	// si true indica que se recivio la activacion del pipe, pero ha fallado su creacion 
	HANDLE		m_hpipe;		// handle el pipe
	HANDLE		m_hpipe_read_event;
	OVERLAPPED	m_pipe_overlapped;
	char		m_pipe_name[50];

#define PIPE_NULL		0
#define PIPE_CREATE		1
#define PIPE_CONECTING	2
#define PIPE_READING	3
#define PIPE_ERROR		4

	DWORD	m_pipe_status;
	
	HANDLE	m_hthread;
	char	m_read_buffer[1024];	//usado para leer datos del pipe
	DWORD	m_read_bytes;

	char*	m_err_msg;

	static UINT ThreadProc(LPVOID pParam){return ((CLogPipe*)pParam)->Thread();};
};

#endif // !defined(AFX_LOGPIPE_H__6F372048_82BF_4205_8058_CCA39195FF80__INCLUDED_)
