// CT10.h : main header file for the CT10 application
//

#if !defined(AFX_CT10_H__2E837965_F4E6_11D3_BC3C_0000E8DE4B3B__INCLUDED_)
#define AFX_CT10_H__2E837965_F4E6_11D3_BC3C_0000E8DE4B3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCT10App:
// See CT10.cpp for the implementation of this class
//

class CCT10App : public CWinApp
{
public:
	CCT10App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCT10App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCT10App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CT10_H__2E837965_F4E6_11D3_BC3C_0000E8DE4B3B__INCLUDED_)
