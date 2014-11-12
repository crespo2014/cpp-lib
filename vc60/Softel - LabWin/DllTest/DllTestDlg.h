// DllTestDlg.h : header file
//

#if !defined(AFX_DLLTESTDLG_H__6CAEC38E_6A53_449B_BA5F_57B9ECB67DAF__INCLUDED_)
#define AFX_DLLTESTDLG_H__6CAEC38E_6A53_449B_BA5F_57B9ECB67DAF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\interfaces\Ilabdevice.h"

/////////////////////////////////////////////////////////////////////////////
// CDllTestDlg dialog

class CDllTestDlg : public CDialog
{
// Construction
public:
	CDllTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDllTestDlg)
	enum { IDD = IDD_DLLTEST_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDllTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	ILabDevice* m_LabDevice;

	// Generated message map functions
	//{{AFX_MSG(CDllTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLLTESTDLG_H__6CAEC38E_6A53_449B_BA5F_57B9ECB67DAF__INCLUDED_)
