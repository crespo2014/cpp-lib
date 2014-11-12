// CSerialPort.cpp: implementation of the CSerialPort class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SerialPort.h"
#include "errorcodes.h"
#include "stdio.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// Mensajes enviados por el hilo que atiende el puerto
#define THREAD_CLOSE	0
#define PORT_OPEN		1
#define PORT_CLOSE		2
#define THREAD_INIT		3
#define TH_REQUESTDATA	4
#define M_LAST			100

DWORD _stdcall CSerialPort::DeleteObject()
{
	DWORD dr;
	dr = UnInitialize();
	DLLDestroyInstance(this);
	return dr;				
}

DWORD _stdcall CSerialPort::Initialize()
{
	if (m_ISerialPortEvents == NULL) 
		return ERR_NOINTERFACE;
	DWORD	dr;
	DWORD threadId;
	if (OnInitialize == TRUE) return ERR_NONE;
	dr = CMessageEvent::Initialize();
	if (dr != 0) return dr;
	for(;;)
	{
		m_hTriggerEvent = ::CreateEvent(NULL,FALSE,FALSE,NULL);
		if (m_hTriggerEvent == NULL) break;
		hEventEvent = ::CreateEvent(NULL,FALSE,FALSE,NULL);
		if (hEventEvent == NULL) break;
		hReadEvent = ::CreateEvent(NULL,FALSE,FALSE,NULL);
		if (hReadEvent == NULL) break;
		hWriteEvent = ::CreateEvent(NULL,FALSE,FALSE,NULL);
		if (hWriteEvent == NULL) break;
		EventOverlapped.hEvent = hEventEvent;
		ReadOverlapped.hEvent = hReadEvent;
		WriteOverlapped.hEvent = hWriteEvent;
		hThread = ::CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ThreadProc,this,0,&threadId);
		if (hThread == NULL) break;
		if (!::SetThreadPriority(hThread,THREAD_PRIORITY_TIME_CRITICAL)) break;
		OnInitialize = TRUE;
		return 0;
	};
	UnInitialize();
	m_LastError = ::GetLastError();
	return ERR_APIFAIL;
}
DWORD _stdcall CSerialPort::GetInterfaz(char* lpName,void** lpInterfaz)
{
	*lpInterfaz = NULL;
	if (strcmp(lpName,"ISerialPort") == 0) *lpInterfaz = (ISerialPort*)this;
	if (*lpInterfaz == NULL) return ERR_NOINTERFACE;
	return ERR_NONE;
}

DWORD _stdcall CSerialPort::Attach(_IUnknown* lpInterfaz)
{
	DWORD	dr;
	m_ISerialPortEvents = NULL;
	dr = lpInterfaz->GetInterfaz("ISerialPortEvents",(void**)&m_ISerialPortEvents);
	if ((dr == ERR_NONE) && (m_ISerialPortEvents))
		m_ISerialPortEvents->OnSetSerialPort(this);
	else
		return ERR_NOINTERFACE;
	return dr;
}

DWORD _stdcall CSerialPort::SetCommunicationMode(DWORD bAsyncRead,DWORD WaitTimeout,LPVOID lpParam,DWORD ReadBufferLen)
{
	m_OnAsyncRead = bAsyncRead;
	TimeOut = WaitTimeout;
	m_lpParam = lpParam;
	if ((ReadBufferLen == -1) || (ReadBufferLen > BUFFERSIZE))
		m_ReadBufferLen = BUFFERSIZE;
	else
		m_ReadBufferLen = ReadBufferLen;
	return 0;
}

DWORD _stdcall CSerialPort::SetPort(BYTE port)
{
	if (m_hPort) return ERR_OPEN;
	Port = port;
	return ERR_NONE;
}

DWORD _stdcall CSerialPort::SetReadTimeOuts(DWORD Interval,DWORD Total,DWORD Multiplier)
{
	if (m_hPort == NULL) return ERR_CLOSE;
	CommTimeOuts.ReadIntervalTimeout=Interval;		
	CommTimeOuts.ReadTotalTimeoutConstant=Total;
	CommTimeOuts.ReadTotalTimeoutMultiplier=Multiplier;
	if (::SetCommTimeouts(m_hPort,&CommTimeOuts) == FALSE) return ERR_APIFAIL;
	return ERR_NONE;
}

