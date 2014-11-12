// ISerialPort.h: interface for the ISerialPort class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ISERIALPORT_H__F046CF68_2D28_479D_BE37_6504A1E95567__INCLUDED_)
#define AFX_ISERIALPORT_H__F046CF68_2D28_479D_BE37_6504A1E95567__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Unknown.h"
#include "_IUnknown.h"
#include "MessageEvent.h"
#include "errorcodes.h"

// definiciones del puerto serie
typedef struct
{
	char* str;
	DWORD val;
} S_PORTDATA;

#define MAXPORTS 4
#define MAXDTROFC 3
#define MAXRTSOFC 4
#define MAXBYTESIZE 4
#define MAXSTOPBITS 3
#define MAXPARITY 5
#define MAXBAUDRATE 15

extern char* PORTS[];
extern S_PORTDATA DTROFC[];
extern S_PORTDATA RTSOFC[];
extern S_PORTDATA BYTESIZE[];
extern S_PORTDATA STOPBITS[];
extern S_PORTDATA PARITY[];
extern S_PORTDATA BAUDRATE[];

typedef struct
{
	DWORD BaudRate;
	BYTE ByteSize;
	BYTE Parity;
	BYTE StopBits;
	DWORD CheckParity;
	DWORD DSRStopOutFlow;	 
	DWORD CTSStopOutFlow;			
	DWORD DSRStopInFlow;
	DWORD RTSMode;
	DWORD DTRMode;
	void*	lParam;
} PORT_CONFIG;

class ISerialPort : public _IUnknown   
{
public:
	virtual DWORD _stdcall SetCommunicationMode(DWORD bAsyncRead,DWORD WaitTimeout,LPVOID lpParam,DWORD ReadBufferLen) = 0;
	virtual DWORD _stdcall SetPort(BYTE port) = 0;
	virtual DWORD _stdcall SetReadTimeOuts(DWORD Interval,DWORD Total,DWORD Multiplier) = 0;
	virtual DWORD _stdcall SetTrigger() = 0;
	virtual DWORD _stdcall SetPortConfiguration(PORT_CONFIG* lpPortConfig) = 0;
	virtual DWORD _stdcall SetCommMask(DWORD dwEvtMask) = 0;
	virtual DWORD _stdcall GetThreadError() = 0;		// Estado del hilo
	virtual DWORD _stdcall GetThreadLastError() = 0;	// Error extendido del hilo depende del tipo de error
	virtual DWORD _stdcall GetLastError() = 0;			// Error extendido
	virtual DWORD _stdcall GetPortConfiguration(PORT_CONFIG* lpPortConfig) = 0;
	virtual DWORD _stdcall GetInputSignals(DWORD* lpdwSignals) = 0;
	virtual DWORD _stdcall GetCommunicationError(DWORD* lpErrors) = 0;
	virtual DWORD _stdcall GetWriteBuffer(BYTE** lpbBuffer,DWORD* lpdwSize) = 0;
	virtual DWORD _stdcall ThreadSend(BYTE* lpBuffer,DWORD dwCant) = 0;
	virtual DWORD _stdcall ThreadRead(BYTE* lpBuffer,DWORD dwCant) = 0;
	virtual DWORD _stdcall ChangeOutputSignal(DWORD Operation) = 0;
	virtual DWORD _stdcall CancelSend() = 0;
	virtual DWORD _stdcall ClosePort() = 0;
	virtual DWORD _stdcall SendThreadMessage(LP_MESSAGE lpMessage) = 0;
	virtual DWORD _stdcall OpenPort() = 0;
	/*
	 Usada para indicar que la clase puede pedir enviar informacion a traves del puerto
	 usando ThreadSend, es mas bien un inicio de comunicacion
	*/
	virtual DWORD _stdcall RequestData() = 0;	
	virtual DWORD _stdcall Attach(_IUnknown* lpInterfaz) = 0;
};


class CISerialPort : public ISerialPort,
					 protected CUnknown  
{
protected:
	virtual DWORD _stdcall QueryInterface(char* lpName,void** lpInterfaz)	{return CUnknown::QueryInterface(lpName,lpInterfaz);}
	virtual DWORD _stdcall AddRef()											{return CUnknown::AddRef();}
	virtual DWORD _stdcall Release()										{return CUnknown::Release();}
	virtual DWORD _stdcall Initialize()										{return CUnknown::Initialize();}
	virtual DWORD _stdcall GetInterfaz(char* lpName,void** lpInterfaz)		{return CUnknown::GetInterfaz(lpName,lpInterfaz);}
	virtual DWORD _stdcall DeleteObject()									{return CUnknown::DeleteObject();}

	virtual DWORD _stdcall SetCommunicationMode(DWORD bAsyncRead,DWORD WaitTimeout,LPVOID lpParam,DWORD ReadBufferLen)	{return ERR_INV_FUNC;};
	virtual DWORD _stdcall SetPort(BYTE port)																			{return ERR_INV_FUNC;};
	virtual DWORD _stdcall SetReadTimeOuts(DWORD Interval,DWORD Total,DWORD Multiplier)									{return ERR_INV_FUNC;};
	virtual DWORD _stdcall SetTrigger()																					{return ERR_INV_FUNC;};
	virtual DWORD _stdcall SetPortConfiguration(PORT_CONFIG* lpPortConfig)												{return ERR_INV_FUNC;};
	virtual DWORD _stdcall SetCommMask(DWORD dwEvtMask)																	{return ERR_INV_FUNC;};
	virtual DWORD _stdcall GetThreadError()																				{return ERR_INV_FUNC;};
	virtual DWORD _stdcall GetThreadLastError()																			{return ERR_INV_FUNC;};
	virtual DWORD _stdcall GetLastError()																				{return ERR_INV_FUNC;};			
	virtual DWORD _stdcall GetPortConfiguration(PORT_CONFIG* lpPortConfig)												{return ERR_INV_FUNC;};
	virtual DWORD _stdcall GetInputSignals(DWORD* lpdwSignals)															{return ERR_INV_FUNC;};
	virtual DWORD _stdcall GetCommunicationError(DWORD* lpErrors)														{return ERR_INV_FUNC;};
	virtual DWORD _stdcall GetWriteBuffer(BYTE** lpbBuffer,DWORD* lpdwSize)												{return ERR_INV_FUNC;};
	virtual DWORD _stdcall ThreadSend(BYTE* lpBuffer,DWORD dwCant)														{return ERR_INV_FUNC;};
	virtual DWORD _stdcall ThreadRead(BYTE* lpBuffer,DWORD dwCant)														{return ERR_INV_FUNC;};
	virtual DWORD _stdcall ChangeOutputSignal(DWORD Operation)															{return ERR_INV_FUNC;};
	virtual DWORD _stdcall CancelSend()																					{return ERR_INV_FUNC;};
	virtual DWORD _stdcall ClosePort()																					{return ERR_INV_FUNC;};
	virtual DWORD _stdcall SendThreadMessage(LP_MESSAGE lpMessage)														{return ERR_INV_FUNC;};
	virtual DWORD _stdcall OpenPort()																					{return ERR_INV_FUNC;};
	virtual DWORD _stdcall RequestData()																				{return ERR_INV_FUNC;};	
	virtual DWORD _stdcall Attach(_IUnknown* lpInterfaz)																{return ERR_INV_FUNC;};
};

#endif // !defined(AFX_ISERIALPORT_H__F046CF68_2D28_479D_BE37_6504A1E95567__INCLUDED_)
