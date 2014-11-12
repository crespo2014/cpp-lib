// IDUpload.h : main header file for the IDUPLOAD application
//

#if !defined(AFX_IDUPLOAD_H__CCED0C86_368F_4CC6_AAA5_8377AAB0A555__INCLUDED_)
#define AFX_IDUPLOAD_H__CCED0C86_368F_4CC6_AAA5_8377AAB0A555__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CIDUploadApp:
// See IDUpload.cpp for the implementation of this class
//

class CIDUploadApp : public CWinApp
{
public:
	CIDUploadApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIDUploadApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CIDUploadApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IDUPLOAD_H__CCED0C86_368F_4CC6_AAA5_8377AAB0A555__INCLUDED_)
