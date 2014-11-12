// Lisa200Wind.cpp: implementation of the CLisa200Wind class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Lisa200Wind.h"
#include "shellapi.h"
#include "resource.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define UM_TASKBAR_NOTIFY WM_USER+1

static UINT s_uTaskbarRestart = RegisterWindowMessage(TEXT("TaskbarCreated"));

static const char* CNF_CTS = "CTS";
static const char* CNF_DSR = "DSR";
static const char* CNF_DTR = "DTR";
static const char* CNF_RTS = "RTS";
static const char* CNF_PORT1 = "PORT1";
static const char* CNF_PORT2 = "PORT2";
static const char* CNF_PARITY = "PARITY";
static const char* CNF_STOPBITS = "STOPBITS";
static const char* CNF_BAUDRATE = "BAUDRATE";
static const char* CNF_SERVERPORT = "SERVERPORT";
static const char* CNF_CHECKPARITY = "CHECKPARITY";
static const char* CNF_BRIDGEAUTOSTART = "BRIDGEAUTOSTART";
static const char* CNF_SERVERAUTOSTART = "SERVERAUTOSTART";
static const char* CNF_CANSSBRIDGE = "CANSSBRIDGE";
static const char* CNF_CANSSSERVER = "CANSSSERVER";
static const char* CNF_CANCHANGEBRIDGE = "CANCHANGEBRIDGE";
static const char* CNF_CANCHANGESERVERPORT = "CANCHANGESERVERPORT";

CLisa200Wind::CLisa200Wind()
{
	m_CanSSBridge = false;
	m_CanSSServer = false;
	m_hDlg = NULL;
}

CLisa200Wind::~CLisa200Wind()
{

}

DWORD CLisa200Wind::Create_Window()
{
#define WIDTH 280
#define HEIGHT 250
	for (;;)
	{
		HICON hicon = LoadIcon(GetModuleHandle (NULL),"LISA200ICO");
		if (Create("Lisa 200 Utility (LYFSoft)",WS_CAPTION|WS_BORDER|WS_SYSMENU,40,40,WIDTH+6,HEIGHT,NULL,NULL,(HINSTANCE)GetModuleHandle(NULL),NULL) !=0 ) break;
		::SendMessage(m_hwnd,WM_SETICON,ICON_BIG,(long)hicon);
		// Crear dialogos
		HRSRC hrscr = ::FindResource(GetModuleHandle(NULL),"LISA200DLG",RT_DIALOG);
		if (hrscr == NULL) break;
		HGLOBAL hGlobal =::LoadResource(GetModuleHandle(NULL),hrscr);
		if (hGlobal == NULL) break;
		LPVOID lpvoid =::LockResource(hGlobal);
		if (lpvoid == NULL) break;
		m_hDlg = ::CreateDialogIndirect(GetModuleHandle (NULL),(LPCDLGTEMPLATE)lpvoid,m_hwnd,(DLGPROC)DlgProc);
		if (m_hDlg == NULL) break;
		::SetWindowPos(m_hDlg,NULL,0,0,WIDTH,HEIGHT,0);
		ShowWindow(m_hDlg,SW_SHOW);
		UnlockResource(hGlobal);
		// Inicializar la interfaz gráfica
		InitializeDlg();
		// Leer configuracion e iniciar los servicios
		LoadConfiguration();
		UpdateDlg();
		if (ShowShellIcon()!=0) break;
		LoadResults();
		return 0;
	}
	return 1;
}

LRESULT CLisa200Wind::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_ENDSESSION :	 return EndSession(wParam,lParam);
	case WM_QUERYENDSESSION: return QueryEndSession(wParam,lParam);
	case UM_TASKBAR_NOTIFY:  return ProcessTaskBarMessage(wParam,lParam);
	case WM_TIMER:			 return RefreshDlg();
	case WM_COMMAND:
		{
			int wmId    = LOWORD(wParam); 
			int wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			if (wmEvent != BN_CLICKED) break;
			switch (wmId)
			{
			case BTN_SRV_START: return StartServer();
			case BTN_BRIDGE_START : return StartBridge();
			case BTN_BRIDGE_STOP : return StopBridge();
			}
			break;
		}
		
	case WM_CLOSE:
		{
			ShowWindow(m_hwnd,SW_HIDE);
			KillTimer(m_hwnd,0);
			ShowShellIcon();
			break;
		}
	case WM_DESTROY: PostQuitMessage(0);break;
	default:
		{
			if (uMsg == s_uTaskbarRestart)
				return ShowShellIcon();
		return DefWindowProc(hWnd,uMsg,wParam,lParam);
		}
	}
	return 0;
}

