// TestDLLs.h : main header file for the TESTDLLS application
//

#if !defined(AFX_TESTDLLS_H__52C5611D_755C_4CB5_83D9_9F69B4D7BB0E__INCLUDED_)
#define AFX_TESTDLLS_H__52C5611D_755C_4CB5_83D9_9F69B4D7BB0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestDLLsApp:
// See TestDLLs.cpp for the implementation of this class
//

class CTestDLLsApp : public CWinApp
{
public:
	CTestDLLsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDLLsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestDLLsApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDLLS_H__52C5611D_755C_4CB5_83D9_9F69B4D7BB0E__INCLUDED_)
