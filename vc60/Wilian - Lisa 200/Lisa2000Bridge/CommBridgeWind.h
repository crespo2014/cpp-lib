// CommBridgeWind.h: interface for the CCommBridgeWind class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMBRIDGEWIND_H__B250F736_D9F7_45E1_93E4_43464DED2FFD__INCLUDED_)
#define AFX_COMMBRIDGEWIND_H__B250F736_D9F7_45E1_93E4_43464DED2FFD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wind.h"
#include "serialport.h"
#include "trafficWind.h"
#include "lockevent.h"
#include "serialportbridge.h"
#include "ICommunicationEvents.h"
#include "..\Lisa200\Lisa2000Filter.h"


#define UM_REFRESH_TW WM_USER+1		// Atualizar Traffic Window
#define COMMAND_COMM1 WM_USER+2
#define COMMAND_COMM2 WM_USER+3
#define UM_REFRESH_RB1 WM_USER+4		// Actualizar radio buttons puerto 1
#define UM_REFRESH_RB2 WM_USER+5		// Actualizar radio buttons puerto 1
#define UM_REFRESH_LB WM_USER+6			// Atualizar ListBox

#define SND 1
#define RCV 2
#define END 0

class CCommBridgeWind : public CWind, private ICommunicationEvents, private CLockEvent 
{
public:
	DWORD OnTimer();
	DWORD ClearListBox();
	DWORD OnEnableCommand();
	DWORD RefreshListBox();
	DWORD Release();
	DWORD Initialize();
	DWORD Create_Window();
	CCommBridgeWind();
	~CCommBridgeWind();
private:
	DWORD SetOutPutFile();
	// Interfaz ICommunicationEvents
	virtual DWORD _stdcall OnReceivedData(BYTE* Buffer,DWORD cant,LPVOID lpParam);
	virtual DWORD _stdcall OnCommEvent(DWORD pEventMask,LPVOID lpParam);
	virtual DWORD _stdcall OnSendBytes(BYTE* Buffer,DWORD BytesWritten,LPVOID lpParam);
	virtual DWORD _stdcall OnProcessMessage(LP_MESSAGE lpMessage,LPVOID lpParam);
	virtual DWORD _stdcall OnWaitTimeOut(LPVOID lpParam);
	virtual DWORD _stdcall OnTrigger(LPVOID lpParam);

	DWORD ProcessReadBuffer(BYTE *buffer, DWORD dwsize);
	DWORD ProcessSendBuffer(BYTE *buffer, DWORD dwsize);
	DWORD InitializeActDlg();
	DWORD WriteToFile(BYTE* buffer,DWORD dwcant,BYTE type);
	DWORD CloseFile();
	DWORD ChangeBreak(HWND hDlg, CSerialPort *lpSerialPort);
	DWORD ChangeRTS(HWND hDlg, CSerialPort *lpSerialPort);
	DWORD ChangeDTR(HWND hDlg, CSerialPort *lpSerialPort);
	DWORD UpdateInputSignals(HWND hDlg, CSerialPort *lpSerialPort);
	DWORD DisconnectPort(HWND hDlg, CSerialPort *lpSerialPort);
	DWORD ConnectPort(HWND hDlg, CSerialPort *lpSerialPort);
	DWORD ConfigurePort(HWND hDlg,CSerialPort* lpSerialPort);
	DWORD ConfigCommDlg(HWND hDlg,PORT_CONFIG* lpPortConfig);
	DWORD GetDlgConfig(HWND hDlg,PORT_CONFIG* lpPortConfig);
	DWORD InitializeCommDlg(HWND hDlg);
	virtual LRESULT WndProc(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam);

	// Procedimientos para procesar los mensajes de los dialogos
	static INT_PTR Comm2DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static INT_PTR Comm1DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static INT_PTR DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	HWND m_hComm1Dlg;
	HWND m_hComm2Dlg;
	HWND m_hActDlg;
	PORT_CONFIG m_Comm1Config;
	PORT_CONFIG m_Comm2Config;
	CSerialPort	m_Port1;
	CSerialPort	m_Port2;
	CTrafficWind m_TrafficWind;
	// Buffers
	COMM_BUFFER m_Port1Buffer;
	COMM_BUFFER m_Port2Buffer;
	// Flags
	BOOL	m_OnShowLastRow;
	BOOL	m_OnShowTraffic;
	// Indicadores
	DWORD	m_SendCant;
	DWORD	m_ReadCant;
	DWORD	m_FileSize;
	HANDLE	m_hFile;
	// Buffer temporal antes de pasar los datos al listbox
	BYTE	m_Buff1[1000];
	BYTE	m_Buff2[1000];
	BYTE*	m_Buff;			//Puntero que indica el buffer en uso
	DWORD	m_BuffPos;		//Posicion de escritura.
	CLisa2000Filter Filter;
};

#endif // !defined(AFX_COMMBRIDGEWIND_H__B250F736_D9F7_45E1_93E4_43464DED2FFD__INCLUDED_)
