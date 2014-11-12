// LFC10C01.h: interface for the CAsyncCommPort class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LFC10C01_H__D37E2261_79FE_11D4_8632_00D0093D4380__INCLUDED_)
#define AFX_LFC10C01_H__D37E2261_79FE_11D4_8632_00D0093D4380__INCLUDED_

#include "sigc02.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define COM1 _T("COM1")
#define COM2 _T("COM2")
#define COM3 _T("COM3")
#define LPT1 _T("LPT1")

typedef struct 
{
	long			BytesToRead;
	long			BufferLen;
	unsigned long	BytesRead;
	unsigned char*	Buffer;
	long			WaitTimeOut;
	char			PortName[20];
	HANDLE			PortHandle;
	BOOL			OnOpen;
	CWinThread*		ReadThread;
	DWORD			EventMask;
	OVERLAPPED		ReadOverlapped,WriteOverlapped,EventOverlapped;
	CEvent			ReadEvent,WriteEvent,EventEvent;
	DCB				dcb;
	COMMTIMEOUTS	CommTimeOuts;
	COMSTAT			CommStat;
	COMMCONFIG		CommConfig;
	COMMPROP		CommProp;

} S_ASYNCCOMMPORT;


class CAsyncCommPort: public CMessageEvent 
{
public:
	BOOL IsOpen();
	int ClosePort();
	int SetStopBits(BYTE pStopBits);
	int SetByteSize(BYTE pByteSize);
	int SetParity(DWORD pParity);
	int SetBaudRate(DWORD pBaudRate);
	int SendBuffer(BYTE* pBuffer,DWORD pCant);
	int SendThreadMessage(S_MESSAGE* pMessage);
	int OpenPort();
	int ApplyConfiguration();
	int SetupReadEvent();
	int SetupCommEvent();
	int ThreadProcessMessage();
	int ThreadGetMessage();
	int SetPort(char* pPortName);
	virtual int OnProcessMessage(S_MESSAGE *pMessage);
	virtual int OnWaitTimeOut();
	virtual int OnReceiveData(BYTE* pBuffer, DWORD pCant);
	virtual int OnCommEvent(DWORD pEventMask);
	int SetBufferLen(long pBufferLen);
	int InitAsyncCommPort();
	int SetWaitTimeOut(long pTimeOut);
	CAsyncCommPort();
	virtual ~CAsyncCommPort();
	S_ASYNCCOMMPORT* Data;

protected:
	static UINT ThreadProc(LPVOID pParam);
private:
	int ThreadMain();
};

#endif // !defined(AFX_LFC10C01_H__D37E2261_79FE_11D4_8632_00D0093D4380__INCLUDED_)
