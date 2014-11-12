#if !defined(AFX_CLASS4_H__A19EB524_DE27_11D3_A036_0000E83D722B__INCLUDED_)
#define AFX_CLASS4_H__A19EB524_DE27_11D3_A036_0000E83D722B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// class4.h : header file
//

typedef struct
{
	HGLRC					m_hGLRC;
	HDC						m_hDC;
	HPALETTE				m_hPalette;
	PIXELFORMATDESCRIPTOR	m_PFD;
	int						m_PFI;
} S_GLView;
/////////////////////////////////////////////////////////////////////////////
// CGLView window


class AFX_EXT_CLASS CGLView : public CWnd
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
	int Init();
	HDC GetViewDC();
	virtual int InitView(BOOL pOnSize, int pWidth, int pHeight);
	virtual int RenderScene();
	int SetupPF();
	int SetupPalette();
	int CreateRC();
	virtual ~CGLView();

	// Generated message map functions
protected:
	S_GLView* m_Params;

	//{{AFX_MSG(CGLView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLASS4_H__A19EB524_DE27_11D3_A036_0000E83D722B__INCLUDED_)
