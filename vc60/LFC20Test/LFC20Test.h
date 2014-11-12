// LFC20Test.h : main header file for the LFC20TEST application
//

#if !defined(AFX_LFC20TEST_H__FFB7F78C_D3A8_11D4_8637_00D0093D4380__INCLUDED_)
#define AFX_LFC20TEST_H__FFB7F78C_D3A8_11D4_8637_00D0093D4380__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CLFC20TestApp:
// See LFC20Test.cpp for the implementation of this class
//

class CLFC20TestApp : public CWinApp
{
public:
	CLFC20TestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLFC20TestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CLFC20TestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LFC20TEST_H__FFB7F78C_D3A8_11D4_8637_00D0093D4380__INCLUDED_)
