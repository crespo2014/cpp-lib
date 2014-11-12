 #if !defined(AFX_GL10C13_H__670B76E1_0254_11D4_9118_0000E83D722B__INCLUDED_)
#define AFX_GL10C13_H__670B76E1_0254_11D4_9118_0000E83D722B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// gl10c13.h : header file
//

#include "gl10c11.h"
/////////////////////////////////////////////////////////////////////////////
// CGraphWnd window
typedef struct
{
	CMemDC	memdc;
} S_GRAPHWND;

class CGraphWnd : public CWnd
{
// Construction
public:
	CGraphWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	int InitGraphWnd();
	S_GRAPHWND* m_GraphWnd;
	virtual ~CGraphWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGraphWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GL10C13_H__670B76E1_0254_11D4_9118_0000E83D722B__INCLUDED_)
