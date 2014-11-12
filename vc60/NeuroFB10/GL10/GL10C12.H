 #if !defined(AFX_GL10C12_H__BC9C1FE1_FE55_11D3_BC3C_0000E8DE4B3B__INCLUDED_)
#define AFX_GL10C12_H__BC9C1FE1_FE55_11D3_BC3C_0000E8DE4B3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// gl10c12.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMemDCView window

#include "gl10c11.h"

typedef struct
{
	HGLRC					hrc;
	HPALETTE				hPalette;
	PIXELFORMATDESCRIPTOR	PFD;
	int						PFI;
	CMemDC					memdc;
	BOOL					autopaint;
} S_MEMDCVIEW;

class AFX_EXT_CLASS CMemDCView : public CWnd
{
// Construction
public:
	CMemDCView();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMemDCView)
	//}}AFX_VIRTUAL

// Implementation
public:
	CMemDC* GetMemDC();
	HGLRC GetRC();
	int SetAutoPaint(BOOL state);
	int SetupPalette();
	virtual int Init(BOOL pOnSize, int pWidth, int pHeight);
	virtual int RenderDC(CDC* dc);
	int CreateRC();
	int InitMemDCView();
	S_MEMDCVIEW* m_MemDCView;
	int SetupPixelFormat();
	virtual ~CMemDCView();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMemDCView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GL10C12_H__BC9C1FE1_FE55_11D3_BC3C_0000E8DE4B3B__INCLUDED_)
