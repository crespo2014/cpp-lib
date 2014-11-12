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
	ON_BN_CLICKED(IDC_SAVE_AND_EXIT, OnSaveandExit)
	ON_BN_CLICKED(IDC_CHANGEPARAMETERS, OnChangeparameters)
	ON_BN_CLICKED(IDC_STARTTRAINING, OnStarttraining)
	ON_BN_CLICKED(IDC_CANCELSESSION, OnCancelsession)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_TRAININGOFFLINE, OnTrainingoffline)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewTraining message handlers

void CViewTraining::OnCliniciandisplay() 
{
	m_pApp->m_viewsig->LoadClinician(m_pApp);
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
	//training online
	m_pApp->m_3dgame.SetGameMode(true);
	//tirmp[o de parada
	m_pApp->m_3dgame.m_last_time=m_pApp->pParam->m_Duracion_Cond*60*1000;
	//abrir el juego
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

void CViewTraining::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CViewTraining::OnSaveandExit() 
{
	/*contador_condiciones<cantidad condiciones solo si aun no se han hecho todas */
	/*las condiciones definidas para esa sesion*/
	if((m_pApp->paciente.GetContadorCondiciones()<m_pApp->paciente.cantidad_condiciones) && (m_pApp->paciente.GetContadorCondiciones()>1))
	{
		
		
		/*Actualizando en la tabla la cantidad de condiciones realmente ejecutadas*/
		m_pApp->paciente.EliminarCondiciones();
		/*Si se desea terminar antes de haber concluido 10 condiciones*/
		m_pApp->paciente.FinalizarSesion();

		AfxMessageBox("All data has been saved to disk \n Session end ");
		//preparar para destruir la ventana
		OnDestroy();
		EndDialog(0);
		return;
	}
	
	if(m_pApp->paciente.GetContadorCondiciones()==1)
		AfxMessageBox("No condition to save.");
              
}