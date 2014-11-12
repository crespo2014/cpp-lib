// Lfc2p1Dlg.h : header file
//

#if !defined(AFX_LFC2P1DLG_H__BE46B5D9_FDB5_11D4_8D3A_00D0093D4380__INCLUDED_)
#define AFX_LFC2P1DLG_H__BE46B5D9_FDB5_11D4_8D3A_00D0093D4380__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\lfc2\lfc2c02.h"
/////////////////////////////////////////////////////////////////////////////
// CLfc2p1Dlg dialog

class CLfc2p1Dlg : public CDialog
{
// Construction
public:
	CLfc2p1Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CLfc2p1Dlg)
	enum { IDD = IDD_LFC2P1_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLfc2p1Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CShareSignalDevice	m_SSignalDevice;
	HANDLE	m_hevent;

	// Generated message map functions
	//{{AFX_MSG(CLfc2p1Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOpen();
	afx_msg void OnCreate();
	afx_msg void OnWait();
	afx_msg void OnSet();
	afx_msg void OnRun();
	afx_msg void OnBeep();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LFC2P1DLG_H__BE46B5D9_FDB5_11D4_8D3A_00D0093D4380__INCLUDED_)
