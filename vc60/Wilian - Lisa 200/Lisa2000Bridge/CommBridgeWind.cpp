// CommBridgeWind.cpp: implementation of the CCommBridgeWind class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CommBridgeWind.h"
#include "resource.h"
#include "..\clases\common.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CCommBridgeWind::CCommBridgeWind()
{
	m_Port1.SetCommunicationEvents(this);
	m_Port2.SetCommunicationEvents(this);
	m_Port1.SetParam((void*)1);
	m_Port2.SetParam((void*)2);
	m_hComm1Dlg = NULL;
	m_hComm2Dlg = NULL;
	m_hActDlg	= NULL;
	// Buffers
	m_Port1Buffer.lpParam = &m_Port1;
	m_Port1Buffer.OnWriting = FALSE;
	m_Port1Buffer.ReadIndex = 0;
	m_Port1Buffer.WriteIndex = 0;

	m_Port2Buffer.lpParam = &m_Port2;
	m_Port2Buffer.OnWriting = FALSE;
	m_Port2Buffer.ReadIndex = 0;
	m_Port2Buffer.WriteIndex = 0;

	m_OnShowLastRow = FALSE;
	m_OnShowTraffic = TRUE;

	m_FileSize = 0;
	m_hFile = NULL;
	m_ReadCant = 0;
	m_SendCant = 0;
	m_hFile = NULL;

	m_Buff = m_Buff1;
	m_BuffPos = 0;
}

CCommBridgeWind::~CCommBridgeWind()
{

}

DWORD CCommBridgeWind::Create_Window()
{
#define PROP_HEIGHT 120	//Ventana de propiedades del puerto
#define TRAF_HEIGHT 0 //170 //Ventana de trafico
#define MNU_HEIGHT	45	//Menu y caption 
#define INF_HEIGHT	270 //75  // Informacion 
#define WND_WIDTH	695
#define P0 0
#define P1 PROP_HEIGHT
#define P1_1 (P1+TRAF_HEIGHT)
#define P2 (P1_1+INF_HEIGHT)
#define P3 (P2+PROP_HEIGHT)
#define P4 (P3+MNU_HEIGHT)

	DWORD result;
	HMENU hmenu=LoadMenu(NULL,"COMMBRIDGE_MENU1");
	HICON hicon = LoadIcon(GetModuleHandle (NULL),"COMMBRIDGE_ICON1");
	result = Create("Serial Port Bridge",WS_CAPTION|WS_BORDER|WS_VISIBLE|WS_MINIMIZEBOX|WS_SYSMENU,40,40,WND_WIDTH+6,P4,NULL,hmenu,(HINSTANCE)GetModuleHandle(NULL),NULL);
	if (result != 0)
		return 1;
	SendMessage(m_hwnd,WM_SETICON,ICON_BIG,(long)hicon);
	// Crear ventanas internas
	m_TrafficWind.Create_Window(1,P1,WND_WIDTH-1,TRAF_HEIGHT,m_hwnd);
	// Crear ventanas de dialogo
	HRSRC hrscr = ::FindResource(GetModuleHandle(NULL),"COM_PROPERTIES",RT_DIALOG);
	if (hrscr == NULL) return 2;
	HGLOBAL hGlobal =::LoadResource(GetModuleHandle(NULL),hrscr);
	if (hGlobal == NULL) return 2;
	LPVOID lpvoid =::LockResource(hGlobal);
	if (lpvoid == NULL) return 2;
	m_hComm1Dlg = ::CreateDialogIndirect(GetModuleHandle (NULL),(LPCDLGTEMPLATE)lpvoid,m_hwnd,(DLGPROC)Comm1DlgProc);
	if (m_hComm1Dlg == NULL) return 2;
	::SetWindowPos(m_hComm1Dlg,NULL,P0,0,WND_WIDTH,PROP_HEIGHT,0);
	ShowWindow(m_hComm1Dlg,SW_SHOW);
	// Segundo dialogo
	m_hComm2Dlg = ::CreateDialogIndirect(GetModuleHandle (NULL),(LPCDLGTEMPLATE)lpvoid,m_hwnd,(DLGPROC)Comm2DlgProc);
	if (m_hComm2Dlg == NULL) return 2;
	::SetWindowPos(m_hComm2Dlg,NULL,0,P2,WND_WIDTH,PROP_HEIGHT,0);
	ShowWindow(m_hComm2Dlg,SW_SHOW);
	UnlockResource(hGlobal);
	// Ventana de informcion y acciones
	hrscr = ::FindResource(GetModuleHandle(NULL),"BRG_INFO",RT_DIALOG);
	if (hrscr == NULL) return 2;
	hGlobal =::LoadResource(GetModuleHandle(NULL),hrscr);
	if (hGlobal == NULL) return 2;
	lpvoid =::LockResource(hGlobal);
	if (lpvoid == NULL) return 2;
	m_hActDlg = ::CreateDialogIndirect(GetModuleHandle (NULL),(LPCDLGTEMPLATE)lpvoid,m_hwnd,(DLGPROC)DlgProc);
	if (m_hActDlg == NULL) return 2;
	::SetWindowPos(m_hActDlg,NULL,0,P1_1,WND_WIDTH,INF_HEIGHT,0);
	ShowWindow(m_hActDlg,SW_SHOW);
	UnlockResource(hGlobal);
	InitializeActDlg();
	
	InitializeCommDlg(m_hComm1Dlg);
	InitializeCommDlg(m_hComm2Dlg);
	m_Port1.GetConfiguration(&m_Comm1Config);
	m_Port2.GetConfiguration(&m_Comm2Config);
	ConfigCommDlg(m_hComm1Dlg,&m_Comm1Config);
	ConfigCommDlg(m_hComm2Dlg,&m_Comm2Config);
	::SetTimer(m_hwnd,0,1000,NULL);
	return 0;
}

