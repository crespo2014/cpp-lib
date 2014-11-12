// ISerialPort1.h: interface for the ISerialPort1 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ISERIALPORT1_H__61184290_0BA6_4418_BAE0_1728A4659763__INCLUDED_)
#define AFX_ISERIALPORT1_H__61184290_0BA6_4418_BAE0_1728A4659763__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MessageEvent.h"
#include "ISerialPortEvents.h"
#include "errorcodes.h"
#include "iserialport.h"
#include "dllCommon.h"
#include "unknown.h"

#define BUFFERSIZE 500

class CSerialPort : public CISerialPort,
					public CMessageEvent
{
public:
	
	// Interfaz IUnknown
	virtual DWORD _stdcall Initialize();
	virtual DWORD _stdcall GetInterfaz(char* lpName,void** lpInterfaz);
	virtual DWORD _stdcall DeleteObject();

	// Interfaz ISerialPort
	virtual DWORD _stdcall SetCommunicationMode(DWORD bAsyncRead,DWORD WaitTimeout,LPVOID lpParam,DWORD ReadBufferLen);
	virtual DWORD _stdcall SetPort(BYTE port);
	virtual DWORD _stdcall SetReadTimeOuts(DWORD Interval,DWORD Total,DWORD Multiplier);
	virtual DWORD _stdcall SetTrigger();
	virtual DWORD _stdcall SetPortConfiguration(PORT_CONFIG* lpPortConfig);
	virtual DWORD _stdcall SetCommMask(DWORD dwEvtMask);
	virtual DWORD _stdcall GetThreadError();		// Estado del hilo
	virtual DWORD _stdcall GetThreadLastError();	// Error extendido del hilo depende del tipo de error
	virtual DWORD _stdcall GetLastError();			// Error extendido
	virtual DWORD _stdcall GetPortConfiguration(PORT_CONFIG* lpPortConfig);
	virtual DWORD _stdcall GetInputSignals(DWORD* lpdwSignals);
	virtual DWORD _stdcall GetWriteBuffer(BYTE** lpbBuffer,DWORD* lpdwSize);
	virtual DWORD _stdcall GetCommunicationError(DWORD* lpErrors);
	virtual DWORD _stdcall ThreadSend(BYTE* lpBuffer,DWORD dwCant);
	virtual DWORD _stdcall ThreadRead(BYTE* lpBuffer,DWORD dwCant);
	virtual DWORD _stdcall ChangeOutputSignal(DWORD Operation);
	virtual DWORD _stdcall CancelSend();
	virtual DWORD _stdcall ClosePort();
	virtual DWORD _stdcall SendThreadMessage(LP_MESSAGE lpMessage);
	virtual DWORD _stdcall OpenPort();
	virtual DWORD _stdcall RequestData();
	virtual DWORD _stdcall Attach(_IUnknown* lpInterfaz);
	CSerialPort();
	~CSerialPort();
private:
	DWORD _stdcall UnInitialize();
	DWORD OnSend(DWORD dwBytesWritten);
	DWORD ThreadGetMessage();
	DWORD ThreadProcessMessage();
	DWORD SetupCommEvent();
	UINT Thread();
	static UINT ThreadProc(LPVOID pParam);

	COMMTIMEOUTS	CommTimeOuts;
	OVERLAPPED		ReadOverlapped,WriteOverlapped,EventOverlapped;
	ISerialPortEvents* m_ISerialPortEvents;	// Interfaz de notificacion

	LPVOID	m_lpParam;	// De uso general
	HANDLE	m_hPort;
	DWORD	TimeOut;
	BYTE	Port;
	HANDLE	hThread;
	DWORD	EventMask;
	DWORD	EventType;
	HANDLE	hReadEvent,hWriteEvent,hEventEvent;
	HANDLE  m_hTriggerEvent;
	DCB		dcb;

	// relacionadas con la lectura
	
	BYTE	m_RDBuffer[BUFFERSIZE];
	BYTE	m_WRBuffer[BUFFERSIZE];
	
	DWORD	BytesRead;
	DWORD	m_ReadBufferLen;
	
	BOOL	OnInitialize;
	DWORD	m_BytesToSend;		// Cantidad de bytes por enviar
	DWORD	m_BytesWritten;		// Cantidad de bytes ya enviados
	BOOL	m_OnAsyncRead;
	BYTE*	m_SendBuffer;
	BYTE*	m_ReadBuffer;

	DWORD	m_ThreadError;
	DWORD	m_ThreadLastError;
	DWORD	m_LastError;
	
};

#endif // !defined(AFX_ISERIALPORT1_H__61184290_0BA6_4418_BAE0_1728A4659763__INCLUDED_)
