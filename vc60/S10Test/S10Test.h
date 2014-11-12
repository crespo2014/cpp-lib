// S10Test.h : main header file for the S10TEST application
//

#if !defined(AFX_S10TEST_H__7F29B7E6_13C2_11D3_BC46_0000E8DE4B3B__INCLUDED_)
#define AFX_S10TEST_H__7F29B7E6_13C2_11D3_BC46_0000E8DE4B3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CS10TestApp:
// See S10Test.cpp for the implementation of this class
//

class CS10TestApp : public CWinApp
{
public:
	CS10TestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CS10TestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CS10TestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_S10TEST_H__7F29B7E6_13C2_11D3_BC46_0000E8DE4B3B__INCLUDED_)
