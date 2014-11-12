// Clases.cpp: implementation of the CCommPort class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CC01.h"
#include "CDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CCommPort::CCommPort()
{
	InitCommPort();	
}

CCommPort::~CCommPort()
{
	Disconnect();
	m_CommPort->message.SendMessage(UM_THREAD_CLOSE,0,0);
	WaitForSingleObject(*m_CommPort->readthread,INFINITE);
	delete m_CommPort;
}

int CCommPort::SendThreadMessage(UINT Msg, WPARAM wParam, LPARAM lParam)
{
	return m_CommPort->message.SendMessage(Msg,wParam,lParam);
}

UINT CCommPort::ThreadProc(LPVOID pParam)
{
	return ((CCommPort*)pParam)->ThreadMain();
	
}

UINT CCommPort::ThreadMain()
{
	HANDLE m_HEvents[3];
	m_HEvents[0]=m_CommPort->readevent;
	m_HEvents[1]=m_CommPort->commevent;
	m_HEvents[2]=*m_CommPort->message.GetMessageEvent();
	while (true)
	{
		if (!ThreadGetMessage())
			break;
		if (IsConnect())
		{
			SetupReadEvent();
			SetupCommEvent();
			do
			{
				switch(WaitForMultipleObjects(3,m_HEvents,false,INFINITE))
				{
				case WAIT_OBJECT_0:
					{
						if (m_CommPort->readoverlapped.InternalHigh !=0)
						{
							OnReceiveData(m_CommPort->buffer,
								m_CommPort->readoverlapped.InternalHigh);
						}
						SetupReadEvent();
						break;
					}
				case WAIT_OBJECT_0+1:
					{
						OnCommEvent(m_CommPort->eventmask);
						SetupCommEvent();
						break;
					}
				case WAIT_OBJECT_0+2:
					{
						ProcessMessages();
						break;
					}
				case WAIT_FAILED:
					{
						break;
					}
				case WAIT_TIMEOUT:
					{
						break;
					}
				default: break;
				}
				
			} while (IsConnect());
		}
	}
	return 0;
}

int CCommPort::ProcessMessages()
{
	UINT   Msg;
	LPARAM lParam;
	WPARAM wParam;
	int    Answer;
	if (!m_CommPort->message.GetMesage(&Msg,&wParam,&lParam))
	{
		return true;
	}
	switch(Msg)
	{
	case UM_PORT_OPEN:
		{
			Answer=true;
			break;
		}
	case UM_PORT_CLOSE:
		{
			Answer=true;
			break;
			
		}
	case UM_THREAD_CLOSE:
		{
			Answer=false;
			break;
		}
	default:
		{
			OnProcessMessage(Msg,wParam,lParam);
			Answer=true;
			break;
		}
	}
	m_CommPort->message.ReplyMessage();
	return Answer;
}

int CCommPort::Connect()
{
	if (m_CommPort->onconnect) return true;
	
	m_CommPort->hport=CreateFile(m_CommPort->portname,
		GENERIC_READ+GENERIC_WRITE,
		0,NULL,OPEN_EXISTING,FILE_FLAG_OVERLAPPED,0);

	if (m_CommPort->hport==INVALID_HANDLE_VALUE)
	{
		AfxMessageBox("Open Port Failed ....");
		return false;
	}
	if (GetFileType(m_CommPort->hport)!=FILE_TYPE_CHAR)
	{
		CloseHandle(m_CommPort->hport);
		return false;
	}
	m_CommPort->onconnect=true;
	DWORD size=sizeof(COMMCONFIG);

	GetCommProperties ( m_CommPort->hport,&m_CommPort->commprop);
	SetCommMask       ( m_CommPort->hport,m_CommPort->eventsmask);
	SetCommTimeouts   ( m_CommPort->hport,&m_CommPort->commtimeouts);
	GetCommModemStatus( m_CommPort->hport,&m_CommPort->modemstat);
	GetCommConfig     ( m_CommPort->hport,&m_CommPort->commconfig,&size);
	Config();
	SendThreadMessage(UM_PORT_OPEN,0,0);
	return true;
}

