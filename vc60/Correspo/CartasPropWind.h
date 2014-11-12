// CartasPropWind.h: interface for the CCartasPropWind class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CARTASPROPWIND_H__35D6C965_9939_4ABE_9D39_13A9A5875360__INCLUDED_)
#define AFX_CARTASPROPWIND_H__35D6C965_9939_4ABE_9D39_13A9A5875360__INCLUDED_

#include "WindComboBox.h"	// Added by ClassView
#include "dbCommon.h"
#include "Wind.h"
#include "carta.h"
#include "Correspodb.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCartasPropWind : private CdbView 
{
	//
	virtual DWORD _stdcall OnInitView();
	virtual DWORD _stdcall OnCreateCtrl(DWORD dwCtrlIndex);
	virtual DWORD _stdcall GetGui(DBGUI** dbgui);
	virtual DWORD _stdcall OnChildViewClose();
	virtual LRESULT _stdcall OnWindProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	
	HWND	m_hParent;
	DBGUI	m_gui;
	CCarta	m_carta;
	BYTE	m_status;
	BOOL	m_bOnExpteChange;	//Indica un expediente valido
	BOOL	m_bUpdating;
	CWindComboBox	m_cmbProvincia;
	CWindComboBox	m_cmbMunicipio;
	DBGUI_CTRL		m_gui_ctrls[20];
	IdbView*		m_pParentView;
public:
	
	DWORD UpdateData(BOOL bRead);
	DWORD EnableControls(BOOL bEnable);
	LRESULT OnNextID();
	LRESULT OnCommand(WORD wCode, WORD wId, HWND hWind);
	DWORD ActualizarCartas(IdbView* pParentView,HWND hParentWind);
	DWORD Initialize();
	DWORD Show(HWND hWndParent);
	CCartasPropWind();
	virtual ~CCartasPropWind();
};

#endif // !defined(AFX_CARTASPROPWIND_H__35D6C965_9939_4ABE_9D39_13A9A5875360__INCLUDED_)
