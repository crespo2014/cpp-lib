// S25_8Dlg.h : header file
//

#if !defined(AFX_S25_8DLG_H__C014CBE7_7AD8_11D4_8632_00D0093D4380__INCLUDED_)
#define AFX_S25_8DLG_H__C014CBE7_7AD8_11D4_8632_00D0093D4380__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CS25_8Dlg dialog

#include "..\lfc10\lfc10c04.h"
#include "..\lfc10\lfc10c03.h"

class CS25_8Dlg : public CDialog
{
// Construction
public:
	CS25_8Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CS25_8Dlg)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CS25_8Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CSignalWnd	Wnd;
	// Generated message map functions
	//{{AFX_MSG(CS25_8Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_S25_8DLG_H__C014CBE7_7AD8_11D4_8632_00D0093D4380__INCLUDED_)