DWORD CCommBridgeWind::Initialize()
{
	m_Port1.Initialize();
	m_Port2.Initialize();
	m_TrafficWind.Initialize();
	CLockEvent::Initialize();
	return 0;
}

DWORD CCommBridgeWind::Release()
{
	CloseFile();
	m_Port1.Release();
	m_Port2.Release();
	m_TrafficWind.Release();
	CLockEvent::Release();
	return 0;
}

LRESULT CCommBridgeWind::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	HWND hwnd;
	CSerialPort* serialport;
	switch (uMsg)
	{
	case WM_TIMER: OnTimer();break;
	case UM_REFRESH_TW:
		{
			if (m_OnShowLastRow)
				m_TrafficWind.ShowLastBuffer();
			m_TrafficWind.Invalidate();
			break;
		}
	case UM_REFRESH_LB:	 RefreshListBox();break;
	case UM_REFRESH_RB1: UpdateInputSignals(m_hComm1Dlg,&m_Port1);break;
	case UM_REFRESH_RB2: UpdateInputSignals(m_hComm2Dlg,&m_Port2);break;
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
	case WM_COMMAND:
		{
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			if (wmEvent != BN_CLICKED) break;
			switch (wmId)
			{
			case BTN_SETOUTFILE:	SetOutPutFile();break;
			case BTN_CLOSEFILE:		CloseFile();break;
			case BTN_CLEAR:			ClearListBox();break;
			case CHK_05:
			case CHK_06:
			case CHK_07:
			case CHK_08:
			case CHK_10:
			case CHK_0F:
			case CHK_12:
			case CHK_13:
			case CHK_14:
			case CHK_BUSY:			OnEnableCommand();

			}
			break;
		}
	case COMMAND_COMM1:
	case COMMAND_COMM2:
		{
			if (uMsg == COMMAND_COMM1) 
			{
				hwnd = m_hComm1Dlg;
				serialport = &m_Port1;
			}
			else
			{
				hwnd = m_hComm2Dlg;
				serialport = &m_Port2;
			}
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam);
			if (wmEvent != BN_CLICKED) break;
			switch (wmId)
			{
			case BTN_CONFIGURE:		ConfigurePort(hwnd,serialport);break;
			case IDC_CONNECT:		ConnectPort(hwnd,serialport);break;
			case IDC_DISCONNECT:	DisconnectPort(hwnd,serialport);break;
			case IDC_DTR:			ChangeDTR(hwnd,serialport);break;
			case IDC_RTS:			ChangeRTS(hwnd,serialport);break;
			case IDC_BREAK:			ChangeBreak(hwnd,serialport);break;
			}
			break;
		}
	default:
		return DefWindowProc(hWnd,uMsg,wParam,lParam);
	}
	return 0;
}

INT_PTR CCommBridgeWind::Comm1DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND hwnd = GetParent(hDlg);
	switch (message)
	{
		case WM_INITDIALOG:
			return TRUE;
		case WM_COMMAND:
			// Despachar el comando a la ventana padre
			::SendMessage(hwnd,COMMAND_COMM1,wParam,lParam);
			return TRUE;
	}
    return FALSE;
}

INT_PTR CCommBridgeWind::Comm2DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND hwnd = GetParent(hDlg);
	switch (message)
	{
		case WM_INITDIALOG:
			return TRUE;
		case WM_COMMAND:
			// Despachar el comando a la ventana padre
			::SendMessage(hwnd,COMMAND_COMM2,wParam,lParam);
			return TRUE;
	}
    return FALSE;
}

INT_PTR CCommBridgeWind::DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND hwnd = GetParent(hDlg);
	switch (message)
	{
		case WM_INITDIALOG:
			return TRUE;
		case WM_COMMAND:
			// Despachar el comando a la ventana padre
			HWND hwnd = GetParent(hDlg);
			::SendMessage(hwnd,message,wParam,lParam);
			return TRUE;
	}
    return FALSE;
}

