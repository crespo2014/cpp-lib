// SigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SigDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSigDlg dialog


CSigDlg::CSigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSigDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSigDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSigDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSigDlg, CDialog)
	//{{AFX_MSG_MAP(CSigDlg)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSigDlg message handlers

BOOL CSigDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CRect rect;
	CWnd *pWnd =GetDlgItem(IDC_G3D_BUTTON1);
	pWnd->SetDlgCtrlID(0xffff);
	pWnd->GetWindowRect(rect);
	ScreenToClient(&rect);
	GetClientRect(&rect);
	GrafSig.SetDevice(&Device);
	GrafSig.Create(NULL,NULL,WS_CHILD|WS_VISIBLE,rect,this,IDC_G3D_BUTTON1);
	ShowWindow(SW_SHOWMAXIMIZED);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSigDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	CRect rect;
	GetClientRect(&rect);
	//rect.DeflateRect(5,5);
	if (::IsWindow(GrafSig.m_hWnd))
		GrafSig.MoveWindow(&rect,true);
}
