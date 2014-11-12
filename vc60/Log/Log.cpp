// Log.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Log.h"
#include "LogDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogApp

BEGIN_MESSAGE_MAP(CLogApp, CWinApp)
	//{{AFX_MSG_MAP(CLogApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogApp construction

CLogApp::CLogApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CLogApp object

CLogApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CLogApp initialization

BOOL CLogApp::InitInstance()
{
	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CLogDlg dlg;
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
