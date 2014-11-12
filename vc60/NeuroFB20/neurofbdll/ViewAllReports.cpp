// ViewAllReports.cpp : implementation file
//

#include "stdafx.h"
#include "stdafx.h"
#include "ViewAllReports.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewAllReports dialog


CViewAllReports::CViewAllReports(CWnd* pParent /*=NULL*/)
	: CDialog("IDD_REPORTES", pParent)
{
	//{{AFX_DATA_INIT(CViewAllReports)
	m_reporte = _T("");
	//}}AFX_DATA_INIT
}


void CViewAllReports::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewAllReports)
	DDX_Text(pDX, IDC_EDITREPORTS, m_reporte);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CViewAllReports, CDialog)
	//{{AFX_MSG_MAP(CViewAllReports)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewAllReports message handlers

BOOL CViewAllReports::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    CEdit* pE = (CEdit*) GetDlgItem(IDC_EDITREPORTS);
	pE->SendMessage(EM_SETREADONLY, true, 0);
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
