// serverDlg.h : header file
//

#if !defined(AFX_SERVERDLG_H__DBA9C407_3E9D_11D3_9261_000021B01127__INCLUDED_)
#define AFX_SERVERDLG_H__DBA9C407_3E9D_11D3_9261_000021B01127__INCLUDED_
#define WM_SHOW WM_USER+5
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CServerDlg dialog

class CServerDlg : public CDialog
{
// Construction
public:
	bool one;
	
	CServerDlg(CWnd* pParent = NULL);	// standard constructor
    bool on;
// Dialog Data
	//{{AFX_DATA(CServerDlg)
	enum { IDD = IDD_SERVER_DIALOG };
	
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
    
	// Generated message map functions
	//{{AFX_MSG(CServerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDriveroff();
	afx_msg void OnDriveron();
	afx_msg void OnSend();
	afx_msg void OnChat();
	afx_msg void OnFinishChat();
	afx_msg void OnSettings();
	afx_msg void OnFinishVideo();
	//}}AFX_MSG
	afx_msg LRESULT OnShow(WPARAM wParam,LPARAM lParam); 
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVERDLG_H__DBA9C407_3E9D_11D3_9261_000021B01127__INCLUDED_)
