// LogPipe.cpp: implementation of the CLogPipe class.
//
//////////////////////////////////////////////////////////////////////

#include "LogPipe.h"
#include "LogClient.h"
#include "stdio.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define TMSG_PIPE_OPEN		1
#define TMSG_THREAD_CLOSE	2
#define TMSG_PIPE_CLOSE		3

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLogPipe::CLogPipe()
{
	m_pipe_status = PIPE_NULL;

}

CLogPipe::~CLogPipe()
{
	PipeClose();
	if (m_hpipe_event != NULL)	CloseHandle(m_hpipe_event);
}

void CLogPipe::CheckEvent()
{
	DWORD	dwr;
	if (m_hpipe_event != NULL)
	{
		dwr = WaitForSingleObject(m_hpipe_event,0);
		if ((dwr == WAIT_OBJECT_0) && (!m_bpipe_status)) OpenPipe();
		else
			ClosePipe();
	}
}

void CLogPipe::OpenPipe()
{
	if (m_pipe_name[0] == 0) return;
	char	spipe_name[50];
	sprintf(spipe_name,"%s%s","\\\\.\\pipe\\",m_pipe_name);

	if (!m_bpipe_status)
	{
		m_bpipe_status = true;	// evitar que se intente crear el pipe una vez que falla
		m_hpipe = CreateFile(spipe_name,GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);
	}
}

void CLogPipe::ClosePipe()
{
	if (m_bpipe_status)
	{
		m_bpipe_status = false;		// solo se sierra una vez
		CloseHandle(m_hpipe);
		m_hpipe = NULL;
	}
}

DWORD CLogPipe::ThreadCreatePipe(char *pipe_name)
{
	char	spipe_name[50];
	sprintf(spipe_name,"%s%s","\\\\.\\pipe\\",pipe_name);
	m_hpipe = CreateNamedPipe(spipe_name,PIPE_ACCESS_INBOUND|FILE_FLAG_OVERLAPPED,PIPE_TYPE_BYTE,1,1048,2048,0,NULL);
	if (m_hpipe == NULL) return ERR_FATAL;
	m_pipe_status = PIPE_CREATE;
	return ERR_OK;
}


UINT CLogPipe::Thread()
{
	/*	estado del hilo .
	- Esperar por la solicitud de creacion del pipe
	- Crear el pipe y esperar por la conexion con el cliente
	- Recivir datos del pipe
	- pipe desconectado conexion perdida
	*/


	DWORD	dr;
	HANDLE	Events[2];
	m_pipe_overlapped.hEvent = m_hpipe_read_event;
	
	GetSendEventHandle(&Events[0]);
	Events[1] = m_hpipe_read_event;
	
	dr = ERR_OK;
	while (dr == ERR_OK)
	{
		dr = WaitMessage(); if (dr != 0) break;
		if (ThreadProcessMessage() != ERR_OK) break;
		if (m_hpipe == NULL) continue;
		
		// Conectar el pipe
		dr = ConnectNamedPipe(m_hpipe,&m_pipe_overlapped);
		if (dr == 0) 
			dr = GetLastError();
		else
			dr = ERROR_PIPE_CONNECTED;

		if (dr == ERROR_PIPE_CONNECTED) m_pipe_status = PIPE_READING;
		if ((dr == ERROR_PIPE_LISTENING) || (dr == ERROR_IO_PENDING)) m_pipe_status = PIPE_CONECTING;

		dr = ERR_OK;
		// esperar porque se conecte el pipe o un mensaje
		while ((m_pipe_status == PIPE_CONECTING) && (dr == ERR_OK))
		{
			DWORD dwo = WaitForMultipleObjects(2,Events,FALSE,INFINITE);
			if (dwo == WAIT_OBJECT_0)
			{
				dr = ThreadProcessMessage();continue;
			}
			if (dwo == WAIT_OBJECT_0+1)
			{
				if (GetOverlappedResult(m_hpipe,&m_pipe_overlapped,&dr,false) != 0) 
					m_pipe_status = PIPE_READING;
				else
					m_pipe_status = PIPE_CREATE;
				dr = ERR_OK;
			}
		}

		// leer datos del pipe
		BOOL	bread = false;
		while ((m_pipe_status == PIPE_READING) && (dr == ERR_OK))
		{
			if (!bread) 
			{
				bread = true;
				dr = Pipe_SetupRead(); if (dr != ERR_OK) break;
			}
			DWORD dwo = WaitForMultipleObjects(2,Events,FALSE,INFINITE);
			if (dwo == WAIT_OBJECT_0)
			{
				dr = ThreadProcessMessage();continue;
			}
			if (dwo == WAIT_OBJECT_0+1)
			{
				bread = false;
				dr = Pipe_ProcessRead();
			}
		}	
		// el pipe se cerro o fallo una operacion sobre el
	}
	PipeClose();
	return dr;
}

