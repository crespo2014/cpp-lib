// P02.h : main header file for the P02 application
//

#if !defined(AFX_P02_H__0F764D45_A341_11D4_8633_00D0093D4380__INCLUDED_)
#define AFX_P02_H__0F764D45_A341_11D4_8633_00D0093D4380__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CP02App:
// See P02.cpp for the implementation of this class
//

class CP02App : public CWinApp
{
public:
	CP02App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CP02App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CP02App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_P02_H__0F764D45_A341_11D4_8633_00D0093D4380__INCLUDED_)
