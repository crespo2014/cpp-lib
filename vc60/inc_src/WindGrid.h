// Grid.h: interface for the CWindGrid class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINDGRID_H__6AA7C5EA_6AEC_4764_B1BF_D5D3F8D5CE95__INCLUDED_)
#define AFX_WINDGRID_H__6AA7C5EA_6AEC_4764_B1BF_D5D3F8D5CE95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wind.h"
#include "DBCommon.h"
#include "memarray.h"

struct GCOLUMNINFO
{
	WORD	width;	// ancho de la columna incluyendo los bordes
	WORD	pos;	// orden de aparicion de las columnas 0 .. max
};		// Column info

struct GROWINFO
{
	DWORD	height;		// alto de la fila incluyendo los bordes
};

struct GCELL : RECT
{
	WORD	columnIndex;	//			"	"	"	"	"	"	"
	WORD	arrayIndex;		// 0 - MAX : Indice en el arreglo en memoria
	DWORD	rowIndex;		// 0 - MAX-1) : Rows -1 : Invalid 
	WORD	hiddenTop;		// Puntos no visibles
	WORD	hiddenRight;
	WORD	hiddenBottom;
	WORD	hiddenLeft;
	WORD	type;			// tipo de celda fixed, datos, etc
};

struct GNOTIFY
{
	DWORD	rowIndex;
	WORD	columnIndex;
};

#define G_MAXCOLUMN 50

// Mensajes 
#define GM_SHOWHEADER		WM_LAST+1	// wParam -> bShow 
#define GM_SHOWSCROLL		WM_LAST+2	// wParam = type	lParam = visibilidad
#define GM_DRAWALL			WM_LAST+3	// Dibuja todas las celdas incluyendo el header

#define GN_DBLCLK		CN_LAST+1		//  GNOTIFY* 
#define GN_HOTTRACK		CN_LAST+2
#define GN_SELCHANGE	CN_LAST+3

