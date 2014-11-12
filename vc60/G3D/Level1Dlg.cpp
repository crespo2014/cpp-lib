// Level1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "stdafx.h"
#include "Level1Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLevel1Dlg dialog


CLevel1Dlg::CLevel1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLevel1Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLevel1Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CLevel1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLevel1Dlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLevel1Dlg, CDialog)
	//{{AFX_MSG_MAP(CLevel1Dlg)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_G3D_START, OnG3dStart)
	ON_BN_CLICKED(IDC_G3D_PAUSE, OnG3dPause)
	ON_BN_CLICKED(IDC_G3D_FINISH, OnG3dFinish)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLevel1Dlg message handlers

BOOL CLevel1Dlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	CRect rect;
	CWnd *pWnd =GetDlgItem(IDC_G3D_BUTTON1);
	pWnd->SetDlgCtrlID(0xffff);
	pWnd->GetWindowRect(rect);
	ScreenToClient(&rect);
	m_Video.Create(NULL,NULL,WS_CHILD|WS_VISIBLE,rect,this,IDC_G3D_BUTTON1);
	//m_Video.BeginGame();
	m_Video.SetFocus();
	m_TimerID=SetTimer(1,500,NULL);
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLevel1Dlg::OnTimer(UINT nIDEvent) 
{

	CDialog::OnTimer(nIDEvent);
}

void CLevel1Dlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(m_TimerID);	
	CDialog::OnClose();
}

void CLevel1Dlg::OnG3dStart() 
{
	m_Video.Play();	
}

void CLevel1Dlg::OnG3dPause() 
{
	// TODO: Add your control notification handler code here
	m_Video.Pause();	
}

void CLevel1Dlg::OnG3dFinish() 
{
	// TODO: Add your control notification handler code here
	m_Video.Pause();
	
}