DWORD CCommBridgeWind::InitializeCommDlg(HWND hDlg)
{
	// Actualizacion de los combobox
	HWND hcontrol = GetDlgItem(hDlg,IDC_PORT_CMB);
	BYTE i;
	for (i=0;i<MAXPORTS;i++)
	{
		::SendMessage(hcontrol,CB_ADDSTRING,0,(long)PORTS[i]);
	}
	// Byte size
	hcontrol = GetDlgItem(hDlg,IDC_CBS_CMB);
	for (i=0;i<MAXBYTESIZE;i++)
	{
		::SendMessage(hcontrol,CB_ADDSTRING,0,(long)BYTESIZE[i].str);
	}
	// Stop Bits
	hcontrol = GetDlgItem(hDlg,IDC_SB_CMB);
	for (i=0;i<MAXSTOPBITS;i++)
	{
		::SendMessage(hcontrol,CB_ADDSTRING,0,(long)STOPBITS[i].str);
	}
	// Parity
	hcontrol = GetDlgItem(hDlg,IDC_PAR_CMB);
	for (i=0;i<MAXPARITY;i++)
	{
		::SendMessage(hcontrol,CB_ADDSTRING,0,(long)PARITY[i].str);
	}
	// Baud Rate
	hcontrol = GetDlgItem(hDlg,IDC_BR_CMB);
	for (i=0;i<MAXBAUDRATE;i++)
	{
		::SendMessage(hcontrol,CB_ADDSTRING,0,(long)BAUDRATE[i].str);
	}
	// DTR
	hcontrol = GetDlgItem(hDlg,IDC_DTR_CMB);
	for (i=0;i<MAXDTROFC;i++)
	{
		::SendMessage(hcontrol,CB_ADDSTRING,0,(long)DTROFC[i].str);
	}
	// RTS
	hcontrol = GetDlgItem(hDlg,IDC_RTS_CMB);
	for (i=0;i<MAXRTSOFC;i++)
	{
		::SendMessage(hcontrol,CB_ADDSTRING,0,(long)RTSOFC[i].str);
	}
	// Actualizacion de los botones
	hcontrol = GetDlgItem(hDlg,IDC_CONNECT);
	::EnableWindow(hcontrol,true);
	hcontrol = GetDlgItem(hDlg,IDC_DISCONNECT);
	::EnableWindow(hcontrol,false);
	hcontrol = GetDlgItem(hDlg,BTN_CONFIGURE);
	::EnableWindow(hcontrol,false);
	return 0;
}

DWORD CCommBridgeWind::GetDlgConfig(HWND hDlg, PORT_CONFIG *lpPortConfig)
{
	LRESULT	result;
	HWND hcontrol;

	hcontrol = GetDlgItem(hDlg,IDC_PORT_CMB);
	result = ::SendMessage(hcontrol,CB_GETCURSEL,0,0);
	if (result == CB_ERR) return 1;
	lpPortConfig->Port = (BYTE)result+1;

	hcontrol = GetDlgItem(hDlg,IDC_BR_CMB);
	result = ::SendMessage(hcontrol,CB_GETCURSEL,0,0);
	if (result == CB_ERR) return 1;
	lpPortConfig->BaudRate = BAUDRATE[result].val;

	hcontrol = GetDlgItem(hDlg,IDC_PAR_CMB);
	result = ::SendMessage(hcontrol,CB_GETCURSEL,0,0);
	if (result == CB_ERR) return 1;
	lpPortConfig->Parity = (BYTE)PARITY[result].val;

	hcontrol = GetDlgItem(hDlg,IDC_SB_CMB);
	result = ::SendMessage(hcontrol,CB_GETCURSEL,0,0);
	if (result == CB_ERR) return 1;
	lpPortConfig->StopBits = (BYTE)STOPBITS[result].val;

	hcontrol = GetDlgItem(hDlg,IDC_CBS_CMB);
	result = ::SendMessage(hcontrol,CB_GETCURSEL,0,0);
	if (result == CB_ERR) return 1;
	lpPortConfig->ByteSize = (BYTE)BYTESIZE[result].val;

	hcontrol = GetDlgItem(hDlg,IDC_RTS_CMB);
	result = ::SendMessage(hcontrol,CB_GETCURSEL,0,0);
	if (result == CB_ERR) return 1;
	lpPortConfig->RTS = RTSOFC[result].val;

	hcontrol = GetDlgItem(hDlg,IDC_DTR_CMB);
	result = ::SendMessage(hcontrol,CB_GETCURSEL,0,0);
	if (result == CB_ERR) return 1;
	lpPortConfig->DTR = DTROFC[result].val;

	hcontrol = GetDlgItem(hDlg,IDC_PARITY);
	result = ::SendMessage(hcontrol,BM_GETCHECK,0,0);
	if (result & BST_CHECKED) 
		lpPortConfig->CheckParity = TRUE;
	else
		lpPortConfig->CheckParity = FALSE;

	hcontrol = GetDlgItem(hDlg,IDC_DSR_OFC);
	result = ::SendMessage(hcontrol,BM_GETCHECK,0,0);
	if (result & BST_CHECKED) 
		lpPortConfig->DSR = TRUE;
	else
		lpPortConfig->DSR = FALSE;

	hcontrol = GetDlgItem(hDlg,IDC_CTS_OFC);
	result = ::SendMessage(hcontrol,BM_GETCHECK,0,0);
	if (result & BST_CHECKED) 
		lpPortConfig->CTS = TRUE;
	else
		lpPortConfig->CTS = FALSE;

	return 0;
}

