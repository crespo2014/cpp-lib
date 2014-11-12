// S25_8.h : main header file for the S25_8 application
//

#if !defined(AFX_S25_8_H__C014CBE5_7AD8_11D4_8632_00D0093D4380__INCLUDED_)
#define AFX_S25_8_H__C014CBE5_7AD8_11D4_8632_00D0093D4380__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CS25_8App:
// See S25_8.cpp for the implementation of this class
//

class CS25_8App : public CWinApp
{
public:
	CS25_8App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CS25_8App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CS25_8App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_S25_8_H__C014CBE5_7AD8_11D4_8632_00D0093D4380__INCLUDED_)
