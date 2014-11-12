// ISerialPortEvents.h: interface for the ISerialPortEvents class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ISERIALPORTEVENTS_H__F65F07E8_9256_46A0_B525_520E4A669A14__INCLUDED_)
#define AFX_ISERIALPORTEVENTS_H__F65F07E8_9256_46A0_B525_520E4A669A14__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ISerialPort.h"
#include "errorcodes.h"

class ISerComEvents		// Serial Communication Events
{
public:
	virtual DWORD _stdcall OnReceivedData(BYTE* Buffer,DWORD cant,LPVOID lpParam)=0;
	virtual DWORD _stdcall OnCommEvent(DWORD pEventMask,LPVOID lpParam)=0;
	virtual DWORD _stdcall OnSendBytes(BYTE* Buffer,DWORD BytesWritten,LPVOID lpParam)=0;
	virtual DWORD _stdcall OnProcessMessage(LP_MESSAGE lpMessage,LPVOID lpParam)=0;
	virtual DWORD _stdcall OnTrigger(LPVOID lpParam)=0;
	virtual DWORD _stdcall OnRequestData(LPVOID lpParam)=0;
	virtual DWORD _stdcall OnSetSerialPort(ISerialPort* lpSerialPort)=0;
	virtual DWORD _stdcall OnOpenPort(LPVOID lpParam)=0;
};

class ISerialPortEvents 
{
public:
	virtual DWORD _stdcall OnReceivedData(BYTE* Buffer,DWORD cant,LPVOID lpParam)=0;
	virtual DWORD _stdcall OnCommEvent(DWORD pEventMask,LPVOID lpParam)=0;
	virtual DWORD _stdcall OnSendBytes(BYTE* Buffer,DWORD BytesWritten,LPVOID lpParam)=0;
	virtual DWORD _stdcall OnProcessMessage(LP_MESSAGE lpMessage,LPVOID lpParam)=0;
	virtual DWORD _stdcall OnWaitTimeOut(LPVOID lpParam)=0;
	virtual DWORD _stdcall OnTrigger(LPVOID lpParam)=0;
	virtual DWORD _stdcall OnRequestData(LPVOID lpParam)=0;
	virtual DWORD _stdcall OnSetSerialPort(ISerialPort* lpSerialPort)=0;
	virtual DWORD _stdcall OnOpenPort(LPVOID lpParam)=0;
};

class CSerialPortEvents : public ISerialPortEvents
{
protected:
	virtual DWORD _stdcall OnReceivedData(BYTE* Buffer,DWORD cant,LPVOID lpParam){return ERR_NONE;};
	virtual DWORD _stdcall OnCommEvent(DWORD pEventMask,LPVOID lpParam){return ERR_NONE;};
	virtual DWORD _stdcall OnSendBytes(BYTE* Buffer,DWORD BytesWritten,LPVOID lpParam){return ERR_NONE;};
	virtual DWORD _stdcall OnProcessMessage(LP_MESSAGE lpMessage,LPVOID lpParam){return ERR_NONE;};
	virtual DWORD _stdcall OnWaitTimeOut(LPVOID lpParam){return ERR_NONE;};
	virtual DWORD _stdcall OnTrigger(LPVOID lpParam){return ERR_NONE;};
	virtual DWORD _stdcall OnRequestData(LPVOID lpParam){return ERR_NONE;};
	virtual DWORD _stdcall OnSetSerialPort(ISerialPort* lpSerialPort)
	{
		m_ISerialPort = lpSerialPort;
		if (!m_ISerialPort) return ERR_NOINTERFACE;
		m_ISerialPort->SetCommunicationMode(m_bAsyncRead,m_WaitTimeout,m_lpParam,m_ReadBufferLen);
		return ERR_NONE;
	};
	virtual DWORD _stdcall OnOpenPort(LPVOID lpParam)
	{
		m_ISerialPort->SetReadTimeOuts(m_ReadIntervalTimeout,m_ReadTotalTimeoutConstant,m_ReadTotalTimeoutMultiplier);
		m_ISerialPort->SetPortConfiguration(&m_PortConfig);
		return ERR_NONE;
	};
	CSerialPortEvents()
	{
		m_ISerialPort = NULL;
		m_PortConfig.BaudRate = CBR_9600;
		m_PortConfig.Parity = NOPARITY;
		m_PortConfig.StopBits = ONESTOPBIT;
		m_PortConfig.ByteSize = 8;
		m_PortConfig.CheckParity = false;
		m_PortConfig.CTSStopOutFlow = false;
		m_PortConfig.DSRStopInFlow = false;
		m_PortConfig.DSRStopOutFlow = false;
		m_PortConfig.DTRMode = DTR_CONTROL_ENABLE;
		m_PortConfig.RTSMode = RTS_CONTROL_ENABLE;
		m_PortConfig.lParam = NULL;
		m_bAsyncRead = true;
		m_WaitTimeout = INFINITE;
		m_lpParam = NULL;
		m_ReadBufferLen = -1;
		m_ReadIntervalTimeout = 1; 
		m_ReadTotalTimeoutMultiplier = 0; 
		m_ReadTotalTimeoutConstant = 0;
	};
	PORT_CONFIG		m_PortConfig;
	DWORD			m_ReadIntervalTimeout; 
	DWORD			m_ReadTotalTimeoutMultiplier; 
	DWORD			m_ReadTotalTimeoutConstant; 
	ISerialPort*	m_ISerialPort;
	DWORD			m_bAsyncRead;
	DWORD			m_WaitTimeout;
	LPVOID			m_lpParam;
	DWORD			m_ReadBufferLen;
};

#endif // !defined(AFX_ISERIALPORTEVENTS_H__F65F07E8_9256_46A0_B525_520E4A669A14__INCLUDED_)
