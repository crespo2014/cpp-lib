// LFC10C01.cpp: implementation of the CAsyncCommPort class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sigC01.h"
#include "sigdef.h"

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
	
	InitAsyncCommPort();
	
}

CAsyncCommPort::~CAsyncCommPort()
{
	ClosePort();
	S_MESSAGE Message;
	Message.Msg=UM_THREAD_CLOSE;
	SendThreadMessage(&Message);
	WaitForSingleObject(Data->ReadThread->m_hThread,INFINITE);
	delete Data->Buffer;
	delete Data;
}

int CAsyncCommPort::SetWaitTimeOut(long pTimeOut)
{
	Data->WaitTimeOut=pTimeOut;
	return true;
}

int CAsyncCommPort::InitAsyncCommPort()
{
	Data=new S_ASYNCCOMMPORT;
	if (Data==NULL)
		return false;

	strcpy(Data->PortName,COM2);
	Data->BufferLen=0;
	Data->Buffer=NULL;
	Data->BytesToRead=0;
	Data->WaitTimeOut=INFINITE;
	Data->PortHandle=NULL;
	Data->OnOpen=false;
	Data->EventMask=EV_BREAK+EV_ERR;
	ZeroMemory(&Data->ReadOverlapped,sizeof(OVERLAPPED));
	ZeroMemory(&Data->WriteOverlapped,sizeof(OVERLAPPED));
	ZeroMemory(&Data->EventOverlapped,sizeof(OVERLAPPED));
	ZeroMemory(&Data->dcb,sizeof(DCB));
	Data->ReadOverlapped.hEvent=Data->ReadEvent;
	Data->WriteOverlapped.hEvent=Data->WriteEvent;
	Data->EventOverlapped.hEvent=Data->EventEvent;
	Data->CommTimeOuts.ReadIntervalTimeout=500;
	Data->CommTimeOuts.ReadTotalTimeoutConstant=-1;
	Data->CommTimeOuts.ReadTotalTimeoutMultiplier=0;
	Data->CommTimeOuts.WriteTotalTimeoutConstant=0;
	Data->CommTimeOuts.WriteTotalTimeoutMultiplier=0;
	Data->dcb.DCBlength=sizeof(DCB);
	Data->dcb.BaudRate=CBR_19200;
	Data->dcb.fBinary=true;
	Data->dcb.fParity=false;
	Data->dcb.fOutxCtsFlow=false;
	Data->dcb.fOutxDsrFlow=false;
	Data->dcb.fDtrControl=DTR_CONTROL_ENABLE;
	Data->dcb.fDsrSensitivity=false;
	Data->dcb.fTXContinueOnXoff=false;
	Data->dcb.fOutX=false;
	Data->dcb.fInX=false;
	Data->dcb.fErrorChar=false;
	Data->dcb.fNull=false;
	Data->dcb.fRtsControl=RTS_CONTROL_ENABLE;
	Data->dcb.fAbortOnError=false;
	Data->dcb.ByteSize=8;
	Data->dcb.Parity=NOPARITY;
	Data->dcb.StopBits=ONESTOPBIT;
	Data->ReadThread=AfxBeginThread(ThreadProc,this,THREAD_PRIORITY_TIME_CRITICAL,0,0,NULL);
	return true;
}

int CAsyncCommPort::SetBufferLen(long pBufferLen)
{
	if (Data->OnOpen)
		return false;
	if (pBufferLen > Data->BufferLen)
	{
		delete Data->Buffer;
		Data->Buffer= new unsigned char[pBufferLen];
	}
	Data->BufferLen=pBufferLen;
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
	m_HEvents[0]=Data->ReadEvent;
	m_HEvents[1]=Data->EventEvent;
	m_HEvents[2]=GetSendEventHandle();
	while (true)
	{
		if (!ThreadGetMessage())
			break;
		if (Data->OnOpen)
		{
			SetupReadEvent();
			SetupCommEvent();
			do
			{
				switch(WaitForMultipleObjects(3,m_HEvents,false,Data->WaitTimeOut))
				{
				case WAIT_OBJECT_0:
					{
						if (Data->ReadOverlapped.InternalHigh !=0)
						{
							OnReceiveData(Data->Buffer,
								Data->ReadOverlapped.InternalHigh);
						}
						SetupReadEvent();
						break;
					}
				case WAIT_OBJECT_0+1:
					{
						OnCommEvent(Data->EventMask);
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
						OnWaitTimeOut();
					}
				default: break;
				}
			} while (Data->OnOpen);
		}
	}
	return 0;
}