INT_PTR CALLBACK CLisa200Wind::DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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

DWORD CLisa200Wind::LoadResults()
{
	BYTE Buffer[100];
	DWORD CantRead,i;
	BYTE  Val;			// Valor del numero leido
	BYTE Valor;
	DWORD LinePos;		// Posicion dentro de la linea que se esta procesando
	char TmpBuf[10];	// Buffer temporal que almacena valores para su posterior uso
	BOOL OnRcv;			// Indica que se esta reciviendo informacion
	BOOL OnIgnore;		// Indica que deben ser ignorados todos los bytes hasta el fin de linea
	BOOL OnHiChar;
	LinePos = 0;
	OnHiChar = false;
	OnIgnore = false;      

	// Abrir fichero
	HANDLE m_hInFile = CreateFile("historico.txt",GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	while(ReadFile(m_hInFile,Buffer,99,&CantRead,NULL))
	{
		if (!CantRead)
		{
			break;
		}
		for (i=0;i<CantRead;i++)
		{
			LinePos++;
			Valor = Buffer[i]; 
			if (Valor == 0x0a)
			{
				// Fin de linea
				LinePos = 0;
				OnIgnore = false;
				OnHiChar = false;
			}
			else
			switch (LinePos)
			{
			case 1:
			case 2:
			case 3:
				{
					TmpBuf[LinePos-1] = Buffer[i];
					break;
				}
			case 4:
				{
					TmpBuf[3] = 0;
					if (strcmp(TmpBuf,"Rcv") == 0)
					{
						OnRcv = true;
						break;
					}
					if (strcmp(TmpBuf,"Snd") == 0)
					{
						OnRcv = false;
						break;
					}
					if (strcmp(TmpBuf,"Cmt") == 0)
					{
						OnIgnore = true;
						break;
					}
					TmpBuf[2]=0;
					if (strcmp(TmpBuf,"//") == 0)
					{
						OnIgnore = true;
						break;
					}
					break;
				}
			default:
				{
					if (OnIgnore) break;
					if (LinePos>57) break;
					if (Buffer[i]==' ') break;
					if ((Buffer[i] >= '0') && (Buffer[i] <= 'F'))
					{
						BYTE tmpval;
						if (Buffer[i] > '9') tmpval = Buffer[i]-'A'+10;
						else
							tmpval = Buffer[i]-'0';
						if (OnHiChar) 
							Val = Val*16+tmpval;
						else
							Val = tmpval;
						OnHiChar = !OnHiChar;
						if (!OnHiChar)
						{
							DWORD result;
							if (OnRcv)
								result = ProcessRcvBuffer(&Val,1);
							else
								result = ProcessSndBuffer(&Val,1);
						}
					}
					break;
				}
			}
		} 
	}
	CloseHandle(m_hInFile);
	return 0;
}

DWORD CLisa200Wind::LoadConfiguration()
{
	LISA_CONF cnf;
	if (LoadIniFile("lisa200.ini",this,&cnf) != 0)
	{
		// cargar configuracion por defecto
		cnf.port_cnf.BaudRate = CBR_9600;
		cnf.port_cnf.ByteSize = 8;
		cnf.port_cnf.CheckParity = true;
		cnf.port_cnf.CTS = FALSE;
		cnf.port_cnf.DSR = FALSE;
		cnf.port_cnf.DTR = DTR_CONTROL_ENABLE;
		cnf.port_cnf.Parity = EVENPARITY;
		cnf.port_cnf.RTS = RTS_CONTROL_ENABLE;
		cnf.port_cnf.StopBits = TWOSTOPBITS;
		cnf.port1 = 3;
		cnf.port2 = 4;
		cnf.serverport = 2000;
		cnf.BridgeAutoStart = TRUE;
		cnf.ServerAutoStart = TRUE;
		cnf.CanChangeBridge = FALSE;
		cnf.CanChangeServerPort = FALSE;
		cnf.CanSSBridge = TRUE;
		cnf.CanSSServer = TRUE;
		// Guardar configuracion
		SaveConfiguration(&cnf);
	}
	ApplyConfiguration(&cnf);
	return 0;
}

DWORD CLisa200Wind::OnProcessParam(char *name, double val,void* lpParam)
{
	LISA_CONF* cnf = (LISA_CONF*)lpParam;
	if (strcmp(name,CNF_PORT1)==0)
	{cnf->port1 = val;return 0;}
	if (strcmp(name,CNF_PORT2)==0)
	{cnf->port2 = val;return 0;}
	if (strcmp(name,CNF_BAUDRATE)==0)
	{cnf->port_cnf.BaudRate = val;return 0;}
	if (strcmp(name,CNF_CHECKPARITY)==0)
	{cnf->port_cnf.CheckParity = val;return 0;}
	if (strcmp(name,CNF_CTS)==0)
	{cnf->port_cnf.CTS = val;return 0;}
	if (strcmp(name,CNF_DSR)==0)
	{cnf->port_cnf.DSR = val;return 0;}
	if (strcmp(name,CNF_DTR)==0)
	{cnf->port_cnf.DTR = val;return 0;}
	if (strcmp(name,CNF_PARITY)==0)
	{cnf->port_cnf.Parity = val;return 0;}
	if (strcmp(name,CNF_RTS)==0)
	{cnf->port_cnf.RTS = val;return 0;}
	if (strcmp(name,CNF_STOPBITS)==0)
	{cnf->port_cnf.StopBits = val;return 0;}
	if (strcmp(name,CNF_SERVERPORT)==0)
	{cnf->serverport = val;return 0;}
	if (strcmp(name,CNF_BRIDGEAUTOSTART)==0)
	{cnf->BridgeAutoStart = val;return 0;}
	if (strcmp(name,CNF_SERVERAUTOSTART)==0)
	{cnf->ServerAutoStart = val;return 0;}
	if (strcmp(name,CNF_CANCHANGEBRIDGE)==0)
	{cnf->CanChangeBridge = val;return 0;}
	if (strcmp(name,CNF_CANCHANGESERVERPORT)==0)
	{cnf->CanChangeServerPort = val;return 0;}
	return 1;
}

DWORD CLisa200Wind::SaveConfiguration(LISA_CONF* cnf)
{
	char buffer[255];
	DWORD byteswritten; 
	HANDLE hfile = CreateFile("lisa200.ini",GENERIC_WRITE,FILE_SHARE_READ,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if (hfile == INVALID_HANDLE_VALUE) return 1;
	sprintf(buffer,"%s=%d;\x0d\x0a",CNF_PORT1,cnf->port1);
	WriteFile(hfile,buffer,strlen(buffer),&byteswritten,NULL);
	sprintf(buffer,"%s=%d;\x0d\x0a",CNF_PORT2,cnf->port2);
	WriteFile(hfile,buffer,strlen(buffer),&byteswritten,NULL);
	sprintf(buffer,"%s=%d;\x0d\x0a",CNF_BAUDRATE,cnf->port_cnf.BaudRate);
	WriteFile(hfile,buffer,strlen(buffer),&byteswritten,NULL);
	sprintf(buffer,"%s=%d;\x0d\x0a",CNF_CHECKPARITY,cnf->port_cnf.CheckParity);
	WriteFile(hfile,buffer,strlen(buffer),&byteswritten,NULL);
	sprintf(buffer,"%s=%d;\x0d\x0a",CNF_CTS,cnf->port_cnf.CTS);
	WriteFile(hfile,buffer,strlen(buffer),&byteswritten,NULL);
	sprintf(buffer,"%s=%d;\x0d\x0a",CNF_DSR,cnf->port_cnf.DSR);
	WriteFile(hfile,buffer,strlen(buffer),&byteswritten,NULL);
	sprintf(buffer,"%s=%d;\x0d\x0a",CNF_DTR,cnf->port_cnf.DTR);
	WriteFile(hfile,buffer,strlen(buffer),&byteswritten,NULL);
	sprintf(buffer,"%s=%d;\x0d\x0a",CNF_PARITY,cnf->port_cnf.Parity);
	WriteFile(hfile,buffer,strlen(buffer),&byteswritten,NULL);
	sprintf(buffer,"%s=%d;\x0d\x0a",CNF_STOPBITS,cnf->port_cnf.StopBits);
	WriteFile(hfile,buffer,strlen(buffer),&byteswritten,NULL);
	sprintf(buffer,"%s=%d;\x0d\x0a",CNF_SERVERPORT,cnf->serverport);
	WriteFile(hfile,buffer,strlen(buffer),&byteswritten,NULL);
	sprintf(buffer,"%s=%d;\x0d\x0a",CNF_BRIDGEAUTOSTART,cnf->BridgeAutoStart);
	WriteFile(hfile,buffer,strlen(buffer),&byteswritten,NULL);
	sprintf(buffer,"%s=%d;\x0d\x0a",CNF_SERVERAUTOSTART,cnf->ServerAutoStart);
	WriteFile(hfile,buffer,strlen(buffer),&byteswritten,NULL);
	sprintf(buffer,"%s=%d;\x0d\x0a",CNF_CANCHANGEBRIDGE,cnf->CanChangeBridge);
	WriteFile(hfile,buffer,strlen(buffer),&byteswritten,NULL);
	sprintf(buffer,"%s=%d;\x0d\x0a",CNF_CANCHANGESERVERPORT,cnf->CanChangeServerPort);
	WriteFile(hfile,buffer,strlen(buffer),&byteswritten,NULL);
	
	CloseHandle(hfile);
	return 0;
}

DWORD CLisa200Wind::ApplyConfiguration(LISA_CONF* cnf)
{
	cnf->port_cnf.Port = cnf->port1;
	SetPortConfiguration(true,&cnf->port_cnf);
	cnf->port_cnf.Port = cnf->port2;
	SetPortConfiguration(false,&cnf->port_cnf);
	SetServerPort(cnf->serverport);
	if (cnf->BridgeAutoStart)
		StartBridge();
	if (cnf->ServerAutoStart)
		StartServer();

	m_CanChangeBridge = cnf->CanChangeBridge;
	m_CanChangeServerPort = cnf->CanChangeServerPort;
	m_CanSSBridge = cnf->CanSSBridge;
	m_CanSSServer = cnf->CanSSServer;
	
	// Actualizar interfaz gráfica
	HWND hcontrol = GetDlgItem(m_hDlg,CMB_RCVPORT);
	::EnableWindow(hcontrol,m_CanChangeBridge);

	hcontrol = GetDlgItem(m_hDlg,CMB_SNDPORT);
	::EnableWindow(hcontrol,m_CanChangeBridge);

	hcontrol = GetDlgItem(m_hDlg,EDT_SRV_PORT);
	::EnableWindow(hcontrol,m_CanChangeServerPort);

	/*
	hcontrol = GetDlgItem(m_hDlg,BTN_BRIDGE_START);
	::EnableWindow(hcontrol,m_CanSSBridge);
	hcontrol = GetDlgItem(m_hDlg,BTN_BRIDGE_STOP);
	::EnableWindow(hcontrol,m_CanSSBridge);

	hcontrol = GetDlgItem(m_hDlg,BTN_SRV_START);
	::EnableWindow(hcontrol,m_CanSSServer);
	hcontrol = GetDlgItem(m_hDlg,BTN_SRV_STOP);
	::EnableWindow(hcontrol,m_CanSSServer);
	*/

	return 0;
}

DWORD CLisa200Wind::ShowShellIcon()
{
	NOTIFYICONDATA pnid;
	pnid.cbSize = sizeof(pnid);
	pnid.hIcon = LoadIcon(GetModuleHandle (NULL),"TASKBARICO");
	if (pnid.hIcon == NULL) return 1;
	pnid.hWnd = m_hwnd; 
	strcpy(pnid.szTip,"Lisa 200 Monitor (LYFSoft)");
	pnid.uCallbackMessage = UM_TASKBAR_NOTIFY;
	pnid.uFlags = NIF_ICON |NIF_MESSAGE |NIF_TIP;
	pnid.uID = 1;
	if (Shell_NotifyIcon(NIM_ADD,&pnid) == FALSE)
		return 1;
	return 0;
}

DWORD CLisa200Wind::ProcessTaskBarMessage(WPARAM wParam, LPARAM lParam)
{
	switch (lParam)
	{
	case WM_LBUTTONDBLCLK : 
		{
			ShowWindow(m_hwnd,SW_SHOW);
			SetTimer(m_hwnd,0,1000,NULL);
//			ShowWindow(m_hwnd,SW_RESTORE);
		//	HideShellIcon();
			break;
		}
	}
	return 0;
}

DWORD CLisa200Wind::HideShellIcon()
{
	NOTIFYICONDATA pnid;
	pnid.cbSize = sizeof(pnid);
	pnid.hIcon = LoadIcon(GetModuleHandle (NULL),"TASKBARICO");
	if (pnid.hIcon == NULL) return 1;
	pnid.hWnd = m_hwnd; 
	strcpy(pnid.szTip,"Lisa 200 Monitor (LYFSoft)");
	pnid.uCallbackMessage = UM_TASKBAR_NOTIFY;
	pnid.uFlags = NIF_ICON |NIF_MESSAGE |NIF_TIP;
	pnid.uID = 1;
	if (Shell_NotifyIcon(NIM_DELETE,&pnid) == FALSE)
		return 1;
	return 0;
}

DWORD CLisa200Wind::QueryEndSession(WPARAM wParam, LPARAM lParam)
{
	Sleep(60000);
	// Stop services
	// Remove Icon
	return TRUE;
}

DWORD CLisa200Wind::EndSession(WPARAM wParam, LPARAM lParam)
{
	Release();
	return 0;
}

DWORD CLisa200Wind::InitializeDlg()
{
	HWND hcontrol = GetDlgItem(m_hDlg,CMB_RCVPORT);
	BYTE i;
	for (i=0;i<MAXPORTS;i++)
	{
		::SendMessage(hcontrol,CB_ADDSTRING,0,(long)PORTS[i]);
	}
	hcontrol = GetDlgItem(m_hDlg,CMB_SNDPORT);
	for (i=0;i<MAXPORTS;i++)
	{
		::SendMessage(hcontrol,CB_ADDSTRING,0,(long)PORTS[i]);
	}
	hcontrol = GetDlgItem(m_hDlg,EDT_SRV_PORT);
	::SendMessage(hcontrol,EM_LIMITTEXT,5,0);

	hcontrol = GetDlgItem(m_hDlg,BTN_BRIDGE_START);
	::EnableWindow(hcontrol,true);
	hcontrol = GetDlgItem(m_hDlg,BTN_BRIDGE_STOP);
	::EnableWindow(hcontrol,false);

	hcontrol = GetDlgItem(m_hDlg,BTN_SRV_START);
	::EnableWindow(hcontrol,true);
	hcontrol = GetDlgItem(m_hDlg,BTN_SRV_STOP);
	::EnableWindow(hcontrol,false);


	return 0;
}



DWORD CLisa200Wind::UpdateDlg()
{
	PORT_CONFIG portcnf;
	HWND hcontrol = GetDlgItem(m_hDlg,CMB_RCVPORT);
	GetPortConfiguration(true,&portcnf);
	::SendMessage(hcontrol,CB_SETCURSEL,portcnf.Port-1,0);

	hcontrol = GetDlgItem(m_hDlg,CMB_SNDPORT);
	GetPortConfiguration(false,&portcnf);
	::SendMessage(hcontrol,CB_SETCURSEL,portcnf.Port-1,0);

	hcontrol = GetDlgItem(m_hDlg,EDT_SRV_PORT);
	unsigned short port;
	char buffer[6];
	GetServerPort(&port);
	sprintf(buffer,"%d",port);
	SetWindowText(hcontrol,buffer);

	return 0;
}

DWORD CLisa200Wind::RefreshDlg()
{
	DWORD stat;
	int err;
	char str[20];
	HWND hcontrol = GetDlgItem(m_hDlg,ST_SRV_STAT);
	GetServerStatus(&stat,&err);
	switch(stat)
	{
	case SRV_STARTED:strcpy(str,"Running ...");break;
	case SRV_STOPED: strcpy(str,"Stopped ...");break;
	case SRV_ERROR:sprintf(str,"Error %d ...");break;
	}
	SetWindowText(hcontrol,str);
	hcontrol = GetDlgItem(m_hDlg,ST_BRIDGE_STAT);
	GetBridgeStatus(&stat,&err);
	switch(stat)
	{
	case BS_OK   : strcpy(str,"Running ...");break;
	case BS_STOP : strcpy(str,"Stopped ...");break;
	default :
		sprintf(str,"Error %d ...");break;
	}
	SetWindowText(hcontrol,str);
	return 0;
}

LRESULT CLisa200Wind::StartBridge()
{
	if (CSerialPortBridge::Start() == 0)
	{
		HWND hcontrol = GetDlgItem(m_hDlg,BTN_BRIDGE_START);
		::EnableWindow(hcontrol,false);
		hcontrol = GetDlgItem(m_hDlg,BTN_BRIDGE_STOP);
		::EnableWindow(hcontrol,true);
		return 0;
	}
	return 1;
}

DWORD CLisa200Wind::StartServer()
{
	if (CTcpIpServer::ServerStart()==0)
	{
		HWND hcontrol = GetDlgItem(m_hDlg,BTN_SRV_START);
		::EnableWindow(hcontrol,false);
		hcontrol = GetDlgItem(m_hDlg,BTN_SRV_STOP);
		::EnableWindow(hcontrol,true);
		return 0;
	}
	return 1;
}

DWORD CLisa200Wind::StopBridge()
{
	CSerialPortBridge::Stop();
	HWND hcontrol = GetDlgItem(m_hDlg,BTN_BRIDGE_START);
	::EnableWindow(hcontrol,true);
	hcontrol = GetDlgItem(m_hDlg,BTN_BRIDGE_STOP);
	::EnableWindow(hcontrol,false);
	return 0;
}
