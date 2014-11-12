// Dlg03.cpp : implementation file
//

#include "stdafx.h"
#include "Dlg03.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg03 dialog


CDlg03::CDlg03(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg03::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg03)
	//}}AFX_DATA_INIT
}


void CDlg03::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg03)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg03, CDialog)
	//{{AFX_MSG_MAP(CDlg03)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg03 message handlers

BOOL CDlg03::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	CRect rect;
	CWnd *pWnd =GetDlgItem(IDC_G3D_BUTTON1);
	pWnd->SetDlgCtrlID(0xffff);
	pWnd->GetWindowRect(rect);
	ScreenToClient(&rect);
	m_GLGame.Create(NULL,NULL,WS_CHILD|WS_VISIBLE|WS_BORDER,rect,this,IDC_G3D_BUTTON1);
	m_GLGame.Play();
	m_GLGame.SetFocus();
	return false;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
