// Wind.h: interface for the CWind class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WIND_H__720DE771_250F_41EE_B6B8_291C45843235__INCLUDED_)
#define AFX_WIND_H__720DE771_250F_41EE_B6B8_291C45843235__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

const char CWindClassName[]= "Wind";
DWORD RegisterCWind();

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
public:
	DWORD Invalidate();
	CWind();
	virtual ~CWind();
	virtual LRESULT WndProc(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam)=0;
protected:
	DWORD Create(LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam);
protected:
	HWND m_hwnd;
private:
	LPVOID	m_lpParam;
};

#endif // !defined(AFX_WIND_H__720DE771_250F_41EE_B6B8_291C45843235__INCLUDED_)
