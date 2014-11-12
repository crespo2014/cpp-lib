// EditList.h: interface for the CEditList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EDITLIST_H__91B89B8E_480F_4748_B0E4_AED7C578AE10__INCLUDED_)
#define AFX_EDITLIST_H__91B89B8E_480F_4748_B0E4_AED7C578AE10__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Wind.h"
#include "correspodef.h"

struct EDTCELLINFO : RECT
{
	WORD	dbIndex;	// Elemento de base de datos
	DWORD	column;		// 0 o 1
	DWORD	row;		// 0 header 1-65535 rows mostrables
};

class CEditList : public CWind  
{
public:
	LRESULT OnNotify(int idCtrl,LPNMHDR pnmh);
	DWORD SetFirstRow(DWORD dwFirstRow);
	DWORD SetFocusRow(DWORD dwRow);
	DWORD DrawCells(DWORD StartRow,DWORD EndRow,EDTCELLINFO *cellinfo,HDC hdc);
	DWORD GetCellAt(DWORD dwRow,DWORD dwColumn, EDTCELLINFO* lpcellinfo);
	
	DWORD UpdateRowHeight(DWORD dbIndex);
	DWORD OnEndEditCell();
	DWORD OnEditCell(EDTCELLINFO* cellinfo);
	DWORD Refresh();
	DWORD Initialize();
	DWORD SetDBInterfaz(IDBClass* lpIDBClass);
	DWORD Create(int x, int y, int nWidth, int nHeight, HWND hWndParent);
	CEditList();
	virtual ~CEditList();
private:
	static LRESULT EditWndProc(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnSize(WPARAM wParam, LPARAM lParam);
	LRESULT OnLButtonDown(WPARAM wParam, WPARAM lParam);
	LRESULT OnLButtonUp(WPARAM wParam, WPARAM lParam);
	LRESULT OnCreate(CREATESTRUCT * lpCreateStruct);
	LRESULT OnEditWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnVScroll(WPARAM wParam);
	LRESULT OnCommand(WPARAM wParam, LPARAM lParam);
	DWORD CellFromPoint(short x, short y,EDTCELLINFO* cellinfo);
	DWORD GetFirstVisibleCell(EDTCELLINFO* cellinfo);
	DWORD GetNextVisibleCell(EDTCELLINFO *cellinfo);
	LRESULT OnPaint();
	virtual LRESULT WndProc(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam);
	IDBClass*	m_IDBClass;
	DWORD	m_RowCount;		// Actualizado cuando se invalida el alto de las filas
	WORD	m_FirstColumn;	// Primera columna visible
	DWORD	m_FirstRow;		// Primera posicion visible 1-65535
	WORD	m_FirstRowTop;	// Primer punto visile de la primera fila visible
	HFONT	m_hfont;
	HWND	m_hEdit;		// Edit de edicion de un elemento
	WORD	m_MouseStatus;
	WNDPROC	m_EditWndProc;
	BOOL	m_OnEditUpdate;	// Actualizar el elmento al perder el focus
	BOOL	m_OnEditNext;	// Editar el proximo elemento

	DWORD	m_FocusRow;

	// interfaz grafica
	BYTE	m_cellTopMargin;
	BYTE	m_cellRigthMargin;
	BYTE	m_cellBottomMargin;
	BYTE	m_cellLeftMargin;
	//
	BYTE	m_RightMargin;
	BYTE	m_LeftMargin;

	WORD	m_Column0Width;		// Ancho de la columna de caption
	BYTE	m_Row0Height;		// Alto de la columna 0 y de una columna simplelinea
};

#endif // !defined(AFX_EDITLIST_H__91B89B8E_480F_4748_B0E4_AED7C578AE10__INCLUDED_)
