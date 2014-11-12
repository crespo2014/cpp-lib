// db11d2.cpp : implementation file
//

#include "stdafx.h"
#include "stdafx.h"
#include "db11d2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSQLDlg dialog


CSQLDlg::CSQLDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSQLDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSQLDlg)
	m_On1apellido = FALSE;
	m_On2apellido = FALSE;
	m_OnClasificacion = FALSE;
	m_OnDesde = FALSE;
	m_OnHasta = FALSE;
	m_OnMunicipio = FALSE;
	m_OnNombre = FALSE;
	m_OnNumero = FALSE;
	m_OnOrdenar = FALSE;
	m_OnOrganismo = FALSE;
	m_OnRespuesta = FALSE;
	m_OnSindicato = FALSE;
	m_OnTDepartamento = FALSE;
	m_OnTema = FALSE;
	m_OnTProvincia = FALSE;
	m_OnTSindicato = FALSE;
	//}}AFX_DATA_INIT
	strcpy(sqlstring,"");
}


void CSQLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSQLDlg)
	DDX_Control(pDX, IDC_TSINDICATO, m_TSindicato);
	DDX_Control(pDX, IDC_TPROVINCIA, m_TProvincia);
	DDX_Control(pDX, IDC_TDEPARTAMENTO, m_TDepartamento);
	DDX_Control(pDX, IDC_TEMA, m_tema);
	DDX_Control(pDX, IDC_SINDICATO, m_Sindicato);
	DDX_Control(pDX, IDC_ORGANISMO, m_Organismo);
	DDX_Control(pDX, IDC_ORDENAR, m_Ordenar);
	DDX_Control(pDX, IDC_NUMERO, m_Numero);
	DDX_Control(pDX, IDC_NOMBRE, m_Nombre);
	DDX_Control(pDX, IDC_MUNICIPIO, m_Municipio);
	DDX_Control(pDX, IDC_HASTA, m_Hasta);
	DDX_Control(pDX, IDC_DESDE, m_Desde);
	DDX_Control(pDX, IDC_CLASIFICACION, m_clasificacion);
	DDX_Control(pDX, IDC_2APELLIDO, m_2apellido);
	DDX_Control(pDX, IDC_1APELLIDO, m_1apellido);
	DDX_Check(pDX, IDC_B1APELLIDO, m_On1apellido);
	DDX_Check(pDX, IDC_B2APELLIDO, m_On2apellido);
	DDX_Check(pDX, IDC_BCLASIFICACION, m_OnClasificacion);
	DDX_Check(pDX, IDC_BDESDE, m_OnDesde);
	DDX_Check(pDX, IDC_BHASTA, m_OnHasta);
	DDX_Check(pDX, IDC_BMUNICIPIO, m_OnMunicipio);
	DDX_Check(pDX, IDC_BNOMBRE, m_OnNombre);
	DDX_Check(pDX, IDC_BNUMERO, m_OnNumero);
	DDX_Check(pDX, IDC_BORDENAR, m_OnOrdenar);
	DDX_Check(pDX, IDC_BORGANISMO, m_OnOrganismo);
	DDX_Check(pDX, IDC_BSINDICATO, m_OnSindicato);
	DDX_Check(pDX, IDC_BTDEPARTAMENTO, m_OnTDepartamento);
	DDX_Check(pDX, IDC_BTEMA, m_OnTema);
	DDX_Check(pDX, IDC_BTPROVINCIA, m_OnTProvincia);
	DDX_Check(pDX, IDC_BTSINDICATO, m_OnTSindicato);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSQLDlg, CDialog)
	//{{AFX_MSG_MAP(CSQLDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSQLDlg message handlers

void CSQLDlg::OnOK() 
{
	// CDialog::OnOK();
}

