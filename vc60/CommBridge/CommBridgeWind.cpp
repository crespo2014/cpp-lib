// CommBridgeWind.cpp: implementation of the CCommBridgeWind class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CommBridgeWind.h"
#include "resource.h"
#include "common.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CCommBridgeWind::CCommBridgeWind()
{
	SetICommunicationBridgeEvents(this);
	/*
	GetReceivedSerialPort(&m_RcvPort);
	GetSendSerialPort(&m_SndPort);
	*/

	m_hComm1Dlg = NULL;
	m_hComm2Dlg = NULL;
	m_hActDlg	= NULL;

	m_OnShowLastRow = FALSE;
	m_OnShowTraffic = TRUE;

	m_FileSize = 0;
	m_hFile = NULL;
	m_ReadCant = 0;
	m_SendCant = 0;
	m_hFile = NULL;
}

CCommBridgeWind::~CCommBridgeWind()
{

}

DWORD CCommBridgeWind::Create_Window()
{
#define PROP_HEIGHT 120	//Ventana de propiedades del puerto
#define TRAF_HEIGHT 100 //Ventana de trafico
#define MNU_HEIGHT	45	//Menu y caption 
#define INF_HEIGHT	75  // Informacion 
#define WND_WIDTH	695
#define P0 0
#define P1 PROP_HEIGHT
#define P1_1 (P1+TRAF_HEIGHT)
#define P2 (P1_1+INF_HEIGHT)
#define P3 (P2+PROP_HEIGHT)
#define P4 (P3+MNU_HEIGHT)

	DWORD result;
	HWND hcontrol;
	HMENU hmenu=LoadMenu(NULL,"COMMBRIDGE_MENU1");
	HICON hicon = LoadIcon(GetModuleHandle (NULL),"COMMBRIDGE_ICON1");
	result = Create("Serial Port Bridge",WS_CAPTION|WS_BORDER|WS_VISIBLE|WS_MINIMIZEBOX|WS_SYSMENU,40,40,WND_WIDTH+6,P4,NULL,hmenu,NULL);
	if (result != 0)
		return 1;
	SendMessage(*this,WM_SETICON,ICON_BIG,(long)hicon);
	// Crear ventanas internas
	m_TrafficWind.Create_Window(1,P1,WND_WIDTH-1,TRAF_HEIGHT,*this);
	// Crear ventanas de dialogo
	HRSRC hrscr = ::FindResource(GetModuleHandle(NULL),"COM_PROPERTIES",RT_DIALOG);
	if (hrscr == NULL) return 2;
	HGLOBAL hGlobal =::LoadResource(GetModuleHandle(NULL),hrscr);
	if (hGlobal == NULL) return 2;
	LPVOID lpvoid =::LockResource(hGlobal);
	if (lpvoid == NULL) return 2;
	m_hComm1Dlg = ::CreateDialogIndirect(GetModuleHandle (NULL),(LPCDLGTEMPLATE)lpvoid,*this,(DLGPROC)Comm1DlgProc);
	if (m_hComm1Dlg == NULL) return 2;
	::SetWindowPos(m_hComm1Dlg,NULL,P0,0,WND_WIDTH,PROP_HEIGHT,0);
	ShowWindow(m_hComm1Dlg,SW_SHOW);
	// Segundo dialogo
	m_hComm2Dlg = ::CreateDialogIndirect(GetModuleHandle (NULL),(LPCDLGTEMPLATE)lpvoid,*this,(DLGPROC)Comm2DlgProc);
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
	m_hActDlg = ::CreateDialogIndirect(GetModuleHandle (NULL),(LPCDLGTEMPLATE)lpvoid,*this,(DLGPROC)DlgProc);
	if (m_hActDlg == NULL) return 2;
	::SetWindowPos(m_hActDlg,NULL,0,P1_1,WND_WIDTH,INF_HEIGHT,0);
	ShowWindow(m_hActDlg,SW_SHOW);
	UnlockResource(hGlobal);
	InitializeActDlg();
	UpdateActDlg();
	
	// Inicializar edit de comentario
	hcontrol = GetDlgItem(m_hActDlg,ED_COMMENT);
	::SendMessage(hcontrol,EM_LIMITTEXT,255,0);

	InitializeCommDlg(m_hComm1Dlg);
	InitializeCommDlg(m_hComm2Dlg);
	CSerialPortBridge::GetPortConfiguration(true,&m_Comm1Config);
	CSerialPortBridge::GetPortConfiguration(false,&m_Comm2Config);
	ConfigCommDlg(m_hComm1Dlg,&m_Comm1Config);
	ConfigCommDlg(m_hComm2Dlg,&m_Comm2Config);
	::SetTimer(*this,0,500,NULL);
	return 0;
}

