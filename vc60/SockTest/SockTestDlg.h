// SockTestDlg.h : header file
//

#if !defined(AFX_SOCKTESTDLG_H__1637A146_ECA3_43F6_A193_FF6E830599E9__INCLUDED_)
#define AFX_SOCKTESTDLG_H__1637A146_ECA3_43F6_A193_FF6E830599E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "tcpipsocket.h"
#include "SockSvr.h"	// Added by ClassView
#include "BridgeSvr.h"	// Added by ClassView

/////////////////////////////////////////////////////////////////////////////
// CSockTestDlg dialog

class CSockTestDlg : public CDialog
{
// Construction
public:
	CBridgeSvr m_BridgeServ;
	//CSockSvr m_Server;
	CSockTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSockTestDlg)
	enum { IDD = IDD_SOCKTEST_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSockTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CTcpIpSocket m_Socket;

	// Generated message map functions
	//{{AFX_MSG(CSockTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnStartServer();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOCKTESTDLG_H__1637A146_ECA3_43F6_A193_FF6E830599E9__INCLUDED_)
