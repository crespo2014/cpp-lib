// ViewTraining.cpp : implementation file
//

#include "stdafx.h"
#include "stdafx.h"
#include "ViewTraining.h"
#include "app.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewTraining dialog


CViewTraining::CViewTraining(CWnd* pParent /*=NULL*/)
	: CDialog("IDD_TRAINING", pParent)
{
	//{{AFX_DATA_INIT(CViewTraining)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CViewTraining::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewTraining)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CViewTraining, CDialog)
	//{{AFX_MSG_MAP(CViewTraining)
	ON_BN_CLICKED(IDC_CLINICIANDISPLAY, OnCliniciandisplay)
	ON_BN_CLICKED(IDC_CHANGEPARAMETERS, OnChangeparameters)
	ON_BN_CLICKED(IDC_STARTTRAINING, OnStarttraining)
	ON_BN_CLICKED(IDC_CANCELSESSION, OnCancelsession)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_TRAININGOFFLINE, OnTrainingoffline)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewTraining message handlers

void CViewTraining::OnCliniciandisplay() 
{
	m_pApp->senales.DoModal();
	
}

void CViewTraining::OnChangeparameters() 
{
    
	if (m_pApp->paciente.nueva_sesion == true)
	{
	 m_pApp->medico.task = SESSIONSETTINGS;
	 m_pApp->medico.ConfigurarSesion();
	}
	else
	{
	  AfxMessageBox("No Session configurated");
	}

	
}

void CViewTraining::OnStarttraining() 
{
	m_pApp->pParam = new struct parametros;
	
	if (!m_pApp->paciente.GetParametros(m_pApp->pParam)) 
     return;
    
	m_pApp->pDatos = new struct datos*[m_pApp->pParam->m_Duracion_Cond];
	for (int i=0; i< m_pApp->pParam->m_Duracion_Cond; i++)
	{
		m_pApp->pDatos[i] = new struct datos;
		m_pApp->pDatos[i]->minuto = i;
	}
    m_pApp->m_device.SetParameters(m_pApp->pParam, m_pApp->pDatos);
	m_pApp->m_device.StartData();
	m_pApp->m_3dgame.SetGameMode(true);
	m_pApp->m_3dgame.m_last_time=m_pApp->pParam->m_Duracion_Cond*60*1000;
	m_pApp->m_3dgame.GameStart();

}

bool CViewTraining::SetApp(CApp *pAppt)
{
  m_pApp = pAppt;
  return true;

}

BOOL CViewTraining::PreTranslateMessage(MSG* pMsg) 
{
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam==27))
		return 0;
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CViewTraining::OnCancelsession() 
{
	m_pApp->paciente.AbortarSesion();
	EndDialog(0);
}

void CViewTraining::OnDestroy() 
{
	CDialog::OnDestroy();
	
   if (m_pApp->paciente.nueva_sesion == true)
   {
     if (AfxMessageBox("Cancel Session?", MB_YESNO|MB_ICONSTOP) == IDYES)
	 {
        	 m_pApp->paciente.AbortarSesion();
	 }
   
   }
	
}

void CViewTraining::OnTrainingoffline() 
{
	m_pApp->m_3dgame.SetGameMode(false);
	m_pApp->m_3dgame.GameStart();
}