DWORD CCommBridgeWind::Initialize()
{
	DWORD dr;
	for (;;)
	{
		dr = CSerialPortBridge::Initialize();
		if (dr != 0) break;
		dr = m_TrafficWind.Initialize();
		if (dr != 0) break;
		break;
	}
	return dr;
}

DWORD _stdcall CCommBridgeWind::Release()
{
	CSerialPortBridge::UnInitialize();
	m_TrafficWind.Release();
	CloseFile();
	return 0;
}

LRESULT _stdcall CCommBridgeWind::OnWindProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	HWND hwnd;
	ISerialPort* serialport;
	switch (uMsg)
	{
	case UM_REFRESH_TW:
		{
			if (m_OnShowLastRow)
				m_TrafficWind.ShowLastBuffer();
			m_TrafficWind.Invalidate();
			break;
		}
	case UM_REFRESH_RB1: 
		{
			DWORD Signals;
			CSerialPortBridge::GetPortSignals(true,&Signals);
			UpdateInputSignals(m_hComm1Dlg,Signals);
			break;
		}
	case UM_REFRESH_RB2: 
		{
			DWORD Signals;
			CSerialPortBridge::GetPortSignals(false,&Signals);
			UpdateInputSignals(m_hComm2Dlg,Signals);
			break;
		}
	case WM_TIMER:		 UpdateActDlg();break;
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
			case BTN_ADD_CMT:		AddComment();break;
			case BTN_CLR_ALL:		ClearAll();break;
			case BTN_SETOUTFILE:	SetOutPutFile();break;
			case BTN_CLOSEFILE:		CloseFile();break;
			case CHK_SLR:			OnShowLastRow();break;
			case CHK_SHOWTRAFFIC:	OnShowTraffic();break;
			}
			break;
		}
	case COMMAND_COMM1:
	case COMMAND_COMM2:
		{
			if (uMsg == COMMAND_COMM1) 
			{
				hwnd = m_hComm1Dlg;
				CSerialPortBridge::GetSerialPort(true,&serialport);
			}
			else
			{
				hwnd = m_hComm2Dlg;
				CSerialPortBridge::GetSerialPort(false,&serialport);
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
	lpPortConfig->lParam = (void*)(result+1);

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
	lpPortConfig->RTSMode = RTSOFC[result].val;

	hcontrol = GetDlgItem(hDlg,IDC_DTR_CMB);
	result = ::SendMessage(hcontrol,CB_GETCURSEL,0,0);
	if (result == CB_ERR) return 1;
	lpPortConfig->DTRMode = DTROFC[result].val;

	hcontrol = GetDlgItem(hDlg,IDC_PARITY);
	result = ::SendMessage(hcontrol,BM_GETCHECK,0,0);
	if (result & BST_CHECKED) 
		lpPortConfig->CheckParity = TRUE;
	else
		lpPortConfig->CheckParity = FALSE;

	hcontrol = GetDlgItem(hDlg,IDC_DSR_OFC);
	result = ::SendMessage(hcontrol,BM_GETCHECK,0,0);
	if (result & BST_CHECKED) 
		lpPortConfig->DSRStopOutFlow = TRUE;
	else
		lpPortConfig->DSRStopOutFlow = FALSE;

	hcontrol = GetDlgItem(hDlg,IDC_CTS_OFC);
	result = ::SendMessage(hcontrol,BM_GETCHECK,0,0);
	if (result & BST_CHECKED) 
		lpPortConfig->CTSStopOutFlow = TRUE;
	else
		lpPortConfig->CTSStopOutFlow = FALSE;

	return 0;
}

DWORD CCommBridgeWind::ConfigCommDlg(HWND hDlg, PORT_CONFIG* lpPortConfig)
{
	LRESULT	result;
	HWND hcontrol;
	DWORD i;

	hcontrol = GetDlgItem(hDlg,IDC_PORT_CMB);
	::SendMessage(hcontrol,CB_SETCURSEL,((int)lpPortConfig->lParam)-1,0);
	
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
	for (i=0;(i<MAXDTROFC) && (DTROFC[i].val != lpPortConfig->DTRMode);i++);
	::SendMessage(hcontrol,CB_SETCURSEL,i,0);
	
	// RTS
	hcontrol = GetDlgItem(hDlg,IDC_RTS_CMB);
	for (i=0;(i<MAXRTSOFC) && (RTSOFC[i].val != lpPortConfig->RTSMode);i++);
	::SendMessage(hcontrol,CB_SETCURSEL,i,0);

	// Check Parity
	hcontrol = GetDlgItem(hDlg,IDC_PARITY);
	::SendMessage(hcontrol,BM_SETCHECK,(lpPortConfig->CheckParity) ? (BST_CHECKED):(BST_UNCHECKED),0);

	// DSR Input sensibility	
	hcontrol = GetDlgItem(hDlg,IDC_DSR_OFC);
	result = ::SendMessage(hcontrol,BM_SETCHECK,(lpPortConfig->DSRStopOutFlow) ? (BST_CHECKED):(BST_UNCHECKED),0);

	// CTS output flow control
	hcontrol = GetDlgItem(hDlg,IDC_CTS_OFC);
	result = ::SendMessage(hcontrol,BM_SETCHECK,(lpPortConfig->CTSStopOutFlow) ? (BST_CHECKED):(BST_UNCHECKED),0);
	return 0;
}

DWORD CCommBridgeWind::ConfigurePort(HWND hDlg, ISerialPort *lpSerialPort)
{
	PORT_CONFIG portconfig;
	GetDlgConfig(hDlg,&portconfig);
	lpSerialPort->SetPortConfiguration(&portconfig);
	return 0;
}

DWORD CCommBridgeWind::ConnectPort(HWND hDlg, ISerialPort *lpSerialPort)
{
	DWORD	result;
	HWND	hcontrol;
	hcontrol = GetDlgItem(hDlg,IDC_PORT_CMB);
	result = ::SendMessage(hcontrol,CB_GETCURSEL,0,0);
	if (result == CB_ERR) return 1;
	lpSerialPort->SetPort(result+1);
	result = lpSerialPort->OpenPort();
	if (result !=0) 
	{
		::MessageBox(*this,"Error Opening Port","CommPort",MB_OK|MB_ICONERROR);
		return 0;
	}
	return 0;
}

DWORD CCommBridgeWind::DisconnectPort(HWND hDlg, ISerialPort *lpSerialPort)
{
	DWORD result;
	HWND	hcontrol;
	result = lpSerialPort->ClosePort();
	if (result !=0) ::MessageBox(*this,"Error Closing Port","Serial Port",MB_OK|MB_ICONERROR);
	hcontrol = GetDlgItem(hDlg,IDC_CONNECT);
	::EnableWindow(hcontrol,true);
	hcontrol = GetDlgItem(hDlg,IDC_DISCONNECT);
	::EnableWindow(hcontrol,false);
	hcontrol = GetDlgItem(hDlg,BTN_CONFIGURE);
	::EnableWindow(hcontrol,false);
	return result;
}

DWORD CCommBridgeWind::UpdateInputSignals(HWND hDlg, DWORD Signals)
{
	HWND hcontrol;
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

DWORD CCommBridgeWind::AddComment()
{
	DWORD	byteswritten;
	char cmt[400];
	HWND hcontrol = GetDlgItem(m_hActDlg,ED_COMMENT);
	GetWindowText(hcontrol,cmt,256);
	if (cmt[0]== 0) return 0;
	m_TrafficWind.AddComment(cmt);
	m_TrafficWind.Invalidate();
	if (m_hFile) 
	{
		memmove(&cmt[4],&cmt[0],400-4);
		memcpy(cmt,"Cmt ",4);
		strcat(cmt,"\x0d\x0a");
		WriteFile(m_hFile,cmt,strlen(cmt),&byteswritten,NULL);
	}
	return 0;
}

DWORD CCommBridgeWind::ClearAll()
{
	m_TrafficWind.Clear();
	m_TrafficWind.Invalidate();
	return 0;
}

DWORD CCommBridgeWind::ChangeDTR(HWND hDlg, ISerialPort *lpSerialPort)
{
	HWND	hcontrol;
	hcontrol = GetDlgItem(hDlg,IDC_DTR);
	LRESULT result = ::SendMessage(hcontrol,BM_GETCHECK,0,0);
	if (result & BST_CHECKED) lpSerialPort->ChangeOutputSignal(SETDTR);
	else
		lpSerialPort->ChangeOutputSignal(CLRDTR);
	return 0;
}

DWORD CCommBridgeWind::ChangeRTS(HWND hDlg, ISerialPort *lpSerialPort)
{
	HWND	hcontrol;
	hcontrol = GetDlgItem(hDlg,IDC_RTS);
	LRESULT result = ::SendMessage(hcontrol,BM_GETCHECK,0,0);
	if (result & BST_CHECKED) lpSerialPort->ChangeOutputSignal(SETRTS);
	else
		lpSerialPort->ChangeOutputSignal(CLRRTS);
	return 0;

}

DWORD CCommBridgeWind::ChangeBreak(HWND hDlg, ISerialPort *lpSerialPort)
{
	HWND	hcontrol;
	hcontrol = GetDlgItem(hDlg,IDC_BREAK);
	LRESULT result = ::SendMessage(hcontrol,BM_GETCHECK,0,0);
	if (result & BST_CHECKED) lpSerialPort->ChangeOutputSignal(SETBREAK);
	else
		lpSerialPort->ChangeOutputSignal(CLRBREAK);
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
//	Lock();
	HWND hcontrol;
	CloseHandle(m_hFile);
	m_hFile = NULL;
//	UnLock();
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

DWORD CCommBridgeWind::OnShowLastRow()
{
	HWND	hcontrol;
	hcontrol = GetDlgItem(m_hActDlg,CHK_SLR);
	LRESULT result = ::SendMessage(hcontrol,BM_GETCHECK,0,0);
	m_OnShowLastRow = (result & BST_CHECKED);
	return 0;	
}

DWORD CCommBridgeWind::OnShowTraffic()
{
	HWND	hcontrol;
	hcontrol = GetDlgItem(m_hActDlg,CHK_SHOWTRAFFIC);
	LRESULT result = ::SendMessage(hcontrol,BM_GETCHECK,0,0);
	m_OnShowTraffic = (result & BST_CHECKED);
	return 0;

}

DWORD CCommBridgeWind::InitializeActDlg()
{
	HWND hcontrol;
	hcontrol = GetDlgItem(m_hActDlg,BTN_CLOSEFILE);
	::EnableWindow(hcontrol,false);
	hcontrol = GetDlgItem(m_hActDlg,BTN_SETOUTFILE);
	::EnableWindow(hcontrol,true);
	hcontrol = GetDlgItem(m_hActDlg,CHK_SLR);
	if (m_OnShowLastRow)
		SendMessage(hcontrol,BM_SETCHECK,BST_CHECKED,0);
	else
		SendMessage(hcontrol,BM_SETCHECK,BST_UNCHECKED,0);
	hcontrol = GetDlgItem(m_hActDlg,CHK_SHOWTRAFFIC);
	if (m_OnShowTraffic)
		SendMessage(hcontrol,BM_SETCHECK,BST_CHECKED,0);
	else
		SendMessage(hcontrol,BM_SETCHECK,BST_UNCHECKED,0);
	return 0;
}

DWORD CCommBridgeWind::UpdateActDlg()
{
	HWND hcontrol;
	char	str[100];
	// File size
	hcontrol = GetDlgItem(m_hActDlg,LBL_FILESIZE);
	FileSizeToString(m_FileSize,str);
	SetWindowText(hcontrol,str);
	// Send cant
	hcontrol = GetDlgItem(m_hActDlg,LBL_SNDCANT);
	FileSizeToString(m_SendCant,str);
	SetWindowText(hcontrol,str);
	// Read cant
	hcontrol = GetDlgItem(m_hActDlg,LBL_RCVCANT);
	FileSizeToString(m_ReadCant,str);
	SetWindowText(hcontrol,str);
	return 0;
}

DWORD _stdcall CCommBridgeWind::OnBridgeSndBuffer(BYTE *buffer, DWORD dwsize)
{
	if (dwsize == 0) return 0;
	m_SendCant+=dwsize;
	if (m_OnShowTraffic)
	{
		m_TrafficWind.AddSendBuffer(buffer,dwsize);
		PostMessage(*this,UM_REFRESH_TW,0,0);
	}
	WriteToFile(buffer,dwsize,SND_BUF);
	return 0;
}
DWORD _stdcall CCommBridgeWind::OnBridgeRcvBuffer(BYTE *buffer, DWORD dwsize)
{
	if (dwsize == 0) return 0;
	m_ReadCant+=dwsize;
	if (m_OnShowTraffic)
	{
		m_TrafficWind.AddReadBuffer(buffer,dwsize);
		PostMessage(*this,UM_REFRESH_TW,0,0);
	}
	WriteToFile(buffer,dwsize,RCV_BUF);
	return 0;
}
DWORD _stdcall CCommBridgeWind::OnBridgeSndPortEvent(DWORD pEventMask)
{
	PostMessage(*this,UM_REFRESH_RB2,0,0);
	DWORD error;
	if (pEventMask & EV_ERR)
		GetCommError(false,&error);
	ReportCommError(pEventMask,error);
	return 0;
}
DWORD _stdcall CCommBridgeWind::OnBridgeRcvPortEvent(DWORD pEventMask)
{
	PostMessage(*this,UM_REFRESH_RB1,0,0);
	DWORD error;
	if (pEventMask & EV_ERR)
		GetCommError(true,&error);
	ReportCommError(pEventMask,error);
	return 0;
}

DWORD CCommBridgeWind::ReportCommError(DWORD dwEventMask, DWORD dwError)
{
	char* str1[100];
	str1[0]=0;
	char* str = (char*)str1;

	if (dwEventMask & EV_BREAK)
		m_TrafficWind.AddComment("Line Break Detected");
	if (dwEventMask & EV_ERR)
	{
		strcpy(str,"Errors Detected");
		if (dwError & CE_FRAME)
			strcat(str," (Framing Error)");
		if (dwError & CE_OVERRUN)
			strcat(str," (Character-buffer overrun)");
		if (dwError & CE_RXPARITY)
			strcat(str," (Parity error)");
		if (dwError & CE_BREAK)
			strcat(str," (Line Break)");
		if (dwError & CE_RXOVER)
			strcat(str," (Input buffer overflow)");
		if (dwError & CE_TXFULL)
			strcat(str," (Output buffer full)");
		m_TrafficWind.AddComment(str);
	}
	return 0;
}

DWORD _stdcall CCommBridgeWind::OnBridgePortOpen(LPVOID lpParam)
{
	ISerialPort*	serialport;
	HWND			hDlg;
	HWND	hcontrol;
	if (lpParam == (void*)1) 
	{
		hDlg = m_hComm1Dlg;
		CSerialPortBridge::GetSerialPort(true,&serialport);
	}
	else
	{
		hDlg = m_hComm2Dlg;
		CSerialPortBridge::GetSerialPort(false,&serialport);
	}
	PORT_CONFIG portconfig;
	GetDlgConfig(hDlg,&portconfig);
	serialport->SetPortConfiguration(&portconfig);
	serialport->SetReadTimeOuts(1,0,0);
	serialport->SetCommMask(0);
	
	hcontrol = GetDlgItem(hDlg,IDC_CONNECT);
	::EnableWindow(hcontrol,false);
	hcontrol = GetDlgItem(hDlg,IDC_DISCONNECT);
	::EnableWindow(hcontrol,true);
	hcontrol = GetDlgItem(hDlg,BTN_CONFIGURE);
	::EnableWindow(hcontrol,true);

	DWORD Signals;
	serialport->GetInputSignals(&Signals);
	UpdateInputSignals(hDlg,Signals);

	return 0;
}
