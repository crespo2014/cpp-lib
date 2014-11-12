// IOFlow.h: interface for the CIOFlow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IOFLOW_H__9139CD5C_83D2_44C9_A302_397A09DFF410__INCLUDED_)
#define AFX_IOFLOW_H__9139CD5C_83D2_44C9_A302_397A09DFF410__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bObject.h"

// condiciones de un wait
#define IO_ONNONE	0		// sin evento o timeot
#define IO_ONREAD	1		// evento de lectura
#define IO_ONWRITE	2		// evento de escritura
#define IO_ONMSG	3		// evento de mensaje en la cola
#define IO_ONEVENT	4		// indica que se ha activado el evento del usuario

class CIOFlow : public CbObject  
{
public:
	DWORD Open(char* name,DWORD AccessMode,DWORD ShareMode,LPSECURITY_ATTRIBUTES lpSecurityAttributes,DWORD dwCreationMode,DWORD Attributes);
	DWORD PipeConnectionAccept();
	DWORD Write(void* buffer, DWORD dwSize,DWORD* BytesWritten);
	DWORD PipeCreateNew(char* pipe_name,DWORD nOutBufferSize = 512, DWORD nInBufferSize = 512, DWORD nDefaultTimeOut = 5000);
	DWORD PipeConnect(char* pipe_name,DWORD AccessMode = (GENERIC_READ|GENERIC_WRITE));
	DWORD WaitPipe(char* pipe_name,DWORD timeout = NMPWAIT_WAIT_FOREVER);
	DWORD WaitEvent_Flow(HANDLE hevent,WORD *pwEventType, DWORD milliseconds = INFINITE);
	DWORD Wait_Flow(WORD* pwIOEvent,DWORD milliseconds = INFINITE);
	DWORD WaitMsg_Flow(WORD* pwIOEvent,DWORD dwWakeMask = (QS_ALLEVENTS|QS_ALLINPUT|QS_ALLPOSTMESSAGE),DWORD milliseconds = INFINITE);
	DWORD OnWriteEvent(DWORD *pBytesWritten);
	DWORD OnReadEvent(DWORD *pBytesRead);
	DWORD Read(void* buffer,DWORD dwSize,DWORD* pBytesRead);
	DWORD Close();
	DWORD CreateNamedPipe(char* pipe_name,DWORD dwOpenMode,DWORD dwPipeMode,DWORD nMaxInstances,DWORD nOutBufferSize,DWORD nInBufferSize,DWORD nDefaultTimeOut,LPSECURITY_ATTRIBUTES lpSecurityAttributes = NULL);
	DWORD EnableAsyncMode(BOOL bEnable);
	void	GetReadEventHandle(HANDLE* phandle) {*phandle = m_hrdEvent;};
	CIOFlow();
	virtual ~CIOFlow();
private:
	HANDLE		m_fhandle;			// handle del flow
	OVERLAPPED	m_rdOverlapped;
	OVERLAPPED	m_wrOverlapped;
	HANDLE		m_hrdEvent;
	HANDLE		m_hwrEvent;
	BOOL		m_bWritten;			// operacion de escritura en curso
	BOOL		m_bAsyncMode;		// Modo asyncronico de operacion
	char		m_flow_name[300];	// nombre del flujo (fichero, pipe, etc)
	DWORD		*m_pBytesRead;		// indica los bytes leidos 
};

#endif // !defined(AFX_IOFLOW_H__9139CD5C_83D2_44C9_A302_397A09DFF410__INCLUDED_)

/*

DWORD ReadIntervalTimeout; 
  DWORD ReadTotalTimeoutMultiplier; 
  DWORD ReadTotalTimeoutConstant; 
  DWORD WriteTotalTimeoutMultiplier; 
  DWORD WriteTotalTimeoutConstant; 
*/