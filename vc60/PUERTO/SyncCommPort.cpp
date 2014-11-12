// SyncCommPort.cpp: implementation of the CSyncCommPort class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "puerto.h"
#include "SyncCommPort.h"
 
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
 
CSyncCommPort::CSyncCommPort()
{
	EventMask=EV_TXEMPTY;
	OnOpen=false;
	strcpy((char*)PortName,"COM1");
	PortHandle=NULL;
	memset(&dcb,0,sizeof(DCB));
	CommTimeOuts.ReadIntervalTimeout=500;
	CommTimeOuts.ReadTotalTimeoutConstant=500;
	CommTimeOuts.ReadTotalTimeoutMultiplier=1;
	CommTimeOuts.WriteTotalTimeoutConstant=0;
	CommTimeOuts.WriteTotalTimeoutMultiplier=0;
	dcb.DCBlength=sizeof(DCB);
	dcb.BaudRate=CBR_9600;
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
	
}

CSyncCommPort::~CSyncCommPort()
{

}

int CSyncCommPort::OpenPort()
{
	if (OnOpen) return true;
	PortHandle=CreateFile((char*)PortName,
		GENERIC_READ+GENERIC_WRITE,
		0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
	if (PortHandle==INVALID_HANDLE_VALUE)
	{
		AfxMessageBox("Open Port Failed ....");
		return false;
	}
	if (GetFileType(PortHandle)!=FILE_TYPE_CHAR)
	{
		CloseHandle(PortHandle);
		return false;
	}
	OnOpen=true;	
	SetCommMask			(PortHandle,EventMask);
	SetCommTimeouts		(PortHandle,&CommTimeOuts);
	ApplyConfiguration();
	return true;
}

int CSyncCommPort::ClosePort()
{
	if (OnOpen)
	{
		CloseHandle(PortHandle);
		OnOpen=false;
		return true;
	}
	return false;
}

int CSyncCommPort::ApplyConfiguration()
{
	if (!OnOpen)
		return -1;
	if (SetCommState(PortHandle,&dcb)) 
		return 0;
	AfxMessageBox("Unsupported Configuration ......");
	return false;
}

int CSyncCommPort::SetBaudRate(DWORD pBaudRate)
{
	dcb.BaudRate=pBaudRate;
	return ApplyConfiguration();
}

int CSyncCommPort::SetParity(DWORD pParity)
{
	dcb.Parity=pParity;
	return ApplyConfiguration();
}

int CSyncCommPort::SetStopBits(BYTE pStopBits)
{
	dcb.StopBits=pStopBits;
	return ApplyConfiguration();
}

int CSyncCommPort::SetPort(char *pPortName)
{
	strcpy((char*)PortName,pPortName);
	return true;
}

int CSyncCommPort::SendBuffer(BYTE *pBuffer, DWORD pCant)
{
	DWORD m_Error;
	if(!OnOpen)
		return -1;
	DWORD NumberOfBytesWritten;
	if (WriteFile(PortHandle,pBuffer,pCant,&NumberOfBytesWritten,NULL))
		return 0;
	m_Error=GetLastError();
	return m_Error;	
}

int CSyncCommPort::ReadBuffer(BYTE *pBuffer, DWORD pBufferLen, DWORD *pCantRead)
{
	if (!OnOpen)
		return false;
	if (ReadFile(PortHandle,pBuffer,pBufferLen,pCantRead,NULL))
		return true;
	DWORD m_Error;
	m_Error=GetLastError();
	return false;	

}
