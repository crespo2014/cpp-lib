// IOFlow.cpp: implementation of the CIOFlow class.
//
//////////////////////////////////////////////////////////////////////

#include "IOFlow.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#ifndef FILE_FLAG_FIRST_PIPE_INSTANCE
#define FILE_FLAG_FIRST_PIPE_INSTANCE 0x00080000
#endif


CIOFlow::CIOFlow()
{
	m_fhandle = NULL;
	m_hrdEvent = NULL;
	m_hwrEvent = NULL;
	m_bAsyncMode = false;
	m_bWritten = false;
	ZERO(m_rdOverlapped);
	ZERO(m_wrOverlapped);
}

CIOFlow::~CIOFlow()
{
	Close();
}

DWORD CIOFlow::CreateNamedPipe(char *pipe_name, DWORD dwOpenMode, DWORD dwPipeMode, DWORD nMaxInstances, DWORD nOutBufferSize, DWORD nInBufferSize, DWORD nDefaultTimeOut, LPSECURITY_ATTRIBUTES lpSecurityAttributes)
{
	if ((pipe_name == NULL) || (pipe_name[0] == 0)) return SetError(false,ERR_PARAM,"Invalid name for pipe");
	if (m_fhandle != NULL)							return SetError(false,ERR_OP,"The ioflow is already open");
	sprintf(m_flow_name,"\\\\.\\pipe\\%s",pipe_name);
	
	BOOL bok = false;
	char	*emsg;
	for (;;)
	{
		if (m_bAsyncMode)
		{
			emsg = "CIOFlow::CreateNamedPipe -> ::CreateEvent failed with code ";
			m_hrdEvent =::CreateEvent(NULL,FALSE,FALSE,NULL); if (m_hrdEvent == NULL) break;
			m_hwrEvent =::CreateEvent(NULL,FALSE,FALSE,NULL); if (m_hwrEvent == NULL) break;
			ZERO(m_rdOverlapped);
			ZERO(m_wrOverlapped);
			m_rdOverlapped.hEvent = m_hrdEvent;
			m_wrOverlapped.hEvent = m_hwrEvent;
			dwPipeMode  |= FILE_FLAG_OVERLAPPED;
		}
		else
			dwPipeMode &= (!FILE_FLAG_OVERLAPPED);
		emsg = "CIOFlow::CreateNamedPipe -> ::CreateNamedPipe failed with code ";
		m_fhandle = ::CreateNamedPipe(m_flow_name,dwOpenMode,dwPipeMode,nMaxInstances,nOutBufferSize,nInBufferSize,nDefaultTimeOut,lpSecurityAttributes);
		bok = true;
	}
	if (bok) return ERR_OK;
	SetError_Add_W32_code_msg(false,ERR_FATAL,GetLastError(),emsg);
	Close();
	return ERR_FATAL;
}

DWORD CIOFlow::EnableAsyncMode(BOOL bEnable)
{
	if (m_fhandle != NULL) return SetError(false,ERR_OP,"The ioflow is open can´t change property");
	m_bAsyncMode = bEnable; 
	return ERR_OK;
};

DWORD CIOFlow::Close()
{
	CloseHandle(m_fhandle);
	CloseHandle(m_hrdEvent);
	CloseHandle(m_hwrEvent);
	m_fhandle = NULL;
	m_hrdEvent = NULL;
	m_hwrEvent = NULL;
	m_flow_name[0] = 0;
	ZERO(m_rdOverlapped);
	ZERO(m_wrOverlapped);
	return ERR_OK;
}

DWORD CIOFlow::Read(void *buffer, DWORD dwSize, DWORD *pBytesRead)
{
	DWORD		dwr;
	OVERLAPPED*	poverlapped;
	if (m_bAsyncMode)
		poverlapped = &m_rdOverlapped;
	else
		poverlapped = NULL;
	if(::ReadFile(m_fhandle,buffer,dwSize,pBytesRead,poverlapped)) return ERR_OK;
	dwr = GetLastError();
	switch (dwr)
	{
	case ERROR_HANDLE_EOF:	return ERR_EOF;
	case ERROR_IO_PENDING:	return ERR_PENDING;
	default: 
		return	SetError_Add_W32_code_msg(false,ERR_FATAL,dwr,"CIOFlow::Read .. failed with windows code ");
	}
	return ERR_FATAL;
}

DWORD CIOFlow::OnReadEvent(DWORD *pBytesRead)
{
	if (m_bAsyncMode)
		*pBytesRead = m_rdOverlapped.InternalHigh;
			
	return ERR_OK;
}

DWORD CIOFlow::OnWriteEvent(DWORD *pBytesWritten)
{
	return ERR_OK;
}

