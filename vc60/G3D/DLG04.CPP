// Dlg04.cpp : implementation file
//

#include "stdafx.h"
#include "Dlg04.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg04 dialog


CDlg04::CDlg04(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg04::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg04)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlg04::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg04)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg04, CDialog)
	//{{AFX_MSG_MAP(CDlg04)
	ON_BN_CLICKED(IDC_G3D_BUTTON5, OnG3dButton5)
	ON_BN_CLICKED(IDC_G3D_BUTTON6, OnG3dButton6)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg04 message handlers

BOOL CDlg04::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CRect rect;
	CWnd *pWnd =GetDlgItem(IDC_G3D_BUTTON4);
	pWnd->SetDlgCtrlID(0xffff);
	pWnd->GetWindowRect(rect);
	ScreenToClient(&rect);
	m_Video.Create(NULL,NULL,WS_CHILD|WS_VISIBLE,rect,this,IDC_G3D_BUTTON1);
	m_TimerID=SetTimer(0,500,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlg04::OnG3dButton5() 
{
	m_Video.Play();	
	m_Video.SetFocus();
}

void CDlg04::OnG3dButton6() 
{
	if (m_TovaDlg.DoModal() == IDOK)
		m_TovaParams=m_TovaDlg.m_TovaParams;
}

void CDlg04::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(m_TimerID);
	CDialog::OnClose();
}

void CDlg04::OnTimer(UINT nIDEvent) 
{
	GetDlgItem(IDC_G3D_ACIERTOS)->SetWindowText(m_Video.m_Number01.m_String);
	CDialog::OnTimer(nIDEvent);
}
