// GraphicsSettings.cpp : implementation file
//

#include "stdafx.h"
#include "GraphicsSettings.h"
#include "..\neurofbdll\app.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//parametros de inicializacion de los combobox de configuracion

float VoltPerDivTable[]={
	1.0f,2.0f,5.0f,7.0f,10.0f,15.0f};
float SampCantTable[]={
	100.0f,200.0f,300.0f,400.0f,500.0f
	};
#define MaxSampCant 5
#define MaxVoltPerDiv 6

static int AxisPosTable[]=
		{1,0,-1};
const char* AxisPosString[]={
			"Up","Center","Down"
			};

#define MaxAxisPos 3
//----------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////
// CGraphicsSettings dialog


CGraphicsSettings::CGraphicsSettings(CWnd* pParent /*=NULL*/)
	: CDialog("IDD_SETTINGS", pParent)
{
	//{{AFX_DATA_INIT(CGraphicsSettings)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CGraphicsSettings::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGraphicsSettings)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGraphicsSettings, CDialog)
	//{{AFX_MSG_MAP(CGraphicsSettings)
	ON_CBN_SELCHANGE(IDC_VOLT_POR_DIV, OnSelchangeVoltPorDiv)
	ON_BN_CLICKED(IDC_SIGNAL_COLOR, OnSignalColor)
	ON_CBN_SELCHANGE(IDC_SAMPLES_CANT, OnSelchangeSamplesCant)
	ON_BN_CLICKED(IDC_GRID_COLOR, OnGridColor)
	ON_BN_CLICKED(IDC_BACK_COLOR, OnBackColor)
	ON_CBN_SELCHANGE(IDC_AXIS_POSITION, OnSelchangeAxisPosition)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphicsSettings message handlers

void CGraphicsSettings::OnSelchangeVoltPorDiv() 
{
	CComboBox* Volts=(CComboBox*)GetDlgItem(IDC_VOLT_POR_DIV);
	DWORD Pos=Volts->GetCurSel();
	//pasarle a la ventana la ventana los Volts/Div
    m_pApp->m_Signal_Wnd.ChangeVoltPorDiv(Pos);
}

void CGraphicsSettings::OnSignalColor() 
{
	m_pApp->m_Signal_Wnd.OnSignalColor();
}

void CGraphicsSettings::OnSelchangeSamplesCant() 
{
	CComboBox* SC=(CComboBox*)GetDlgItem(IDC_SAMPLES_CANT);
	DWORD Pos=SC->GetCurSel();
    m_pApp->m_Signal_Wnd.ChangeSamplesCant(Pos);
}

void CGraphicsSettings::OnGridColor() 
{
	m_pApp->m_Signal_Wnd.OnGridColor();
}

void CGraphicsSettings::OnBackColor() 
{
	m_pApp->m_Signal_Wnd.OnBackColor();
}

void CGraphicsSettings::OnSelchangeAxisPosition() 
{
	CComboBox* SC=(CComboBox*)GetDlgItem(IDC_AXIS_POSITION);
	DWORD Pos=SC->GetCurSel();
    m_pApp->m_Signal_Wnd.ChangeAxisPosition(Pos);
}

void CGraphicsSettings::SetAppPointer(void *pApp)
{
	m_pApp = (CApp*)pApp;
}

BOOL CGraphicsSettings::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    char Number[255];
	//parametros de escala
	CComboBox* Combo=(CComboBox*)GetDlgItem(IDC_VOLT_POR_DIV);
	for (int i=0;i<MaxVoltPerDiv;i++)
	{
		sprintf(Number,"%.1f µV/Div",VoltPerDivTable[i]);
		Combo->AddString(Number);
	}
	Combo->SetCurSel(0);

	//cantidad de muestras
	Combo=(CComboBox*)GetDlgItem(IDC_SAMPLES_CANT);
	for (i=0;i<MaxSampCant;i++)
	{
		sprintf(Number,"%.1f",SampCantTable[i]);
		Combo->AddString(Number);
	}
	Combo->SetCurSel(0);	

	//posicion del eje
	Combo=(CComboBox*)GetDlgItem(IDC_AXIS_POSITION);
	for (i=0;i<MaxAxisPos;i++)
	{
		Combo->AddString(AxisPosString[i]);
	}
    Combo->SetCurSel(0);	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
