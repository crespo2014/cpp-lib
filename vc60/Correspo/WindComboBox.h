// WindComboBox.h: interface for the CWindComboBox class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINDCOMBOBOX_H__904FC7D2_8B96_4E96_ABC4_2CA96A29C48C__INCLUDED_)
#define AFX_WINDCOMBOBOX_H__904FC7D2_8B96_4E96_ABC4_2CA96A29C48C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Wind.h"
#include "memarray.h"
#include "windGrid.h"	// Added by ClassView

#define CB_GETIDSEL		WM_LAST+1	// Obtener el ID seleccionado
#define CB_SETDBINDEX	WM_LAST+2	// Poner los dbIndex del combobox wParam IDdbIndex, lParam VisibledbIndex
#define CB_SETIDSEL		WM_LAST+3	// Seleccionar un ID específico, wParam = ID
#define CB_SETROWSEL	WM_LAST+4	// Seleccionar una fila wParam = RowIndex

class CWindComboBox : public CWind  
{
	DWORD DrawButtom(HDC hdc);
	DWORD Draw(HDC hdc);
	LRESULT OnPaint();
	LRESULT _stdcall OnWindProc(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnLButtonDown(UINT nFlags,int x,int y);

	DWORD	m_VisibledbIndex;
	DWORD	m_IDdbIndex;
	DWORD	m_SelID;	// ID Seleccionado
	DWORD	m_SelRow;	// Fila Seleccionada
	DWORD	m_TrackChange;	// Ultimo cambio del memarray
	BOOL	m_bPushed;
	IDBArray* m_pIdbArray;
public:
	LRESULT OnGetDlgCode(MSG* pMsg);
	//LRESULT OnSetSelRow(DWORD dwRowIndex);
	DWORD OnSetSelID(DWORD dwSelID);
	DWORD UnPush();
	DWORD DrawItem(HDC hdc);
	DWORD SetRowSel(DWORD dwRowIndex);
	LRESULT OnChildNotify(CNTFDATA* pCNData,GNOTIFY* pgNotify);
	DWORD SetdbIndex(DWORD dwIDIndex,DWORD dwVisibleIndex);
	DWORD CheckTrackChange();
	LRESULT OnGetSelID(DWORD* lpdwSelID);
	LRESULT OnGetInterfaz(char* lpzsName,_IUnknown** lplpIUnknown);
	LRESULT OnLButtonUp(UINT nFlags, int x, int y);
	LRESULT OnMouseMove(UINT nFlags, int x, int y);
	
	CWindGrid m_grid;
	DWORD SetMemArray(IDBArray* pIdbArray);
	CWindComboBox();
	virtual ~CWindComboBox();
private:
	BOOL	m_bDropDown;
};

#endif // !defined(AFX_WINDCOMBOBOX_H__904FC7D2_8B96_4E96_ABC4_2CA96A29C48C__INCLUDED_)
