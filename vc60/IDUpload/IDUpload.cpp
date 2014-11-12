// IDUpload.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "IDUpload.h"
#include "IDUploadDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIDUploadApp

BEGIN_MESSAGE_MAP(CIDUploadApp, CWinApp)
	//{{AFX_MSG_MAP(CIDUploadApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIDUploadApp construction

CIDUploadApp::CIDUploadApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CIDUploadApp object

CIDUploadApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CIDUploadApp initialization

BOOL CIDUploadApp::InitInstance()
{
	// Standard initialization

	CIDUploadDlg dlg;
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
