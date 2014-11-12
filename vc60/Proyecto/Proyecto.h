// Proyecto.h : main header file for the PROYECTO application
//

#if !defined(AFX_PROYECTO_H__991AAD3D_7348_4090_9160_DE1D431C71DE__INCLUDED_)
#define AFX_PROYECTO_H__991AAD3D_7348_4090_9160_DE1D431C71DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CProyectoApp:
// See Proyecto.cpp for the implementation of this class
//

class CProyectoApp : public CWinApp
{
public:
	CProyectoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProyectoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CProyectoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROYECTO_H__991AAD3D_7348_4090_9160_DE1D431C71DE__INCLUDED_)
