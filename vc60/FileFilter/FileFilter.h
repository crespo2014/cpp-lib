// FileFilter.h : main header file for the FILEFILTER application
//

#if !defined(AFX_FILEFILTER_H__8C0D0E4F_D7EA_49A6_B68D_A4E1AD1B3D2B__INCLUDED_)
#define AFX_FILEFILTER_H__8C0D0E4F_D7EA_49A6_B68D_A4E1AD1B3D2B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFileFilterApp:
// See FileFilter.cpp for the implementation of this class
//

class CFileFilterApp : public CWinApp
{
public:
	CFileFilterApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileFilterApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFileFilterApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEFILTER_H__8C0D0E4F_D7EA_49A6_B68D_A4E1AD1B3D2B__INCLUDED_)
