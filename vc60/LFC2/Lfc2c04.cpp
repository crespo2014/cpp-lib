// LFC10C01.cpp: implementation of the CAsyncCommPort class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LFC2C04.h"
#include "lfc2def.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAsyncCommPort::CAsyncCommPort()
{
	hReadEvent=NULL;
	hSendEvent=NULL;
	hEventEvent=NULL;
	ReadThread=NULL;
	VFOnProcessMessage	= SFOnProcessMessage;
	VFOnReceiveData		= SFOnReceiveData;
	VFOnWaitTimeOut		= SFOnWaitTimeOut;
	m_OnConstructor=true;
}

CAsyncCommPort::~CAsyncCommPort()
{
	Release();
}

int CAsyncCommPort::SetWaitTimeOut(long pTimeOut)
{
	WaitTimeOut=pTimeOut;
	return true;
}

int CAsyncCommPort::SetBufferLen(long pBufferLen)
{
	if (OnOpen)
		return false;
	if (pBufferLen > BufferLen)
	{
		delete Buffer;
		Buffer= new unsigned char[pBufferLen];
	}
	BufferLen=pBufferLen;
	return true;
}

int CAsyncCommPort::OnCommEvent(DWORD pEventMask)
{
	return true;
}

int CAsyncCommPort::OnReceiveData(BYTE *pBuffer, DWORD pCant)
{
	return true;
}

int CAsyncCommPort::OnWaitTimeOut()
{
	return true;
}

int CAsyncCommPort::OnProcessMessage(S_MESSAGE *pMessage)
{
	// si esta funcion devuelve true el mensaje es replicado 
	// de lo contrario el mensaje no se replica
	return true;
}

UINT CAsyncCommPort::ThreadProc(LPVOID pParam)
{
	return ((CAsyncCommPort*)pParam)->ThreadMain();
}

int CAsyncCommPort::ThreadMain()
{
	HANDLE m_HEvents[3];
	m_HEvents[0]=hReadEvent;
	m_HEvents[1]=hEventEvent;
	m_HEvents[2]=GetSendEventHandle();
	while (true)
	{
		if (!ThreadGetMessage())
			break;
		if (OnOpen)
		{
			SetupReadEvent();
			SetupCommEvent();
			do
			{
				switch(WaitForMultipleObjects(3,m_HEvents,false,WaitTimeOut))
				{
				case WAIT_OBJECT_0:
					{
						if (ReadOverlapped.InternalHigh !=0)
						{
							VFOnReceiveData(this,
								Buffer,
								ReadOverlapped.InternalHigh);
						}
						SetupReadEvent();
						break;
					}
				case WAIT_OBJECT_0+1:
					{
						VFOnCommEvent(this,EventMask);
						SetupCommEvent();
						break;
					}
				case WAIT_OBJECT_0+2:
					{
						if (!ThreadProcessMessage())
							return 0;
						break;
					}
				case WAIT_FAILED:
					{
						break;
					}
				case WAIT_TIMEOUT:
					{
						VFOnWaitTimeOut(this);
					}
				default: break;
				}
			} while (OnOpen);
		}
	}
	return 0;
}

int CAsyncCommPort::SetPort(char *pPortName)
{
	strcpy(PortName,pPortName);
	return true;
}

int CAsyncCommPort::ThreadGetMessage()
{
	WaitMessage();
	return ThreadProcessMessage();
}

int CAsyncCommPort::ThreadProcessMessage()
{
	S_MESSAGE	Message;
	int			Result=0;
	int			Return= true;
	if (!PeekMessage(&Message))
		return true;

	switch (Message.Msg)
	{
	case UM_PORT_OPEN:
		{
			OnOpen=true;
			break;
		}
	case UM_PORT_CLOSE:
		{
			OnOpen=false;
			break;
			
		}
	case UM_THREAD_CLOSE:
		{
			Return=false;
			break;
		}
	default:
		{
			if (!VFOnProcessMessage(this,&Message))
				return true;
			break;
		}
	}
	ReplyMessage(Result);
	return Return;
}

int CAsyncCommPort::SetupCommEvent()
{
	return true;
}

