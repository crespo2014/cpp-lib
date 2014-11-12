// puerto.h : main header file for the PUERTO application
//

#if !defined(AFX_PUERTO_H__B615690A_7363_11D4_8CE5_00D0093847B4__INCLUDED_)
#define AFX_PUERTO_H__B615690A_7363_11D4_8CE5_00D0093847B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPuertoApp:
// See puerto.cpp for the implementation of this class
//

 class CPuertoApp : public CWinApp
{
public:
	CPuertoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPuertoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPuertoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PUERTO_H__B615690A_7363_11D4_8CE5_00D0093847B4__INCLUDED_)
