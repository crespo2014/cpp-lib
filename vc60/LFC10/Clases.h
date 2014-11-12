// Clases.h: interface for the CCommPort class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLASES_H__4397C912_CC05_11D3_A036_0000E83D722B__INCLUDED_)
#define AFX_CLASES_H__4397C912_CC05_11D3_A036_0000E83D722B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "lfc10c02.h"

typedef enum
{
	UM_THREAD_ACK=10,
	UM_PORT_OPEN,    
	UM_PORT_CLOSE,
	UM_THREAD_CLOSE
};

#define COM1 _T("COM1")
#define COM2 _T("COM2")
#define COM3 _T("COM3")
#define LPT1 _T("LPT1")

typedef struct 
{
	WORD	version;
	DCB		dcb;
	WORD	portnumber;
}S_COMMPORTINFO;

typedef struct
{
	S_COMMPORTINFO	info;
	BOOL			onconnect;
	CMessageEvent   message;
	CWinThread*		readthread;
	COMMPROP		commprop;
	OVERLAPPED		readoverlapped;
	OVERLAPPED		writeoverlapped;
	OVERLAPPED		eventoverlapped;
	CEvent			writeevent;
	CEvent			readevent;
	CEvent			commevent;
	COMMTIMEOUTS	commtimeouts;
	COMSTAT			commstat;
	COMMCONFIG		commconfig;
	CString			filename;
	DWORD			bytesread;
	char			buffer[255];
	DWORD			modemstat;
	DWORD			eventmask;
	DWORD			eventsmask;
	char			portname[20];
	HANDLE			hport;
}S_COMMPORT;

class AFX_EXT_CLASS CCommPort : public CObject  
{
public:
	int InitCommPort();
	int SaveToFile();
	int ReadFromFile();
	int ShowConfigDlg();
	int OnProcessMessage(UINT Msg, WPARAM wParam, LPARAM lParam);
	virtual int OnReceiveData(char* pBuffer,DWORD pCant);
	virtual int OnCommEvent(DWORD pEventMask);
	int SetStopBits(BYTE pStopBits);
	int SetByteSize(BYTE pByteSize);
	int SetParity(DWORD pParity);
	int SetBaudRate(DWORD pBaudRate);
	int Config();
	int IsConnect();
	int SendString(LPCSTR lpBuffer, DWORD nNumberOfBytesToWrite);
	int SetPort(int pPortNumber);
	int Disconnect();
	int Connect();
	int SendThreadMessage(UINT Msg, WPARAM wParam,LPARAM lParam);
	CCommPort();
	virtual ~CCommPort();
protected:
	int ProcessMessages();
	int SetupCommEvent();
	int SetupReadEvent();
	int ThreadGetMessage();
	UINT ThreadMain();
	static UINT ThreadProc(LPVOID pParam);
	S_COMMPORT* m_CommPort;

};

#endif // !defined(AFX_CLASES_H__4397C912_CC05_11D3_A036_0000E83D722B__INCLUDED_)
