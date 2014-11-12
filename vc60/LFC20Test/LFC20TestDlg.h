// LFC20TestDlg.h : header file
//

#if !defined(AFX_LFC20TESTDLG_H__FFB7F78E_D3A8_11D4_8637_00D0093D4380__INCLUDED_)
#define AFX_LFC20TESTDLG_H__FFB7F78E_D3A8_11D4_8637_00D0093D4380__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include  "..\lfc20\lfc20c01.h"

/////////////////////////////////////////////////////////////////////////////
// CLFC20TestDlg dialog

class CLFC20TestDlg : public CDialog
{
// Construction
public:
	DWORD Test();
	CLFC20TestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CLFC20TestDlg)
	enum { IDD = IDD_LFC20TEST_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLFC20TestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CLFCWnd	m_Wnd;

	// Generated message map functions
	//{{AFX_MSG(CLFC20TestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LFC20TESTDLG_H__FFB7F78E_D3A8_11D4_8637_00D0093D4380__INCLUDED_)