DWORD CCommBridgeWind::ConfigCommDlg(HWND hDlg, PORT_CONFIG* lpPortConfig)
{
	LRESULT	result;
	HWND hcontrol;
	DWORD i;

	hcontrol = GetDlgItem(hDlg,IDC_PORT_CMB);
	::SendMessage(hcontrol,CB_SETCURSEL,lpPortConfig->Port-1,0);
	
	// Buscar Baud Rate
	hcontrol = GetDlgItem(hDlg,IDC_BR_CMB);
	for (i=0;(i<MAXBAUDRATE) && (BAUDRATE[i].val != lpPortConfig->BaudRate);i++);
	::SendMessage(hcontrol,CB_SETCURSEL,i,0);

	// Byte size
	hcontrol = GetDlgItem(hDlg,IDC_CBS_CMB);
	for (i=0;(i<MAXBYTESIZE) && (BYTESIZE[i].val != lpPortConfig->ByteSize);i++);
	::SendMessage(hcontrol,CB_SETCURSEL,i,0);

	// Stop Bits
	hcontrol = GetDlgItem(hDlg,IDC_SB_CMB);
	for (i=0;(i<MAXSTOPBITS) && (STOPBITS[i].val != lpPortConfig->StopBits);i++);
	::SendMessage(hcontrol,CB_SETCURSEL,i,0);
	
	// Parity
	hcontrol = GetDlgItem(hDlg,IDC_PAR_CMB);
	for (i=0;(i<MAXPARITY) && (PARITY[i].val != lpPortConfig->Parity);i++);
	::SendMessage(hcontrol,CB_SETCURSEL,i,0);

	// DTR
	hcontrol = GetDlgItem(hDlg,IDC_DTR_CMB);
	for (i=0;(i<MAXDTROFC) && (DTROFC[i].val != lpPortConfig->DTR);i++);
	::SendMessage(hcontrol,CB_SETCURSEL,i,0);
	
	// RTS
	hcontrol = GetDlgItem(hDlg,IDC_RTS_CMB);
	for (i=0;(i<MAXRTSOFC) && (RTSOFC[i].val != lpPortConfig->RTS);i++);
	::SendMessage(hcontrol,CB_SETCURSEL,i,0);

	// Check Parity
	hcontrol = GetDlgItem(hDlg,IDC_PARITY);
	::SendMessage(hcontrol,BM_SETCHECK,(lpPortConfig->CheckParity) ? (BST_CHECKED):(BST_UNCHECKED),0);

	// DSR Input sensibility	
	hcontrol = GetDlgItem(hDlg,IDC_DSR_OFC);
	result = ::SendMessage(hcontrol,BM_SETCHECK,(lpPortConfig->DSR) ? (BST_CHECKED):(BST_UNCHECKED),0);

	// CTS output flow control
	hcontrol = GetDlgItem(hDlg,IDC_CTS_OFC);
	result = ::SendMessage(hcontrol,BM_SETCHECK,(lpPortConfig->CTS) ? (BST_CHECKED):(BST_UNCHECKED),0);
	return 0;
}

