// StartViewWind.cpp: implementation of the CStartViewWind class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StartViewWind.h"
#include "errorcodes.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define SVW_MAINWIND_ID	2000	//ventana principal
#define SVW_BTN_ACT_ID	2001	// actualizar cartas

CStartViewWind::CStartViewWind()
{
	ZeroMemory(&m_gui,sizeof(m_gui));
	m_gui.ctrls = m_gui_ctrls;
}

CStartViewWind::~CStartViewWind()
{

}

LRESULT _stdcall CStartViewWind::OnWindProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (hWnd == *this)
	{
		switch(uMsg)
		{
			//case WM_ERASEBKGND	: return OnEraseBkgnd((HDC)wParam);
			case WM_COMMAND: return OnCommand(HIWORD(wParam),LOWORD(wParam),(HWND)lParam);
		}
		return OnDefWindowProc(uMsg,wParam,lParam);
	}
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

DWORD CStartViewWind::Initialize()
{
	DWORD dr;
	do
	{
		dr = db_GetGuiFromResource("cartas_start_gui",&m_gui);
		if (dr != ERR_NONE) break;
		dr = m_CartasPropWind.Initialize();
		if (dr != ERR_NONE) break;
	}while(false);
	return dr;
}

DWORD _stdcall CStartViewWind::OnInitView()
{
	HWND hButton = ::GetDlgItem(*this,SVW_BTN_ACT_ID);
	::SetFocus(hButton);
	return 0;
}

DWORD _stdcall CStartViewWind::Hide()
{
	::ShowWindow(*this,SW_HIDE);
	return 0;
}

DWORD _stdcall CStartViewWind::OnCreateCtrl(DWORD dwCtrlIndex)
{
	switch (m_gui_ctrls[dwCtrlIndex].id)
	{
	case SVW_MAINWIND_ID:
		{
			CreateEx(NULL,m_gui_ctrls[dwCtrlIndex].style,m_gui_ctrls[dwCtrlIndex].exstyle,m_gui_ctrls[dwCtrlIndex].x,m_gui_ctrls[dwCtrlIndex].y,m_gui_ctrls[dwCtrlIndex].width,m_gui_ctrls[dwCtrlIndex].height,m_hParent,(HMENU)m_gui_ctrls[dwCtrlIndex].id,m_gui_ctrls[dwCtrlIndex].lpvoid);
			m_gui_ctrls[dwCtrlIndex].hwnd = *this;
			break;
		}
	}
	return 0;
}

DWORD _stdcall CStartViewWind::OnChildViewClose()
{
	::SendMessage(m_hParent,UM_SETCONTENT,(WPARAM)(IdbView*)this,NULL);
	return 0;
}

DWORD _stdcall CStartViewWind::GetGui(DBGUI** dbgui)
{
	*dbgui = &m_gui;
	return 0;
}

DWORD CStartViewWind::Show(HWND hWndParent)
{
	m_hParent = hWndParent;
	::SendMessage(hWndParent,UM_SETCONTENT,(WPARAM)(IdbView*)this,NULL);
	return 0;
}

LRESULT CStartViewWind::OnCommand(WORD wCode, WORD wId, HWND hWind)
{
	switch(wCode)
	{
	case BN_CLICKED : return OnButtonClicked(wId,hWind);
	}
	return 0;
}

LRESULT CStartViewWind::OnButtonClicked(WORD wButtonId, HWND hButton)
{
	switch(wButtonId)
	{
	case SVW_BTN_ACT_ID: return OnActualizarCartas();
	case IDCANCEL:
	case IDOK:	return 0;
	}
	return 0;
}

LRESULT CStartViewWind::OnActualizarCartas()
{
	m_CartasPropWind.ActualizarCartas(this,m_hParent);
	return 0;
}
