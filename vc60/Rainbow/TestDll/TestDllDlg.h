// TestDllDlg.h : header file
//

#if !defined(AFX_TESTDLLDLG_H__694FCC8C_EC47_492E_A557_0868365D4A08__INCLUDED_)
#define AFX_TESTDLLDLG_H__694FCC8C_EC47_492E_A557_0868365D4A08__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestDllDlg dialog

#include "..\include\spromeps.h"


typedef WORD _stdcall _RNBOsproInitialize(void*);


class CTestDllDlg : public CDialog
{
// Construction
public:
	CTestDllDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestDllDlg)
	enum { IDD = IDD_TESTDLL_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDllDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestDllDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDLLDLG_H__694FCC8C_EC47_492E_A557_0868365D4A08__INCLUDED_)