int CCommPort::Disconnect()
{
	if (!IsConnect()) 
		return true;
	m_CommPort->onconnect=false;
	m_CommPort->message.SendMessage(UM_PORT_CLOSE,0,0);
	PurgeComm(m_CommPort->hport,
		PURGE_TXABORT+PURGE_RXABORT+PURGE_TXCLEAR+PURGE_RXCLEAR);
	SetCommMask(m_CommPort->hport,0);
	CloseHandle(m_CommPort->hport);
	return true;
}

int CCommPort::SetPort(int pPortNumber)
{
	if (pPortNumber==COM1)
		memcpy(m_CommPort->portname,COMM1,6);
	if (pPortNumber==COM2)
		memcpy(m_CommPort->portname,COMM2,6);
	if (pPortNumber==COM3)
		memcpy(m_CommPort->portname,COMM3,6);
	m_CommPort->info.portnumber=pPortNumber;
	return true;
}

int CCommPort::SendString(LPCSTR lpBuffer, DWORD nNumberOfBytesToWrite)
{
	DWORD m_Error;
	if(!IsConnect()) 
		return false;
	DWORD NumberOfBytesWritten;
	if (!WriteFile(m_CommPort->hport,lpBuffer,nNumberOfBytesToWrite,&NumberOfBytesWritten,&m_CommPort->writeoverlapped))
	{
		m_Error=GetLastError();
		if (m_Error!=ERROR_IO_PENDING)
			return false;
		switch (WaitForSingleObject(m_CommPort->writeevent,nNumberOfBytesToWrite+5))
		{
		case WAIT_OBJECT_0: return true;
		case WAIT_TIMEOUT: 
			{
				PurgeComm(m_CommPort->hport,PURGE_TXABORT+PURGE_TXCLEAR);
				return false;
			}
		default: 
			{
				return false;
			}
		}
	} else return true;
}

int CCommPort::IsConnect()
{
	return m_CommPort->onconnect;
}

int CCommPort::Config()
{
	if (!IsConnect())
		return true;
	if (SetCommState(m_CommPort->hport,&m_CommPort->info.dcb)) 
		return true;
	AfxMessageBox("Unsupported configuration ......");
	GetCommState(m_CommPort->hport,&m_CommPort->info.dcb);
	return false;	
}

int CCommPort::SetBaudRate(DWORD pBaudRate)
{
	m_CommPort->info.dcb.BaudRate=pBaudRate;
	return Config();
}

int CCommPort::SetParity(DWORD pParity)
{
	m_CommPort->info.dcb.fParity=pParity;
	return Config();
}

int CCommPort::SetByteSize(BYTE pByteSize)
{
	m_CommPort->info.dcb.ByteSize=pByteSize;
	return Config();
}

int CCommPort::SetStopBits(BYTE pStopBits)
{
	m_CommPort->info.dcb.StopBits=pStopBits;
	return Config();
}

int CCommPort::ThreadGetMessage()
{
	m_CommPort->message.WaitMessage();
	return ProcessMessages();
}

int CCommPort::SetupReadEvent()
{
	while (true)
	{
		if (!ReadFile(m_CommPort->hport,
			m_CommPort->buffer,255,
			&m_CommPort->bytesread,
			&m_CommPort->readoverlapped))
		{
			if (GetLastError()==ERROR_IO_PENDING)
				return true;
			AfxMessageBox("Critical error ... Close the program");
		}  else
			OnReceiveData(m_CommPort->buffer,
			m_CommPort->readoverlapped.InternalHigh);
	}
}

int CCommPort::SetupCommEvent()
{
	while (true)
	{
		if (WaitCommEvent(m_CommPort->hport,
			&m_CommPort->eventmask,
			&m_CommPort->eventoverlapped))
		{
			OnCommEvent(m_CommPort->eventmask);
		}
		else
		{
			if (GetLastError() == ERROR_IO_PENDING)
				return true;
			AfxMessageBox("Critical error ... Close the program");
		}
	}
}

int CCommPort::OnCommEvent(DWORD pEventMask)
{
	return true;
}

int CCommPort::OnReceiveData(char *pBuffer, DWORD pCant)
{
	return true;
}

int CCommPort::OnProcessMessage(UINT Msg, WPARAM wParam, LPARAM lParam)
{
	return true;
}

