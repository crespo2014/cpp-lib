#if !defined(AFX_VIDEOLEVEL1_H__B4088AE2_B88B_11D3_A036_0000E8DE4B3B__INCLUDED_)
#define AFX_VIDEOLEVEL1_H__B4088AE2_B88B_11D3_A036_0000E8DE4B3B__INCLUDED_

#include "video.h"
#include "struct.h"
#include "joystick.h"
#include "glfont.h"

#include "..\lfc10\lfc10c03.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VideoLevel1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVideoLevel1 window

class CVideoLevel1 : public CVideo
{
// Construction
public:
	CVideoLevel1();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVideoLevel1)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	int SetDevice(CSignalDevice* pDevice);
	int InitGame();
	int MoveObjects();
	int GenGLList();
	int CheckColision();
	int NewFire();
	FireParams   m_FireData[10];
	GameParams   m_GameParams;
	ObjectParams m_ObjectParams[10];
	BOOL m_OnDevice;
	CJoystick m_Joystick;
	CSignalDevice* m_LPDevice;
	HCURSOR m_hCursor;
	int i,j;
	BOOL m_Dir;
	SYSTEMTIME m_Time,m_TimeLast;
	char cadena1[50];
	char cadena2[50];
	CGLFont m_font;
	BYTE m_FPS;
	BYTE m_FPSLast;
	int m_Key;
	CGLBmp m_GLBmp;
	// Caracteristicas del grafico
	double m_GrafMinZ;
	double m_GrafMaxZ;
	double m_GrafMinY;
	double m_GrafMaxY;
	double m_GrafMaxX;
	double m_GrafMinX;
	double m_MouseX;
	double m_MouseY;
	double m_angX;
	double m_dangX;

	virtual int InitView(BOOL pOnSize);
	virtual int RenderScene();
	virtual int ThreadProcessMessages();
	virtual ~CVideoLevel1();

	// Generated message map functions
protected:
	//{{AFX_MSG(CVideoLevel1)
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIDEOLEVEL1_H__B4088AE2_B88B_11D3_A036_0000E8DE4B3B__INCLUDED_)
