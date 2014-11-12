// DlgTest.h : main header file for the DLGTEST application
//

#if !defined(AFX_DLGTEST_H__D4A7CCCB_FD40_458A_ADAE_97B3CDA9F57B__INCLUDED_)
#define AFX_DLGTEST_H__D4A7CCCB_FD40_458A_ADAE_97B3CDA9F57B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDlgTestApp:
// See DlgTest.cpp for the implementation of this class
//

class CDlgTestApp : public CWinApp
{
public:
	CDlgTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDlgTestApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTEST_H__D4A7CCCB_FD40_458A_ADAE_97B3CDA9F57B__INCLUDED_)
