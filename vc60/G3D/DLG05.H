#if !defined(AFX_DLG05_H__2CFDA624_AFAD_11D3_A036_0000E8DE4B3B__INCLUDED_)
#define AFX_DLG05_H__2CFDA624_AFAD_11D3_A036_0000E8DE4B3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg05.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlg05 dialog

#include "resource.h"

class CDlg05 : public CDialog
{
// Construction
public:
	CDlg05(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlg05)
	enum { IDD = IDD_G3D_DIALOG5 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg05)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg05)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG05_H__2CFDA624_AFAD_11D3_A036_0000E8DE4B3B__INCLUDED_)
