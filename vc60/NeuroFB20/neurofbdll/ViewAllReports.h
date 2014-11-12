#if !defined(AFX_VIEWALLREPORTS_H__750B3C43_C5DA_11D4_9126_0000E83D722B__INCLUDED_)
#define AFX_VIEWALLREPORTS_H__750B3C43_C5DA_11D4_9126_0000E83D722B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewAllReports.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewAllReports dialog
#include "resource.h"

class CViewAllReports : public CDialog
{
// Construction
public:
	CViewAllReports(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CViewAllReports)
//	enum { IDD = IDD_REPORTES };
	CString	m_reporte;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewAllReports)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CViewAllReports)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWALLREPORTS_H__750B3C43_C5DA_11D4_9126_0000E83D722B__INCLUDED_)