int CAsyncCommPort::SetupReadEvent()
{
	while (true)
	{
		if (!ReadFile(PortHandle,
			Buffer,BufferLen,
			&BytesRead,
			&ReadOverlapped))
		{
			if (GetLastError()==ERROR_IO_PENDING)
				return true;
			AfxMessageBox("Critical error ... Close the program");
		}  else
			OnReceiveData(Buffer,
			ReadOverlapped.InternalHigh);
	}
}

int CAsyncCommPort::ApplyConfiguration()
{
	char Msg[100];
	if (!OnOpen)
		return false;
	if (SetCommState(PortHandle,&dcb)) 
		return true;

	DWORD Error=GetLastError();
	sprintf(Msg," Error %d Appling Configuration \r to Comunication Port \r See Help for details ",Error);
	MessageBox(AfxGetApp()->GetMainWnd()->m_hWnd,Msg,"Comunication Configuration",MB_OK|MB_ICONINFORMATION|MB_APPLMODAL);
	return false;
}

int CAsyncCommPort::OpenPort()
{
	char	MsgError[100];
	if (OnOpen) return true;
	
	PortHandle=CreateFile(PortName,
		GENERIC_READ+GENERIC_WRITE,
		0,NULL,OPEN_EXISTING,FILE_FLAG_OVERLAPPED,0);

	if (PortHandle==INVALID_HANDLE_VALUE)
	{
		DWORD Error=GetLastError();
		sprintf(MsgError," Error %d Opening Comunication Port \r	See Help for details ",Error);
		MessageBox(AfxGetApp()->GetMainWnd()->m_hWnd,MsgError,"Comunication",MB_OK|MB_ICONINFORMATION|MB_APPLMODAL);
		return false;
	}
	if (GetFileType(PortHandle)!=FILE_TYPE_CHAR)
	{
		CloseHandle(PortHandle);
		return false;
	}

	OnOpen=true;
	DWORD size=sizeof(COMMCONFIG);

	GetCommProperties	(PortHandle,&CommProp);
	SetCommMask			(PortHandle,EventMask);
	SetCommMask			(PortHandle,0);
	SetCommTimeouts		(PortHandle,&CommTimeOuts);
	ApplyConfiguration();
	S_MESSAGE	Message;
	Message.Msg=UM_PORT_OPEN;
	SendThreadMessage(&Message);
	return true;
}

int CAsyncCommPort::SendThreadMessage(S_MESSAGE *pMessage)
{
	return SendMessage(pMessage);
}

int CAsyncCommPort::SendBuffer(BYTE *pBuffer, DWORD pCant)
{
	DWORD m_Error;
	if(!OnOpen)
		return false;
	DWORD NumberOfBytesWritten;
	if (WriteFile(PortHandle,pBuffer,pCant,&NumberOfBytesWritten,&WriteOverlapped))
		return true;
	m_Error=GetLastError();
	if (m_Error=ERROR_IO_PENDING)
	{
		if (WaitForSingleObject(hWriteEvent,5000)==WAIT_OBJECT_0)
			return true;
	}
	PurgeComm(PortHandle,PURGE_TXABORT+PURGE_TXCLEAR);
	return false;	
}
int CAsyncCommPort::SetBaudRate(DWORD pBaudRate)
{
	dcb.BaudRate=pBaudRate;
	return ApplyConfiguration();
}

int CAsyncCommPort::SetParity(DWORD pParity)
{
	dcb.fParity=pParity;
	return ApplyConfiguration();
}

int CAsyncCommPort::SetByteSize(BYTE pByteSize)
{
	dcb.ByteSize=pByteSize;
	return ApplyConfiguration();
}

int CAsyncCommPort::SetStopBits(BYTE pStopBits)
{
	dcb.StopBits=pStopBits;
	return ApplyConfiguration();
}

int CAsyncCommPort::ClosePort()
{
	if (!OnOpen)
		return true;
	S_MESSAGE Message;
	Message.Msg=UM_PORT_CLOSE;
	SendThreadMessage(&Message);
	PurgeComm(PortHandle,
		PURGE_TXABORT+PURGE_RXABORT+PURGE_TXCLEAR+PURGE_RXCLEAR);
	SetCommMask(PortHandle,0);
	CloseHandle(PortHandle);
	return true;
}

