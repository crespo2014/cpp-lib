// CSerialPort.cpp: implementation of the CSerialPort class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SerialPort.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSerialPort::CSerialPort()
{
	CommTimeOuts.ReadIntervalTimeout=2;			// 2 ms entre cada byte
	CommTimeOuts.ReadTotalTimeoutConstant=0;
	CommTimeOuts.ReadTotalTimeoutMultiplier=0;
	CommTimeOuts.WriteTotalTimeoutConstant=2;
	CommTimeOuts.WriteTotalTimeoutMultiplier=1000;
	ZeroMemory(&dcb,sizeof(DCB));
	dcb.DCBlength=sizeof(DCB);
	dcb.BaudRate=CBR_19200;
	dcb.fBinary=true;
	dcb.fParity=false;
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
	dcb.Parity=SPACEPARITY;
	dcb.StopBits=ONESTOPBIT;
	EventMask=EV_BREAK|EV_CTS|EV_DSR|EV_ERR;
	ZeroMemory(&EventOverlapped,sizeof(OVERLAPPED));
	hEventEvent = NULL;
	hPort = NULL;
	hReadEvent = NULL;
	hThread = NULL;
	hWriteEvent = NULL;
	OnOpen = false;
	strcpy(Port,"COM2");
	ReadBufferLen = 1024;
	ZeroMemory(&ReadOverlapped,sizeof(OVERLAPPED));
	TimeOut=INFINITE;
	ZeroMemory(&WriteOverlapped,sizeof(OVERLAPPED));

	lpICommunicationEvents = NULL;
	m_ReadOffset = 5;
	m_WriteOffset = 5;
	m_OnSending = FALSE;

	OnInitialize = FALSE;
}

CSerialPort::~CSerialPort()
{
	if (OnInitialize == FALSE)
		return;
	//detener el hilo
}

DWORD CSerialPort::SetPort(BYTE port)
{
	if (port > 4)
		return 2;
	sprintf(Port,"COM%d",port);
	return 0;
}

DWORD CSerialPort::OpenPort()
{
	if (OnOpen) return 0;
	hPort=CreateFile(Port,GENERIC_READ+GENERIC_WRITE,
		0,NULL,OPEN_EXISTING,FILE_FLAG_OVERLAPPED,0);

	if (hPort==INVALID_HANDLE_VALUE)
	{
		return 2;
	}
	if (GetFileType(hPort)!=FILE_TYPE_CHAR)
	{
		CloseHandle(hPort);
		return 2;
	}
	OnOpen=TRUE;
	SetCommMask(EventMask);
	SetCommTimeouts(hPort,&CommTimeOuts);
	ApplyConfiguration();
	S_MESSAGE	Message; 
	Message.Msg=PORT_OPEN;
	SendMessage(&Message);
	return 0;
}

DWORD CSerialPort::Initialize()
{
	if (OnInitialize == TRUE)
		return 0;
	if (CMessageEvent::Initialize() == 1)
		return 1;
	hEventEvent = ::CreateEvent(NULL,FALSE,FALSE,NULL);
	if (hEventEvent == NULL) return 1;
	hReadEvent = ::CreateEvent(NULL,FALSE,FALSE,NULL);
	if (hReadEvent == NULL) goto failed_2;
	hWriteEvent = ::CreateEvent(NULL,FALSE,FALSE,NULL);
	if (hWriteEvent == NULL) goto failed_3;
	hThread = ::CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ThreadProc,this,0,0);
	if (hThread == NULL) goto failed_4;
	if (!::SetThreadPriority(hThread,THREAD_PRIORITY_TIME_CRITICAL)) goto failed_5;
	EventOverlapped.hEvent = hEventEvent;
	ReadOverlapped.hEvent = hReadEvent;
	WriteOverlapped.hEvent = hWriteEvent;
	OnInitialize = TRUE;
	return 0;
failed_5: CloseHandle(hThread);
failed_4: CloseHandle(hWriteEvent);
failed_3: CloseHandle(hReadEvent);
failed_2: CloseHandle(hEventEvent);
	return 1;
}

UINT CSerialPort::ThreadProc(LPVOID pParam)
{
	return ((CSerialPort*)pParam)->Thread();
}

