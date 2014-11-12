// T_CS_DLG.cpp : implementation file
//

#include "stdafx.h"
#include "Proyecto.h"
#include "T_CS_DLG.h"
#include "T_G_DLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// T_CS_DLG dialog


T_CS_DLG::T_CS_DLG(CWnd* pParent /*=NULL*/)
	: CDialog(T_CS_DLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(T_CS_DLG)
	m_pos = _T("");
	m_vox = 0.0f;
	m_voy = 0.0f;
	m_voz = 0.0f;
	m_vpx = 0.0f;
	m_vpy = 0.0f;
	m_vpz = 0.0f;
	m_cr = 0.0f;
	//}}AFX_DATA_INIT
}


void T_CS_DLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(T_CS_DLG)
	DDX_Control(pDX, IDC_S_SIGUIENTE, m_siguiente);
	DDX_Control(pDX, IDC_S_ANTERIOR, m_anterior);
	DDX_Text(pDX, IDC_S_POS, m_pos);
	DDX_Text(pDX, VOX, m_vox);
	DDX_Text(pDX, VOY, m_voy);
	DDX_Text(pDX, VOZ, m_voz);
	DDX_Text(pDX, VPX, m_vpx);
	DDX_Text(pDX, VPY, m_vpy);
	DDX_Text(pDX, VPZ, m_vpz);
	DDX_Text(pDX, CR, m_cr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(T_CS_DLG, CDialog)
	//{{AFX_MSG_MAP(T_CS_DLG)
	ON_BN_CLICKED(IDC_S_GRAFICAR, OnSGraficar)
	ON_BN_CLICKED(IDC_S_ANTERIOR, OnSAnterior)
	ON_BN_CLICKED(IDC_S_ADICONAR, OnSAdiconar)
	ON_BN_CLICKED(IDC_S_SIGUIENTE, OnSSiguiente)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// T_CS_DLG message handlers

void T_CS_DLG::OnOK() 
{
	if (!Validar())
		return;
	ToCanal();
	lpCanal->CantSup=Cantidad;
	CDialog::OnOK();
}

void T_CS_DLG::OnSGraficar() 
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

void T_CS_DLG::OnSAnterior() 
{
	if (!Validar())
		return;
	if (Activo == 0)
		return;
	ToCanal();
	Activo--;
	FromCanal();
}

void T_CS_DLG::OnSAdiconar() 
{
	if (!Validar())
		return;
	if (Cantidad < 50)
		Cantidad++;
	ToCanal();
	Activo=Cantidad-1;
	FromCanal();
}

void T_CS_DLG::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void T_CS_DLG::OnSSiguiente() 
{
	if (!Validar())
		return;
	if (Activo == Cantidad-1)
		return;
	ToCanal();
	Activo++;
	FromCanal();		
}

BOOL T_CS_DLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	Cantidad = lpCanal->CantSup;
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



void T_CS_DLG::ToCanal()
{
	UpdateData(TRUE);
	lpCanal->Superficies[Activo].SetVectorO(m_vox,m_voy,m_voz);	
	lpCanal->Superficies[Activo].SetVectorP(m_vpx,m_vpy,m_vpz);
	lpCanal->Superficies[Activo].SetCoefRef(m_cr);
}

void T_CS_DLG::FromCanal()
{
	char pos[255];
	sprintf(pos," Superficie %d de %d ",Activo+1,Cantidad);
	m_pos=pos;
	lpCanal->Superficies[Activo].GetVectorO(&m_vox,&m_voy,&m_voz);
	lpCanal->Superficies[Activo].GetVectorP(&m_vpx,&m_vpy,&m_vpz);
	m_cr=lpCanal->Superficies[Activo].GetCoefRef();
	UpdateData(FALSE);
}

BOOL T_CS_DLG::Validar()
{
	UpdateData(TRUE);
	if ((m_cr <= 0 )|| (m_cr>1))
	{
		MessageBox("El coeficiente de reflexión debe ser mayor que cero y menor que 1");
		return false;
	}
	/*
	if ((m_vox < 0 )|| (m_vox> lpCanal->largo))
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
