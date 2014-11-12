#if !defined(AFX_GLWIND_H__70917604_28C0_11D4_911D_0000E83D722B__INCLUDED_)
#define AFX_GLWIND_H__70917604_28C0_11D4_911D_0000E83D722B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GLWind.h : header file
//

#include "..\gl10\gl10c12.h"
#include "..\gl10\gl10c5.h"
//#include "3dsftk.h"

// dimensiones de la mesa en la que estaran las fichas
#define MESA_DX		60
#define	MESA_DY		90
#define MESA_MINX	-20
#define MESA_MINY	-50
#define MESA_MINZ	0
#define MESA_DZ		30
// cada cuantos ptos se mueve un centimetro
#define MX			10
#define MY			10
#define MZ			15

/////////////////////////////////////////////////////////////////////////////
// CGLWind window

class CGLWind : public CMemDCView
{
// Construction
public:
	CGLWind();

// Attributes
public:
	float ang;
	CEscena	m_Escena;
	float CurX,CurY,CurZ;
	POINT	pt;
	BOOL	OnLDown,OnRDown;
	double m_Ang[3];
	double m_LastAng[3];
	// Hay que almacenar la ultima posicion de la ficha
	float	lastx,lasty,lastz;
	// hay que almacenar la ultima posicion valida de la ficha
	float	lastcx,lastcy,lastcz;
	BOOL	OnCoord;
	BOOL	OnEraseBackground;
	int		LineStipple;
	CPtrList	Points;
	// Angulos del robot
	float	RobLastAng[4];
	float	RobAng[4];
	float	RobTable[4];
	float	RobDAng[4];
	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGLWind)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL IsMoving();
	int CalcAng();
	int DeleteLastPoint();
	int EraseBackground(BOOL state);
	int ClearAllPoints();
	int NewPoint();
	int OnInvalidPoint();
	int GetFichas(struct coord *fich, char cant);
	int ReadCoord();
	CEscena* GetEscena();
	int OpenFile(char* file);
	int MouseUp();
	virtual int RenderDC(CDC *dc);
	virtual ~CGLWind();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGLWind)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GLWIND_H__70917604_28C0_11D4_911D_0000E83D722B__INCLUDED_)
