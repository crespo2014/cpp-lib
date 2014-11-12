// T_CD.cpp : implementation file
//

#include "stdafx.h"
#include "Proyecto.h"
#include "T_CD.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// T_CD dialog


T_CD::T_CD(CWnd* pParent /*=NULL*/)
	: CDialog(T_CD::IDD, pParent)
{
	//{{AFX_DATA_INIT(T_CD)
	m_altura = 0.0f;
	m_ancho = 0.0f;
	m_largo = 0.0f;
	//}}AFX_DATA_INIT
}


void T_CD::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(T_CD)
	DDX_Text(pDX, IDC_ALTURA, m_altura);
	DDX_Text(pDX, IDC_ANCHO, m_ancho);
	DDX_Text(pDX, IDC_LARGO, m_largo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(T_CD, CDialog)
	//{{AFX_MSG_MAP(T_CD)
	ON_BN_CLICKED(IDOK, OnAceptar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// T_CD message handlers

void T_CD::OnAceptar() 
{
	UpdateData(true);
	if ((m_altura <= 0) || (m_altura > 100))
	{
		MessageBox("La altura debe estar entre (0-100)");
		return;
	}
	if ((m_ancho <=0) || (m_ancho > 100))
	{
		MessageBox("El ancho debe estar entre (0-100)");
		return;
	}
	if ((m_largo <=0) || (m_largo > 100))
	{
		MessageBox("El largo debe estar entre (0-100)");
		return;
	}
	CDialog::OnOK();
}


