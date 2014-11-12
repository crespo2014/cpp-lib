// BinaryWnd.h: interface for the CBinaryWnd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BINARYWND_H__42E8BE37_040D_4A03_847A_47D179B47C4C__INCLUDED_)
#define AFX_BINARYWND_H__42E8BE37_040D_4A03_847A_47D179B47C4C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "virtualmemory.h"
#include "Wind.h"



#define SPC0	5	// Posicion de la dirección
#define SPC1	2	// cantidad de espacios entre direccion y primer valor
#define SPC2	1	// Cantidad de espacios que acompañan un byte
#define SPC3	1	// Cantidad de espacios entre el ultimo byte y el primer ascii

// banderas que contiene flags
#define ON_HI_CHAR	2	// Indica si el caracter escrito es el segundo es decir parte alta del numero
#define ON_ASCII_CARET	4	// Indica que el caret se encuentra en la parte de los ascii

DWORD RegisterBinaryWnd();

class CBinaryWnd : public CWind, public CVirtualMemory 
{
public:
	DWORD GetWindowMetrics(WINDOW_METRICS* lpwindowmetrics);
	DWORD MakeIndexVisible(DWORD dwIndex);

	void UpdateScrolls();
	DWORD MoveCaret(DWORD dwIndex);
	DWORD UpdateCaret();
	DWORD SetCursor(long lx,long ly);
	DWORD PosToIndex(long lx,long ly,DWORD* lpdwIndex);
	DWORD IndexToCursor( DWORD Index,DWORD* lpdwx, DWORD* lpdwy);
	DWORD OnLButtonDown(WPARAM wParam, LPARAM lParam);
	DWORD OnKillFocus();
	DWORD OnSetFocus();
	DWORD OnCreate();
	DWORD Initialize();
	// Windows Messages
	LRESULT Paint();
	LRESULT OnMouseMove(WPARAM wParam, LPARAM lParam);
	LRESULT OnSetCursor(WPARAM wParam, LPARAM lParam);
	LRESULT OnChar(WPARAM wParam, LPARAM lParam);
	LRESULT OnKeyDown(WPARAM wParam, LPARAM lParam);
	LRESULT OnVerticalScroll(WPARAM wParam, LPARAM lParam);
	LRESULT OnSize(WPARAM wParam, LPARAM lParam);
	
	virtual LRESULT WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
	CBinaryWnd();
	virtual ~CBinaryWnd();
private:
	HFONT	m_hFont;		
	
	// cosas que tienen que ver con la vista
	DWORD	m_topIndex;		// Posicion del primer valor que se muestra en pantalla
	DWORD	m_selStart;		// Texto seleccionado
	DWORD	m_selEnd;
	DWORD	m_CareIndex;	// Posicion del Caret

	// Medidas de las letras.
	long	m_fontHeight;
	long	m_fontWidth;
	DWORD	m_bpr;			// bytes per rows (Bytes en cada fila)

	DWORD	m_flags;		// bandera de uso general
public:
	DWORD Create_Window(int x,int y,int nWidth,int nHeight,HWND hWndParent);
};

#endif // !defined(AFX_BINARYWND_H__42E8BE37_040D_4A03_847A_47D179B47C4C__INCLUDED_)