DWORD _stdcall CSerialPort::SetTrigger()
{
	SetEvent(m_hTriggerEvent);
	return 0;
}

DWORD _stdcall CSerialPort::SetPortConfiguration(PORT_CONFIG* lpPortConfig)
{
	if (m_hPort == NULL) return ERR_CLOSE;
	dcb.BaudRate		= lpPortConfig->BaudRate;
	dcb.Parity			= lpPortConfig->Parity;
	dcb.StopBits		= lpPortConfig->StopBits;
	dcb.ByteSize		= lpPortConfig->ByteSize;
	dcb.fOutxDsrFlow	= lpPortConfig->DSRStopOutFlow;
	dcb.fDsrSensitivity = lpPortConfig->DSRStopInFlow;
	dcb.fOutxCtsFlow	= lpPortConfig->CTSStopOutFlow;
	dcb.fParity			= lpPortConfig->CheckParity;
	dcb.fRtsControl		= lpPortConfig->RTSMode;
	dcb.fDtrControl		= lpPortConfig->DTRMode;
	if (::SetCommState(m_hPort,&dcb) == FALSE) return ERR_APIFAIL;
	return ERR_NONE;
}

DWORD _stdcall CSerialPort::GetThreadError()		// Estado del hilo
{
	return m_ThreadError;
}

DWORD _stdcall CSerialPort::GetThreadLastError()	// Error extendido del hilo depende del tipo de error
{
	return m_ThreadLastError;
}

DWORD _stdcall CSerialPort::GetLastError()			// Error extendido
{
	return m_LastError;
}

DWORD _stdcall CSerialPort::ThreadRead(BYTE* lpBuffer,DWORD dwCant)
{
	if (lpBuffer == NULL) 
	{
		m_ReadBuffer = m_RDBuffer;
		dwCant = m_ReadBufferLen;
	}
	else
		m_ReadBuffer = lpBuffer;
	for (;;)
	{
		if (ReadFile(m_hPort,m_ReadBuffer,dwCant,&BytesRead,&ReadOverlapped)==TRUE)
		{
				m_ISerialPortEvents->OnReceivedData(m_ReadBuffer,ReadOverlapped.InternalHigh,m_lpParam);
		}
		else
		{
			DWORD error = ::GetLastError();
			if (error != ERROR_IO_PENDING) 
			{
				m_ThreadLastError = error;
				m_ThreadError = ERR_APIFAIL;
			}
			return ERR_NONE;
		}
		if (!m_OnAsyncRead) return ERR_NONE;	// Solo una lectura
	}
	return ERR_NONE;
}


CSerialPort::CSerialPort()
{
	CommTimeOuts.ReadIntervalTimeout=0;		
	CommTimeOuts.ReadTotalTimeoutConstant=0;
	CommTimeOuts.ReadTotalTimeoutMultiplier=0;
	CommTimeOuts.WriteTotalTimeoutConstant=0;
	CommTimeOuts.WriteTotalTimeoutMultiplier=0;
	ZeroMemory(&dcb,sizeof(DCB));
	dcb.DCBlength=sizeof(DCB);
	dcb.BaudRate=CBR_9600;
	dcb.fBinary=true;
	dcb.fParity=true;
	dcb.fOutxCtsFlow=false;
	dcb.fOutxDsrFlow=false;
	dcb.fDtrControl=DTR_CONTROL_ENABLE;
	dcb.fDsrSensitivity=false;
	dcb.fTXContinueOnXoff=false;
	dcb.fOutX=false;
	dcb.fInX=false;
	dcb.fErrorChar=false;
	dcb.fNull=false;
	dcb.fRtsControl=RTS_CONTROL_ENABLE;
	dcb.fAbortOnError=false;
	dcb.ByteSize=8;
	dcb.Parity=EVENPARITY;
	dcb.StopBits=TWOSTOPBITS;
	EventMask=EV_BREAK|EV_CTS|EV_DSR|EV_ERR;
	ZeroMemory(&EventOverlapped,sizeof(OVERLAPPED));
	hEventEvent = NULL;
	m_hPort = NULL;
	hReadEvent = NULL;
	hThread = NULL;
	hWriteEvent = NULL;
	Port = 2;
	ZeroMemory(&ReadOverlapped,sizeof(OVERLAPPED));
	TimeOut=INFINITE;
	ZeroMemory(&WriteOverlapped,sizeof(OVERLAPPED));

	m_ISerialPortEvents = NULL;
	OnInitialize = FALSE;
	m_hTriggerEvent = NULL;
	m_BytesToSend = 0;
	m_ThreadError = ERR_NONE;
	m_LastError = 0;
	m_ThreadLastError = 0;
	m_OnAsyncRead = true;
	m_ReadBufferLen = BUFFERSIZE;
}

