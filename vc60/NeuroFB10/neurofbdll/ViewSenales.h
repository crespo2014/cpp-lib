#if !defined(AFX_VIEWSENALES_H__3256D181_CB5B_11D4_9126_0000E83D722B__INCLUDED_)
#define AFX_VIEWSENALES_H__3256D181_CB5B_11D4_9126_0000E83D722B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewSenales.h : header file
//

#include "resource.h"
#include "..\lfc10\lfc10c04.h"
/////////////////////////////////////////////////////////////////////////////
// CViewSenales dialog

class CApp;

class CViewSenales : public CDialog
{
// Construction
public:
	CViewSenales(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CViewSenales)
//	enum { IDD = IDD_CLINICIANDISPLAY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewSenales)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CViewSenales)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	DWORD SetApp(CApp* pApp);
	CSignalWnd	Wnd;
	CApp*	m_app;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWSENALES_H__3256D181_CB5B_11D4_9126_0000E83D722B__INCLUDED_)
