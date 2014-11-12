// Lisa200TestDlg.h : header file
//

#if !defined(AFX_LISA200TESTDLG_H__67442525_3DB8_413E_B38C_67E1BE246D4A__INCLUDED_)
#define AFX_LISA200TESTDLG_H__67442525_3DB8_413E_B38C_67E1BE246D4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CLisa200TestDlg dialog

class CLisa200TestDlg : public CDialog
{
// Construction
public:
	CLisa200TestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CLisa200TestDlg)
	enum { IDD = IDD_LISA200TEST_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLisa200TestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CLisa200TestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnConnect();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISA200TESTDLG_H__67442525_3DB8_413E_B38C_67E1BE246D4A__INCLUDED_)
