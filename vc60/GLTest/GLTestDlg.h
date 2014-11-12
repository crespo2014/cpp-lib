// GLTestDlg.h : header file
//

#if !defined(AFX_GLTESTDLG_H__79E3A1D9_DD5B_11D3_A036_0000E83D722B__INCLUDED_)
#define AFX_GLTESTDLG_H__79E3A1D9_DD5B_11D3_A036_0000E83D722B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "glwind.h"
#include "..\gl10\gl10c7.h"
#include "..\gl10\gl10c12.h"

/////////////////////////////////////////////////////////////////////////////
// CGLTestDlg dialog

class CGLTestDlg : public CDialog
{
// Construction
public:
	CGLTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGLTestDlg)
	enum { IDD = IDD_GLTEST_DIALOG };
	CEscenaTree	m_Tree;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGLTestDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
	public:
		CGLWind m_Opengl;
		
// Implementation
protected:
	HICON m_hIcon;
	// Generated message map functions
	//{{AFX_MSG(CGLTestDlg)
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GLTESTDLG_H__79E3A1D9_DD5B_11D3_A036_0000E83D722B__INCLUDED_)