// Interfaz ICommunicationEvents
DWORD _stdcall CCommBridgeWind::OnReceivedData(BYTE* Buffer,DWORD cant,LPVOID lpParam)
{
	if (cant == 0) return 0;
	DWORD result = 0;
	COMM_BUFFER* buffer;
	if (Lock() != 0)
	{
		m_TrafficWind.AddComment("Lock failed in Read Bytes");
		return 1;
	}
	for (;;)
	{
		if (lpParam == (void*)1) buffer = &m_Port2Buffer;
		else
			buffer = &m_Port1Buffer;

		// Adicionar datos al buffer
		if (buffer->WriteIndex + cant > COMM_BUFFER_SIZE)
		{
			m_TrafficWind.AddComment("WriteIndex + cant > BUFFER_SIZE in Received Data");
			result = 1;
			break;
		}
		memmove(&buffer->Buffer[buffer->WriteIndex],Buffer,cant);
		buffer->WriteIndex += cant;
		if (!buffer->OnWriting) ((CSerialPort*)buffer->lpParam)->SetTrigger();
		break;
	}
	if (UnLock() != 0)
	{
		m_TrafficWind.AddComment("UnLock failed in Send Bytes");
		return result;
	}
	return result;
}
DWORD _stdcall CCommBridgeWind::OnCommEvent(DWORD pEventMask,LPVOID lpParam)
{
	if (lpParam == (void*)1)
		PostMessage(m_hwnd,UM_REFRESH_RB1,0,0);
	else
		PostMessage(m_hwnd,UM_REFRESH_RB2,0,0);
	char* str1[100];
	str1[0]=0;
	char* str = (char*)str1;
	COMM_BUFFER* buffer;
	DWORD error;

	if (lpParam == (void*)1) buffer = &m_Port2Buffer;
		else
			buffer = &m_Port1Buffer;
	/*
	if (pEventMask & EV_BREAK)
		m_TrafficWind.AddComment("Line Break Detected");
		*/
	if (pEventMask & EV_ERR)
	{
		strcpy(str,"Errors Detected");
		((CSerialPort*)buffer->lpParam)->GetCommError(&error);
		if (error & CE_FRAME)
			strcat(str," (Framing Error)");
		if (error & CE_OVERRUN)
			strcat(str," (Character-buffer overrun)");
		if (error & CE_RXPARITY)
			strcat(str," (Parity error)");
		if (error & CE_BREAK)
			strcat(str," (Line Break)");
		if (error & CE_RXOVER)
			strcat(str," (Input buffer overflow)");
		if (error & CE_TXFULL)
			strcat(str," (Output buffer full)");
		m_TrafficWind.AddComment(str);
	}
	return 0;
}
DWORD _stdcall CCommBridgeWind::OnSendBytes(BYTE* Buffer,DWORD BytesWritten,LPVOID lpParam)
{
	DWORD	result = 0;
	COMM_BUFFER* buffer;
	BYTE*	SndBuffer;
	DWORD	Size;
	DWORD	SendCant;	//Cantidad que debian enviarse
	if (Lock() != 0)
	{
		m_TrafficWind.AddComment("Lock failed in Send Bytes");
		return 0;
	}
	for (;;)
	{
		if (lpParam == (void*)1) 
		{
			// bytes que envia el 1 son bytes que llegan por el 2
			ProcessReadBuffer(Buffer,BytesWritten);
			buffer = &m_Port1Buffer;
		}
		else
		{
			// bytes que envia el 2 son bytes que llegaron por el 1
			ProcessSendBuffer(Buffer,BytesWritten);
			buffer = &m_Port2Buffer;
		}
		if (buffer->WriteIndex < buffer->ReadIndex)
		{
			m_TrafficWind.AddComment("Read pointer > Write Pointer in SendBytes");
			result = 1;
			buffer = NULL;
			break;
		}
		// Recoger bytes
		// Contar bytes enviados
		SendCant = ((CSerialPort*)buffer->lpParam)->GetCantBytesToSend();
		((CSerialPort*)buffer->lpParam)->GetWriteBuffer(&SndBuffer,&Size);

		if (( SendCant > BytesWritten) && (Buffer != NULL))
		{
			// Enviar los que no se fueron
			memmove(SndBuffer,&SndBuffer[BytesWritten],SendCant-BytesWritten);
			Size = SendCant-BytesWritten;
		}
		else
		{
			// Revisar si quedan bytes por enviar
			if (buffer->ReadIndex != buffer->WriteIndex)
			{
				Size = buffer->WriteIndex-buffer->ReadIndex;
				memmove(SndBuffer,&buffer->Buffer[buffer->ReadIndex],Size);
				buffer->ReadIndex=0;
				buffer->WriteIndex=0;
				buffer->OnWriting = TRUE;
			}
			else
			{	
				// Ya todos los bytes fueron enviados
				buffer->ReadIndex = 0;
				buffer->WriteIndex = 0;
				buffer->OnWriting = FALSE;
				buffer = NULL;
			}
		}
		break;
	}
	if (UnLock() != 0)
	{
		m_TrafficWind.AddComment("UnLock failed in Send Bytes");
		return 0;
	}
	// No se puede enviar dentro del bloqueo
	if (buffer) ((CSerialPort*)buffer->lpParam)->Send(Size);
	return 0;
}
DWORD _stdcall CCommBridgeWind::OnProcessMessage(LP_MESSAGE lpMessage,LPVOID lpParam)
{
	return 0;
}
DWORD _stdcall CCommBridgeWind::OnWaitTimeOut(LPVOID lpParam)
{
	return 0;
}

DWORD _stdcall CCommBridgeWind::OnTrigger(LPVOID lpParam)
{
	return OnSendBytes(NULL,0,lpParam);
}

DWORD CCommBridgeWind::ConfigurePort(HWND hDlg, CSerialPort *lpSerialPort)
{
	PORT_CONFIG portconfig;
	GetDlgConfig(hDlg,&portconfig);
	lpSerialPort->SetConfiguration(&portconfig);
	return 0;
}

DWORD CCommBridgeWind::ConnectPort(HWND hDlg, CSerialPort *lpSerialPort)
{
	DWORD result;
	HWND hcontrol;
	PORT_CONFIG portconfig;
	GetDlgConfig(hDlg,&portconfig);
	lpSerialPort->SetConfiguration(&portconfig);
	result = lpSerialPort->OpenPort();
	if (result !=0) 
	{
		::MessageBox(m_hwnd,"Error Opening Port","CommPort",MB_OK|MB_ICONERROR);
		return 0;
	}
	hcontrol = GetDlgItem(hDlg,IDC_CONNECT);
	::EnableWindow(hcontrol,false);
	hcontrol = GetDlgItem(hDlg,IDC_DISCONNECT);
	::EnableWindow(hcontrol,true);
	hcontrol = GetDlgItem(hDlg,BTN_CONFIGURE);
	::EnableWindow(hcontrol,true);
	UpdateInputSignals(hDlg,lpSerialPort);
	return 0;
}

