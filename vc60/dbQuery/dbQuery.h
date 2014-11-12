// dbQuery.h : main header file for the DBQUERY application
//

#if !defined(AFX_DBQUERY_H__9B0BB15C_39B6_49D5_BDA4_B7BC50E41DC1__INCLUDED_)
#define AFX_DBQUERY_H__9B0BB15C_39B6_49D5_BDA4_B7BC50E41DC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDbQueryApp:
// See dbQuery.cpp for the implementation of this class
//

class CDbQueryApp : public CWinApp
{
public:
	CDbQueryApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDbQueryApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDbQueryApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBQUERY_H__9B0BB15C_39B6_49D5_BDA4_B7BC50E41DC1__INCLUDED_)