int CCommPort::ShowConfigDlg()
{
	CConfigDlg	Dlg;
	Dlg.m_OnConnect=IsConnect();
	switch(m_CommPort->info.dcb.BaudRate)
	{
	case CBR_110:
		{
			Dlg.m_Bits=0;
			break;
		}
	case CBR_300:
		{
			Dlg.m_Bits=1;
			break;
		}
	case CBR_1200:
		{
			Dlg.m_Bits=2;
			break;
		}
	case CBR_2400:
		{
			Dlg.m_Bits=3;
			break;
		}
	case CBR_4800:
		{
			Dlg.m_Bits=4;
			break;
		}
	case CBR_9600:
		{
			Dlg.m_Bits=5;
			break;
		}
	case CBR_19200:
		{
			Dlg.m_Bits=6;
			break;
		}
	case CBR_38400:
		{
			Dlg.m_Bits=7;
			break;
		}
	case CBR_57600:
		{
			Dlg.m_Bits=8;
			break;
		}
	case CBR_115200:
		{
			Dlg.m_Bits=9;
			break;
		}
	}
	Dlg.m_Port=m_CommPort->info.portnumber-1;
	Dlg.m_Data=m_CommPort->info.dcb.ByteSize-5;
	switch(m_CommPort->info.dcb.StopBits)
	{
	case ONESTOPBIT:
		{
			Dlg.m_Stop=0;
			break;
		}
	case ONE5STOPBITS:
		{
			Dlg.m_Stop=1;
			break;
		}
	case TWOSTOPBITS:
		{
			Dlg.m_Stop=2;
			break;
		}
		
	}
	switch(m_CommPort->info.dcb.Parity)
	{
	case NOPARITY:
		{
			Dlg.m_Paridad=0;
			break;
		}
	case ODDPARITY:
		{
			Dlg.m_Paridad=1;
			break;
		}
	case EVENPARITY:
		{
			Dlg.m_Paridad=2;
			break;
		}
	case MARKPARITY:
		{
			Dlg.m_Paridad=3;
			break;
		}
	}
	HINSTANCE hInst=GetModuleHandle("LFC10.DLL");
	HINSTANCE hRec=AfxGetResourceHandle();
	AfxSetResourceHandle(hInst);
	if (Dlg.DoModal()==IDOK)
	{
		switch (Dlg.m_Bits)
		{
		case 0:
			{
				m_CommPort->info.dcb.BaudRate=CBR_110;
				break;
			}
		case 1:
			{
				m_CommPort->info.dcb.BaudRate=CBR_300;
				break;
			}
		case 2:
			{
				m_CommPort->info.dcb.BaudRate=CBR_1200;
				break;
			}
		case 3:
			{
				m_CommPort->info.dcb.BaudRate=CBR_2400;
				break;
			}
		case 4:
			{
				m_CommPort->info.dcb.BaudRate=CBR_4800;
				break;
			}
			
		case 5:
			{
				m_CommPort->info.dcb.BaudRate=CBR_9600;
				break;
			}
		case 6:
			{
				m_CommPort->info.dcb.BaudRate=CBR_19200;
				break;
			}
		case 7:
			{
				m_CommPort->info.dcb.BaudRate=CBR_38400;
				break;
			}
		case 8:
			{
				m_CommPort->info.dcb.BaudRate=CBR_57600;
				break;
			}
		case 9:
			{
				m_CommPort->info.dcb.BaudRate=CBR_115200;
				break;
			}
		}
		switch(Dlg.m_Stop)
		{
		case 0:
			{
				m_CommPort->info.dcb.StopBits=ONESTOPBIT;
				break;
			}
		case 1:
			{
				m_CommPort->info.dcb.StopBits=ONE5STOPBITS;
				break;
			}
		case 2:
			{
				m_CommPort->info.dcb.StopBits=TWOSTOPBITS;
				break;
			}
		}
		switch(Dlg.m_Paridad)
		{
		case 0:
			{
				m_CommPort->info.dcb.Parity=NOPARITY;
				break;
			}
		case 1:
			{
				m_CommPort->info.dcb.Parity=ODDPARITY;
				break;
			}
		case 2:
			{
				m_CommPort->info.dcb.Parity=EVENPARITY;
				break;
			}
		case 3:
			{
				m_CommPort->info.dcb.Parity=MARKPARITY;
				break;
			}

		}
		SetPort(Dlg.m_Port+1);
		SetByteSize(Dlg.m_Data+5);
		SaveToFile();
		return Config();
	};
	return true;	
}