DWORD CIOFlow::WaitMsg_Flow(WORD* pwIOEvent,DWORD dwWakeMask,DWORD milliseconds)
{
	HANDLE	aObjects[2];
	DWORD	dwr;

	aObjects[0] = m_hrdEvent;
	aObjects[1] = m_hwrEvent;
	*pwIOEvent = IO_ONNONE;
	dwr = MsgWaitForMultipleObjects(2,aObjects,false,milliseconds,dwWakeMask);
	switch (dwr)
	{
	case WAIT_TIMEOUT: return ERR_TIMEOUT;
	case WAIT_OBJECT_0:
		{
			*pwIOEvent = IO_ONREAD;
			return ERR_OK;
		}
	case WAIT_OBJECT_0+1:
		{
			*pwIOEvent = IO_ONWRITE;
			return ERR_OK;
		}
	case WAIT_OBJECT_0+2:
		{
			*pwIOEvent = IO_ONMSG;
			return ERR_OK;
		}
	}
	/*
	case WAIT_FAILED:
	default:
		{
			return SetError_Add_W32_code_msg(true,ERR_API,GetLastError(),"CIOFlow::MsgWaitEvents ...MsgWaitForMultipleObjects failed ");
		}
	}
	*/
	return SetError_Add_W32_code_msg(true,ERR_API,GetLastError(),"CIOFlow::MsgWaitEvents ...MsgWaitForMultipleObjects failed ");
}

DWORD CIOFlow::Wait_Flow(WORD *pwIOEvent, DWORD milliseconds)
{
	HANDLE	aObjects[2];
	DWORD	dwr;

	aObjects[0] = m_hrdEvent;
	aObjects[1] = m_hwrEvent;
	*pwIOEvent = IO_ONNONE;
	dwr = WaitForMultipleObjects(2,aObjects,false,milliseconds);
	switch (dwr)
	{
	case WAIT_TIMEOUT: return ERR_TIMEOUT;
	case WAIT_OBJECT_0:
		{
			*pwIOEvent = IO_ONREAD;
			return ERR_OK;
		}
	case WAIT_OBJECT_0+1:
		{
			*pwIOEvent = IO_ONWRITE;
			return ERR_OK;
		}
		/*
	case WAIT_OBJECT_0+2:
		{
			*pwIOEvent = IO_ONMSG;
			return ERR_OK;
		}
		*/
	}
	/*
	case WAIT_FAILED:
	default:
		{
			return SetError_Add_W32_code_msg(true,ERR_API,GetLastError(),"CIOFlow::MsgWaitEvents ...MsgWaitForMultipleObjects failed ");
		}
	}
	*/
	return SetError_Add_W32_code_msg(true,ERR_API,GetLastError(),"CIOFlow::MsgWaitEvents ...MsgWaitForMultipleObjects failed ");

	return ERR_OK;
}

DWORD CIOFlow::Open(char *name, DWORD AccessMode, DWORD ShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationMode, DWORD Attributes)
{
	return ERR_OK;
}

DWORD CIOFlow::WaitPipe(char *pipe_name, DWORD timeout)
{
	DWORD	dwr;
	_snprintf(SSIZE(m_flow_name),"\\\\.\\pipe\\%s",pipe_name);
	if (WaitNamedPipe(pipe_name,timeout)) return ERR_OK;
	dwr = GetLastError();
	return ERR_TIMEOUT;
	return SetError_Add_W32_code_msg(true,ERR_API,dwr,"CIOFlow::WaitPipe for %s",m_flow_name);
}

DWORD CIOFlow::PipeConnect(char *pipe_name, DWORD AccessMode)
{
	DWORD	dwr;
	DWORD	dwAttributes;
	WORD	ec = 0;
	_snprintf(SSIZE(m_flow_name),"\\\\.\\pipe\\%s",pipe_name);
	for (;;)
	{
		if (m_bAsyncMode)
		{
			ec = 1;
			m_hrdEvent =::CreateEvent(NULL,FALSE,FALSE,NULL); if (m_hrdEvent == NULL) break;
			m_hwrEvent =::CreateEvent(NULL,FALSE,FALSE,NULL); if (m_hwrEvent == NULL) break;
			ZERO(m_rdOverlapped);
			ZERO(m_wrOverlapped);
			m_rdOverlapped.hEvent = m_hrdEvent;
			m_wrOverlapped.hEvent = m_hwrEvent;
			dwAttributes = FILE_FLAG_OVERLAPPED;
		}
		else
			dwAttributes = 0;
		ec = 2;
		m_fhandle = CreateFile(m_flow_name,AccessMode,0,NULL,OPEN_EXISTING,dwAttributes,NULL);if (m_fhandle == INVALID_HANDLE_VALUE) break;
		return ERR_OK;
	}
	Close();	
	switch (ec)
	{
	case 1: return SetError_Add_W32_code_msg(true,ERR_API,GetLastError(),"CIOFlow::CreateNamedPipe -> ::CreateEvent failed ");
	case 2: return SetError_Add_W32_code_msg(true,ERR_API,GetLastError(),"CIOFlow::OpenPipe -> CreateFile (%s) ... failed ",m_flow_name);
	}
	return ERR_FATAL;
}