DWORD CLogPipe::Initialize()
{
	// Iniciar el hilo
	DWORD	dr;
	for(;;)
	{
		m_err_msg = "CLogPipe Failed to Initialize CMessageEvent";
		dr = CMessageEvent::Initialize();
		if (dr == 1) break;
		
		m_err_msg = "CLogPipe Failed to Create Pipe Read Event";
		m_hpipe_read_event = ::CreateEvent(NULL,FALSE,FALSE,NULL);
		if (m_hpipe_read_event == NULL) break;

		m_err_msg = "CLogPipe Failed to Create Pipe Thread";
		m_hthread = ::CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ThreadProc,this,0,0);
		if (m_hthread == NULL) break;

		return ERR_OK;
	}

	return ERR_FATAL;
}

BOOL CLogPipe::ThreadProcessMessage()
{
	BOOL	br = true;
	DWORD	dr = ERR_OK;
	S_MESSAGE	message;
	
	if (PeekMessage(&message) != 0)	return ERR_FATAL;
	switch (message.Msg)
	{
	case TMSG_THREAD_CLOSE:{br = ERR_FALSE;break;}
	case TMSG_PIPE_OPEN:
		{
			dr = ThreadCreatePipe((char*)message.ExtraData);
			break;
		}
	case TMSG_PIPE_CLOSE:
		{
			PipeClose();
			break;
		}
	default:dr = ERR_PARAM;break;
	}
	ReplyMessage(dr);
	return ERR_OK;	
}

void CLogPipe::PipeClose()
{
	if (m_hpipe != NULL) CloseHandle(m_hpipe);
	m_pipe_status = PIPE_NULL;
	m_hpipe = NULL;
}


DWORD CLogPipe::Thread_Pipe_Read()
{
	// leer datos hasta que agoten
	return ERR_OK;
}

DWORD CLogPipe::Pipe_SetupRead()
{
	while (true)
	{
		if (ReadFile(m_hpipe,m_read_buffer,sizeof(m_read_buffer),&m_read_bytes,&m_pipe_overlapped)==TRUE)
		{
			m_read_bytes = m_pipe_overlapped.InternalHigh;
			Pipe_ProcessRead();
		}
		else
			if (GetLastError() == ERROR_IO_PENDING) 
				return ERR_OK;
			else
				return ERR_FATAL;
	}
	return ERR_OK;
}

DWORD CLogPipe::Pipe_ProcessRead()
{
	// salida a consola de la informacion
	m_read_buffer[m_pipe_overlapped.InternalHigh] = 0;
	printf("%s",m_read_buffer);
	return 0;
}

DWORD CLogPipe::CreatePipe(char *pipe_name)
{
	S_MESSAGE	msg;
	msg.Msg = TMSG_PIPE_OPEN;
	msg.ExtraData = (void*)pipe_name;
	SendMessage(&msg);
	return msg.Result;
}

DWORD CLogPipe::SendMsg(char *msg)
{
	DWORD bw;
	WriteFile(m_hpipe,msg,strlen(msg),&bw,NULL);
	return ERR_OK;
}

void CLogPipe::Pipe_SetName(char *pname)
{
	if (pname != NULL) 
		strcpy(m_pipe_name,pname);
	else
		m_pipe_name[0] = 0;
}