CSerialPort::~CSerialPort()
{

}


DWORD _stdcall CSerialPort::OpenPort()
{
	if (m_ISerialPortEvents == NULL) return ERR_NOINTERFACE;
	m_BytesWritten = 0;
	char cm_hPort[10];
	if (m_hPort != NULL) return ERR_NONE;
	sprintf(cm_hPort,"COM%d",Port);
	m_hPort = CreateFile(cm_hPort,GENERIC_READ+GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_FLAG_OVERLAPPED,0);
	if (m_hPort == INVALID_HANDLE_VALUE)
	{
		m_hPort = NULL;
		return ERR_APIFAIL;
	}
	if (GetFileType(m_hPort)!=FILE_TYPE_CHAR)
	{
		CloseHandle(m_hPort);
		return ERR_APIFAIL;
	}
	EventMask = 0;
	m_ISerialPortEvents->OnOpenPort(m_lpParam);
	S_MESSAGE	Message; 
	Message.Msg=PORT_OPEN;
	SendMessage(&Message);
	return 0;
}

UINT CSerialPort::ThreadProc(LPVOID pParam)
{
	return ((CSerialPort*)pParam)->Thread();
}

UINT CSerialPort::Thread()
{
	HANDLE	Events[5];
	Events[0] = hReadEvent;
	Events[1] = hWriteEvent;
	Events[2] = hEventEvent;
	GetSendEventHandle(&Events[3]);
	Events[4] = m_hTriggerEvent;
	m_ThreadError = ERR_NONE;
	for (;;)
	{
		if (ThreadGetMessage() == 1) return 0;
		if (m_hPort == NULL) continue;
		if (m_ThreadError != ERR_NONE) continue;
		if (m_OnAsyncRead) ThreadRead(NULL,m_ReadBufferLen);
		SetupCommEvent();
		for(;;)
		{
			if (m_hPort == NULL) break;
			if (m_ThreadError != ERR_NONE) break;
			switch(WaitForMultipleObjects(5,Events,FALSE,TimeOut))
			{
			case WAIT_OBJECT_0:
				{
					m_ISerialPortEvents->OnReceivedData(m_ReadBuffer,ReadOverlapped.InternalHigh,m_lpParam);
					if (m_OnAsyncRead) ThreadRead(NULL,m_ReadBufferLen);
					break;
				}
			case WAIT_OBJECT_0+1:
				{
					OnSend(WriteOverlapped.InternalHigh);
					break;
				}
			case WAIT_OBJECT_0+2:
				{
					m_ISerialPortEvents->OnCommEvent(EventType,m_lpParam);
					SetupCommEvent();
					break;
				}
			case WAIT_OBJECT_0+3:
				{
					if (ThreadProcessMessage() == 1)
						return 0;
					break;
				}
			case WAIT_OBJECT_0+4:
				{
					m_ISerialPortEvents->OnTrigger(m_lpParam);
					break;
				}
			case WAIT_TIMEOUT:
				{
					m_ISerialPortEvents->OnWaitTimeOut(m_lpParam);
					break;
				}
			default :
				{
					m_ThreadLastError = ::GetLastError();
					m_ThreadError = ERR_APIFAIL;
					break;
				}
			} 
		}
	}
	return 0;
}

