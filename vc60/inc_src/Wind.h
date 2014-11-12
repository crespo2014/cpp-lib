// Wind.h: interface for the CWind class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WIND_H__720DE771_250F_41EE_B6B8_291C45843235__INCLUDED_)
#define AFX_WIND_H__720DE771_250F_41EE_B6B8_291C45843235__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define UM_SETCONTENT	WM_APP+1
#define UM_CLOSECONTENT	WM_APP+2
#define UM_GET_INTERFAZ	WM_APP+3	// wParam = (char*) interfazname lParam IUnknown**
#define UM_DESKTOP_SIZE	WM_APP+4
#define UM_CNOTIFY		WM_APP+5	// wParam = CNTFDATA* lParam = void*
#define UM_DELCONTENT	WM_APP+6
#define WM_LAST			WM_APP+200

#define CN_SETFOCUS		1	// Child Notify Set Focus
#define CN_KILLFOCUS	2	// Child Notify Kill Focus
#define CN_LAST			200

struct CNTFDATA	// Control notify data
{
	DWORD ctrlID;
	DWORD message;
	HWND hwnd;
};

/*
struct DLGMSG
{
	HWND hDlg;
	UINT message;
	WPARAM wParam;
	LPARAM lParam;
};
OnChildNotify(CNTFDATA pCNData,void* pvoid)
*/

typedef struct 
{
	DWORD WinHeight;
	DWORD WinWidth;
	DWORD WinRows;
	DWORD ScrollHeight;
	DWORD ScrollWidth;
	DWORD RowCount;		// Cantidad de filas de texto
	DWORD TopRow;		// Primera fila visible
} WINDOW_METRICS;

class CWind  
{
protected:
	LRESULT OnDefWindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnCommand(WORD wCode, WORD wId, HWND hWind);
	LRESULT OnEraseBkgnd(HDC hdc);
	LRESULT OnSetFocus(HWND hOldWnd);
	LRESULT OnMouseMove(UINT uFlags,WORD x,WORD y);
	LRESULT OnSetFont(HFONT hfont,BOOL bRedraw);
	LRESULT OnChildNotify(CNTFDATA* pCNData,void* pvoid);
	LRESULT OnEnable(BOOL bEnable);
public:
	DWORD GetPos(DWORD* pdwPos);
	DWORD SetPos(DWORD dwPos);
	DWORD DecPos(DWORD dwMinPos);
	DWORD SetPrevPtr(void* pvoid);
	LRESULT OnKillFocus();
	DWORD SetCapture();
	LRESULT OnDestroy();
	DWORD SetBackgroundColor(COLORREF crBckgndColor);
	DWORD CenterWindow();
	DWORD CreateEx(LPCTSTR lpWindowName, DWORD dwStyle,DWORD dwExStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu,LPVOID lpParam);
	DWORD Create(LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu,LPVOID lpParam);
	DWORD EnableWindow(BOOL bEnable);
	DWORD Invalidate();
	CWind();
	virtual ~CWind();
	virtual LRESULT _stdcall OnWindProc(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam)=0;
	operator HWND()  const {return m_hwnd;};
	HWND	m_hwnd;
	DWORD	m_Pos;		//Posicion dentro de la cola de ventanas
protected:
	HFONT	m_hFont;
	HWND	m_hNotifyWind;		// Ventana padre o de notificacion
	BOOL	m_bOnFocus;			// Indica si la ventana posee o no el focus
	BOOL	m_bEnable;			// Indica si la ventana esta habilitada o no
	BOOL	m_bCapture;			// Indica que se tiene la captura del mouse
	BOOL	m_bEraseBkgnd;		// Indica que el background debe borrarse
	HWND	m_hOldFocusWind;	// Ultima ventana hija que tenia el foco	
	COLORREF	m_BkgndColor;
private:
	LPVOID		m_lpParam;
	
};

const char CWindClassName[]= "Wind";
DWORD RegisterCWind();



#endif // !defined(AFX_WIND_H__720DE771_250F_41EE_B6B8_291C45843235__INCLUDED_)
