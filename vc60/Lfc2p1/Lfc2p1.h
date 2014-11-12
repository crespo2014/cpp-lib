// Lfc2p1.h : main header file for the LFC2P1 application
//

#if !defined(AFX_LFC2P1_H__BE46B5D7_FDB5_11D4_8D3A_00D0093D4380__INCLUDED_)
#define AFX_LFC2P1_H__BE46B5D7_FDB5_11D4_8D3A_00D0093D4380__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CLfc2p1App:
// See Lfc2p1.cpp for the implementation of this class
//

class CLfc2p1App : public CWinApp
{
public:
	CLfc2p1App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLfc2p1App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CLfc2p1App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LFC2P1_H__BE46B5D7_FDB5_11D4_8D3A_00D0093D4380__INCLUDED_)
