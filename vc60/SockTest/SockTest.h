// SockTest.h : main header file for the SOCKTEST application
//

#if !defined(AFX_SOCKTEST_H__71D0C404_85B1_4B20_A890_F7CA35989CF3__INCLUDED_)
#define AFX_SOCKTEST_H__71D0C404_85B1_4B20_A890_F7CA35989CF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSockTestApp:
// See SockTest.cpp for the implementation of this class
//

class CSockTestApp : public CWinApp
{
public:
	CSockTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSockTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSockTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOCKTEST_H__71D0C404_85B1_4B20_A890_F7CA35989CF3__INCLUDED_)