DWORD CCommBridgeWind::DisconnectPort(HWND hDlg, CSerialPort *lpSerialPort)
{
	DWORD result;
	HWND	hcontrol;
	result = lpSerialPort->ClosePort();
	if (result !=0) ::MessageBox(m_hwnd,"Error Closing Port","Serial Port",MB_OK|MB_ICONERROR);
	hcontrol = GetDlgItem(hDlg,IDC_CONNECT);
	::EnableWindow(hcontrol,true);
	hcontrol = GetDlgItem(hDlg,IDC_DISCONNECT);
	::EnableWindow(hcontrol,false);
	hcontrol = GetDlgItem(hDlg,BTN_CONFIGURE);
	::EnableWindow(hcontrol,false);
	return result;
}

DWORD CCommBridgeWind::UpdateInputSignals(HWND hDlg, CSerialPort *lpSerialPort)
{
	DWORD Signals;
	HWND hcontrol;
	lpSerialPort->GetSignals(&Signals);
	// DSR
	hcontrol = GetDlgItem(hDlg,IDC_DSR);
	if (Signals & MS_DSR_ON)
		SendMessage(hcontrol,BM_SETCHECK,BST_CHECKED,0);
	else
		SendMessage(hcontrol,BM_SETCHECK,BST_UNCHECKED,0);
	// CTS
	hcontrol = GetDlgItem(hDlg,IDC_CTS);
	if (Signals & MS_CTS_ON)
		SendMessage(hcontrol,BM_SETCHECK,BST_CHECKED,0);
	else
		SendMessage(hcontrol,BM_SETCHECK,BST_UNCHECKED,0);
	// RING
	hcontrol = GetDlgItem(hDlg,IDC_RING);
	if (Signals & MS_RING_ON)
		SendMessage(hcontrol,BM_SETCHECK,BST_CHECKED,0);
	else
		SendMessage(hcontrol,BM_SETCHECK,BST_UNCHECKED,0);
	// RLSD
	hcontrol = GetDlgItem(hDlg,IDC_RLSD);
	if (Signals & MS_RLSD_ON)
		SendMessage(hcontrol,BM_SETCHECK,BST_CHECKED,0);
	else
		SendMessage(hcontrol,BM_SETCHECK,BST_UNCHECKED,0);
	return 0;
}

DWORD CCommBridgeWind::ProcessReadBuffer(BYTE *buffer, DWORD dwsize)
{
	if (dwsize == 0) return 0;
	m_ReadCant+=dwsize;

	// Enviar al listbox los bytes
	DWORD* lpdw;
	m_Buff[m_BuffPos] = RCV;
	lpdw = (DWORD*)&m_Buff[m_BuffPos+1];
	*lpdw=dwsize;
	m_BuffPos+=sizeof(DWORD)+1;
	memcpy(&m_Buff[m_BuffPos],buffer,dwsize);
	m_BuffPos+=dwsize;
	m_Buff[m_BuffPos] = END;
	PostMessage(m_hwnd,UM_REFRESH_LB,0,0);
	/*
	if (m_OnShowTraffic)
	{
		m_TrafficWind.AddReadBuffer(buffer,dwsize);
		PostMessage(m_hwnd,UM_REFRESH_TW,0,0);
	}
	*/
	WriteToFile(buffer,dwsize,RCV_BUF);
	return 0;
}

DWORD CCommBridgeWind::ProcessSendBuffer(BYTE *buffer, DWORD dwsize)
{
	if (dwsize == 0) return 0;
	m_SendCant+=dwsize;
	
	// Enviar al listbox los bytes
	DWORD* lpdw;
	m_Buff[m_BuffPos] = SND;
	lpdw = (DWORD*)&m_Buff[m_BuffPos+1];
	*lpdw=dwsize;
	m_BuffPos+=sizeof(DWORD)+1;
	memcpy(&m_Buff[m_BuffPos],buffer,dwsize);
	m_BuffPos+=dwsize;
	m_Buff[m_BuffPos] = END;
	PostMessage(m_hwnd,UM_REFRESH_LB,0,0);
	/*
	if (m_OnShowTraffic)
	{
		m_TrafficWind.AddSendBuffer(buffer,dwsize);
		PostMessage(m_hwnd,UM_REFRESH_TW,0,0);
	}
	*/
	WriteToFile(buffer,dwsize,SND_BUF);
	return 0;
}

DWORD CCommBridgeWind::ChangeDTR(HWND hDlg, CSerialPort *lpSerialPort)
{
	HWND	hcontrol;
	hcontrol = GetDlgItem(hDlg,IDC_DTR);
	LRESULT result = ::SendMessage(hcontrol,BM_GETCHECK,0,0);
	if (result & BST_CHECKED) lpSerialPort->SetDTR();
	else
		lpSerialPort->ClearDTR();
	return 0;
}

DWORD CCommBridgeWind::ChangeRTS(HWND hDlg, CSerialPort *lpSerialPort)
{
	HWND	hcontrol;
	hcontrol = GetDlgItem(hDlg,IDC_RTS);
	LRESULT result = ::SendMessage(hcontrol,BM_GETCHECK,0,0);
	if (result & BST_CHECKED) lpSerialPort->SetRTS();
	else
		lpSerialPort->ClearRTS();
	return 0;

}

