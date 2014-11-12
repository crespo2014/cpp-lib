#if !defined(AFX_SIGDLG_H__8FC3CE34_AEEE_11D3_A036_0000E8DE4B3B__INCLUDED_)
#define AFX_SIGDLG_H__8FC3CE34_AEEE_11D3_A036_0000E8DE4B3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SigDlg.h : header file
//

#include "resource.h"
#include "..\Signal\grafsig.h"

/////////////////////////////////////////////////////////////////////////////
// CSigDlg dialog

class AFX_EXT_CLASS CSigDlg : public CDialog
{
// Construction
public:
	
	CGrafSig GrafSig;
	CDevice Device;
	CSigDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSigDlg)
	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSigDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSigDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIGDLG_H__8FC3CE34_AEEE_11D3_A036_0000E8DE4B3B__INCLUDED_)
