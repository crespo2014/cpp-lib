// GamDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GamDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGamDlg dialog


CGamDlg::CGamDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGamDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGamDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CGamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGamDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGamDlg, CDialog)
	//{{AFX_MSG_MAP(CGamDlg)
	ON_BN_CLICKED(IDC_G3D_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_G3D_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_G3D_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_G3D_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_G3D_BUTTON6, OnButton6)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGamDlg message handlers

void CGamDlg::OnButton3() 
{
	m_Video.Pause();
	m_Level1Dlg.DoModal();		
	m_Video.Play();
}

void CGamDlg::OnButton4() 
{
	m_Video.Pause();
	m_Dlg04.DoModal();	
	m_Video.Play();
}

void CGamDlg::OnButton2() 
{
	m_Video.Pause();
	m_Dlg03.DoModal();
	m_Video.Play();
}

void CGamDlg::OnButton5() 
{
	m_Video.Pause();
	m_Dlg03.DoModal();		
	m_Video.Play();
}


void CGamDlg::OnButton6() 
{
	m_Video.Pause();
	m_Dlg05.DoModal();		
	m_Video.Play();
}

BOOL CGamDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CRect rect;
	CWnd *pWnd =GetDlgItem(IDC_G3D_BUTTON1);
	pWnd->SetDlgCtrlID(0xffff);
	pWnd->GetWindowRect(rect);
	ScreenToClient(&rect);
	m_Video.Create(NULL,NULL,WS_CHILD|WS_VISIBLE,rect,this,IDC_G3D_BUTTON1);
	m_Video.Play();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
