// ViewSenales.cpp : implementation file
//

#include "stdafx.h"
#include "stdafx.h"
#include "ViewSenales.h"
#include "app.h" 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewSenales dialog


CViewSenales::CViewSenales(CWnd* pParent /*=NULL*/)
	: CDialog("IDD_CLINICIANDISPLAY", pParent)
{
	//{{AFX_DATA_INIT(CViewSenales)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CViewSenales::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewSenales)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CViewSenales, CDialog)
	//{{AFX_MSG_MAP(CViewSenales)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewSenales message handlers

BOOL CViewSenales::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CRect rect;
	GetClientRect(&rect);
	rect.DeflateRect(10,10);
	Wnd.Create(NULL,NULL,WS_CHILD|WS_VISIBLE,rect,this,0);	
	ShowWindow(SW_SHOWMAXIMIZED);
	return false;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

DWORD CViewSenales::SetApp(CApp *pApp)
{
	m_app=pApp;
	return 0;
}

void CViewSenales::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	CRect rect;
	GetClientRect(&rect);
	rect.DeflateRect(10,10);
	if (Wnd.m_hWnd)
		Wnd.MoveWindow(&rect,true);	
}
