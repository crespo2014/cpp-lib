// T_CT_DLG.cpp : implementation file
//

#include "stdafx.h"
#include "Proyecto.h"
#include "T_CT_DLG.h"
#include "T_G_DLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// T_CT_DLG dialog


T_CT_DLG::T_CT_DLG(CWnd* pParent /*=NULL*/)
	: CDialog(T_CT_DLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(T_CT_DLG)
	m_voz = 0.0f;
	m_vox = 0.0f;
	m_voy = 0.0f;
	m_vpx = 0.0f;
	m_vpy = 0.0f;
	m_vpz = 0.0f;
	m_perrad = 0.0f;
	m_potrad = 0.0f;
	m_pos = _T("");
	//}}AFX_DATA_INIT
}


void T_CT_DLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(T_CT_DLG)
	DDX_Control(pDX, IDC_T_SIGUIENTE, m_siguiente);
	DDX_Control(pDX, IDC_T_ANTERIOR, m_anterior);
	DDX_Text(pDX, VOZ, m_voz);
	DDX_Text(pDX, VOX, m_vox);
	DDX_Text(pDX, VOY, m_voy);
	DDX_Text(pDX, VPX, m_vpx);
	DDX_Text(pDX, VPY, m_vpy);
	DDX_Text(pDX, VPZ, m_vpz);
	DDX_Text(pDX, PERRAD, m_perrad);
	DDX_Text(pDX, POTRAD, m_potrad);
	DDX_Text(pDX, IDC_T_POS, m_pos);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(T_CT_DLG, CDialog)
	//{{AFX_MSG_MAP(T_CT_DLG)
	ON_BN_CLICKED(IDC_T_GRAFICAR, OnTGraficar)
	ON_BN_CLICKED(IDC_T_ANTERIOR, OnTAnterior)
	ON_BN_CLICKED(IDC_T_ADICIONAR, OnTAdicionar)
	ON_BN_CLICKED(IDC_T_SIGUIENTE, OnTSiguiente)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// T_CT_DLG message handlers

void T_CT_DLG::OnTGraficar() 
{
	if (!Validar())
		return;
	UpdateData(TRUE);
	T_G_DLG Dlg;
	Dlg.lpCanal=lpCanal;
	float max,escala;
	if (lpCanal->altura > max)
		max=lpCanal->altura;
	if (lpCanal->ancho > max)
		max=lpCanal->ancho;
	if (lpCanal->largo > max)
		max=lpCanal->largo;
	if (max > 50)
		escala=1.5;
	else
		if (max > 25)
			escala=3;
		else
			if (max> 10)
				escala=6;
			else 
				escala=15;
	Dlg.m_grafico.escala=escala;

	Dlg.m_x=m_vpx;
	Dlg.m_y=m_vpy;
	Dlg.m_z=m_vpz;
	if (Dlg.DoModal()== IDOK)
	{
		m_vpx=Dlg.m_grafico.x;
		m_vpy=Dlg.m_grafico.y;
		m_vpz=Dlg.m_grafico.z;
		UpdateData(FALSE);
	}
}

void T_CT_DLG::OnTAnterior() 
{
	if (!Validar())
		return;
	if (Activo == 0)
		return;
	ToCanal();
	Activo--;
	FromCanal();	
}

void T_CT_DLG::OnOK() 
{
	if (!Validar())
		return;
	ToCanal();
	lpCanal->CantTrans=Cantidad;	
	CDialog::OnOK();
}

void T_CT_DLG::OnTAdicionar() 
{
	if (!Validar())
		return;
	if (Cantidad < 50)
		Cantidad++;
	ToCanal();
	Activo=Cantidad-1;
	FromCanal();
}

void T_CT_DLG::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void T_CT_DLG::OnTSiguiente() 
{
	if (!Validar())
		return;
	if (Activo == Cantidad-1)
		return;
	ToCanal();
	Activo++;
	FromCanal();
}

BOOL T_CT_DLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	Cantidad = lpCanal->CantTrans;
	Activo =0 ;
	if (Cantidad ==0 )
	{
		Cantidad =1;
		ToCanal();
	}
	FromCanal();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL T_CT_DLG::Validar()
{
	UpdateData(TRUE);
	if ((m_perrad < 1 )|| (m_perrad>500))
	{
		MessageBox("El perfil de radiacion debe ser mayor que cero y menor que 500");
		return false;
	}
	if ((m_potrad < 0.001 )|| (m_potrad>1))
	{
		MessageBox("La Potencia de radiacion debe ser mayor que cero y menor que 1");
		return false;
	}
	/*
	if ((m_vox < 0 )|| (m_vox>lpCanal->largo))
	{
		MessageBox("El parametro X del vector de orientacion debe ser mayor que 0 y menor que el largo del canal");
		return false;
	}
	if ((m_voy < 0 )|| (m_voy>lpCanal->ancho))
	{
		MessageBox("El parametro Y del vector de orientacion debe ser mayor que 0 y menor que el ancho del canal");
		return false;
	}
	if ((m_voz < 0 )|| (m_voz>lpCanal->altura))
	{
		MessageBox("El parametro Z del vector de orientacion debe ser mayor que 0 y menor que el alto del canal");
		return false;
	}
	*/
	if ((m_vpx < 0 )|| (m_vpx>lpCanal->largo))
	{
		MessageBox("El parametro X del vector de posicion debe ser mayor que 0 y menor que el largo del canal");
		return false;
	}
	if ((m_vpy < 0 )|| (m_vpy>lpCanal->ancho))
	{
		MessageBox("El parametro Y del vector de posicion debe ser mayor que 0 y menor que el ancho del canal");
		return false;
	}
		if ((m_vpz < 0 )|| (m_vpz>lpCanal->altura))
	{
		MessageBox("El parametro Z del vector de posicion debe ser mayor que 0 y menor que el alto del canal");
		return false;
	}
	return true;

}

void T_CT_DLG::FromCanal()
{
	char pos[255];
	sprintf(pos," Transmisor %d de %d ",Activo+1,Cantidad);
	m_pos=pos;
	lpCanal->Transmisores[Activo].GetVectorO(&m_vox,&m_voy,&m_voz);
	lpCanal->Transmisores[Activo].GetVectorP(&m_vpx,&m_vpy,&m_vpz);
	m_potrad=lpCanal->Transmisores[Activo].GetPotenciaRadiacion();
	m_perrad=lpCanal->Transmisores[Activo].GetPerfilRadiacion();
	UpdateData(FALSE);
}

void T_CT_DLG::ToCanal()
{
	UpdateData(TRUE);
	lpCanal->Transmisores[Activo].SetVectorO(m_vox,m_voy,m_voz);	
	lpCanal->Transmisores[Activo].SetVectorP(m_vpx,m_vpy,m_vpz);
	lpCanal->Transmisores[Activo].SetPerfilRadiacion(m_perrad);
	lpCanal->Transmisores[Activo].SetPotenciaRadiacion(m_potrad);
}
