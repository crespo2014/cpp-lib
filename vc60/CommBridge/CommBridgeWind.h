// CommBridgeWind.h: interface for the CCommBridgeWind class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMBRIDGEWIND_H__B250F736_D9F7_45E1_93E4_43464DED2FFD__INCLUDED_)
#define AFX_COMMBRIDGEWIND_H__B250F736_D9F7_45E1_93E4_43464DED2FFD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wind.h"
#include "iserialport.h"
#include "SerialPortBridge.h"
#include "trafficWind.h"
#include "lockevent.h"
#include "common.h"
#include "ICommunicationBridgeEvents.h"


#define UM_REFRESH_TW WM_USER+1		// Atualizar Traffic Window
#define COMMAND_COMM1 WM_USER+2
#define COMMAND_COMM2 WM_USER+3
#define UM_REFRESH_RB1 WM_USER+4		// Actualizar radio buttons puerto 1
#define UM_REFRESH_RB2 WM_USER+5		// Actualizar radio buttons puerto 1

class CCommBridgeWind : public CWind,
						private ICommunicationBridgeEvents, private CSerialPortBridge 
{
public:
	
	virtual DWORD _stdcall Release();
	virtual DWORD _stdcall Initialize();
	DWORD Create_Window();
	CCommBridgeWind();
	~CCommBridgeWind();
private:
	DWORD SetOutPutFile();
	DWORD ClearAll();
	// Interfaz ICommunicationBridgeEvents  
	virtual DWORD _stdcall OnBridgeSndBuffer(BYTE *buffer, DWORD dwsize);
	virtual DWORD _stdcall OnBridgeRcvBuffer(BYTE *buffer, DWORD dwsize);
	virtual DWORD _stdcall OnBridgeSndPortEvent(DWORD pEventMask);
	virtual DWORD _stdcall OnBridgeRcvPortEvent(DWORD pEventMask);
	virtual DWORD _stdcall OnBridgePortOpen(LPVOID lpParam);

	DWORD AddComment();
	DWORD UpdateActDlg();
	DWORD InitializeActDlg();
	DWORD OnShowTraffic();
	DWORD OnShowLastRow();
	DWORD WriteToFile(BYTE* buffer,DWORD dwcant,BYTE type);
	DWORD CloseFile();
	DWORD ChangeBreak(HWND hDlg, ISerialPort *lpSerialPort);
	DWORD ChangeRTS(HWND hDlg, ISerialPort *lpSerialPort);
	DWORD ChangeDTR(HWND hDlg, ISerialPort *lpSerialPort);
	DWORD UpdateInputSignals(HWND hDlg, DWORD Signals);
	DWORD DisconnectPort(HWND hDlg, ISerialPort *lpSerialPort);
	DWORD ConnectPort(HWND hDlg, ISerialPort *lpSerialPort);
	DWORD ConfigurePort(HWND hDlg,ISerialPort* lpSerialPort);
	DWORD ConfigCommDlg(HWND hDlg,PORT_CONFIG* lpPortConfig);
	DWORD GetDlgConfig(HWND hDlg,PORT_CONFIG* lpPortConfig);
	DWORD InitializeCommDlg(HWND hDlg);
	DWORD ReportCommError(DWORD dwEventMask,DWORD dwError);
	virtual LRESULT _stdcall OnWindProc(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam);

	// Procedimientos para procesar los mensajes de los dialogos
	static INT_PTR Comm2DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static INT_PTR Comm1DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static INT_PTR DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	HWND m_hComm1Dlg;
	HWND m_hComm2Dlg;
	HWND m_hActDlg;
	PORT_CONFIG m_Comm1Config;
	PORT_CONFIG m_Comm2Config;

	/*
	ISerialPort* m_RcvPort;
	ISerialPort* m_SndPort;
	*/

	CTrafficWind m_TrafficWind;

	// Flags
	BOOL	m_OnShowLastRow;
	BOOL	m_OnShowTraffic;
	// Indicadores
	DWORD	m_SendCant;
	DWORD	m_ReadCant;
	DWORD	m_FileSize;
	HANDLE	m_hFile;
};

#endif // !defined(AFX_COMMBRIDGEWIND_H__B250F736_D9F7_45E1_93E4_43464DED2FFD__INCLUDED_)
