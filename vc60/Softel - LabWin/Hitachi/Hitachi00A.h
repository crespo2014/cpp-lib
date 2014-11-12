// Hitachi00A.h: interface for the CHitachi00A class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HITACHI00A_H__39CF634C_0E36_4B81_AD5B_50FD207D48C7__INCLUDED_)
#define AFX_HITACHI00A_H__39CF634C_0E36_4B81_AD5B_50FD207D48C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\interfaces\Ilabdevice.h"
#include "ISerialPort.h"
#include "ISerialPortEvents.h"


class CHitachi00A : public ILabDevice,
					private ISerialPortEvents   
{
	// Interfaz IUnknown
	virtual DWORD _stdcall QueryInterface(char* lpName,_IUnknown** lpInterfaz);
	virtual DWORD _stdcall AddRef();	
	virtual DWORD _stdcall Release();
	virtual DWORD _stdcall Initialize();
	virtual DWORD _stdcall GetInterfaz(char* lpName,_IUnknown** lpInterfaz);
	//
	virtual DWORD _stdcall SetPort(BYTE port);
	virtual DWORD _stdcall GetName(char* lpBuffer,DWORD* bufferSize);
	virtual DWORD _stdcall SetPortConfiguration(DWORD dwBaudRate,BYTE bParity,BYTE bStopBits);
	virtual DWORD _stdcall GetPortConfiguration(DWORD* dwBaudRate,BYTE* bParity,BYTE* bStopBits);
	virtual DWORD _stdcall Connect();
	virtual DWORD _stdcall Disconnect();
	virtual DWORD _stdcall GetResults(ANALYSIS* lpResults,DWORD* lpCount);
	virtual DWORD _stdcall ClearResults();
	virtual DWORD _stdcall ProcessFile(char* lpFileName);

	// 
	virtual DWORD _stdcall OnReceivedData(BYTE* Buffer,DWORD cant,LPVOID lpParam);
	virtual DWORD _stdcall OnCommEvent(DWORD pEventMask,LPVOID lpParam);
	virtual DWORD _stdcall OnSendBytes(BYTE* Buffer,DWORD BytesWritten,LPVOID lpParam);
	virtual DWORD _stdcall OnProcessMessage(LP_MESSAGE lpMessage,LPVOID lpParam);
	virtual DWORD _stdcall OnWaitTimeOut(LPVOID lpParam);
	virtual DWORD _stdcall OnTrigger(LPVOID lpParam);
	virtual DWORD _stdcall OnRequestData(LPVOID lpParam);
	virtual DWORD _stdcall OnSetSerialPort(ISerialPort* lpSerialPort);
	virtual DWORD _stdcall OnOpenPort(LPVOID lpParam);
public:
	static DWORD _stdcall ProcessBuffer(BYTE *lpBuffer, DWORD dwSize, void *lParam);
	DWORD ProcessBlock();
	DWORD ResetBufferStatus();
	CHitachi00A();
	virtual ~CHitachi00A();
private:
	DWORD ProcessData(BYTE *lpData, DWORD dwSize);
	DWORD			m_cRef;
	PORT_CONFIG		m_PortConfig;
	ISerialPort*	m_ISerialPort;

	// Interpretador del buffer
	char	m_str[200];		// Almacena un string
	BYTE	m_separator;	// Indica en que separador esta 0 
	BYTE	m_strpos;		// proxima posicion del string a llenar
	BYTE	m_frame;		// Frame que se esta procesando
	BYTE	m_nextframe;	// Proximo frame que debe llegar
	BYTE	m_framestatus;	// Posicion que se esta procesando es la guia principal
	// datos temporales
	char	m_patient[200];
	char	m_analysis[10];
	char	m_sample[10];
	char	m_value[10];
	char	m_unit[10];
	char	m_time[20];
	ANALYSIS	m_Results[100];
	WORD		m_ResultCount;


};

#endif // !defined(AFX_HITACHI00A_H__39CF634C_0E36_4B81_AD5B_50FD207D48C7__INCLUDED_)
