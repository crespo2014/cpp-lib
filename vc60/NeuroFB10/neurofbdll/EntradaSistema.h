#if !defined(AFX_ENTRADASISTEMA_H__FEEEA3C1_BFC2_11D4_9126_0000E83D722B__INCLUDED_)
#define AFX_ENTRADASISTEMA_H__FEEEA3C1_BFC2_11D4_9126_0000E83D722B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EntradaSistema.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEntradaSistema dialog
#include "resource.h"

class CEntradaSistema : public CDialog
{
// Construction
public:
	bool CheckData();
	CEntradaSistema(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEntradaSistema)
//	enum { IDD = IDD_PASSWORD };
	CString	m_Password;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEntradaSistema)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEntradaSistema)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENTRADASISTEMA_H__FEEEA3C1_BFC2_11D4_9126_0000E83D722B__INCLUDED_)