BOOL CAsyncCommPort::IsOpen()
{
	return OnOpen;
}

DWORD CAsyncCommPort::Initialize()
{
	if (m_OnInitialize)
		return 1;
	if (CMessageEvent::Initialize()!=0)
		return 1;

	VFOnProcessMessage	= SFOnProcessMessage;
	VFOnReceiveData		= SFOnReceiveData;
	VFOnWaitTimeOut		= SFOnWaitTimeOut;

	strcpy(PortName,COM2);
	BufferLen=0;
	Buffer=NULL;
	BytesToRead=0;
	WaitTimeOut=INFINITE;
	PortHandle=NULL;
	OnOpen=false;
	EventMask=EV_BREAK+EV_ERR;
	ZeroMemory(&ReadOverlapped,sizeof(OVERLAPPED));
	ZeroMemory(&WriteOverlapped,sizeof(OVERLAPPED));
	ZeroMemory(&EventOverlapped,sizeof(OVERLAPPED));
	ZeroMemory(&dcb,sizeof(DCB));
	CommTimeOuts.ReadIntervalTimeout=500;
	CommTimeOuts.ReadTotalTimeoutConstant=-1;
	CommTimeOuts.ReadTotalTimeoutMultiplier=0;
	CommTimeOuts.WriteTotalTimeoutConstant=0;
	CommTimeOuts.WriteTotalTimeoutMultiplier=0;
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
	dcb.Parity=NOPARITY;
	dcb.StopBits=ONESTOPBIT;
	//	Crear todos los eventos
	SECURITY_ATTRIBUTES	sa;
	ZeroMemory(&sa,sizeof(sa));
	sa.nLength=sizeof(sa);
	sa.bInheritHandle=TRUE;
	hReadEvent=::CreateEvent(&sa,FALSE,FALSE,NULL);
	if (hReadEvent==NULL)
		goto failed;
	hSendEvent=::CreateEvent(&sa,FALSE,FALSE,NULL);
	if (hSendEvent==NULL)
		goto failed;
	hEventEvent=::CreateEvent(&sa,FALSE,FALSE,NULL);
	if (hEventEvent==NULL)
		goto failed;
	/*
		Actualizar los hEvent hasta de comenzar el hilo
	*/
	ReadOverlapped.hEvent=hReadEvent;
	WriteOverlapped.hEvent=hWriteEvent;
	EventOverlapped.hEvent=hEventEvent;

	ReadThread=AfxBeginThread(ThreadProc,this,THREAD_PRIORITY_TIME_CRITICAL,0,0,NULL);
	if(ReadThread==NULL)
		goto failed;
	m_OnInitialize=true;
	return 0;
failed:
	Release();
	return 1;
}

DWORD CAsyncCommPort::Release()
{
	ClosePort();
	if (ReadThread)
	{
		S_MESSAGE Message;
		Message.Msg=UM_THREAD_CLOSE;
		SendThreadMessage(&Message);
		WaitForSingleObject(ReadThread->m_hThread,INFINITE);
		delete Buffer;
	}
	CloseHandle(hReadEvent);
	CloseHandle(hSendEvent);
	CloseHandle(hEventEvent);
	hReadEvent=NULL;
	hSendEvent=NULL;
	hEventEvent=NULL;
	m_OnInitialize=false;
	CMessageEvent::Release();
	return 0;
}

DWORD CAsyncCommPort::SFOnProcessMessage(void *lpthis, S_MESSAGE *pMessage)
{
	return ((CAsyncCommPort*)lpthis)->OnProcessMessage(pMessage);
}

DWORD CAsyncCommPort::SFOnWaitTimeOut(void *lpthis)
{
	return ((CAsyncCommPort*)lpthis)->OnWaitTimeOut();
}

DWORD CAsyncCommPort::SFOnReceiveData(void *lpthis, BYTE *pBuffer, DWORD pCant)
{
	return ((CAsyncCommPort*)lpthis)->OnReceiveData(pBuffer,pCant);
}

DWORD CAsyncCommPort::SFOnCommEvent(void *lpthis, DWORD pEventMask)
{
	return ((CAsyncCommPort*)lpthis)->OnCommEvent(pEventMask);
}
