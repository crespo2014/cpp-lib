// ProgDlg.h : header file
//

#if !defined(AFX_PROGDLG_H__8FC3CE3B_AEEE_11D3_A036_0000E8DE4B3B__INCLUDED_)
#define AFX_PROGDLG_H__8FC3CE3B_AEEE_11D3_A036_0000E8DE4B3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\g3d\GamDlg.h"
#include "..\g3d\video.h"
#include "..\G_01\G_01C06.h"

/////////////////////////////////////////////////////////////////////////////
// CProgDlg dialog

class CProgDlg : public CDialog
{
// Construction
public:
	CGamDlg		m_GamDlg;
	C3DViewGame	Game;
	CProgDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CProgDlg)
	enum { IDD = IDD_PROG_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CProgDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGDLG_H__8FC3CE3B_AEEE_11D3_A036_0000E8DE4B3B__INCLUDED_)
