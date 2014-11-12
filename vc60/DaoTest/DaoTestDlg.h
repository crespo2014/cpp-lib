// DaoTestDlg.h : header file
//

#if !defined(AFX_DAOTESTDLG_H__B87AFA67_71CC_11D2_8635_00D0093D4380__INCLUDED_)
#define AFX_DAOTESTDLG_H__B87AFA67_71CC_11D2_8635_00D0093D4380__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDaoTestDlg dialog

class CDaoTestDlg : public CDialog
{
// Construction
public:
	CDaoTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDaoTestDlg)
	enum { IDD = IDD_DAOTEST_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDaoTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CdbDBEngine		eng;
	CdbWorkspace	ws;
	CdbDatabase		db;
	CdbConnection	cn;

	// Generated message map functions
	//{{AFX_MSG(CDaoTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DAOTESTDLG_H__B87AFA67_71CC_11D2_8635_00D0093D4380__INCLUDED_)
