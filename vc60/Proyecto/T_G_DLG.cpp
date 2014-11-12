// T_G_DLG.cpp : implementation file
//

#include "stdafx.h"
#include "Proyecto.h"
#include "T_G_DLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// T_G_DLG dialog


T_G_DLG::T_G_DLG(CWnd* pParent /*=NULL*/)
	: CDialog(T_G_DLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(T_G_DLG)
	m_x = 0.0f;
	m_y = 0.0f;
	m_z = 0.0f;
	//}}AFX_DATA_INIT
}


void T_G_DLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(T_G_DLG)
	DDX_Control(pDX, IDC_GRAFICO, m_grafico);
	DDX_Text(pDX, IDC_X, m_x);
	DDX_Text(pDX, IDC_Y, m_y);
	DDX_Text(pDX, IDC_Z, m_z);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(T_G_DLG, CDialog)
	//{{AFX_MSG_MAP(T_G_DLG)
	ON_BN_CLICKED(IDC_APLICAR, OnAplicar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// T_G_DLG message handlers

BOOL T_G_DLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_grafico.MoveWindow(0,0,300,300,TRUE);
	m_grafico.x=m_x;
	m_grafico.y=m_y;
	m_grafico.z=m_z;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void T_G_DLG::OnAplicar() 
{
	UpdateData(TRUE);
	if (!Validar())
		return;
	m_grafico.x=m_x;
	m_grafico.y=m_y;
	m_grafico.z=m_z;
	Invalidate();
}

BOOL T_G_DLG::Validar()
{
	if ((m_x < 0 )|| (m_x>lpCanal->largo))
	{
		MessageBox("El parametro X del vector de posicion debe ser mayor que 0 y menor que el largo del canal");
		return false;
	}
	if ((m_y < 0 )|| (m_y>lpCanal->ancho))
	{
		MessageBox("El parametro Y del vector de posicion debe ser mayor que 0 y menor que el ancho del canal");
		return false;
	}
		if ((m_z < 0 )|| (m_z>lpCanal->altura))
	{
		MessageBox("El parametro Z del vector de posicion debe ser mayor que 0 y menor que el alto del canal");
		return false;
	}
	return true;
}

void T_G_DLG::OnOK() 
{
	if (!Validar())
		return;
	CDialog::OnOK();
}
