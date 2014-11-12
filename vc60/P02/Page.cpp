// Page.cpp : implementation file
//

#include "stdafx.h"
#include "P02.h"
#include "Page.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPage

CPage::CPage()
{
}

CPage::~CPage()
{
}


BEGIN_MESSAGE_MAP(CPage, CWnd)
	//{{AFX_MSG_MAP(CPage)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPage message handlers

LRESULT CPage::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{

	return CWnd::WindowProc(message, wParam, lParam);
}
