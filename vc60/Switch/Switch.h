// Switch.h : main header file for the SWITCH application
//

#if !defined(AFX_SWITCH_H__57AA75FA_645E_4925_A628_08217F10D7BE__INCLUDED_)
#define AFX_SWITCH_H__57AA75FA_645E_4925_A628_08217F10D7BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSwitchApp:
// See Switch.cpp for the implementation of this class
//

class CSwitchApp : public CWinApp
{
public:
	CSwitchApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSwitchApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSwitchApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SWITCH_H__57AA75FA_645E_4925_A628_08217F10D7BE__INCLUDED_)
