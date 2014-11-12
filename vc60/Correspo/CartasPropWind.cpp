// CartasPropWind.cpp: implementation of the CCartasPropWind class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CartasPropWind.h"
#include "errorcodes.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define CPW_MAINWIND_ID			2000
#define CPW_EDT_EXPTE_ID		1002
#define CPW_EDT_NOMBRE_ID		1003
#define CPW_EDT_DIRECCION_ID	1004
#define CPW_EDT_SINDICATO_ID	1005
#define CPW_EDT_TEMA_ID			1006
#define CPW_CMB_PROVINCIA_ID	1007
#define CPW_EDT_SINTESIS_ID		1008
#define CPW_BTN_GUARDAR_ID		2001
#define CPW_BTN_NEXTCTRL_ID		2002

// Estados de la ventana
#define CPW_ST_UPDATING	1

CCartasPropWind::CCartasPropWind()
{
	ZeroMemory(&m_gui,sizeof(m_gui));
	m_gui.ctrls = m_gui_ctrls;
	m_carta.SetDatabase(&Correspodb);
	m_bOnExpteChange = false;
	m_bUpdating = false;
}

CCartasPropWind::~CCartasPropWind()
{

}

LRESULT _stdcall CCartasPropWind::OnWindProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (hWnd == *this)
	{
		switch(uMsg)
		{
			case WM_COMMAND :	return OnCommand(HIWORD(wParam),LOWORD(wParam),(HWND)lParam);			
		}
		return OnDefWindowProc(uMsg,wParam,lParam);
	}
	return ::DefWindowProc(hWnd,uMsg,wParam,lParam);
}

DWORD CCartasPropWind::Initialize()
{
	DWORD dr;
	dr = m_carta.Initialize();
	if (dr != ERR_NONE) return dr;
	dr = db_GetGuiFromResource("cartas_prop_gui",&m_gui);
	return dr;
}

DWORD _stdcall CCartasPropWind::OnInitView()
{
	if (m_status == CPW_ST_UPDATING)
	{
		(&m_carta)->Clear();
		UpdateData(true);
		EnableControls(false);
	}
	HWND hWind = ::GetDlgItem(*this,CPW_EDT_EXPTE_ID);
	::SetFocus(hWind);
	::SendMessage(*this,DM_SETDEFID,CPW_BTN_NEXTCTRL_ID,0);
	return 0;
}

DWORD _stdcall CCartasPropWind::OnChildViewClose()
{
	return 0;
}

DWORD _stdcall CCartasPropWind::OnCreateCtrl(DWORD dwCtrlIndex)
{
	DWORD		dr;
	IDBArray*	pIdbArray;
	switch (m_gui_ctrls[dwCtrlIndex].id)
	{
	case CPW_MAINWIND_ID:
		{
			CreateEx(NULL,m_gui_ctrls[dwCtrlIndex].style,m_gui_ctrls[dwCtrlIndex].exstyle,m_gui_ctrls[dwCtrlIndex].x,m_gui_ctrls[dwCtrlIndex].y,m_gui_ctrls[dwCtrlIndex].width,m_gui_ctrls[dwCtrlIndex].height,m_hParent,(HMENU)m_gui_ctrls[dwCtrlIndex].id,m_gui_ctrls[dwCtrlIndex].lpvoid);
			m_gui_ctrls[dwCtrlIndex].hwnd = *this;
			break;
		}
	case CPW_CMB_PROVINCIA_ID:
		{
			dr = m_cmbProvincia.CreateEx(NULL,m_gui_ctrls[dwCtrlIndex].style,m_gui_ctrls[dwCtrlIndex].exstyle,m_gui_ctrls[dwCtrlIndex].x,m_gui_ctrls[dwCtrlIndex].y,m_gui_ctrls[dwCtrlIndex].width,m_gui_ctrls[dwCtrlIndex].height,*this,(HMENU)m_gui_ctrls[dwCtrlIndex].id,m_gui_ctrls[dwCtrlIndex].lpvoid);
			if (dr != ERR_NONE) break;
			m_gui_ctrls[dwCtrlIndex].hwnd = m_cmbProvincia;
			Correspodb.LoadCatalogo(PROVINCIA_TINDEX,&pIdbArray);
			m_cmbProvincia.SetMemArray(pIdbArray);
			break;
		}
	}
	if (m_gui_ctrls[dwCtrlIndex].dbIndex)
		m_carta.InitializeControl(m_gui.ctrls[dwCtrlIndex].dbIndex,m_gui.ctrls[dwCtrlIndex].hwnd);	
	return 0;
}

