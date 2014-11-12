#if !defined(AFX_CHANGEPASS_H__CB3CE921_C71E_11D4_9126_0000E83D722B__INCLUDED_)
#define AFX_CHANGEPASS_H__CB3CE921_C71E_11D4_9126_0000E83D722B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChangePass.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChangePass dialog
#include "resource.h"

class CChangePass : public CDialog
{
// Construction
public:
	CChangePass(CWnd* pParent = NULL);   // standard constructor
    bool CheckData(); 
// Dialog Data
	//{{AFX_DATA(CChangePass)
	//enum { IDD = PASSWORD };
	CString	m_new_pass;
	CString	m_retype_pass;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChangePass)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChangePass)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHANGEPASS_H__CB3CE921_C71E_11D4_9126_0000E83D722B__INCLUDED_)
