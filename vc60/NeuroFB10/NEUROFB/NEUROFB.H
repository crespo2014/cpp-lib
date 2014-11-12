// neurofb.h : main header file for the NEUROFB application
//

#if !defined(AFX_NEUROFB_H__FEC7B9A5_BFA8_11D4_9126_0000E83D722B__INCLUDED_)
#define AFX_NEUROFB_H__FEC7B9A5_BFA8_11D4_9126_0000E83D722B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CNeurofbApp:
// See neurofb.cpp for the implementation of this class
//

class CNeurofbApp : public CWinApp
{
public:
	CNeurofbApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNeurofbApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	//{{AFX_MSG(CNeurofbApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEUROFB_H__FEC7B9A5_BFA8_11D4_9126_0000E83D722B__INCLUDED_)
