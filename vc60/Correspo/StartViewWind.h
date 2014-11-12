// StartViewWind.h: interface for the CStartViewWind class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STARTVIEWWIND_H__34DDB0E2_8859_42C6_8EF7_B1EC74C33601__INCLUDED_)
#define AFX_STARTVIEWWIND_H__34DDB0E2_8859_42C6_8EF7_B1EC74C33601__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Wind.h"
#include "dbcommon.h"
#include "CartasPropWind.h"

class CStartViewWind : private CdbView  
{
	//
	virtual DWORD _stdcall OnInitView();
	virtual DWORD _stdcall OnCreateCtrl(DWORD dwCtrlIndex);
	virtual DWORD _stdcall GetGui(DBGUI** dbgui);
	virtual DWORD _stdcall OnChildViewClose();
	virtual DWORD _stdcall Hide();
	virtual LRESULT _stdcall OnWindProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	
	LRESULT OnActualizarCartas();
	LRESULT OnButtonClicked(WORD wButtonId,HWND hButton);
	LRESULT OnCommand(WORD wCode,WORD wId,HWND hWind);

	HWND		m_hParent;
	DBGUI		m_gui;
	DBGUI_CTRL	m_gui_ctrls[10];
	CCartasPropWind m_CartasPropWind;

public:
	DWORD Initialize();
	DWORD Show(HWND hWndParent);
	CStartViewWind();
	virtual ~CStartViewWind();
};

#endif // !defined(AFX_STARTVIEWWIND_H__34DDB0E2_8859_42C6_8EF7_B1EC74C33601__INCLUDED_)