/*
	Crea un pipe para actuar como servidor, transmision Duples,byte mode, instancia unica, write_throught
*/
DWORD CIOFlow::PipeCreateNew(char *pipe_name, DWORD nOutBufferSize, DWORD nInBufferSize, DWORD nDefaultTimeOut)
{
	DWORD dwOpenMode;
	char	*func_name;

	_snprintf(SSIZE(m_flow_name),"\\\\.\\pipe\\%s",pipe_name);
	dwOpenMode = PIPE_ACCESS_DUPLEX | FILE_FLAG_FIRST_PIPE_INSTANCE | FILE_FLAG_WRITE_THROUGH;

	for (;;)
	{
		if (m_bAsyncMode) 
		{
			func_name = "CreateEvent";
			m_hrdEvent =::CreateEvent(NULL,FALSE,FALSE,NULL); if (m_hrdEvent == NULL) break;
			m_hwrEvent =::CreateEvent(NULL,FALSE,FALSE,NULL); if (m_hwrEvent == NULL) break;
			dwOpenMode |= FILE_FLAG_OVERLAPPED;
		}
		func_name = "CreateNamedPipe";
		m_fhandle = ::CreateNamedPipe(m_flow_name,dwOpenMode,PIPE_TYPE_BYTE|PIPE_READMODE_BYTE,1,nOutBufferSize,nInBufferSize,nDefaultTimeOut,NULL);
		if (m_fhandle == INVALID_HANDLE_VALUE) break;
		ZERO(m_rdOverlapped);
		ZERO(m_wrOverlapped);
		m_rdOverlapped.hEvent = m_hrdEvent;
		m_wrOverlapped.hEvent = m_hwrEvent;
		return ERR_OK;
	}
	Close();
	return SetError_Add_W32_code_msg(false,ERR_API,GetLastError(),"CIOFlow::CreateNewPipe -> %s failed ... ",func_name);
}

DWORD CIOFlow::Write(void *buffer, DWORD dwSize,DWORD* BytesWritten)
{
	DWORD		dwr;
	OVERLAPPED*	poverlapped;

	if (m_bAsyncMode)
		poverlapped = &m_wrOverlapped;
	else
		poverlapped = NULL;

	poverlapped->Internal = 0;
	poverlapped->InternalHigh = 0;
	poverlapped->Offset = 0;
	poverlapped->OffsetHigh = 0;

	if(::WriteFile(m_fhandle,buffer,dwSize,BytesWritten,poverlapped)) return ERR_OK;
	dwr = GetLastError();
	switch (dwr)
	{
	case ERROR_HANDLE_EOF:	return ERR_EOF;
	case ERROR_IO_PENDING:	return ERR_PENDING;
	default: 
		return	SetError_Add_W32_code_msg(false,ERR_FATAL,dwr,"CIOFlow::Read .. failed with windows code ");
	}
	return ERR_FATAL;
}

DWORD CIOFlow::PipeConnectionAccept()
{
	DWORD		dwr;
	OVERLAPPED*	poverlapped;
	if (m_bAsyncMode)
		poverlapped = &m_rdOverlapped;
	else
		poverlapped = NULL;
	if (ConnectNamedPipe(m_fhandle,poverlapped)) return ERR_OK;
	dwr = GetLastError();
	switch(dwr)
	{
	case ERROR_IO_PENDING:
	case ERROR_PIPE_LISTENING:	return ERR_PENDING;
	case ERROR_PIPE_CONNECTED:	return ERR_OK;
	case ERROR_NO_DATA:			return ERR_EOF;
	}

	return SetError_Add_W32_code_msg(false,ERR_API,dwr,"CIOFlow::ConnectPipe .. ConnectNamedPipe failed ");
}

// Esperar por un evento y por los eventos del flujo
DWORD CIOFlow::WaitEvent_Flow(HANDLE hevent, WORD *pwEventType, DWORD milliseconds)
{
	HANDLE	aObjects[3];
	DWORD	dwr;

	aObjects[0] = m_hrdEvent;
	aObjects[1] = m_hwrEvent;
	aObjects[2] = hevent;
	*pwEventType = IO_ONNONE;
	dwr = WaitForMultipleObjects(3,aObjects,false,milliseconds);
	switch (dwr)
	{
	case WAIT_TIMEOUT: return ERR_TIMEOUT;
	case WAIT_OBJECT_0:
		{
			*pwEventType = IO_ONREAD;
			return ERR_OK;
		}
	case WAIT_OBJECT_0+1:
		{
			*pwEventType = IO_ONWRITE;
			return ERR_OK;
		}
	case WAIT_OBJECT_0+2:
		{
			*pwEventType = IO_ONEVENT;
			return ERR_OK;
		}
	}
	/*
	case WAIT_FAILED:
	default:
		{
			return SetError_Add_W32_code_msg(true,ERR_API,GetLastError(),"CIOFlow::MsgWaitEvents ...MsgWaitForMultipleObjects failed ");
		}
	}
	*/
	return SetError_Add_W32_code_msg(true,ERR_API,GetLastError(),"CIOFlow::MsgWaitEvents ...MsgWaitForMultipleObjects failed ");
}
