// Lisa200Test.h : main header file for the LISA200TEST application
//

#if !defined(AFX_LISA200TEST_H__D2622C0F_43D4_471B_898E_83BFBC39F2E4__INCLUDED_)
#define AFX_LISA200TEST_H__D2622C0F_43D4_471B_898E_83BFBC39F2E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CLisa200TestApp:
// See Lisa200Test.cpp for the implementation of this class
//

class CLisa200TestApp : public CWinApp
{
public:
	CLisa200TestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLisa200TestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CLisa200TestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISA200TEST_H__D2622C0F_43D4_471B_898E_83BFBC39F2E4__INCLUDED_)