int CCommPort::ReadFromFile()
{
	S_COMMPORTINFO info;
	FILE *fd;
	if ((fd=fopen(m_CommPort->filename,"rb"))==NULL)
	{
		return SaveToFile();	
	}
	if (fread(&info,sizeof(info),1,fd)==0)
	{
		fclose(fd);
		return SaveToFile();
	}
	m_CommPort->info=info;
	m_CommPort->info=info;
	fclose(fd);
	return true;
}

int CCommPort::SaveToFile()
{
	FILE *fd;
	if ((fd=fopen(m_CommPort->filename,"wb"))==NULL)
	{
		return false;
	}
	if (fwrite(&m_CommPort->info,sizeof(S_COMMPORTINFO),1,fd)!=1)
	{
		fclose(fd);
		return false;
	}

	fclose(fd);
	return true;
}

int CCommPort::InitCommPort()
{
	m_CommPort=new S_COMMPORT;
	memcpy(m_CommPort->portname,COMM2,6);
	m_CommPort->info.portnumber=2;
	m_CommPort->hport=NULL;
	m_CommPort->onconnect=false;
	m_CommPort->readthread=NULL;
	m_CommPort->eventsmask=EV_BREAK+EV_ERR;
	ZeroMemory(&m_CommPort->readoverlapped,sizeof(OVERLAPPED));
	ZeroMemory(&m_CommPort->writeoverlapped,sizeof(OVERLAPPED));
	ZeroMemory(&m_CommPort->eventoverlapped,sizeof(OVERLAPPED));
	ZeroMemory(&m_CommPort->info.dcb,sizeof(DCB));
	m_CommPort->readoverlapped.hEvent=m_CommPort->readevent;
	m_CommPort->writeoverlapped.hEvent=m_CommPort->writeevent;
	m_CommPort->eventoverlapped.hEvent=m_CommPort->commevent;
	m_CommPort->commtimeouts.ReadIntervalTimeout=100;
	m_CommPort->commtimeouts.ReadTotalTimeoutConstant=60000;
	m_CommPort->commtimeouts.ReadTotalTimeoutMultiplier=2;
	m_CommPort->commtimeouts.WriteTotalTimeoutConstant=0;
	m_CommPort->commtimeouts.WriteTotalTimeoutMultiplier=0;
	m_CommPort->info.dcb.DCBlength=sizeof(DCB);
	m_CommPort->info.dcb.BaudRate=CBR_9600;
	m_CommPort->info.dcb.fBinary=true;
	m_CommPort->info.dcb.fParity=false;
	m_CommPort->info.dcb.fOutxCtsFlow=false;
	m_CommPort->info.dcb.fOutxDsrFlow=false;
	m_CommPort->info.dcb.fDtrControl=DTR_CONTROL_ENABLE;
	m_CommPort->info.dcb.fDsrSensitivity=false;
	m_CommPort->info.dcb.fTXContinueOnXoff=false;
	m_CommPort->info.dcb.fOutX=false;
	m_CommPort->info.dcb.fInX=false;
	m_CommPort->info.dcb.fErrorChar=false;
	m_CommPort->info.dcb.fNull=false;
	m_CommPort->info.dcb.fRtsControl=RTS_CONTROL_ENABLE;
	m_CommPort->info.dcb.fAbortOnError=false;
	m_CommPort->info.dcb.ByteSize=8;
	m_CommPort->info.dcb.Parity=NOPARITY;
	m_CommPort->info.dcb.StopBits=ONESTOPBIT;
	m_CommPort->filename.Empty();
	::GetCurrentDirectory(254,m_CommPort->filename.GetBuffer(254));
	m_CommPort->filename.ReleaseBuffer();
	m_CommPort->filename=m_CommPort->filename+"\\ConfPort.inf";
	m_CommPort->readthread=AfxBeginThread(ThreadProc,this,THREAD_PRIORITY_TIME_CRITICAL,0,0,NULL);
	ReadFromFile();
	return true;
}
