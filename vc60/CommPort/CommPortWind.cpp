// CommPortWind.cpp: implementation of the CCommPortWind class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CommPortWind.h"
#include "resource.h"
#include "factory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
// Interfaz IUnknown

DWORD _stdcall CCommPortWind::Initialize()
{
	DWORD dr;
	for (;;)
	{
		// Cargar instancia de puerto serie
		dr = CreateInstance("SerialPort32.dll","ISerialPort",(_IUnknown**)&m_ISerialPort);
		if (dr != 0) break;
		dr = m_ISerialPort->Attach(this);
		if (dr != 0) break;
		m_ISerialPort->Initialize();
		m_BinaryWind.Initialize();
		m_TrafficWind.Initialize();
		return ERR_NONE;
	}
	return dr;
}
DWORD _stdcall CCommPortWind::GetInterfaz(char* lpName,void** lpInterfaz)
{
	*lpInterfaz = NULL;
	if (strcmp(lpName,"ISerialPortEvents") == 0) *lpInterfaz = (ISerialPortEvents*)this;
	if (*lpInterfaz == NULL) return ERR_NOINTERFACE;
	return ERR_NONE;
}

CCommPortWind::CCommPortWind()
{
	m_hActDlg = NULL;
	m_hPropDlg = NULL;
	m_BaudRateIndex = 0;
	m_ByteSizeIndex = 0;
	m_DTRIndex = 0;
	m_ParityIndex = 0;
	m_PortIndex = 0;
	m_RTSIndex = 0;
	m_StopBitsIndex = 0;
	m_OnSending = FALSE;
}

CCommPortWind::~CCommPortWind()
{
	Release();
}

