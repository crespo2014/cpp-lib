// Log.h : main header file for the LOG application
//

#if !defined(AFX_LOG_H__E4AF3DD6_57D2_4715_B5F5_CD307149695E__INCLUDED_)
#define AFX_LOG_H__E4AF3DD6_57D2_4715_B5F5_CD307149695E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CLogApp:
// See Log.cpp for the implementation of this class
//

class CLogApp : public CWinApp
{
public:
	CLogApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CLogApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOG_H__E4AF3DD6_57D2_4715_B5F5_CD307149695E__INCLUDED_)
