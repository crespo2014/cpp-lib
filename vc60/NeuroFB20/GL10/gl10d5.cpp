 // gl10d5.cpp : implementation file
//

#include "stdafx.h"
#include "stdafx.h"
#include "gl10d5.h"
#include "gl10c9.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVariableDlg dialog


CVariableDlg::CVariableDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVariableDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVariableDlg)
	m_max = 0.0f;
	m_pos = 0;
	m_valor = 0.0f;
	//}}AFX_DATA_INIT
}


void CVariableDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVariableDlg)
	DDX_Text(pDX, IDC_MAX, m_max);
	DDX_Slider(pDX, IDC_POS, m_pos);
	DDX_Text(pDX, IDC_VALOR, m_valor);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVariableDlg, CDialog)
	//{{AFX_MSG_MAP(CVariableDlg)
	ON_WM_HSCROLL()
	ON_EN_KILLFOCUS(IDC_MAX, OnKillfocusMax)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVariableDlg message handlers

BOOL CVariableDlg::OnInitDialog() 
{
	m_max=m_var->GetMaxValue();
	m_factor=m_max/100;
	CDialog::OnInitDialog();
	((CSliderCtrl*)GetDlgItem(IDC_VALOR))->SetRange(0,100);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CVariableDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
	UpdateData(true);
	m_valor=m_pos*m_factor;
	m_var->SetValue(m_valor);
	UpdateData(false);
}

void CVariableDlg::OnKillfocusMax() 
{
	UpdateData(true);
	m_var->SetMaxValue(m_max);
	m_factor=m_max/100;
}