class CWindGrid : public CWind  
{
	DWORD Calc_EndY();
	DWORD GetVisibleColumn(WORD dwIndex,GCOLUMNINFO **lpgColumnInfo,WORD* lpdwArrayIndex);
	DWORD Calc_EndX();
	DWORD GetMousePos(int x,int y,GCELL* lpgcell,WORD* lpmousepos);
	DWORD OnMouseMove(UINT nFlags,int x, int y);
	DWORD CompareCells(GCELL* lpgcell1,GCELL* lpgcell2,WORD* colrel,WORD* rowrel);
	DWORD DrawCells(GCELL *startcell,GCELL *endcell,HDC hdc);
	DWORD SetStartX(DWORD dwStartX);
	DWORD GetCellRect(GCELL *lpgcell);
	DWORD GetFirstVisibleColumn(GCELL *lpgcell);
	DWORD GetFirstVisibleRow(GCELL *lpgcell);
	DWORD GetNextColumn(GCELL *lpgcell);
	DWORD GetNextRow(GCELL *lpgcell);
	DWORD Get1stVisibleDataColumn(GCELL *lpgcell);
	DWORD Get1stVisibleDataRow(GCELL *lpgcell);
	DWORD ShowScrolls();
	DWORD CalcCellsRect();
	DWORD Get1stVisibleDataCell(GCELL *lpgcell);
	DWORD UpdateMargins();
	DWORD SetStartY(DWORD dwStartY);
	DWORD SetFocus(GCELL* lpgcell);
	DWORD GetCellFromPoint(short x,short y,GCELL* lpgcell);
	DWORD UpdateRowHeight(DWORD dwRowIndex);
	DWORD GetNextVisibleCell(GCELL *lpgcell);
	DWORD GetFirstVisibleCell(GCELL* lpgcell);
	virtual LRESULT _stdcall OnWindProc(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnLButtonDown(UINT nFlags,int x,int y);
	LRESULT OnPaint();
	LRESULT OnVScroll(WPARAM wParam);
	LRESULT OnHScroll(WPARAM wParam);
	LRESULT OnCommand(WORD ctrlID,WORD  message,LPARAM lParam);
	LRESULT OnLButtonDblClk(UINT nFlags,int x,int y);
	LRESULT OnLButtonUp(UINT nFlags,int x,int y);
	LRESULT OnSize( UINT nType, int cx, int cy );
public:
	LRESULT OnSettingChange();
	DWORD ShowPopup(HWND hNotifyWind, WORD Height);
	LRESULT OnKillFocus(HWND hOldWind);
	LRESULT OnSetFont(HFONT hfont,BOOL bRedraw);
	DWORD UpdateTextHeight();
	DWORD ShowScrollBar(DWORD dwBar,BOOL bShow);
	LRESULT ShowHeader(BOOL bShow);
	DWORD GetExtraDataSize(WORD* lpdwRowExtraDataSize, WORD* lpdwColumnExtraDataSize);
	DWORD SetExtraDataOffset(WORD dwRowExtraDataOffset,WORD dwColumnExtraDataOffset);
	DWORD SetColumnWidth(WORD dwColumnIndex,WORD width);
	DWORD SetIdbClass(IDBClass* lpIdbClass);
	DWORD SetNotifyWind(HWND hwnd);
	CWindGrid();
	DWORD InvalidateData();
	DWORD GetSelRow(DWORD* dwRowIndex);
	DWORD Initialize();
	DWORD Create(DWORD dwStyle,DWORD dwExStyle,int x, int y, int nWidth, int nHeight,DWORD dwCtrlID,HWND hWndParent);
	DWORD SetDBArray(IDBArray* lpIDBArray);
	virtual ~CWindGrid();

private:
//	HFONT	m_hfont;
	WORD	m_ColumnDataOffset;	// Offset de los datos extras de la columna
	WORD	m_RowDataOffset;
	DWORD	m_FocusRow;
	WORD	m_FocusColumn;
	IDBArray*	m_IDBArray;
	IDBClass*	m_IdbClass;
	WORD	m_VColumnCount;		// Cantidad de columnas visibles

	// GUI
	WORD	m_MouseMode;		// Estado del mouse
	WORD	m_HeaderHeight;		// Alto de header
	BOOL	m_OnUpdateHeights;	// Ya se calculo el alto de las filas
	BOOL	m_OnVScroll;
	BOOL	m_OnHScroll;
	BOOL	m_bShowHeader;
	BOOL	m_bOnPopupMode;
	BOOL	m_bShowVScroll;		// Indica si debe o no mostrar los scrolls
	BOOL	m_bShowHScroll;
	HWND	m_hNotifyWind;
	WORD	m_ViewMode;
	WORD	m_TextHeight;
	BOOL	m_bOnVertLine;		// Linea vertical
	BOOL	m_bOnHorzLine;		// Linea horizontal

	WORD	m_ScrollWidth;		// Dimensiones del scroll
	WORD	m_ScrollHeight;
	HWND	m_hHorScroll;		// Scroll windows handle
	HWND	m_hVerScroll;
	WORD	m_VerScrollMode;	// Modo de scroll
	WORD	m_HorScrollMode;
	DWORD	m_StartX;			// Posicion visible
	DWORD	m_StartY;			// Posicion o columna de inicio
	DWORD	m_EndY;
	DWORD	m_EndX;				// 
	WORD	m_RowHeight;
	
	RECT	m_cellMargin;		// Margen de una celda
	RECT	m_winMargin;		// Margen de las celdas y el header
	RECT	m_clientrect;		// Dimensiones de la ventana
	RECT	m_textMargin;		// Margen del texto
	
	RECT	m_cellsrect;		// Rectangulo donde van las celdas de dato

	int		m_mouselastx,m_mouselasty;		// Ultimo punto por el cual paso el mouse
	int		m_mousestartx,m_mousestarty;	// Punto en el que se inicio el arrastre
	GCELL	m_mousestartcell;

};

#endif // !defined(AFX_GRID_H__6AA7C5EA_6AEC_4764_B1BF_D5D3F8D5CE95__INCLUDED_)
