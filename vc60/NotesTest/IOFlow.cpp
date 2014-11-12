// IOFlow.cpp: implementation of the CIOFlow class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IOFlow.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

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
		}
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

DWORD CIOFlow::Read(BYTE *buffer, DWORD dwSize, DWORD *pBytesRead)
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

DWORD CIOFlow::OnWriteEvent()
{
	return ERR_OK;
}

DWORD CIOFlow::MsgWaitEvents(WORD* pwIOEvent,DWORD dwWakeMask,DWORD milliseconds)
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

DWORD CIOFlow::WaitEvents(WORD *pwIOEvent, DWORD milliseconds)
{
	return ERR_OK;
}
