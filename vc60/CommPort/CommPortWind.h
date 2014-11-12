// CommPortWind.h: interface for the CCommPortWind class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMPORTWIND_H__B7974772_98A2_4CBE_BD2D_362A07BE2C23__INCLUDED_)
#define AFX_COMMPORTWIND_H__B7974772_98A2_4CBE_BD2D_362A07BE2C23__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Wind.h"
#include "ISerialPort.h"
#include "BinaryWnd.h"
#include "TrafficWind.h"
#include "ISerialPortEvents.h"
#include "_IUnknown.h"

#define UM_REFRESH_RB WM_USER+1		// Actualizar radio buttons
#define UM_REFRESH_TW WM_USER+2		// Atualizar Traffic Window
#define UM_SND_FINISH WM_USER+3		// Ya el hilo envio todos los bytes por el puerto serie

#define TM_SEND 1000		// Thread Message Send Iniciar envio de datos
#define TM_ABORT_SEND 1001	// Thread Message Send Abortar el envio de datos

class CCommPortWind : public CWind,
					  private CSerialPortEvents,
					  private CUnknown
{
public:
	DWORD _stdcall UnInitialize();
	DWORD SaveBIN();
	
	// Interfaz IUnknown
	virtual DWORD _stdcall Initialize();
	virtual DWORD _stdcall GetInterfaz(char* lpName,void** lpInterfaz);

	DWORD Create_Window();
	CCommPortWind();
	~CCommPortWind();
private:
	DWORD ReadFile();
	DWORD SendFinish();
	DWORD ThreadSend();
	DWORD RefreshTraffic();
	DWORD AddComment();
	DWORD UpdateInputSignals();
	DWORD ChangeBreak();
	DWORD ChangeRTS();
	DWORD ChangeDTR();
	DWORD Send();
	DWORD Disconnect();
	DWORD Connect();
	DWORD SetPortNumber();
	DWORD ConfigurePort();
	DWORD PortToDlg();
	DWORD DlgToPort();
	
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

	virtual LRESULT _stdcall OnWindProc(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam);
	static INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	CBinaryWnd   m_BinaryWind;
	CTrafficWind m_TrafficWind;
	HWND	m_hPropDlg;
	HWND	m_hActDlg;
	// Item seleccionado de los combobox
	BYTE	m_PortIndex,m_ByteSizeIndex,m_StopBitsIndex,m_ParityIndex;
	BYTE	m_BaudRateIndex,m_DTRIndex,m_RTSIndex;
	// Usadas cuando se esta enviando un buffer por el puerto serie
	BOOL	m_OnSending;

	ISerialPort* m_ISerialPort;

};

#endif // !defined(AFX_COMMPORTWIND_H__B7974772_98A2_4CBE_BD2D_362A07BE2C23__INCLUDED_)
