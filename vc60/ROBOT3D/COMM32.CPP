// Comm32.cpp: implementation of the CComm32 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Comm32.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CComm32::CComm32()
{
	memcpy(m_Name,COMM2,6);
	m_OnMessage=false;
	m_OnOpen=false;
	m_EvtMask=0;
	m_HPort=INVALID_HANDLE_VALUE;
	ZeroMemory(&m_Read_Overlapped,sizeof(m_Read_Overlapped));
	ZeroMemory(&m_Write_Overlapped,sizeof(m_Read_Overlapped));
	ZeroMemory(&m_DCB,sizeof(DCB));
	m_DCB.DCBlength=sizeof(DCB);
	m_DCB.BaudRate=CBR_9600;
	m_DCB.fBinary=true;
	m_DCB.fParity=false;
	m_DCB.fOutxCtsFlow=false;
	m_DCB.fOutxDsrFlow=false;
	m_DCB.fDtrControl=DTR_CONTROL_ENABLE;
	m_DCB.fDsrSensitivity=false;
	m_DCB.fTXContinueOnXoff=false;
	m_DCB.fOutX=false;
	m_DCB.fInX=false;
	m_DCB.fErrorChar=false;
	m_DCB.fNull=false;
	m_DCB.fRtsControl=RTS_CONTROL_ENABLE;
	m_DCB.fAbortOnError=false;
	m_DCB.ByteSize=8;
	m_DCB.Parity=NOPARITY;
	m_DCB.StopBits=ONESTOPBIT;

	m_CommTimeOuts.ReadIntervalTimeout=5;
	m_CommTimeOuts.ReadTotalTimeoutConstant=10;
	m_CommTimeOuts.ReadTotalTimeoutMultiplier=1;
	m_CommTimeOuts.WriteTotalTimeoutConstant=0;
	m_CommTimeOuts.WriteTotalTimeoutMultiplier=0;
}

CComm32::~CComm32()
{
	CloseAll();

}

// Habilitacion y programacion del puerto serie
int CComm32::OpenComm()
{
	if (m_OnOpen) return ERROR_ALREADY_INITIALIZED;
	
	m_HPort=CreateFile(m_Name,GENERIC_READ+GENERIC_WRITE,
		0,NULL,OPEN_EXISTING,FILE_FLAG_OVERLAPPED,0);

	if (m_HPort==INVALID_HANDLE_VALUE)
		return GetLastError();
	
	m_OnOpen=true;

	if (GetFileType(m_HPort)!=FILE_TYPE_CHAR)
	{
		CloseHandle(m_HPort);
		return ERROR_OPEN_FAILED;
	}

	m_Read_Overlapped.hEvent=CreateEvent(NULL,true,true,NULL);
	if (m_Read_Overlapped.hEvent==0)
	{
		CloseAll();
		return GetLastError();
	}

	m_Write_Overlapped.hEvent=CreateEvent(NULL,true,true,NULL);
	if (m_Write_Overlapped.hEvent==0)
	{
		CloseAll();
		return GetLastError();
	}
	GetCommProperties(m_HPort,&m_CommProp);
	SetCommMask(m_HPort,m_EvtMask);
	SetCommTimeouts(m_HPort,&m_CommTimeOuts);
	GetCommModemStatus(m_HPort,&m_ModemStat);
	DWORD size=sizeof(COMMCONFIG);
	GetCommConfig(m_HPort,&m_CommConfig,&size);
	return 0;

}

void CComm32::SetPort(BYTE port)
{
	if (port==COM1)
		memcpy(m_Name,COMM1,6);
	if (port==COM2)
		memcpy(m_Name,COMM2,6);
}


/*
LPVOID lpMsgBuf;
FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | 
FORMAT_MESSAGE_FROM_SYSTEM |
FORMAT_MESSAGE_IGNORE_INSERTS,
NULL,GetLastError(),
MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
(LPTSTR) &lpMsgBuf,    0,    NULL );// Process any inserts in lpMsgBuf.
// ...// Display the string.
::MessageBox(NULL,(LPCTSTR)lpMsgBuf,"Error",MB_OK|MB_ICONINFORMATION);
// Free the buffer.
LocalFree( lpMsgBuf );
*/
		

void CComm32::CloseAll()
{
	if (!m_OnOpen) return;

	CloseHandle(m_HPort);
	m_OnOpen=false;

	if (m_Read_Overlapped.hEvent !=0)
		CloseHandle(m_Read_Overlapped.hEvent);

	if (m_Write_Overlapped.hEvent !=0)
		CloseHandle(m_Write_Overlapped.hEvent);

	ZeroMemory(&m_Read_Overlapped,sizeof(m_Read_Overlapped));
	ZeroMemory(&m_Write_Overlapped,sizeof(m_Read_Overlapped));

}

DWORD CComm32::SendString(LPCSTR lpBuffer, DWORD nNumberOfBytesToWrite)
{
	if(!m_OnOpen) return ERROR_DEVICE_NOT_AVAILABLE;
	DWORD NumberOfBytesWritten;
	if (!WriteFile(m_HPort,lpBuffer,nNumberOfBytesToWrite,&NumberOfBytesWritten,&m_Write_Overlapped))
	{
		m_Error=GetLastError();
		if (m_Error!=ERROR_IO_PENDING) return m_Error;
		m_Error=WaitForSingleObject(m_Write_Overlapped.hEvent,nNumberOfBytesToWrite+5);
		switch (m_Error)
		{
		case WAIT_OBJECT_0: return 0;
		case WAIT_TIMEOUT: 
			{
				PurgeComm(m_HPort,PURGE_TXABORT+PURGE_TXCLEAR);
				return ERROR_IO_INCOMPLETE;
			}
		default: return GetLastError();
		}
	} else return 0;
}

DWORD CComm32::ReadString(LPVOID lpBuffer, LPDWORD lpNumberOfBytesRead)
{
	if(!m_OnOpen) return ERROR_DEVICE_NOT_AVAILABLE;
	if (!ReadFile(m_HPort,lpBuffer,255,lpNumberOfBytesRead,&m_Read_Overlapped))
	{
		m_Error=GetLastError();
		if (m_Error != ERROR_IO_PENDING) return m_Error;
		m_Error=WaitForSingleObject(m_Read_Overlapped.hEvent,INFINITE);
		switch (m_Error)
		{
		case WAIT_OBJECT_0:
			{
				*lpNumberOfBytesRead=m_Read_Overlapped.InternalHigh;
				return 0;
			}
		case WAIT_TIMEOUT: 
			{
				PurgeComm(m_HPort,PURGE_RXABORT+PURGE_RXCLEAR);
				return ERROR_IO_INCOMPLETE;
			}
		default: return GetLastError();
		}
	}  else
	{
		*lpNumberOfBytesRead=m_Read_Overlapped.InternalHigh;
		return 0;
	}

}



void CComm32::CloseComm()
{
	if (m_OnOpen) CloseAll();
}

DWORD CComm32::ConfigComm()
{
	if (!m_OnOpen) return ERROR_DEVICE_NOT_AVAILABLE;
	if (SetCommState(m_HPort,&m_DCB)) return 0;
	return GetLastError();
}

void CComm32::SetBaudRate(DWORD pBaudRate)
{
	m_DCB.BaudRate=pBaudRate;
}

void CComm32::SetParity(DWORD pParity)
{
	m_DCB.fParity=pParity;
}

void CComm32::SetByteSize(BYTE pByteSize)
{
	m_DCB.ByteSize=pByteSize;
}

void CComm32::SetStopBits(BYTE pStopBits)
{
	m_DCB.StopBits=pStopBits;
}
