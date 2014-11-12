// DaoTest.h : main header file for the DAOTEST application
//

#if !defined(AFX_DAOTEST_H__B87AFA65_71CC_11D2_8635_00D0093D4380__INCLUDED_)
#define AFX_DAOTEST_H__B87AFA65_71CC_11D2_8635_00D0093D4380__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDaoTestApp:
// See DaoTest.cpp for the implementation of this class
//

class CDaoTestApp : public CWinApp
{
public:
	CDaoTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDaoTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDaoTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DAOTEST_H__B87AFA65_71CC_11D2_8635_00D0093D4380__INCLUDED_)
