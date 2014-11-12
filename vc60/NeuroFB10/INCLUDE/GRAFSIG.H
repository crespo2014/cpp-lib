// GrafSig.h: interface for the CGrafSig class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAFSIG_H__85CD89C1_99D5_11D3_A036_0000E8DE4B3B__INCLUDED_)
#define AFX_GRAFSIG_H__85CD89C1_99D5_11D3_A036_0000E8DE4B3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OpenGl10.h"
#include "Device.h"
#include "GlNumber.h"
#include "GlString.h"

// Estructura usada para el intercambio de informacion con el hilo de graficacion
typedef struct GrafParams
{
	HANDLE m_hEvent1;
	HGLRC  m_GLContext;
	HDC    m_hDC;
	HCURSOR  m_CursorType;
	HWND   m_hWnd; 
public:
	CDevice* m_Device;
	
} GrafExchange;

// Estructura que almacena caracteristicas de graficos generales
typedef struct S_GrafData
{
	int     m_Version;
	WORD    m_Up,m_Down,m_Left,m_Right; // Margenes del grafico
	double  m_MaxValue,m_MinValue;      // Valores picos
	DWORD   m_Samples;                  // Muestras en la graficacion
	DWORD   m_First;                    // Primera muestra a graficar
	DWORD   m_BufferLength;             // Cantidad de datos almacenados
	double* m_Buffer;					// Buffer de muestras
	
} GrafData;

class CGrafSig : public COpenGl10  
{
public:
	LRESULT MyWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL PreTranslateMessage( MSG* pMsg );
	int StopSampling();
	int BeginSampling();
	int SetDevice(CDevice* pDevice);
	CDevice* m_Device;
	int Close();
	virtual int GlInit();
	CWinThread* m_RenderThread;
	GrafExchange m_ThreadData;
	int BeginPaint();
	CGrafSig();
	virtual ~CGrafSig();
protected:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd( CDC* pDC );
	afx_msg void OnDestroy();
	afx_msg BOOL OnSetCursor( CWnd* pWnd, UINT nHitTest, UINT message );
	afx_msg void OnLButtonDown( UINT nFlags, CPoint point );
	afx_msg void OnLButtonUp( UINT nFlags, CPoint point );
public:
	BOOL m_OnInit;
	HCURSOR m_hCursor;
	DECLARE_MESSAGE_MAP()
	
};

UINT GrafSignalThread(LPVOID pParam);

#endif // !defined(AFX_GRAFSIG_H__85CD89C1_99D5_11D3_A036_0000E8DE4B3B__INCLUDED_)
