// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "neurofb.h"
#include "ChildView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildView

CChildView::CChildView()
{
	
	entrada = false;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView,CWnd )
	//{{AFX_MSG_MAP(CChildView)
	ON_WM_PAINT()
	ON_COMMAND(ID_OPTIONS_GRAPHICS, OnOptionsGraphics)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_GRAPHICS, OnUpdateOptionsGraphics)
	ON_COMMAND(ID_OPTIONS_PRINTSESSION, OnOptionsPrintsession)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_PRINTSESSION, OnUpdateOptionsPrintsession)
	ON_COMMAND(ID_PATIENT_NEWPATIENT, OnPatientNewpatient)
	ON_UPDATE_COMMAND_UI(ID_PATIENT_NEWPATIENT, OnUpdatePatientNewpatient)
	ON_COMMAND(ID_PATIENT_PATIENTOPTIONS, OnPatientPatientoptions)
	ON_UPDATE_COMMAND_UI(ID_PATIENT_PATIENTOPTIONS, OnUpdatePatientPatientoptions)
	ON_COMMAND(ID_PATIENT_SHOWPATIENTDATA, OnPatientShowpatientdata)
	ON_UPDATE_COMMAND_UI(ID_PATIENT_SHOWPATIENTDATA, OnUpdatePatientShowpatientdata)
	ON_COMMAND(ID_SESSION_NEWSESION, OnSessionNewsesion)
	ON_UPDATE_COMMAND_UI(ID_SESSION_NEWSESION, OnUpdateSessionNewsesion)
	ON_COMMAND(ID_SESSION_SESSIONSETTINGS, OnSessionSessionsettings)
	ON_UPDATE_COMMAND_UI(ID_SESSION_SESSIONSETTINGS, OnUpdateSessionSessionsettings)
	ON_COMMAND(ID_SESSION_SHOWALLSESSIONSREPORTS, OnSessionShowallsessionsreports)
	ON_UPDATE_COMMAND_UI(ID_SESSION_SHOWALLSESSIONSREPORTS, OnUpdateSessionShowallsessionsreports)
	ON_COMMAND(ID_SESSION_STARTSESSION, OnSessionStartsession)
	ON_UPDATE_COMMAND_UI(ID_SESSION_STARTSESSION, OnUpdateSessionStartsession)
	ON_COMMAND(CHANGEPASSWORD, OnCHANGEPASSWORD)
	ON_UPDATE_COMMAND_UI(CHANGEPASSWORD, OnUpdateCHANGEPASSWORD)
	ON_COMMAND(ID_OPTIONS_SERIALPORTCONFIGURATION, OnOptionsSerialportconfiguration)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_SERIALPORTCONFIGURATION, OnUpdateOptionsSerialportconfiguration)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CWnd::OnPaint() for painting messages
}


BOOL CChildView::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult) 
{

	if (!entrada)
	{
	  App.EntrarSistema();
	  entrada = true;
	}

	return CWnd ::OnChildNotify(message, wParam, lParam, pLResult);
}

void CChildView::OnOptionsGraphics() 
{
	App.m_viewsig->LoadClinician(&App);

}

void CChildView::OnUpdateOptionsGraphics(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(true);
	
}

void CChildView::OnOptionsPrintsession() 
{
	
	
}

void CChildView::OnUpdateOptionsPrintsession(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(App.medico.ExistMedico());
	
}

void CChildView::OnPatientNewpatient() 
{
	App.medico.RegistrarPaciente();
	
}

void CChildView::OnUpdatePatientNewpatient(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(App.medico.ExistMedico());
	
}

void CChildView::OnPatientPatientoptions() 
{
	App.medico.BuscaPaciente();
	
}

void CChildView::OnUpdatePatientPatientoptions(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(App.medico.ExistMedico());
	
}

void CChildView::OnPatientShowpatientdata() 
{
	
	App.medico.MostrarDatos();
	
}

void CChildView::OnUpdatePatientShowpatientdata(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(App.medico.ExistMedico() && (App.paciente.paciente_cargado));
	
}

void CChildView::OnSessionNewsesion() 
{
	
    App.medico.task = NUEVASESION;
	App.medico.ConfigurarSesion();

}

void CChildView::OnUpdateSessionNewsesion(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(App.medico.ExistMedico() && !(App.paciente.nueva_sesion) && (App.paciente.paciente_cargado));
	
}

void CChildView::OnSessionSessionsettings() 
{

	App.medico.task = SESSIONSETTINGS;
	App.medico.ConfigurarSesion();
	
}

void CChildView::OnUpdateSessionSessionsettings(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(App.medico.ExistMedico()&& App.paciente.nueva_sesion);
	
}

void CChildView::OnSessionShowallsessionsreports() 
{

	App.medico.MostrarReportes();
	
}

void CChildView::OnUpdateSessionShowallsessionsreports(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(App.medico.ExistMedico());
	
}

void CChildView::OnSessionStartsession() //TRAINING
{
	
	

	App.Training();

  }

void CChildView::OnUpdateSessionStartsession(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(true);
	
}

void CChildView::OnCHANGEPASSWORD() 
{
	App.ChangePassword();
	
}

void CChildView::OnUpdateCHANGEPASSWORD(CCmdUI* pCmdUI) 
{
		pCmdUI->Enable(App.medico.ExistMedico());
}

void CChildView::OnOptionsSerialportconfiguration() 
{
	App.SetSerialPortSettings();
	
}

void CChildView::OnUpdateOptionsSerialportconfiguration(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(App.medico.ExistMedico());
	
}