DWORD CCommPortWind::Create_Window()
{
	// posicion de las ventanas
#define Y0 45		// Borde barra de estado y menu
#define HEIGHT 150  // Ventanas de trafico y binaria
#define Y1 140
#define Y2 (Y1+HEIGHT)
#define Y3 (Y2+70)		//ventana de acciones
#define Y4 (Y3+HEIGHT)
#define WIDTH  610
	DWORD result;
	HMENU hmenu;
	hmenu=LoadMenu(NULL,"COMMPORT_MENU1");
	HICON hicon = LoadIcon(GetModuleHandle (NULL),"COMMPORT_ICON1");
	result = Create("Serial Port Utility",WS_CAPTION|WS_BORDER|WS_VISIBLE|WS_MINIMIZEBOX|WS_SYSMENU,40,40,WIDTH+6,Y4+Y0,NULL,hmenu,NULL);
	if (result != 0)
		return 1;
	SendMessage(*this,WM_SETICON,ICON_BIG,(long)hicon);
	// Crear ventanas internas
	m_BinaryWind.Create_Window(1,Y1,WIDTH-1,HEIGHT,*this);
	m_BinaryWind.SetSize(10);
	m_TrafficWind.Create_Window(1,Y3,WIDTH-1,HEIGHT,*this);
	// Crear dialogos
	HRSRC hrscr = ::FindResource(GetModuleHandle(NULL),"COM_PROPERTIES",RT_DIALOG);
	if (hrscr == NULL) return 2;
	HGLOBAL hGlobal =::LoadResource(GetModuleHandle(NULL),hrscr);
	if (hGlobal == NULL) return 2;
	LPVOID lpvoid =::LockResource(hGlobal);
	if (lpvoid == NULL) return 2;
	m_hPropDlg = ::CreateDialogIndirect(GetModuleHandle (NULL),(LPCDLGTEMPLATE)lpvoid,*this,(DLGPROC)DlgProc);
	if (m_hPropDlg == NULL) return 2;
	::SetWindowPos(m_hPropDlg,NULL,0,0,WIDTH,Y1,0);
	ShowWindow(m_hPropDlg,SW_SHOW);
	UnlockResource(hGlobal);
	// Segundo dialogo
	hrscr = ::FindResource(GetModuleHandle(NULL),"COM_ACTIONS",RT_DIALOG);
	if (hrscr == NULL) return 2;
	hGlobal =::LoadResource(GetModuleHandle(NULL),hrscr);
	if (hGlobal == NULL) return 2;
	lpvoid =::LockResource(hGlobal);
	if (lpvoid == NULL) return 2;
	m_hActDlg = ::CreateDialogIndirect(GetModuleHandle (NULL),(LPCDLGTEMPLATE)lpvoid,*this,(DLGPROC)DlgProc);
	if (m_hActDlg == NULL) return 2;
	::SetWindowPos(m_hActDlg,NULL,0,Y2,WIDTH,Y3-Y2,0);
	ShowWindow(m_hActDlg,SW_SHOW);
	UnlockResource(hGlobal);
	// Actualizacion de los combobox
	HWND hcontrol = GetDlgItem(m_hPropDlg,IDC_PORT_CMB);
	BYTE i;
	for (i=0;i<MAXPORTS;i++)
	{
		::SendMessage(hcontrol,CB_ADDSTRING,0,(long)PORTS[i]);
	}
	::SendMessage(hcontrol,CB_SETCURSEL,0,m_PortIndex);
	// Byte size
	hcontrol = GetDlgItem(m_hPropDlg,IDC_CBS_CMB);
	for (i=0;i<MAXBYTESIZE;i++)
	{
		::SendMessage(hcontrol,CB_ADDSTRING,0,(long)BYTESIZE[i].str);
	}
	::SendMessage(hcontrol,CB_SETCURSEL,0,m_ByteSizeIndex);
	// Stop Bits
	hcontrol = GetDlgItem(m_hPropDlg,IDC_SB_CMB);
	for (i=0;i<MAXSTOPBITS;i++)
	{
		::SendMessage(hcontrol,CB_ADDSTRING,0,(long)STOPBITS[i].str);
	}
	::SendMessage(hcontrol,CB_SETCURSEL,0,m_StopBitsIndex);
	// Parity
	hcontrol = GetDlgItem(m_hPropDlg,IDC_PAR_CMB);
	for (i=0;i<MAXPARITY;i++)
	{
		::SendMessage(hcontrol,CB_ADDSTRING,0,(long)PARITY[i].str);
	}
	::SendMessage(hcontrol,CB_SETCURSEL,0,m_ParityIndex);
	// Baud Rate
	hcontrol = GetDlgItem(m_hPropDlg,IDC_BR_CMB);
	for (i=0;i<MAXBAUDRATE;i++)
	{
		::SendMessage(hcontrol,CB_ADDSTRING,0,(long)BAUDRATE[i].str);
	}
	::SendMessage(hcontrol,CB_SETCURSEL,0,m_BaudRateIndex);
	// DTR
	hcontrol = GetDlgItem(m_hPropDlg,IDC_DTR_CMB);
	for (i=0;i<MAXDTROFC;i++)
	{
		::SendMessage(hcontrol,CB_ADDSTRING,0,(long)DTROFC[i].str);
	}
	::SendMessage(hcontrol,CB_SETCURSEL,0,m_DTRIndex);
	// RTS
	hcontrol = GetDlgItem(m_hPropDlg,IDC_RTS_CMB);
	for (i=0;i<MAXRTSOFC;i++)
	{
		::SendMessage(hcontrol,CB_ADDSTRING,0,(long)RTSOFC[i].str);
	}
	::SendMessage(hcontrol,CB_SETCURSEL,0,m_RTSIndex);
	// Inicializar edit de comentario
	hcontrol = GetDlgItem(m_hActDlg,ED_COMMENT);
	::SendMessage(hcontrol,EM_LIMITTEXT,255,0);
	// Inicilizacion de otros controles
	hcontrol = GetDlgItem(m_hPropDlg,IDC_CONNECT);
	::EnableWindow(hcontrol,true);
	hcontrol = GetDlgItem(m_hPropDlg,IDC_DISCONNECT);
	::EnableWindow(hcontrol,false);
	PortToDlg();


	return 0;
}

