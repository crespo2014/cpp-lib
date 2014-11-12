// T_S_DLG.cpp : implementation file
//

#include "stdafx.h"
#include "Proyecto.h"
#include "T_S_DLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// T_S_DLG dialog


T_S_DLG::T_S_DLG(CWnd* pParent /*=NULL*/)
	: CDialog(T_S_DLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(T_S_DLG)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void T_S_DLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(T_S_DLG)
	DDX_Control(pDX, IDC_MSFLEXGRID1, m_fg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(T_S_DLG, CDialog)
	//{{AFX_MSG_MAP(T_S_DLG)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// T_S_DLG message handlers

BOOL T_S_DLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_fg.SetCols(lpCanal->CantRecep+1);
	m_fg.SetRows(lpCanal->CantTrans+1);
	int i;
	char cadena[255];
	m_fg.SetRow(0);
	for (i=0;i<lpCanal->CantRecep;i++)
	{
		m_fg.SetCol(i+1);
		sprintf(cadena,"Receptor %d",i+1);
		m_fg.SetText(cadena);
	}
	m_fg.SetCol(0);
	for (i=0;i<lpCanal->CantTrans;i++)
	{
		m_fg.SetRow(i+1);
		sprintf(cadena,"Transmisor %d",i+1);
		m_fg.SetText(cadena);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