DWORD CCommBridgeWind::ChangeBreak(HWND hDlg, CSerialPort *lpSerialPort)
{
	HWND	hcontrol;
	hcontrol = GetDlgItem(hDlg,IDC_BREAK);
	LRESULT result = ::SendMessage(hcontrol,BM_GETCHECK,0,0);
	if (result & BST_CHECKED) lpSerialPort->SetBreak();
	else
		lpSerialPort->ClearBreak();
	return 0;
}

DWORD CCommBridgeWind::SetOutPutFile()
{
	HWND hcontrol;
	char*	Filter = "Text files (*.TXT)\0*.txt\0All files (*.*)\0*.*\0\0";
	char	filename[300];
	if (!m_hFile)
	{
		// No crear el fichero si ya lo esta pero hay que actualizar los botones
		filename[0]=0;
		OPENFILENAME ofn;
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.Flags = OFN_CREATEPROMPT|OFN_HIDEREADONLY|OFN_NONETWORKBUTTON|
					OFN_OVERWRITEPROMPT;
		ofn.hInstance = NULL;
		ofn.lCustData = NULL;
		ofn.lpfnHook = NULL;
		ofn.lpstrCustomFilter = NULL;
		ofn.lpstrDefExt = NULL;
		ofn.lpstrFile = filename;
		ofn.lpstrFileTitle = NULL;
		ofn.lpstrFilter = (char*)Filter;
		ofn.lpstrInitialDir = NULL;
		ofn.lpstrTitle = "Select file to save traffic";
		ofn.lpTemplateName = NULL;
		ofn.nFileExtension = NULL;
		ofn.nFileOffset = NULL;
		ofn.nFilterIndex = 1;
		ofn.nMaxCustFilter = 0;
		ofn.nMaxFile = 299;
		ofn.nMaxFileTitle = 10;
		if (!GetSaveFileName(&ofn)) return 0;
		m_hFile = CreateFile(ofn.lpstrFile,GENERIC_WRITE,FILE_SHARE_READ,NULL,
			CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
		if (m_hFile == INVALID_HANDLE_VALUE)
			return 1;
	}
	m_FileSize = 0;
	hcontrol = GetDlgItem(m_hActDlg,BTN_CLOSEFILE);
	::EnableWindow(hcontrol,true);
	hcontrol = GetDlgItem(m_hActDlg,BTN_SETOUTFILE);
	::EnableWindow(hcontrol,false);
	return 0;
}

DWORD CCommBridgeWind::CloseFile()
{
	Lock();
	HWND hcontrol;
	CloseHandle(m_hFile);
	m_hFile = NULL;
	UnLock();
	hcontrol = GetDlgItem(m_hActDlg,BTN_CLOSEFILE);
	::EnableWindow(hcontrol,false);
	hcontrol = GetDlgItem(m_hActDlg,BTN_SETOUTFILE);
	::EnableWindow(hcontrol,true);
	return 0;
}

DWORD CCommBridgeWind::WriteToFile(BYTE *buffer, DWORD dwcant, BYTE type)
{
	char str[100];
	DWORD i,j;
	BYTE val;
	DWORD	byteswritten;
	memset(str,' ',SP0+SP1+(2+SP2)*16+SP3+16);
	if (m_hFile)
	{
		if (type == SND_BUF)
			memcpy(str,"Snd ",4);
		else
			memcpy(str,"Rcv ",4);
		j = 0;
		for (i=0;i<dwcant;i++)
		{
			val = buffer[i];
			str[SP0+SP1+(2+SP2)*j] = (val >> 4) + '0';
			str[SP0+SP1+(2+SP2)*j+1] = (val & 0x0F) + '0';
			if (str[SP0+SP1+(2+SP2)*j] > '9') str[SP0+SP1+(2+SP2)*j] += 7;
			if (str[SP0+SP1+(2+SP2)*j+1] > '9') str[SP0+SP1+(2+SP2)*j+1] += 7;
			if (val < 32) 
				str[SP0+SP1+(2+SP2)*16+SP3+j] = '.';
			else
				str[SP0+SP1+(2+SP2)*16+SP3+j] = val;
			j++;
			if ((j==16) || (i==dwcant-1))
			{
				memcpy(&str[SP0+SP1+(2+SP2)*16+SP3+j],"\x0d\x0a",2);
				WriteFile(m_hFile,str,SP0+SP1+(2+SP2)*16+SP3+j+2,&byteswritten,NULL);
				m_FileSize += byteswritten;
				j = 0;
				memset(str,' ',SP0+SP1+(2+SP2)*16+SP3+16);
			}

		}
	}
	return 0;
}

DWORD CCommBridgeWind::InitializeActDlg()
{
	HWND hcontrol;
	hcontrol = GetDlgItem(m_hActDlg,BTN_CLOSEFILE);
	::EnableWindow(hcontrol,false);
	hcontrol = GetDlgItem(m_hActDlg,BTN_SETOUTFILE);
	::EnableWindow(hcontrol,true);
	return 0;
}

DWORD CCommBridgeWind::RefreshListBox()
{
	MSG msg;
	BYTE* Buffer;
	DWORD Pos,i,result;
	DWORD SPos,EPos;	// Posicion de inicio y fin
	DWORD Size;
	BOOL  OnRcv;
	DWORD* lpdw;
	LRESULT Index;
	while (::PeekMessage(&msg,m_hwnd,UM_REFRESH_LB,UM_REFRESH_LB,PM_REMOVE));
	Buffer = m_Buff;
	Pos = 0;
	Lock();
	// Conmutar Buffer
	if (m_Buff == m_Buff1)
		m_Buff = m_Buff2;
	else
		m_Buff = m_Buff1;
	m_BuffPos = 0;
	UnLock();
	// Procesar el buffer
	for (;;)
	{
		if (Buffer[Pos] == END) break;
		if (Buffer[Pos] == RCV) 
			OnRcv = true;
		else
			OnRcv = false;
		Pos++;
		lpdw = (DWORD*)&Buffer[Pos];
		Size = *lpdw;
		Pos+= sizeof(DWORD);
		for (i=0;i<Size;i++,Pos++)
		{
			if (OnRcv) 
				result = Filter.ProcessRcvByte(Buffer[Pos]);
			else
				result = Filter.ProcessSndByte(Buffer[Pos]);
			if (result == 2)
			{
				HWND hControl = GetDlgItem(m_hActDlg,LB_TRAFFIC);
				for (SPos = 0,EPos=0;;EPos++)
				{
					if (Filter.m_OutStr[EPos] == 0) break;
					if (Filter.m_OutStr[EPos] == 0x0d)
					{
						Filter.m_OutStr[EPos] = 0;
						::SendMessage(hControl,LB_ADDSTRING,0,(long)&Filter.m_OutStr[SPos]);
						Index =::SendMessage(hControl,LB_GETCOUNT,0,0);
						::SendMessage(hControl,LB_SETCURSEL,Index-1,0);
						EPos++;
						SPos = EPos+1;
					}
				}
			}
		}
		
	}
		
	return 0;
}

DWORD CCommBridgeWind::OnEnableCommand()
{
	HWND	hcontrol;
	LRESULT result;
	hcontrol = GetDlgItem(m_hActDlg,CHK_05);
	result = ::SendMessage(hcontrol,BM_GETCHECK,0,0);
	Filter.EnableCommand(0x05,result & BST_CHECKED);

	hcontrol = GetDlgItem(m_hActDlg,CHK_06);
	result = ::SendMessage(hcontrol,BM_GETCHECK,0,0);
	Filter.EnableCommand(0x06,result & BST_CHECKED);

	hcontrol = GetDlgItem(m_hActDlg,CHK_07);
	result = ::SendMessage(hcontrol,BM_GETCHECK,0,0);
	Filter.EnableCommand(0x07,result & BST_CHECKED);

	hcontrol = GetDlgItem(m_hActDlg,CHK_08);
	result = ::SendMessage(hcontrol,BM_GETCHECK,0,0);
	Filter.EnableCommand(0x08,result & BST_CHECKED);

	hcontrol = GetDlgItem(m_hActDlg,CHK_10);
	result = ::SendMessage(hcontrol,BM_GETCHECK,0,0);
	Filter.EnableCommand(0x10,result & BST_CHECKED);

	hcontrol = GetDlgItem(m_hActDlg,CHK_0F);
	result = ::SendMessage(hcontrol,BM_GETCHECK,0,0);
	Filter.EnableCommand(0x0F,result & BST_CHECKED);

	hcontrol = GetDlgItem(m_hActDlg,CHK_12);
	result = ::SendMessage(hcontrol,BM_GETCHECK,0,0);
	Filter.EnableCommand(0x12,result & BST_CHECKED);

	hcontrol = GetDlgItem(m_hActDlg,CHK_13);
	result = ::SendMessage(hcontrol,BM_GETCHECK,0,0);
	Filter.EnableCommand(0x13,result & BST_CHECKED);

	hcontrol = GetDlgItem(m_hActDlg,CHK_14);
	result = ::SendMessage(hcontrol,BM_GETCHECK,0,0);
	Filter.EnableCommand(0x14,result & BST_CHECKED);

	hcontrol = GetDlgItem(m_hActDlg,CHK_BUSY);
	result = ::SendMessage(hcontrol,BM_GETCHECK,0,0);
	Filter.EnableCommand(0x0,result & BST_CHECKED);

	return 0;
}

DWORD CCommBridgeWind::ClearListBox()
{
	HWND hControl = GetDlgItem(m_hActDlg,LB_TRAFFIC);
	::SendMessage(hControl,LB_RESETCONTENT,0,0);
	return 0;
}

DWORD CCommBridgeWind::OnTimer()
{
	HWND hControl = GetDlgItem(m_hActDlg,LB_RESULT);
	Filter.FillListBox(hControl);
	return 0;
}