LRESULT _stdcall CCommPortWind::OnWindProc(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	switch (uMsg)
	{
	case UM_REFRESH_RB:
		{
			UpdateInputSignals();
			break;
		}
	case UM_REFRESH_TW:
		{
			RefreshTraffic();
			break;
		}
	case UM_SND_FINISH:
		{
			SendFinish();			
			break;
		}
	case WM_COMMAND:
		wmId    = LOWORD(wParam); 
		wmEvent = HIWORD(wParam); 
		// Parse the menu selections:
		switch (wmId)
		{
			case ID_EXIT:
			    DestroyWindow(hWnd);
			    break;
			case IDC_CONFIGURE:
				if (wmEvent == BN_CLICKED)
				{
					ConfigurePort();
				}
				break;
			case IDC_CONNECT:
				if (wmEvent == BN_CLICKED)
				{
					Connect();
				}
				break;
			case IDC_DISCONNECT:
				if (wmEvent == BN_CLICKED)
				{
					Disconnect();				
				}
				break;
			case IDC_SEND:
				if (wmEvent == BN_CLICKED)
				{
					Send();				
				}
				break;
			case IDC_ADD_CMT:
				if (wmEvent == BN_CLICKED)
				{
					AddComment();				
				}
				break;
			case IDC_DTR:
				if (wmEvent == BN_CLICKED)
				{
					ChangeDTR();				
				}
				break;
			case IDC_RTS:
				if (wmEvent == BN_CLICKED)
				{
					ChangeRTS();				
				}
				break;
			case IDC_BREAK:
				if (wmEvent == BN_CLICKED)
				{
					ChangeBreak();				
				}
				break;
			case CLEAR_HISTORY:
				{
					m_TrafficWind.Clear();
					m_TrafficWind.Invalidate();
					break;
				}
			case IDC_SAVEBIN:
				if (wmEvent == BN_CLICKED)
				{
					SaveBIN();				
				}
				break;
			case IDC_READFILE:
				if (wmEvent == BN_CLICKED)
				{
					ReadFile();				
				}
				break;

			default:
			    return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
	default:
		return DefWindowProc(hWnd,uMsg,wParam,lParam);
	}
	return 0;
}

/*
	Procesar mensajes del dialogo.
*/
INT_PTR CALLBACK CCommPortWind::DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
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


DWORD _stdcall CCommPortWind::OnReceivedData(BYTE* Buffer,DWORD cant,LPVOID lpParam)
{
	m_TrafficWind.AddReadBuffer(Buffer,cant);
	PostMessage(*this,UM_REFRESH_TW,0,0);
	return 0;
}

DWORD _stdcall CCommPortWind::OnSetSerialPort(ISerialPort* lpSerialPort)
{
	m_ISerialPort = lpSerialPort;
	if (!m_ISerialPort) return ERR_NOINTERFACE;
	m_ISerialPort->SetCommunicationMode(true,INFINITE,0,-1);
	return ERR_NONE;
}
DWORD _stdcall CCommPortWind::OnCommEvent(DWORD pEventMask,LPVOID lpParam)
{
	char* str1[100];
	str1[0]=0;
	char* str = (char*)str1;
	DWORD error;
	/*
	if (pEventMask & EV_BREAK)
		m_TrafficWind.AddComment("Line Break Detected");
		*/
	if (pEventMask & EV_ERR)
	{
		strcpy(str,"Errors Detected");
		m_ISerialPort->GetCommunicationError(&error);
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
	PostMessage(*this,UM_REFRESH_RB,0,0);
	return 0;
}
DWORD _stdcall CCommPortWind::OnSendBytes(BYTE* Buffer,DWORD BytesWritten,LPVOID lpParam)
{
	// Poner buffer en ventana de envio
	if (Buffer)
	{
		m_TrafficWind.AddSendBuffer(Buffer,BytesWritten);
		PostMessage(*this,UM_REFRESH_TW,0,0);
	}
	PostMessage(*this,UM_SND_FINISH,0,0); // enviar codigo de error
	return 0;
}
DWORD _stdcall CCommPortWind::OnProcessMessage(LP_MESSAGE lpMessage,LPVOID lpParam)
{
	switch (lpMessage->Msg)
	{
	case TM_SEND: return ThreadSend();
	case TM_ABORT_SEND:
		{
			// No hay que enviar mas nada
			return m_ISerialPort->CancelSend();
		}
	}
	return 0;
}
DWORD _stdcall CCommPortWind::OnWaitTimeOut(LPVOID lpParam)
{
	return 0;
}

DWORD _stdcall CCommPortWind::OnRequestData(LPVOID lpParam)
{
	return 0;
}

DWORD CCommPortWind::DlgToPort()
{
	PORT_CONFIG	pconfig;
	LRESULT	result;
	HWND hcontrol;

	hcontrol = GetDlgItem(m_hPropDlg,IDC_BR_CMB);
	result = ::SendMessage(hcontrol,CB_GETCURSEL,0,0);
	if (result == CB_ERR) return 1;
	pconfig.BaudRate = BAUDRATE[result].val;

	hcontrol = GetDlgItem(m_hPropDlg,IDC_PAR_CMB);
	result = ::SendMessage(hcontrol,CB_GETCURSEL,0,0);
	if (result == CB_ERR) return 1;
	pconfig.Parity = (BYTE)PARITY[result].val;

	hcontrol = GetDlgItem(m_hPropDlg,IDC_SB_CMB);
	result = ::SendMessage(hcontrol,CB_GETCURSEL,0,0);
	if (result == CB_ERR) return 1;
	pconfig.StopBits = (BYTE)STOPBITS[result].val;

	hcontrol = GetDlgItem(m_hPropDlg,IDC_CBS_CMB);
	result = ::SendMessage(hcontrol,CB_GETCURSEL,0,0);
	if (result == CB_ERR) return 1;
	pconfig.ByteSize = (BYTE)BYTESIZE[result].val;

	hcontrol = GetDlgItem(m_hPropDlg,IDC_RTS_CMB);
	result = ::SendMessage(hcontrol,CB_GETCURSEL,0,0);
	if (result == CB_ERR) return 1;
	pconfig.RTSMode = RTSOFC[result].val;

	hcontrol = GetDlgItem(m_hPropDlg,IDC_DTR_CMB);
	result = ::SendMessage(hcontrol,CB_GETCURSEL,0,0);
	if (result == CB_ERR) return 1;
	pconfig.DTRMode = DTROFC[result].val;

	hcontrol = GetDlgItem(m_hPropDlg,IDC_PARITY);
	result = ::SendMessage(hcontrol,BM_GETCHECK,0,0);
	if (result & BST_CHECKED) 
		pconfig.CheckParity = TRUE;
	else
		pconfig.CheckParity = FALSE;

	hcontrol = GetDlgItem(m_hPropDlg,IDC_DSR_OFC);
	result = ::SendMessage(hcontrol,BM_GETCHECK,0,0);
	if (result & BST_CHECKED) 
		pconfig.DSRStopInFlow = TRUE;
	else
		pconfig.DSRStopInFlow = FALSE;

	hcontrol = GetDlgItem(m_hPropDlg,IDC_CTS_OFC);
	result = ::SendMessage(hcontrol,BM_GETCHECK,0,0);
	if (result & BST_CHECKED) 
		pconfig.CTSStopOutFlow = TRUE;
	else
		pconfig.CTSStopOutFlow = FALSE;
	return m_ISerialPort->SetPortConfiguration(&pconfig);
}

DWORD CCommPortWind::PortToDlg()
{
	PORT_CONFIG	pconfig;
	LRESULT	result;
	HWND hcontrol;
	DWORD i;

	m_ISerialPort->GetPortConfiguration(&pconfig);

	hcontrol = GetDlgItem(m_hPropDlg,IDC_PORT_CMB);
	::SendMessage(hcontrol,CB_SETCURSEL,0,0);
	
	// Buscar Baud Rate
	hcontrol = GetDlgItem(m_hPropDlg,IDC_BR_CMB);
	for (i=0;(i<MAXBAUDRATE) && (BAUDRATE[i].val != pconfig.BaudRate);i++);
	::SendMessage(hcontrol,CB_SETCURSEL,i,0);

	// Byte size
	hcontrol = GetDlgItem(m_hPropDlg,IDC_CBS_CMB);
	for (i=0;(i<MAXBYTESIZE) && (BYTESIZE[i].val != pconfig.ByteSize);i++);
	::SendMessage(hcontrol,CB_SETCURSEL,i,0);

	// Stop Bits
	hcontrol = GetDlgItem(m_hPropDlg,IDC_SB_CMB);
	for (i=0;(i<MAXSTOPBITS) && (STOPBITS[i].val != pconfig.StopBits);i++);
	::SendMessage(hcontrol,CB_SETCURSEL,i,0);
	
	// Parity
	hcontrol = GetDlgItem(m_hPropDlg,IDC_PAR_CMB);
	for (i=0;(i<MAXPARITY) && (PARITY[i].val != pconfig.Parity);i++);
	::SendMessage(hcontrol,CB_SETCURSEL,i,0);

	// DTR
	hcontrol = GetDlgItem(m_hPropDlg,IDC_DTR_CMB);
	for (i=0;(i<MAXDTROFC) && (DTROFC[i].val != pconfig.DTRMode);i++);
	::SendMessage(hcontrol,CB_SETCURSEL,i,0);
	
	// RTS
	hcontrol = GetDlgItem(m_hPropDlg,IDC_RTS_CMB);
	for (i=0;(i<MAXRTSOFC) && (RTSOFC[i].val != pconfig.RTSMode);i++);
	::SendMessage(hcontrol,CB_SETCURSEL,i,0);

	// Check Parity
	hcontrol = GetDlgItem(m_hPropDlg,IDC_PARITY);
	::SendMessage(hcontrol,BM_SETCHECK,(pconfig.CheckParity) ? (BST_CHECKED):(BST_UNCHECKED),0);

	// DSR Input sensibility	
	hcontrol = GetDlgItem(m_hPropDlg,IDC_DSR_OFC);
	result = ::SendMessage(hcontrol,BM_SETCHECK,(pconfig.DSRStopOutFlow) ? (BST_CHECKED):(BST_UNCHECKED),0);

	// CTS output flow control
	hcontrol = GetDlgItem(m_hPropDlg,IDC_CTS_OFC);
	result = ::SendMessage(hcontrol,BM_SETCHECK,(pconfig.CTSStopOutFlow) ? (BST_CHECKED):(BST_UNCHECKED),0);
	return 0;
	return 0;
}

DWORD CCommPortWind::ConfigurePort()
{
	return DlgToPort();
}

DWORD CCommPortWind::SetPortNumber()
{
	DWORD result;
	BYTE Port;
	HWND hcontrol;
	hcontrol = GetDlgItem(m_hPropDlg,IDC_PORT_CMB);
	result = ::SendMessage(hcontrol,CB_GETCURSEL,0,0);
	if (result == CB_ERR) return 1;
	Port = (BYTE)result+1;
	return m_ISerialPort->SetPort(Port);
}

DWORD CCommPortWind::Connect()
{
	DWORD result;
	HWND hcontrol;
	result = SetPortNumber();
	if (result != 0) return result;
	result = m_ISerialPort->OpenPort();
	if (result !=0) 
	{
		::MessageBox(*this,"Error Opening Port","CommPort",MB_OK|MB_ICONERROR);
		return 0;
	}
	hcontrol = GetDlgItem(m_hPropDlg,IDC_CONNECT);
	::EnableWindow(hcontrol,false);
	hcontrol = GetDlgItem(m_hPropDlg,IDC_DISCONNECT);
	::EnableWindow(hcontrol,true);
	ConfigurePort();
	UpdateInputSignals();
	return 0;
}

DWORD CCommPortWind::Disconnect()
{
	DWORD result;
	HWND	hcontrol;
	result = m_ISerialPort->ClosePort();
	if (result !=0) ::MessageBox(*this,"Error Closing Port","Serial Port",MB_OK|MB_ICONERROR);
	hcontrol = GetDlgItem(m_hPropDlg,IDC_CONNECT);
	::EnableWindow(hcontrol,true);
	hcontrol = GetDlgItem(m_hPropDlg,IDC_DISCONNECT);
	::EnableWindow(hcontrol,false);
	return result;
}

DWORD CCommPortWind::Send()
{
	DWORD	result;
	HWND	hcontrol;
	S_MESSAGE msg;
	if (m_OnSending)
	{
		// Abortar el envio de bytes
		msg.Msg = TM_ABORT_SEND;
		result = m_ISerialPort->SendThreadMessage(&msg);
		if (result != 0) return 1;
		return msg.Result;
	}
	// El hilo debe iniciar el envio de datos
	msg.Msg = TM_SEND;
	result = m_ISerialPort->SendThreadMessage(&msg);
	if (result != 0) return 1;
	if (msg.Result != 0) return msg.Result;
	//  Se estan enviando datos
	m_OnSending = TRUE;
	hcontrol = GetDlgItem(m_hActDlg,IDC_SEND);
	SetWindowText(hcontrol,"Abort Send");
	m_BinaryWind.EnableWindow(FALSE);
	return 0;
}

DWORD CCommPortWind::ChangeDTR()
{
	HWND	hcontrol;
	hcontrol = GetDlgItem(m_hPropDlg,IDC_DTR);
	LRESULT result = ::SendMessage(hcontrol,BM_GETCHECK,0,0);
	if (result & BST_CHECKED) 
		m_ISerialPort->ChangeOutputSignal(SETDTR);
	else
		m_ISerialPort->ChangeOutputSignal(CLRDTR);
	return 0;
}

DWORD CCommPortWind::ChangeRTS()
{
	HWND	hcontrol;
	hcontrol = GetDlgItem(m_hPropDlg,IDC_RTS);
	LRESULT result = ::SendMessage(hcontrol,BM_GETCHECK,0,0);
	if (result & BST_CHECKED) 
		m_ISerialPort->ChangeOutputSignal(SETRTS);
	else
		m_ISerialPort->ChangeOutputSignal(CLRRTS);
	return 0;
}

DWORD CCommPortWind::ChangeBreak()
{
	HWND	hcontrol;
	hcontrol = GetDlgItem(m_hPropDlg,IDC_BREAK);
	LRESULT result = ::SendMessage(hcontrol,BM_GETCHECK,0,0);
	if (result & BST_CHECKED) 
		m_ISerialPort->ChangeOutputSignal(SETBREAK);
	else
		m_ISerialPort->ChangeOutputSignal(CLRBREAK);
	return 0;
}

DWORD CCommPortWind::UpdateInputSignals()
{
	DWORD Signals;
	HWND hcontrol;
	m_ISerialPort->GetInputSignals(&Signals);
	// DSR
	hcontrol = GetDlgItem(m_hPropDlg,IDC_DSR);
	if (Signals & MS_DSR_ON)
		SendMessage(hcontrol,BM_SETCHECK,BST_CHECKED,0);
	else
		SendMessage(hcontrol,BM_SETCHECK,BST_UNCHECKED,0);
	// CTS
	hcontrol = GetDlgItem(m_hPropDlg,IDC_CTS);
	if (Signals & MS_CTS_ON)
		SendMessage(hcontrol,BM_SETCHECK,BST_CHECKED,0);
	else
		SendMessage(hcontrol,BM_SETCHECK,BST_UNCHECKED,0);
	// RING
	hcontrol = GetDlgItem(m_hPropDlg,IDC_RING);
	if (Signals & MS_RING_ON)
		SendMessage(hcontrol,BM_SETCHECK,BST_CHECKED,0);
	else
		SendMessage(hcontrol,BM_SETCHECK,BST_UNCHECKED,0);
	// RLSD
	hcontrol = GetDlgItem(m_hPropDlg,IDC_RLSD);
	if (Signals & MS_RLSD_ON)
		SendMessage(hcontrol,BM_SETCHECK,BST_CHECKED,0);
	else
		SendMessage(hcontrol,BM_SETCHECK,BST_UNCHECKED,0);
	return 0;
}

DWORD CCommPortWind::AddComment()
{
	char cmt[300];
	HWND hcontrol = GetDlgItem(m_hActDlg,ED_COMMENT);
	GetWindowText(hcontrol,cmt,256);
	m_TrafficWind.AddComment(cmt);
	m_TrafficWind.Invalidate();
	return 0;
}

DWORD CCommPortWind::RefreshTraffic()
{
	LRESULT	result;
	HWND hcontrol = GetDlgItem(m_hActDlg,IDC_SLR);
	result = ::SendMessage(hcontrol,BM_GETCHECK,0,0);
	if (result & BST_CHECKED) 
		m_TrafficWind.ShowLastBuffer();
	else
		m_TrafficWind.Invalidate();
	return 0;
}

DWORD CCommPortWind::ThreadSend()
{
	DWORD dr;
	dr = m_ISerialPort->ThreadSend(m_BinaryWind.Data(),m_BinaryWind.GetSize());
	return dr;
}

DWORD CCommPortWind::SendFinish()
{
	HWND hcontrol;
	hcontrol = GetDlgItem(m_hActDlg,IDC_SEND);
	SetWindowText(hcontrol,"Send");
	m_OnSending = FALSE;
	m_BinaryWind.EnableWindow(TRUE);
	return 0;
}

DWORD _stdcall CCommPortWind::OnTrigger(LPVOID lpParam)
{
	return 0;
}

DWORD CCommPortWind::OnOpenPort(LPVOID lpParam)
{
	m_ISerialPort->SetReadTimeOuts(1,0,0);
	return 0;
}

DWORD CCommPortWind::SaveBIN()
{
	HANDLE hFile;
	char*	Filter = "BIN files (*.BIN)\0*.BIN\0All files (*.*)\0*.*\0\0";
	char	filename[300];

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
	hFile = CreateFile(ofn.lpstrFile,GENERIC_WRITE,FILE_SHARE_READ,NULL,
		CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return 1;
	m_TrafficWind.SaveBIN(hFile);
	CloseHandle(hFile);
	return 0;
}

DWORD CCommPortWind::ReadFile()
{
	HANDLE hFile;
	char*	Filter = "All files (*.*)\0*.*\0\0";
	char	filename[300];
	BYTE	buffer[200];
	DWORD	BytesRead;

	filename[0]=0;
	OPENFILENAME ofn;
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.Flags = OFN_HIDEREADONLY|OFN_NONETWORKBUTTON|
				OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST;
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
	if (!GetOpenFileName(&ofn)) return 0;
	hFile = CreateFile(ofn.lpstrFile,GENERIC_READ,FILE_SHARE_READ,NULL,
		OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return 1;
	m_BinaryWind.SetSize(0);
	for(;;)
	{
		if (::ReadFile(hFile,buffer,200,&BytesRead,NULL)) m_BinaryWind.AddBuffer(buffer,BytesRead);
		if (!BytesRead) break;
	}
	CloseHandle(hFile);
	m_BinaryWind.Invalidate();
	return 0;
}

DWORD _stdcall CCommPortWind::UnInitialize()
{
	if (m_ISerialPort) m_ISerialPort->Release();
	m_ISerialPort = NULL;
	return 0;
}
