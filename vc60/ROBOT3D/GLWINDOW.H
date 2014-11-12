// GLWindow.h: interface for the CGLWindow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLWINDOW_H__A913EC82_41CE_11D3_A264_0000E856599A__INCLUDED_)
#define AFX_GLWINDOW_H__A913EC82_41CE_11D3_A264_0000E856599A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Formas.h"

class  CGLWindow : public CWnd  
{
public:
	CGLWindow();
	virtual ~CGLWindow();

protected:

	BOOL SetWindowPixelFormat(HDC hDC);
	BOOL CreateViewGLContext(HDC hDC);
	void RenderScene();
		
	int m_GLPixelIndex;

public:
	virtual void PaintNow();
	void SetMouse(BOOL estado);

	// Si este miembro es true el movimieento es relativo
	// a la posicion del click y no se usa timer, solo se
	// chequea con MouseMove
	BOOL m_OnRel;
	// Si este miembro es true la camara es sensible al mouse
	// sino la sensibilidad es del robot
	BOOL m_OnMoveCamera;

	// Estado de las teclas del mouse
	BOOL m_On_RButton;
	BOOL m_On_LButton;
	// Punto en el cual se toco el mouse
	CPoint m_RPoint;

	// Incremento en las coordenadas del cursor
	CSize m_dCursor;

	BOOL OnCapture;
	void EndTimer();
	void BeginTimer();
	int TimerID;
	BOOL TimerOn;
	// Indica que el timer esta activo y se esta rotanto
	// o moviendo la figura, si el mouse se mueve con el timer 
	// activo, su coordenada es usada para el calculo del incremento
	// de lo contrario es usada para seleccionar el cursor
	BOOL OnBegin;
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void SizeSetup();
	float	m_lpx;
	float	m_lpy;
	float	m_lpz;
	HCURSOR HCursor[20];

protected:
	HGLRC m_hGLContext;


protected:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct); 
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown( UINT nFlags, CPoint point );
	afx_msg void OnLButtonUp( UINT nFlags, CPoint point );
	afx_msg void OnMouseMove( UINT nFlags, CPoint point );
	afx_msg void OnRButtonDown( UINT nFlags, CPoint point );
	afx_msg void OnRButtonUp( UINT nFlags, CPoint point );
	afx_msg void OnTimer( UINT nIDEvent );
	
	DECLARE_MESSAGE_MAP()

public:
	virtual void Timer();
	virtual void MouseClick();
	// Usada para procesar movimiento del mouse
	virtual void MouseMoving();
	// posicion de la camara
	double Camara_posx;
	double Camara_posy;
	double Camara_posz;
	// giro que hace la camara con los ejes
	double Camara_angy;
	double Camara_angx;
	// punto hacia el cual mira la camara
	double Camara_tox;
	double Camara_toy;
	double Camara_toz;   //si es mas positivo esta mas cerca
	// distancia que la separa del pto de mira
	double Camara_dz;

private:
	// Si es true la camara se vuelve sensible al mouse
	BOOL OnCursor;
	// ajuste de los angulos de la camara 
	void CheckAng();
	// banderas usadas para el movimiento de camara
	BOOL OnAcercar;
	BOOL OnAlejar;
	BOOL OnDerecha;
	BOOL OnIzquierda;
	// ptos en los cuales se dio el click.
	CPoint Left_Point;

	// estado de las teclas del mouse
	BOOL Left_Button;

	// desplazamiento del cursor en x y en y
	double Cursor_dx;
	double Cursor_dy;

	// Indica el cursor a mostrarse esta variable es cambiada por
	// el evento MouseMove
	HCURSOR ActiveCursor;  

	// Ancho y alto de la ventana usadas para transferencia 
	// de datos
	int Width;
	int Height;
};

#endif // !defined(AFX_GLWINDOW_H__A913EC82_41CE_11D3_A264_0000E856599A__INCLUDED_)