UINT CSerialPort::Thread()
{
	HANDLE	Events[4];
	Events[0] = hReadEvent;
	Events[1] = hWriteEvent;
	Events[2] = hEventEvent;
	GetSendEventHandle(&Events[3]);
	while (true)
	{
		if (ThreadGetMessage() == 1)
			break;
		if (OnOpen == TRUE)
		{
			if (SetupRead() == 1)
				return 1;
			if (SetupCommEvent() == 1)
				return 1;
		}
		while (OnOpen == TRUE)
		{
			switch(WaitForMultipleObjects(4,Events,FALSE,TimeOut))
			{
			case WAIT_OBJECT_0:
				{
					if (lpICommunicationEvents)
						lpICommunicationEvents->OnReceivedData(ReadBuffer,ReadOverlapped.InternalHigh);
					if (SetupRead() == 1)
						return 1;
					break;
				}
			case WAIT_OBJECT_0+1:
				{
					m_OnSending = FALSE;
					if (lpICommunicationEvents)
						lpICommunicationEvents->OnSendBytes(WriteBuffer,WriteOverlapped.InternalHigh);
					break;
				}
			case WAIT_OBJECT_0+2:
				{
					if (lpICommunicationEvents)
						lpICommunicationEvents->OnCommEvent(EventType);
					if (SetupCommEvent() == 1)
						return 1;
					break;
				}
			case WAIT_OBJECT_0+3:
				{
					if (ThreadProcessMessage() == 1)
						return 1;
					break;
				}
			case WAIT_TIMEOUT:
				{
					if (lpICommunicationEvents)
						lpICommunicationEvents->OnWaitTimeOut();
					break;
				}
			default :
				{
					return 1;
				}
			} //switch
		}//while
	}
	return 0;
}


DWORD CSerialPort::SendBuffer(BYTE *pBuffer, DWORD pCant)
/*
	Esta funcion es llamada solo desde el hilo
*/
{
	if (OnOpen == FALSE)
		return 2;
	DWORD NumberOfBytesWritten;
//	WriteBuffer = pBuffer;
	if (WriteFile(hPort,pBuffer,pCant,&NumberOfBytesWritten,&WriteOverlapped)==TRUE)
	{
		if (lpICommunicationEvents)
			lpICommunicationEvents->OnSendBytes(WriteBuffer,NumberOfBytesWritten);
		return 0;
	}
	if (GetLastError() != ERROR_IO_PENDING)
		return 1;
	return 0;
}

DWORD CSerialPort::SetupRead()
{
	while (true)
	{
		if (ReadFile(hPort,&ReadBuffer[m_ReadOffset],ReadBufferLen,&BytesRead,&ReadOverlapped)==TRUE)
		{
			if (lpICommunicationEvents)
				lpICommunicationEvents->OnReceivedData(ReadBuffer,ReadOverlapped.InternalHigh);
		}
		else
			if (GetLastError() == ERROR_IO_PENDING) 
				return 0;
			else
				return 1;
	}
}

DWORD CSerialPort::SendThreadMessage(LP_MESSAGE lpMessage)
{
	if (lpMessage->Msg < 100)
		return 2;
	return SendMessage(lpMessage);
}

DWORD CSerialPort::SetWaitTimeOut(DWORD pTimeOut)
{
	TimeOut = pTimeOut;
	return 0;
}

DWORD CSerialPort::ThreadProcessMessage()
{
	S_MESSAGE	message;
	DWORD	result=0;
	if (PeekMessage(&message) != 0)
		return 0;
	switch (message.Msg)
	{
	case PORT_OPEN:
	case PORT_CLOSE:
		{
			break;
		}
	case THREAD_CLOSE:
		{
			result=1;
			break;
		}
	default:
		{
			if (lpICommunicationEvents)
				lpICommunicationEvents->OnProcessMessage(&message);
			break;
		}
	}
	ReplyMessage(0);
	return result;
}

DWORD CSerialPort::Configure()
{
	if (OnOpen == FALSE) 
		return 2;
	if (SetCommState(hPort,&dcb) == FALSE)
		return 2;
	return 0;
}


DWORD CSerialPort::ThreadGetMessage()
{
	WaitMessage();
	return ThreadProcessMessage();
}

DWORD CSerialPort::ClosePort()
{
	if (!OnOpen) return 0;
	OnOpen = FALSE;
	S_MESSAGE Message;
	Message.Msg=PORT_CLOSE;
	SendMessage(&Message);
	PurgeComm(hPort,PURGE_TXABORT+PURGE_RXABORT+PURGE_TXCLEAR+PURGE_RXCLEAR);
	::SetCommMask(hPort,0);
	CloseHandle(hPort);
	ResetEvent(hReadEvent);
	ResetEvent(hWriteEvent);
	ResetEvent(hEventEvent);
	return 0;
}

DWORD CSerialPort::IsOpen()
{
	return OnOpen;
}

DWORD CSerialPort::SetReadBufferLen(DWORD BufferLen)
{
	if (BufferLen > 1024)
		return 1;
	ReadBufferLen = BufferLen;
	return 0;
}

