// T_CR_DLG.cpp : implementation file
//

#include "stdafx.h"
#include "Proyecto.h"
#include "T_CR_DLG.h"
#include "T_G_DLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// T_CR_DLG dialog


T_CR_DLG::T_CR_DLG(CWnd* pParent /*=NULL*/)
	: CDialog(T_CR_DLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(T_CR_DLG)
	m_ac = 0.0f;
	m_as = 0.0f;
	m_cv = 0.0f;
	m_vox = 0.0f;
	m_voy = 0.0f;
	m_voz = 0.0f;
	m_vpx = 0.0f;
	m_vpy = 0.0f;
	m_vpz = 0.0f;
	m_pos = _T("");
	//}}AFX_DATA_INIT
}


void T_CR_DLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(T_CR_DLG)
	DDX_Control(pDX, IDC_SIGUIENTE, m_siguiente);
	DDX_Control(pDX, IDC_ANTERIOR, m_anterior);
	DDX_Text(pDX, AC, m_ac);
	DDX_Text(pDX, AS, m_as);
	DDX_Text(pDX, CV, m_cv);
	DDX_Text(pDX, VOX, m_vox);
	DDX_Text(pDX, VOY, m_voy);
	DDX_Text(pDX, VOZ, m_voz);
	DDX_Text(pDX, VPX, m_vpx);
	DDX_Text(pDX, VPY, m_vpy);
	DDX_Text(pDX, VPZ, m_vpz);
	DDX_Text(pDX, IDC_POS, m_pos);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(T_CR_DLG, CDialog)
	//{{AFX_MSG_MAP(T_CR_DLG)
	ON_BN_CLICKED(IDC_GRAFICAR, OnGraficar)
	ON_BN_CLICKED(IDC_ANTERIOR, OnAnterior)
	ON_BN_CLICKED(IDC_ADICIONAR, OnAdicionar)
	ON_BN_CLICKED(IDC_SIGUIENTE, OnSiguiente)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// T_CR_DLG message handlers

BOOL T_CR_DLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	Cantidad = lpCanal->CantRecep;
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

/*
	Transfiere la informacion del dialogo al receptor activo
*/
void T_CR_DLG::ToCanal()
{
	UpdateData(TRUE);
	lpCanal->Receptores[Activo].SetVectorO(m_vox,m_voy,m_voz);	
	lpCanal->Receptores[Activo].SetVectorP(m_vpx,m_vpy,m_vpz);
	lpCanal->Receptores[Activo].SetAreaCol(m_ac);
	lpCanal->Receptores[Activo].SetAreaSup(m_as);
	lpCanal->Receptores[Activo].SetCampVista(m_cv);
}

void T_CR_DLG::FromCanal()
{
	char pos[255];
	sprintf(pos," Receptor %d de %d ",Activo+1,Cantidad);
	m_pos=pos;
	lpCanal->Receptores[Activo].GetVectorO(&m_vox,&m_voy,&m_voz);
	lpCanal->Receptores[Activo].GetVectorP(&m_vpx,&m_vpy,&m_vpz);
	m_as=lpCanal->Receptores[Activo].GetAreaSup();
	m_ac=lpCanal->Receptores[Activo].GetAreaCol();
	m_cv=lpCanal->Receptores[Activo].GetCampVista();
	UpdateData(FALSE);
}

void T_CR_DLG::OnGraficar() 
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

void T_CR_DLG::OnAnterior() 
{
	if (!Validar())
		return;
	if (Activo == 0)
		return;
	ToCanal();
	Activo--;
	FromCanal();
}

void T_CR_DLG::OnAdicionar() 
{
	if (!Validar())
		return;
	if (Cantidad < 50)
		Cantidad++;
	ToCanal();
	Activo=Cantidad-1;
	FromCanal();
}

void T_CR_DLG::OnSiguiente() 
{
	if (!Validar())
		return;
	if (Activo == Cantidad-1)
		return;
	ToCanal();
	Activo++;
	FromCanal();
	
}

void T_CR_DLG::OnOK() 
{
	if (!Validar())
		return;
	ToCanal();
	lpCanal->CantRecep=Cantidad;
	CDialog::OnOK();
}

BOOL T_CR_DLG::Validar()
{
	UpdateData(TRUE);
	if ((m_ac < 1 )|| (m_ac>50))
	{
		MessageBox("El area de coleccion debe ser mayor que 1 y menor que 50");
		return false;
	}
	if ((m_as <= 0 )|| (m_as>100))
	{
		MessageBox("El area de superficie debe ser mayor que cero y menor que 100");
		return false;
	}
	if ((m_cv < 0 )|| (m_cv>90))
	{
		MessageBox("El campo de vista debe ser mayor que cero y menor que 90");
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
