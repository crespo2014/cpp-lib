// SockApp.h : main header file for the SOCKAPP application
//

#if !defined(AFX_SOCKAPP_H__7968988D_9542_425B_8D64_DA4D182D77E2__INCLUDED_)
#define AFX_SOCKAPP_H__7968988D_9542_425B_8D64_DA4D182D77E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSockAppApp:
// See SockApp.cpp for the implementation of this class
//

class CSockAppApp : public CWinApp
{
public:
	CSockAppApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSockAppApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSockAppApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOCKAPP_H__7968988D_9542_425B_8D64_DA4D182D77E2__INCLUDED_)
