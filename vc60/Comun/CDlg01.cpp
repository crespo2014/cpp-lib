// CDlg.cpp : implementation file
//

#include "stdafx.h"
#include "stdafx.h"
#include "CDlg01.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg dialog


CConfigDlg::CConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigDlg)
	m_Bits = -1;
	m_Data = -1;
	m_Paridad = -1;
	m_Port = -1;
	m_Stop = -1;
	//}}AFX_DATA_INIT
}


void CConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigDlg)
	DDX_CBIndex(pDX, IDC_BITS, m_Bits);
	DDX_CBIndex(pDX, IDC_DATA, m_Data);
	DDX_CBIndex(pDX, IDC_PARITY, m_Paridad);
	DDX_CBIndex(pDX, IDC_PORT, m_Port);
	DDX_CBIndex(pDX, IDC_STOP, m_Stop);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigDlg, CDialog)
	//{{AFX_MSG_MAP(CConfigDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg message handlers

BOOL CConfigDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_PORT)->EnableWindow(!m_OnConnect);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
