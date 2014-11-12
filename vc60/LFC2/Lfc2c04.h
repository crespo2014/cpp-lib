// LFC10C01.h: interface for the CAsyncCommPort class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LFC10C01_H__D37E2261_79FE_11D4_8632_00D0093D4380__INCLUDED_)
#define AFX_LFC10C01_H__D37E2261_79FE_11D4_8632_00D0093D4380__INCLUDED_

#include "lfc2c05.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef DWORD (*LPONPROCESSMESSAGE)	(void* lpthis,S_MESSAGE *pMessage);
typedef DWORD (*LPONWAITTIMEOUT)	(void* lpthis);
typedef DWORD (*LPONRECEIVEDATA)	(void* lpthis,BYTE* pBuffer, DWORD pCant);
typedef DWORD (*LPONCOMMEVENT)		(void* lpthis,DWORD pEventMask);


#define COM1 _T("COM1")
#define COM2 _T("COM2")
#define COM3 _T("COM3")
#define LPT1 _T("LPT1")

class CAsyncCommPort: public CMessageEvent 
{
public:
	DWORD Release();
	DWORD Initialize();
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
	int SetBufferLen(long pBufferLen);
	int SetWaitTimeOut(long pTimeOut);
	CAsyncCommPort();
	virtual ~CAsyncCommPort();
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
	HANDLE			hReadEvent,hWriteEvent,hEventEvent;
	DCB				dcb;
	COMMTIMEOUTS	CommTimeOuts;
	COMSTAT			CommStat;
	COMMCONFIG		CommConfig;
	COMMPROP		CommProp;
protected:
	static UINT ThreadProc(LPVOID pParam);
private:
	int ThreadMain();
public:
	/*
		Funciones virtuales staticas
	*/
	static DWORD SFOnCommEvent(void* lpthis,DWORD pEventMask);
	static DWORD SFOnReceiveData(void* lpthis,BYTE* pBuffer, DWORD pCant);
	static DWORD SFOnWaitTimeOut(void* lpthis);
	static DWORD SFOnProcessMessage(void* lpthis,S_MESSAGE *pMessage);
	/*
		Funciones virtuales
	*/
	
	int OnProcessMessage(S_MESSAGE *pMessage);
	int OnWaitTimeOut();
	int OnReceiveData(BYTE* pBuffer, DWORD pCant);
	int OnCommEvent(DWORD pEventMask);
	
	/*
		Punteros a las funciones virtuales
	*/
	LPONPROCESSMESSAGE	VFOnProcessMessage;
	LPONWAITTIMEOUT		VFOnWaitTimeOut;
	LPONRECEIVEDATA		VFOnReceiveData;
	LPONCOMMEVENT		VFOnCommEvent;
	/*
	*/
	BOOL m_OnConstructor;
	BOOL m_OnInitialize;
};


#endif // !defined(AFX_LFC10C01_H__D37E2261_79FE_11D4_8632_00D0093D4380__INCLUDED_)