int CAsyncCommPort::SetPort(char *pPortName)
{
	strcpy(Data->PortName,pPortName);
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
			Data->OnOpen=true;
			break;
		}
	case UM_PORT_CLOSE:
		{
			Data->OnOpen=false;
			break;
			
		}
	case UM_THREAD_CLOSE:
		{
			Return=false;
			break;
		}
	default:
		{
			if (!OnProcessMessage(&Message))
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
		if (!ReadFile(Data->PortHandle,
			Data->Buffer,Data->BufferLen,
			&Data->BytesRead,
			&Data->ReadOverlapped))
		{
			if (GetLastError()==ERROR_IO_PENDING)
				return true;
			AfxMessageBox("Critical error ... Close the program");
		}  else
			OnReceiveData(Data->Buffer,
			Data->ReadOverlapped.InternalHigh);
	}
}

int CAsyncCommPort::ApplyConfiguration()
{
	char Msg[100];
	if (!Data->OnOpen)
		return false;
	if (SetCommState(Data->PortHandle,&Data->dcb)) 
		return true;

	DWORD Error=GetLastError();
	sprintf(Msg," Error %d Appling Configuration \r to Comunication Port \r See Help for details ",Error);
	MessageBox(AfxGetApp()->GetMainWnd()->m_hWnd,Msg,"Comunication Configuration",MB_OK|MB_ICONINFORMATION|MB_APPLMODAL);
	return false;
}

int CAsyncCommPort::OpenPort()
{
	char	MsgError[100];
	if (Data->OnOpen) return true;
	
	Data->PortHandle=CreateFile(Data->PortName,
		GENERIC_READ+GENERIC_WRITE,
		0,NULL,OPEN_EXISTING,FILE_FLAG_OVERLAPPED,0);

	if (Data->PortHandle==INVALID_HANDLE_VALUE)
	{
		DWORD Error=GetLastError();
		sprintf(MsgError," Error %d Opening Comunication Port \r	See Help for details ",Error);
		MessageBox(AfxGetApp()->GetMainWnd()->m_hWnd,MsgError,"Comunication",MB_OK|MB_ICONINFORMATION|MB_APPLMODAL);
		return false;
	}
	if (GetFileType(Data->PortHandle)!=FILE_TYPE_CHAR)
	{
		CloseHandle(Data->PortHandle);
		return false;
	}

	Data->OnOpen=true;
	DWORD size=sizeof(COMMCONFIG);

	GetCommProperties	(Data->PortHandle,&Data->CommProp);
	SetCommMask			(Data->PortHandle,Data->EventMask);
	SetCommMask			(Data->PortHandle,0);
	SetCommTimeouts		(Data->PortHandle,&Data->CommTimeOuts);
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
	if(!Data->OnOpen)
		return false;
	DWORD NumberOfBytesWritten;
	if (WriteFile(Data->PortHandle,pBuffer,pCant,&NumberOfBytesWritten,&Data->WriteOverlapped))
		return true;
	m_Error=GetLastError();
	if (m_Error=ERROR_IO_PENDING)
	{
		if (WaitForSingleObject(Data->WriteEvent,5000)==WAIT_OBJECT_0)
			return true;
	}
	PurgeComm(Data->PortHandle,PURGE_TXABORT+PURGE_TXCLEAR);
	return false;	
}
int CAsyncCommPort::SetBaudRate(DWORD pBaudRate)
{
	Data->dcb.BaudRate=pBaudRate;
	return ApplyConfiguration();
}

int CAsyncCommPort::SetParity(DWORD pParity)
{
	Data->dcb.fParity=pParity;
	return ApplyConfiguration();
}

int CAsyncCommPort::SetByteSize(BYTE pByteSize)
{
	Data->dcb.ByteSize=pByteSize;
	return ApplyConfiguration();
}

int CAsyncCommPort::SetStopBits(BYTE pStopBits)
{
	Data->dcb.StopBits=pStopBits;
	return ApplyConfiguration();
}

int CAsyncCommPort::ClosePort()
{
	if (!Data->OnOpen)
		return true;
	S_MESSAGE Message;
	Message.Msg=UM_PORT_CLOSE;
	SendThreadMessage(&Message);
	PurgeComm(Data->PortHandle,
		PURGE_TXABORT+PURGE_RXABORT+PURGE_TXCLEAR+PURGE_RXCLEAR);
	SetCommMask(Data->PortHandle,0);
	CloseHandle(Data->PortHandle);
	return true;
}

BOOL CAsyncCommPort::IsOpen()
{
	return Data->OnOpen;
}