DWORD CSerialPort::SetupCommEvent()
{
	while (true)
	{
		if (WaitCommEvent(hPort,&EventType,&EventOverlapped)==TRUE)
		{
			if (lpICommunicationEvents)
				lpICommunicationEvents->OnCommEvent(EventType);
		}
		else
			if (GetLastError() == ERROR_IO_PENDING) 
				return 0;
			else
				return 1;
	}
	return 0;
}

DWORD CSerialPort::SetCommMask(DWORD dwEvtMask)
{
	EventMask = dwEvtMask;
	if (OnOpen == TRUE)
	{
		if (::SetCommMask(hPort,EventMask) == FALSE)
			return 2;
	}
	return 0;
}

DWORD CSerialPort::SetPortConfiguration(DWORD dwBaudRate, BYTE ByteSize, BYTE Parity, BYTE StopBits)
{
	dcb.BaudRate = dwBaudRate;
	dcb.ByteSize = ByteSize;
	dcb.Parity = Parity;
	dcb.StopBits = StopBits;
	return ApplyConfiguration();
}

DWORD CSerialPort::EnableParity(BOOL bEnable)
{
	dcb.fParity = bEnable;
	return ApplyConfiguration();
}

DWORD CSerialPort::SetParity(BYTE bParity)
{
	dcb.Parity = bParity;
	return ApplyConfiguration();
}

DWORD CSerialPort::ApplyConfiguration()
{
	if (OnOpen == TRUE)
	{
		if (::SetCommState(hPort,&dcb) == FALSE)
		{
			::GetCommState(hPort,&dcb);
			return 2;
		}
	}
	return 0;
}

DWORD CSerialPort::CancelSendBuffer()
{
	if (OnOpen == FALSE)
		return 0;
	if (PurgeComm(hPort,PURGE_TXABORT|PURGE_TXCLEAR)== FALSE)
		return 1;
	ResetEvent(hWriteEvent);
	return 0;
}

DWORD CSerialPort::SetCommunicationEvents(LPCOMMUNICATIONEVENTS plpCommunicationEvents)
{
	lpICommunicationEvents = plpCommunicationEvents;
	return 0;
}

DWORD CSerialPort::Release()
{
	return 0;
}

DWORD CSerialPort::ConfigurePort(DWORD dwBaudRate, BYTE bParity, BYTE bStopBits, BYTE bByteSize, DWORD dwDSR,DWORD dwCTS,DWORD dwCheckParity,DWORD dwRTS,DWORD dwDTR)
{
	dcb.BaudRate = dwBaudRate;
	dcb.Parity = bParity;
	dcb.StopBits = bStopBits;
	dcb.ByteSize = bByteSize;
	dcb.fDsrSensitivity = dwDSR;
	dcb.fOutxCtsFlow = dwCTS;
	dcb.fParity = dwCheckParity;
	dcb.fRtsControl = dwRTS;
	dcb.fDtrControl = dwDTR;
	return ApplyConfiguration();
}

DWORD CSerialPort::GetPortConfiguration(DWORD *lpdwBaudRate, DWORD *lpdwParity, BYTE *lpbStopBits, BYTE *lpbByteSize, DWORD *lpdwDSR, DWORD *lpdwCTS, DWORD *lpdwCheckParity, DWORD *lpdwRTS, DWORD *lpdwDTR)
{
	*lpdwBaudRate = dcb.BaudRate;
	*lpdwParity = dcb.Parity;
	*lpbStopBits = dcb.StopBits;
	*lpbByteSize = dcb.ByteSize;
	*lpdwDSR = dcb.fDsrSensitivity;
	*lpdwCTS = dcb.fOutxCtsFlow;
	*lpdwCheckParity = dcb.fParity;
	*lpdwRTS = dcb.fRtsControl;
	*lpdwDTR = dcb.fDtrControl;
	return 0;
}

DWORD CSerialPort::GetWriteBuffer(BYTE **lpbBuffer, DWORD *lpdwSize)
{
	if (m_OnSending)
		return 1;
	*lpbBuffer = &WriteBuffer[m_WriteOffset];
	*lpdwSize = BUFFERSIZE - m_WriteOffset;
	return 0;
}

DWORD CSerialPort::Send(DWORD dwCant)
{
	if (m_OnSending) return 1;
	m_OnSending = TRUE;
	DWORD NumberOfBytesWritten;
	if (WriteFile(hPort,&WriteBuffer[m_WriteOffset],dwCant,&NumberOfBytesWritten,&WriteOverlapped)==TRUE)
	{
		m_OnSending = FALSE;
		if (lpICommunicationEvents)
			lpICommunicationEvents->OnSendBytes(WriteBuffer,NumberOfBytesWritten);
		return 0;
	}
	if (GetLastError() != ERROR_IO_PENDING)
		return 1;
	return 0;	
}

