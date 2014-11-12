// ViewCondicion.cpp : implementation file
//

#include "stdafx.h"
#include "stdafx.h"
#include "ViewCondicion.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewCondicion dialog
#include "app.h"
#include "viewconfigurarsesion.h"

CApp* pMyApp;

CViewCondicion::CViewCondicion(CWnd* pParent /*=NULL*/)
	: CDialog("IDD_CONDICION", pParent)
{
	//{{AFX_DATA_INIT(CViewCondicion)
	m_Crit_Comp_Burst = 0;
	m_Duracion_Cond = 0;
	m_Nivel_I_Eeg = 0.0;
	m_Nivel_I_Musculo = 0.0;
	m_Nivel_R_Eeg = 0.0;
	m_Temperatura = 0;
	m_Tiempo_Conteo_Burst = 0;
	//}}AFX_DATA_INIT
}


void CViewCondicion::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewCondicion)
	DDX_Text(pDX, IDC_EDITCRITERIOCOMPARACIONBURST, m_Crit_Comp_Burst);
	DDX_Text(pDX, IDC_EDITDURACIONCONDICION, m_Duracion_Cond);
	DDX_Text(pDX, IDC_EDITNIVELINHIBICIONEEG, m_Nivel_I_Eeg);
	DDX_Text(pDX, IDC_EDITNIVELINHIBICIONMUSCULO, m_Nivel_I_Musculo);
	DDX_Text(pDX, IDC_EDITNIVELREWARDEEG, m_Nivel_R_Eeg);
	DDX_Text(pDX, IDC_EDITTEMPERATURA, m_Temperatura);
	DDX_Text(pDX, IDC_EDITTIEMPOCONTEOBURST, m_Tiempo_Conteo_Burst);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CViewCondicion, CDialog)
	//{{AFX_MSG_MAP(CViewCondicion)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewCondicion message handlers

void CViewCondicion::OnDestroy() 
{
	CDialog::OnDestroy();

	//pasar los datos de los comobobox para los cstring
    CString temp;
	CComboBox* pC = (CComboBox*) GetDlgItem(IDC_COMBOILOWFREQ);
    ((CApp*)pMyApp)->GetComboBoxSel(pC, temp);
    m_Bf_I_Eeg = StrToInt((LPCSTR) temp);

	pC = (CComboBox*) GetDlgItem(IDC_COMBOIHIGHFREQ);
    ((CApp*)pMyApp)->GetComboBoxSel(pC, temp);
	m_Af_I_Eeg = StrToInt((LPCSTR) temp);

	pC = (CComboBox*) GetDlgItem(IDC_COMBORLOWFREQ);
    ((CApp*)pMyApp)->GetComboBoxSel(pC, temp);
	m_Bf_R_Eeg = StrToInt((LPCSTR) temp);

	pC = (CComboBox*) GetDlgItem(IDC_COMBORHIGHFREQ);
	((CApp*)pMyApp)->GetComboBoxSel(pC, temp);
	m_Af_R_Eeg = StrToInt((LPCSTR) temp);

	pC = (CComboBox*) GetDlgItem(IDC_COMBOMUSCLEFREQ);
	((CApp*)pMyApp)->GetComboBoxSel(pC, temp);
	m_Af_Musculo = StrToInt((LPCSTR) temp);
	
	UpdateData(TRUE);
	
}

BOOL CViewCondicion::OnInitDialog() 
{
	CDialog::OnInitDialog();
	COleVariant Valor;

    CComboBox* pC = (CComboBox*) GetDlgItem(IDC_COMBOILOWFREQ);
    pC->SetCurSel(0);

	pC = (CComboBox*) GetDlgItem(IDC_COMBOIHIGHFREQ);
    pC->SetCurSel(0);

	pC = (CComboBox*) GetDlgItem(IDC_COMBORLOWFREQ);
    pC->SetCurSel(0);

	pC = (CComboBox*) GetDlgItem(IDC_COMBORHIGHFREQ);
	pC->SetCurSel(0);

	pC = (CComboBox*) GetDlgItem(IDC_COMBOMUSCLEFREQ);
	pC->SetCurSel(0);

	if (m_task == ADICIONAR)
	{
	
		m_Nivel_I_Eeg = 12;
        m_Nivel_I_Musculo = 16;
        m_Nivel_R_Eeg = 4;
		m_Crit_Comp_Burst = 20;
		m_Duracion_Cond = 5;
		m_Temperatura = 30;
		m_Tiempo_Conteo_Burst = 20;

       UpdateData(FALSE);
	}

	
	if (m_task == ACTUALIZAR)
	{
		
		
		try
		{
		
		Valor.vt= VT_I4;
        ((CApp*)pMyApp)->paciente.pRs_parametros_sesion->GetFieldValue("Duracion_Condicion", Valor);
        m_Duracion_Cond = Valor.lVal;
		
		((CApp*)pMyApp)->paciente.pRs_parametros_sesion->GetFieldValue("Criterio_Comparacion_Burst", Valor);
		m_Crit_Comp_Burst = Valor.lVal;
		
		((CApp*)pMyApp)->paciente.pRs_parametros_sesion->GetFieldValue("Tiempo_Conteo_Burst", Valor);
		m_Tiempo_Conteo_Burst = Valor.lVal;
		
		((CApp*)pMyApp)->paciente.pRs_parametros_sesion->GetFieldValue("Temperatura", Valor);
		m_Temperatura = Valor.lVal;
		
		((CApp*)pMyApp)->paciente.pRs_parametros_sesion->GetFieldValue("Bf_Inhibicion_Eeg", Valor);
		m_Bf_I_Eeg = Valor.lVal;
		
		((CApp*)pMyApp)->paciente.pRs_parametros_sesion->GetFieldValue("Af_Inhibicion_Eeg", Valor);
		m_Af_I_Eeg = Valor.lVal;
		
		((CApp*)pMyApp)->paciente.pRs_parametros_sesion->GetFieldValue("Bf_Reward_Eeg", Valor);
		m_Bf_R_Eeg = Valor.lVal;
		
		((CApp*)pMyApp)->paciente.pRs_parametros_sesion->GetFieldValue("Af_Reward_Eeg", Valor);
		m_Af_R_Eeg = Valor.lVal;
		
		Valor.vt =  VT_R8;
		((CApp*)pMyApp)->paciente.pRs_parametros_sesion->GetFieldValue("Nivel_Inhibicion_Eeg", Valor);
		m_Nivel_I_Eeg = Valor.dblVal;
		
		((CApp*)pMyApp)->paciente.pRs_parametros_sesion->GetFieldValue("Nivel_Reward_Eeg", Valor);
		m_Nivel_R_Eeg = Valor.dblVal;
		
		((CApp*)pMyApp)->paciente.pRs_parametros_sesion->GetFieldValue("Nivel_Inhibicion_Musculo", Valor);
		m_Nivel_I_Musculo = Valor.dblVal;
		
		UpdateData(FALSE);
		}
		catch(CDaoException *e)
		{
		AfxMessageBox(e->m_pErrorInfo->m_strDescription);
		e->Delete();
		}
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

bool CViewCondicion::GetAppPointer(void *pApp, int task)
{
    pMyApp = (CApp*) pApp;
	m_task = task;
	return true;
}
