// CT10Dlg.h : header file
//

#if !defined(AFX_CT10DLG_H__2E837967_F4E6_11D3_BC3C_0000E8DE4B3B__INCLUDED_)
#define AFX_CT10DLG_H__2E837967_F4E6_11D3_BC3C_0000E8DE4B3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCT10Dlg dialog

class CCT10Dlg : public CDialog
{
// Construction
public:
	CCT10Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCT10Dlg)
	enum { IDD = IDD_CT10_DIALOG };
	CEdit	m_recbytesedit;
	CStatic	m_receivedbytescant;
	CStatic	m_sentbytes;
	CEdit	m_sentbytesedit;
	CEdit	m_sendedit;
	int		m_sendtoo;
	CString	m_sendmessage;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCT10Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCT10Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton5();
	afx_msg void OnButton2();
	afx_msg void OnButton4();
	afx_msg LRESULT OnData(WPARAM wParam,LPARAM lParam);
	afx_msg void OnSend();
	afx_msg void OnSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CT10DLG_H__2E837967_F4E6_11D3_BC3C_0000E8DE4B3B__INCLUDED_)