DWORD _stdcall CSerialPort::SendThreadMessage(LP_MESSAGE lpMessage)
{
	if (lpMessage->Msg < 100) return ERR_OUT_RANGE;
	return SendMessage(lpMessage);
}

DWORD CSerialPort::ThreadProcessMessage()
{
	S_MESSAGE	message;
	DWORD	result=0;
	if (PeekMessage(&message) != 0)
		return 0;
	switch (message.Msg)
	{
	case PORT_CLOSE:
		{
			m_hPort = NULL;
			break;
		}
	case PORT_OPEN:
		{
			break;
		}
	case THREAD_CLOSE:
		{
			result=1;
			break;
		}
	case TH_REQUESTDATA:
		{
			message.Result = m_ISerialPortEvents->OnRequestData(m_lpParam);
			break;
		}
	default:
		{
			message.Result = m_ISerialPortEvents->OnProcessMessage(&message,m_lpParam);
			break;
		}
	}
	ReplyMessage(message.Result);
	return result;
}

DWORD CSerialPort::ThreadGetMessage()
{
	WaitMessage();
	return ThreadProcessMessage();
}

DWORD _stdcall CSerialPort::ClosePort()
{
	if (m_hPort == NULL) return 0;
	HANDLE hPort = m_hPort;
	S_MESSAGE Message;
	Message.Msg=PORT_CLOSE;
	SendMessage(&Message);
	PurgeComm(hPort,PURGE_TXABORT+PURGE_RXABORT+PURGE_TXCLEAR+PURGE_RXCLEAR);
	::SetCommMask(hPort,0);
	CloseHandle(hPort);
	m_hPort = NULL;
	ResetEvent(hReadEvent);
	ResetEvent(hWriteEvent);
	ResetEvent(hEventEvent);
	ResetEvent(m_hTriggerEvent);
	return 0;
}

DWORD CSerialPort::SetupCommEvent()
{
	if (EventMask == 0) return 0;
	EventType = 0;
	for (;;)
	{
		if (WaitCommEvent(m_hPort,&EventType,&EventOverlapped)==TRUE)
		{
			if (EventType != 0)
				m_ISerialPortEvents->OnCommEvent(EventType,m_lpParam);
		}
		else
		{
			DWORD error = ::GetLastError();
			if (error != ERROR_IO_PENDING) 
			{
				m_ThreadError = ERR_APIFAIL;
				m_ThreadLastError = error;
			}
			return 0;
		}
	}
	return 0;
}

DWORD _stdcall CSerialPort::SetCommMask(DWORD dwEvtMask)
{
	if (m_hPort == NULL) return ERR_CLOSE;
	EventMask = dwEvtMask;
	if (::SetCommMask(m_hPort,EventMask) == FALSE)
	{
		m_LastError = ::GetLastError();
		return ERR_APIFAIL;
	}
	return ERR_NONE;
}

DWORD _stdcall CSerialPort::CancelSend()
{
	if (m_hPort == NULL) return ERR_CLOSE;
	if (::PurgeComm(m_hPort,PURGE_TXABORT/*|PURGE_TXCLEAR*/)) return ERR_NONE;
	return ERR_APIFAIL;
}

DWORD _stdcall CSerialPort::GetWriteBuffer(BYTE **lpbBuffer, DWORD *lpdwSize)
{
	*lpbBuffer = &m_WRBuffer[0];
	*lpdwSize = BUFFERSIZE;
	return 0;
}

DWORD _stdcall CSerialPort::ThreadSend(BYTE* lpBuffer,DWORD dwCant)
{
	if (!m_hPort) return ERR_CLOSE;
	if (lpBuffer == NULL)
		m_SendBuffer = m_WRBuffer;
	else
		m_SendBuffer = lpBuffer;
	DWORD NumberOfBytesWritten;
	m_BytesToSend = dwCant;
	if (WriteFile(m_hPort,&m_SendBuffer[m_BytesWritten],dwCant,&NumberOfBytesWritten,&WriteOverlapped)==TRUE)
	{
		OnSend(NumberOfBytesWritten);
		return 0;
	}
	if (::GetLastError() != ERROR_IO_PENDING)
	{
		m_ISerialPortEvents->OnSendBytes(NULL,0,m_lpParam);
		return ERR_APIFAIL;
	}
	return 0;	
}

