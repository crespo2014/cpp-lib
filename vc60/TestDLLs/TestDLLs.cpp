// TestDLLs.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "TestDLLs.h"
#include "TestDLLsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestDLLsApp

BEGIN_MESSAGE_MAP(CTestDLLsApp, CWinApp)
	//{{AFX_MSG_MAP(CTestDLLsApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDLLsApp construction

CTestDLLsApp::CTestDLLsApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTestDLLsApp object

CTestDLLsApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTestDLLsApp initialization

BOOL CTestDLLsApp::InitInstance()
{
	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CTestDLLsDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
