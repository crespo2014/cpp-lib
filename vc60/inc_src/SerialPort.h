// ISerialPort1.h: interface for the ISerialPort1 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ISERIALPORT1_H__61184290_0BA6_4418_BAE0_1728A4659763__INCLUDED_)
#define AFX_ISERIALPORT1_H__61184290_0BA6_4418_BAE0_1728A4659763__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MessageEvent.h"
#include "ICommunicationEvents.h"

// Mensajes enviados por el hilo que atiende el puerto
#define THREAD_CLOSE	0
#define PORT_OPEN		1
#define PORT_CLOSE		2
#define THREAD_INIT		3
#define M_LAST			100

#define BUFFERSIZE 1024

class CSerialPort : public CMessageEvent
{
public:
	DWORD Send(DWORD dwCant);
	DWORD SendWriteBuffer(DWORD dwSize);
	DWORD GetWriteBuffer(BYTE** lpbBuffer,DWORD* lpdwSize);
	DWORD GetPortConfiguration(DWORD* lpdwBaudRate, DWORD* lpdwParity, BYTE* lpbStopBits, BYTE* lpbByteSize, DWORD* lpdwDSR,DWORD* lpdwCTS,DWORD* lpdwCheckParity,DWORD* lpdwRTS,DWORD* lpdwDTR);
	DWORD ConfigurePort(DWORD dwBaudRate,BYTE bParity,BYTE bStopBits,BYTE bByteSize,DWORD dwDSR,DWORD dwCTS,DWORD dwCheckParity,DWORD dwRTS,DWORD dwDTR);
	DWORD Release();
	DWORD SetCommunicationEvents(LPCOMMUNICATIONEVENTS plpCommunicationEvents);
	DWORD CancelSendBuffer();
	DWORD SetParity(BYTE bParity);
	DWORD EnableParity(BOOL bEnable);
	DWORD SetPortConfiguration(DWORD dwBaudRate,BYTE ByteSize, BYTE Parity, BYTE StopBits);
	DWORD SetCommMask(DWORD dwEvtMask);
	DWORD SetReadBufferLen(DWORD BufferLen);
	DWORD IsOpen();
	DWORD ClosePort();
	DWORD SetWaitTimeOut(DWORD pTimeOut);
	DWORD SendThreadMessage(LP_MESSAGE lpMessage);
	DWORD SendBuffer(BYTE *pBuffer, DWORD pCant);
	DWORD Initialize();
	DWORD OpenPort();
	DWORD SetPort(BYTE port);
	CSerialPort();
	~CSerialPort();
private:
	DWORD ApplyConfiguration();
	DWORD ThreadGetMessage();
	DWORD ThreadProcessMessage();
	DWORD SetupCommEvent();
	DWORD Configure();
	DWORD SetupRead();
	UINT Thread();
	static UINT ThreadProc(LPVOID pParam);
	HANDLE	hPort;
	DWORD	TimeOut;
	char	Port[20];
	BOOL	OnOpen;
	HANDLE	hThread;
	DWORD	EventMask;
	DWORD	EventType;
	HANDLE	hReadEvent,hWriteEvent,hEventEvent;
	DCB		dcb;
	COMMTIMEOUTS	CommTimeOuts;
	OVERLAPPED		ReadOverlapped,WriteOverlapped,EventOverlapped;
	//CMessageEvent	MessageEvent;
	// relacionadas con la lectura
	BYTE	ReadBuffer[BUFFERSIZE];
	BYTE	WriteBuffer[BUFFERSIZE];
	BYTE	m_ReadOffset;
	BYTE	m_WriteOffset;
	DWORD	BytesRead;
	DWORD	ReadBufferLen;
	LPCOMMUNICATIONEVENTS lpICommunicationEvents;
//	BYTE*	WriteBuffer;

	BOOL OnInitialize;
	BOOL m_OnSending;	//Operacion de escritura pendiente
};

#endif // !defined(AFX_ISERIALPORT1_H__61184290_0BA6_4418_BAE0_1728A4659763__INCLUDED_)
