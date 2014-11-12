// SerialPortBridge.h: interface for the CSerialPortBridge class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERIALPORTBRIDGE_H__C248864A_7A4C_4263_97A8_E1F7C9A37800__INCLUDED_)
#define AFX_SERIALPORTBRIDGE_H__C248864A_7A4C_4263_97A8_E1F7C9A37800__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "iSerialPort.h"
#include "lockevent.h"
#include "iSerialPortEvents.h"
#include "ICommunicationBridgeEvents.h"
#include "_IUnknown.h"
#include "errorcodes.h"
#include "unknown.h"

#define COMM_BUFFER_SIZE 1024

typedef struct
{
	BYTE Buffer[COMM_BUFFER_SIZE];
	DWORD WriteIndex;
	DWORD ReadIndex;
	BOOL OnWriting;
	ISerialPort* SerialPort;
} COMM_BUFFER;


#define BS_OK		1	// Todo trabajando bien
#define BS_ERROR	2	// Error en el puente
#define BS_PERROR	3	// Error en un puerto
#define BS_STOP		4	// El puente esta detenido
#define BS_OVERFLOW 5


class CSerialPortBridge : protected ISerialPortEvents, 
						  private CLockEvent,
						  private CUnknown//,_IUnknown
{

public:
	// Interfaz IUnknown
	virtual DWORD _stdcall UnInitialize();
	virtual DWORD _stdcall Initialize();
	virtual DWORD _stdcall GetInterfaz(char* lpName,void** lpInterfaz);

public:
	DWORD GetBridgeStatus(DWORD *dwStatus, int *iError);
	DWORD Stop();
	DWORD GetCommError(BOOL rcvport,LPDWORD lpErrors);
	DWORD GetPortSignals(BOOL rcvport,DWORD *lpdwSignals);
	DWORD GetSerialPort(BOOL rcvport,ISerialPort** lplpISerialPort);
	DWORD GetPortConfiguration(BOOL rcvport, PORT_CONFIG *lpPortConfig);
	DWORD SetPortConfiguration(BOOL rcvport,PORT_CONFIG* lpPortConfig);
	DWORD Start();
	//DWORD GetSendSerialPort(CSerialPort **lplpSerialPort);
	//DWORD GetReceivedSerialPort(CSerialPort** lplpSerialPort);
	CSerialPortBridge();
	DWORD SetICommunicationBridgeEvents(LPCOMMUNICATIONBRIDGEEVENTS lpCommunicationBridgeEvents);
	virtual ~CSerialPortBridge();

protected:
	// Interfaz ICommunicationEvents
	virtual DWORD _stdcall OnReceivedData(BYTE* Buffer,DWORD cant,LPVOID lpParam);
	virtual DWORD _stdcall OnCommEvent(DWORD pEventMask,LPVOID lpParam);
	virtual DWORD _stdcall OnSendBytes(BYTE* Buffer,DWORD BytesWritten,LPVOID lpParam);
	virtual DWORD _stdcall OnProcessMessage(LP_MESSAGE lpMessage,LPVOID lpParam);
	virtual DWORD _stdcall OnWaitTimeOut(LPVOID lpParam);
	virtual DWORD _stdcall OnTrigger(LPVOID lpParam);
	virtual DWORD _stdcall OnRequestData(LPVOID lpParam);
	virtual DWORD _stdcall OnSetSerialPort(ISerialPort* lpSerialPort);
	virtual DWORD _stdcall OnOpenPort(LPVOID lpParam);

	// Buffers
	COMM_BUFFER m_RcvPortBuffer;
	COMM_BUFFER m_SndPortBuffer;

	ISerialPort* m_SndSerialPort;	// Puerto espejo se procesa como un rcv
	ISerialPort* m_RcvSerialPort;	// Puerto serie que recive datos, se procesa como un snd

	// Interfaz
	LPCOMMUNICATIONBRIDGEEVENTS m_lpCommunicationBridgeEvents;

	//Status
	DWORD m_BridgeStatus;
	DWORD m_BridgeError;
};	

#endif // !defined(AFX_SERIALPORTBRIDGE_H__C248864A_7A4C_4263_97A8_E1F7C9A37800__INCLUDED_)
