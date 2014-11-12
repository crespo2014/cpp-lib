// VLClient1.h : main header file for the VLCLIENT1 application
//

#if !defined(AFX_VLCLIENT1_H__B1D8C126_45A1_11D3_8023_0000E8DE4B3B__INCLUDED_)
#define AFX_VLCLIENT1_H__B1D8C126_45A1_11D3_8023_0000E8DE4B3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CVLClient1App:
// See VLClient1.cpp for the implementation of this class
//

class CVLClient1App : public CWinApp
{
public:
	CVLClient1App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVLClient1App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	COleTemplateServer m_server;
		// Server object for document creation
	//{{AFX_MSG(CVLClient1App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VLCLIENT1_H__B1D8C126_45A1_11D3_8023_0000E8DE4B3B__INCLUDED_)