DWORD _stdcall CSerialPort::GetInputSignals(DWORD *lpdwSignals)
{
	if (m_hPort == NULL) return ERR_CLOSE;
	if (::GetCommModemStatus(m_hPort,lpdwSignals)) return ERR_NONE;
	return ERR_APIFAIL;
}

DWORD _stdcall CSerialPort::GetCommunicationError(DWORD* lpErrors)
{
	if (m_hPort == NULL) return ERR_CLOSE;
	if (ClearCommError(m_hPort,lpErrors,NULL)) return 0;
	m_LastError = ::GetLastError();
	return ERR_APIFAIL;
}

DWORD _stdcall CSerialPort::GetPortConfiguration(PORT_CONFIG* lpPortConfig)
{
	lpPortConfig->BaudRate = dcb.BaudRate;
	lpPortConfig->Parity = dcb.Parity;
	lpPortConfig->StopBits = dcb.StopBits;
	lpPortConfig->ByteSize = dcb.ByteSize;
	lpPortConfig->DSRStopInFlow = dcb.fDsrSensitivity;
	lpPortConfig->CTSStopOutFlow = dcb.fOutxCtsFlow;
	lpPortConfig->DSRStopOutFlow = dcb.fOutxDsrFlow;
	lpPortConfig->CheckParity = dcb.fParity;
	lpPortConfig->RTSMode = dcb.fRtsControl;
	lpPortConfig->DTRMode = dcb.fDtrControl;
	return 0;
}

DWORD _stdcall CSerialPort::ChangeOutputSignal(DWORD Operation)
{
	if (m_hPort == NULL) return ERR_CLOSE;
	if (!EscapeCommFunction(m_hPort,Operation))
		return ERR_APIFAIL;
	return 0;
}

DWORD CSerialPort::OnSend(DWORD dwBytesWritten)
{
	DWORD dr;
	m_BytesWritten += dwBytesWritten;
	if (m_BytesToSend < m_BytesWritten)
	{
		dr = ThreadSend(m_SendBuffer,m_BytesToSend-m_BytesWritten);	// enviar los que faltan
		if (dr != ERR_NONE) 
			m_ISerialPortEvents->OnSendBytes(NULL,0,m_lpParam);	// Error
	}
	else
	{
		DWORD written = m_BytesWritten;
		m_BytesWritten = 0;
		m_ISerialPortEvents->OnSendBytes(m_SendBuffer,written,m_lpParam);
	}
	return ERR_NONE;
}

DWORD _stdcall CSerialPort::UnInitialize()
{
	DWORD dr = 0;
	if (OnInitialize == FALSE)	return 0;
	ClosePort();
	S_MESSAGE Message;
	Message.Msg=THREAD_CLOSE;
	dr = SendMessage(&Message);
	if (WaitForSingleObject(hThread,5000) != WAIT_OBJECT_0) dr = ERR_APIFAIL;
	if (!CloseHandle(hThread)) dr = ERR_APIFAIL;
	if (!CloseHandle(hWriteEvent)) dr = ERR_APIFAIL;
	if (!CloseHandle(hReadEvent)) dr = ERR_APIFAIL;
	if (!CloseHandle(hEventEvent)) dr = ERR_APIFAIL;
	hThread = NULL;
	hWriteEvent = NULL;
	hReadEvent = NULL;
	hEventEvent = NULL;
	OnInitialize = FALSE;
//	CMessageEvent::Release();
	return dr;
}

DWORD _stdcall CSerialPort::RequestData()
{
	// Enviar mensaje
	S_MESSAGE	Message; 
	Message.Msg=TH_REQUESTDATA;
	return SendMessage(&Message);
}
