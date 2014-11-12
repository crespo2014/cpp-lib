// ISerialBus.h: interface for the ISerialBus class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ISERIALBUS_H__70344071_3280_409B_9137_9710C17FA546__INCLUDED_)
#define AFX_ISERIALBUS_H__70344071_3280_409B_9137_9710C17FA546__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ISerialPort.h"
#include "_IUnknown.h"

class ISerialBus : public _IUnknown  
{
public:
	virtual DWORD _stdcall SetCommunicationMode(DWORD bAsyncRead,DWORD WaitTimeout,LPVOID lpParam,DWORD ReadBufferLen) = 0;
	virtual DWORD _stdcall SetReadTimeOut(DWORD dwTimeOut) = 0;
	virtual DWORD _stdcall SetTrigger() = 0;
	virtual DWORD _stdcall SetPortConfiguration(PORT_CONFIG* lpPortConfig) = 0;
	virtual DWORD _stdcall GetThreadError() = 0;		// Estado del hilo
	virtual DWORD _stdcall GetThreadLastError() = 0;	// Error extendido del hilo depende del tipo de error
	virtual DWORD _stdcall GetLastError() = 0;			// Error extendido
	virtual DWORD _stdcall GetWriteBuffer(BYTE** lpbBuffer,DWORD* lpdwSize) = 0;
	virtual DWORD _stdcall ThreadWrite(BYTE* lpBuffer,DWORD dwCant) = 0;
	virtual DWORD _stdcall ThreadRead(BYTE* lpBuffer,DWORD dwCant) = 0;
	virtual DWORD _stdcall CancelSend() = 0;
	virtual DWORD _stdcall SendThreadMessage(LP_MESSAGE lpMessage) = 0;
	virtual DWORD _stdcall RequestData() = 0;	
};

class ISSwitchNet : public _IUnknown	// Serial Switch Network Interfaz
{
public:
	virtual DWORD _stdcall CheckConnection(WORD wSwitchNo) = 0;
};

class ISwitch		// Switch Interfaz for Serial Bus class
{
public:
	virtual DWORD _stdcall SetTrigger(DWORD dwID) = 0;
	virtual DWORD _stdcall SendThreadMessage(DWORD dwID,LP_MESSAGE pMessage) = 0;
};


#endif // !defined(AFX_ISERIALBUS_H__70344071_3280_409B_9137_9710C17FA546__INCLUDED_)
