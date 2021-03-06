#if !defined(AFX_GLVIEW_H__7C338943_A1D3_11D3_A036_0000E8DE4B3B__INCLUDED_)
#define AFX_GLVIEW_H__7C338943_A1D3_11D3_A036_0000E8DE4B3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// glview.h : header file
//

#define UM_ACK       (WM_USER+1)
#define UM_BEGINGAME (WM_USER+2)

/////////////////////////////////////////////////////////////////////////////
// CGLView window

#include "glnumber.h"
#include "glbmp.h"
#include "glstring.h"

class CGLView : public CWnd
{
// Construction
public:
	CGLView();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGLView)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	int m_PFI;
	virtual int Init();
	int CreateRC();
	HPALETTE m_hPalette;
	PIXELFORMATDESCRIPTOR m_PFD;
	int SetupPalette();
	int SetupPF();
	HGLRC m_hGLRC;
	HDC m_hDC;
	virtual ~CGLView();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGLView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg BOOL OnQueryNewPalette();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GLVIEW_H__7C338943_A1D3_11D3_A036_0000E8DE4B3B__INCLUDED_)
