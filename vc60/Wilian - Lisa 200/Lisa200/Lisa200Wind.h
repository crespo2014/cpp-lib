// Lisa200Wind.h: interface for the CLisa200Wind class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISA200WIND_H__2CA2C04F_4CF8_498D_B84F_987DB5153B81__INCLUDED_)
#define AFX_LISA200WIND_H__2CA2C04F_4CF8_498D_B84F_987DB5153B81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\CLASES\Wind.h"
#include "..\clases\common.h"
#include "Lisa2000server.h"

typedef struct
{
	BYTE	port1;
	BYTE	port2;
	BOOL	BridgeAutoStart;
	BOOL	ServerAutoStart;
	BOOL	CanChangeBridge;	// Cambiar los puertos del puente
	BOOL	CanChangeServerPort;		// Cambiar el puerto del servidor
	BOOL	CanSSBridge;		// Iniciar detener el puente
	BOOL	CanSSServer;		// Iniciar detener el servidor
	PORT_CONFIG port_cnf;
	unsigned short	serverport;

}LISA_CONF;

class CLisa200Wind : public CWind,
					 public CLisa2000Server,
							 IIniFile
{
public:
	DWORD StopBridge();
	DWORD StartServer();
	LRESULT StartBridge();
	DWORD RefreshDlg();
	DWORD UpdateDlg();
	DWORD InitializeDlg();
	DWORD EndSession(WPARAM wParam, LPARAM lParam);
	DWORD QueryEndSession(WPARAM wParam, LPARAM lParam);
	DWORD HideShellIcon();
	DWORD ProcessTaskBarMessage(WPARAM wParam, LPARAM lParam);
	DWORD ShowShellIcon();
	DWORD ApplyConfiguration(LISA_CONF* cnf);
	DWORD SaveConfiguration(LISA_CONF* cnf);
	virtual DWORD _stdcall OnProcessParam(char* name,double val,void* lpParam);
	DWORD LoadConfiguration();
	DWORD LoadResults();
	static INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	virtual LRESULT  WndProc(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam);
	DWORD Create_Window();
	CLisa200Wind();
	virtual ~CLisa200Wind();
private:
	HWND m_hDlg;
	BOOL m_CanChangeBridge;	// Cambiar los puertos del puente
	BOOL m_CanChangeServerPort;	// Cambiar el puerto del servidor
	BOOL m_CanSSBridge;		// Iniciar detener el puente
	BOOL m_CanSSServer;		// Iniciar detener el servidor
};

#endif // !defined(AFX_LISA200WIND_H__2CA2C04F_4CF8_498D_B84F_987DB5153B81__INCLUDED_)
