// SockAppDlg.h : header file
//

#if !defined(AFX_SOCKAPPDLG_H__943DEB8B_33D3_4281_891C_70AFC4EFFCAD__INCLUDED_)
#define AFX_SOCKAPPDLG_H__943DEB8B_33D3_4281_891C_70AFC4EFFCAD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSockAppDlg dialog

class CSockAppDlg : public CDialog
{
// Construction
public:
	CSockAppDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSockAppDlg)
	enum { IDD = IDD_SOCKAPP_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSockAppDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSockAppDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOCKAPPDLG_H__943DEB8B_33D3_4281_891C_70AFC4EFFCAD__INCLUDED_)