DWORD _stdcall CCartasPropWind::GetGui(DBGUI** dbgui)
{
	*dbgui = &m_gui;
	return 0;
}

DWORD CCartasPropWind::Show(HWND hWndParent)
{
	m_hParent = hWndParent;
	::SendMessage(hWndParent,UM_SETCONTENT,(WPARAM)(IdbView*)this,NULL);
	return 0;
}

DWORD CCartasPropWind::ActualizarCartas(IdbView *pParentView,HWND hParentWind)
{
	m_status = CPW_ST_UPDATING; 
	m_pParentView = pParentView;
	m_hParent = hParentWind;
	::SendMessage(m_hParent,UM_SETCONTENT,(WPARAM)(IdbView*)this,NULL);
	return 0;
}

LRESULT CCartasPropWind::OnCommand(WORD wCode, WORD wId, HWND hWind)
{
	switch(wCode)
	{
	case BN_CLICKED : 
		{
			switch(wId)
			{
			case CPW_BTN_NEXTCTRL_ID: return OnNextID();
			case IDOK:
			case IDCANCEL: return 0;
			}
			break;
		}
	case EN_CHANGE:
		{
			switch(wId)
			{
			case CPW_EDT_EXPTE_ID:
				{
					// revisar si se han guardados los cambios realizados
					m_carta.Clear();
					UpdateData(true);
					m_bOnExpteChange = true;
					return EnableControls(false);
				}
			}
		}
	}
	return CWind::OnCommand(wCode,wId,hWind);
}

LRESULT CCartasPropWind::OnNextID()
{
	HWND	hwnd;
	DWORD	id,dr;
	WORD	index;
	hwnd = GetFocus();
	id = GetDlgCtrlID(hwnd);
	// buscar el control en la lista de controles
	dr = db_GetCtrlIndexFromID(id,&m_gui,&index);
	//if (dr != ERR_NONE) id = 0;
	switch (id)
	{
	case CPW_EDT_EXPTE_ID:
		{
			if (GetWindowTextLength(hwnd) == 0) return 0;
			if (!m_bOnExpteChange) break;
			dr = m_carta.SetValue(m_gui.ctrls[index].dbIndex,m_gui.ctrls[index].hwnd);
			dr = m_carta.LoadExpte();
			m_bOnExpteChange = false;
			UpdateData(true);
			EnableControls(true);
			break;
		}
	case CPW_BTN_GUARDAR_ID: return 0;
	}
	return ::PostMessage(*this,WM_NEXTDLGCTL,0,0);
}

DWORD CCartasPropWind::EnableControls(BOOL bEnable)
{
	HWND hWind;
	hWind = ::GetDlgItem(*this,CPW_EDT_NOMBRE_ID);
	::EnableWindow(hWind,bEnable);
	hWind = ::GetDlgItem(*this,CPW_EDT_DIRECCION_ID);
	::EnableWindow(hWind,bEnable);
	hWind = ::GetDlgItem(*this,CPW_EDT_SINDICATO_ID);
	::EnableWindow(hWind,bEnable);
	hWind = ::GetDlgItem(*this,CPW_EDT_TEMA_ID);
	::EnableWindow(hWind,bEnable);
	hWind = ::GetDlgItem(*this,CPW_CMB_PROVINCIA_ID);
	::EnableWindow(hWind,bEnable);
	hWind = ::GetDlgItem(*this,CPW_EDT_SINTESIS_ID);
	::EnableWindow(hWind,bEnable);
	return 0;
}

DWORD CCartasPropWind::UpdateData(BOOL bRead)
{
	DWORD i;
	for (i=0;i<m_gui.ctrlCount;i++)
	{
		if (m_gui.ctrls[i].dbIndex == 0) continue;
		if (m_gui.ctrls[i].id == CPW_EDT_EXPTE_ID) continue;
		if (bRead) 
			m_carta.GetValue(m_gui.ctrls[i].dbIndex,m_gui.ctrls[i].hwnd);
		else
			m_carta.SetValue(m_gui.ctrls[i].dbIndex,m_gui.ctrls[i].hwnd);
	}
	return 0;
}

// DLGC_BUTTON