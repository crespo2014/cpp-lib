// sigc07.cpp : implementation file
//

#include "stdafx.h"
#include "sigc07.h"
#include "graphicssettings.h"
#include "..\neurofbdll\app.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSignalFrame

IMPLEMENT_DYNCREATE(CSignalFrame, CFrameWnd)

CSignalFrame::CSignalFrame()
{
	m_All_Graphics_State = true;
	m_RAW_State = false;
	m_Temp_State = false;
    m_REEG_State = false;
	m_IEEG_State = false;
	m_IEMG_State = false;
    m_Frec_State = false;
}

CSignalFrame::~CSignalFrame()
{
}


BEGIN_MESSAGE_MAP(CSignalFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CSignalFrame)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_COMMAND(ID_TB_SHOW_ALL_GRAPHICS, OnTbshowallgraphics)
	ON_COMMAND(ID_CONFIGURATION_GRAPHICSSETTINGS, OnConfigurationGraphicssettings)
	ON_UPDATE_COMMAND_UI(ID_TB_SHOW_ALL_GRAPHICS, OnUpdateTbShowAllGraphics)
	ON_COMMAND(ID_TB_SHOW_IEEG, OnTbShowIeeg)
	ON_UPDATE_COMMAND_UI(ID_TB_SHOW_IEEG, OnUpdateTbShowIeeg)
	ON_COMMAND(ID_TB_SHOW_IEMG, OnTbShowIemg)
	ON_UPDATE_COMMAND_UI(ID_TB_SHOW_IEMG, OnUpdateTbShowIemg)
	ON_COMMAND(ID_TB_SHOW_RAW, OnTbShowRaw)
	ON_UPDATE_COMMAND_UI(ID_TB_SHOW_RAW, OnUpdateTbShowRaw)
	ON_COMMAND(ID_TB_SHOW_REEG, OnTbShowReeg)
	ON_UPDATE_COMMAND_UI(ID_TB_SHOW_REEG, OnUpdateTbShowReeg)
//	ON_COMMAND(ID_TBSHOW_TEMP, OnTbshowTemp)
//	ON_UPDATE_COMMAND_UI(ID_TBSHOW_TEMP, OnUpdateTbshowTemp)
	ON_COMMAND(ID_VIEW_FREC, OnViewFrec)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FREC, OnUpdateViewFrec)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSignalFrame message handlers

int CSignalFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	m_lpApp->m_Signal_Wnd.Create(NULL, NULL,WS_CHILD|WS_VISIBLE|WS_EX_CLIENTEDGE, // AFX_WS_DEFAULT_VIEW,
		CRect(0, 0, 0,0), this, AFX_IDW_PANE_FIRST, NULL);
			
    if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_TOOLBAR_CLINICIAN_DISPLAY))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}


	m_lpApp->m_Signal_Wnd.OnDeviceStart();
	
	m_lpApp->m_Signal_Wnd.ChangeGraphName("RAW Signal (µV)", 0);
    m_lpApp->m_Signal_Wnd.ChangeGraphName("Temperature Signal", 1);
	m_lpApp->m_Signal_Wnd.ChangeGraphName("IEEG Signal (µV)", 2);
	m_lpApp->m_Signal_Wnd.ChangeGraphName("REEG Signal (µV)", 4);
	m_lpApp->m_Signal_Wnd.ChangeGraphName("IEMG Signal (µV)", 5);

	m_lpApp->m_Signal_Wnd.ChangeGraphName("RAW Frequency Spectrum", 6);
    m_lpApp->m_Signal_Wnd.ChangeGraphName("IEEG Frequency Spectrum", 8);
	m_lpApp->m_Signal_Wnd.ChangeGraphName("REEG Frequency Spectrum", 10);
	m_lpApp->m_Signal_Wnd.ChangeGraphName("IEMG Frequency Spectrum", 11);

	m_lpApp->m_Signal_Wnd.ShowAll();
	m_lpApp->m_Signal_Wnd.ShowGraphic(false, 3);
	m_lpApp->m_Signal_Wnd.ShowGraphic(false, 1);
	
	m_RAW_State = true;
	m_Temp_State = true;
    m_REEG_State = true;
	m_IEEG_State = true;
	m_IEMG_State = true;


	return 0;
}

DWORD CSignalFrame::SetAppPtr(CApp *lpApp)
{
	m_lpApp=lpApp;
	return 0;
}

void CSignalFrame::OnDestroy() 
{
	m_lpApp->m_viewsig=NULL;
	CFrameWnd::OnDestroy();
}

void CSignalFrame::OnTbshowallgraphics() 
{
    
	m_lpApp->m_Signal_Wnd.ShowAll();
	m_lpApp->m_Signal_Wnd.ShowGraphic(false, 3);
    m_lpApp->m_Signal_Wnd.ShowGraphic(false, 1);
    //m_lpApp->m_Signal_Wnd.ShowGraphic(false, 7);
    m_RAW_State = true;
	m_Temp_State = true;
    m_REEG_State = true;
	m_IEEG_State = true;
	m_IEMG_State = true;
    m_Frec_State = true;
}

void CSignalFrame::OnConfigurationGraphicssettings() 
{
	if (m_lpApp->m_Signal_Wnd.m_SignalWnd->ActiveGraph>5)
		return;
	CGraphicsSettings set;
	set.SetAppPointer(m_lpApp);
	set.DoModal();
	
}



void CSignalFrame::OnUpdateTbShowAllGraphics(CCmdUI* pCmdUI) 
{

	pCmdUI->SetCheck(!m_All_Graphics_State);
	
}

void CSignalFrame::OnTbShowIeeg() 
{
	
	m_IEEG_State = !m_IEEG_State;
    m_lpApp->m_Signal_Wnd.ShowGraphic(m_IEEG_State, 2);
	
}

void CSignalFrame::OnUpdateTbShowIeeg(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_IEEG_State);
	
}

void CSignalFrame::OnTbShowIemg() 
{
	
	m_IEMG_State = !m_IEMG_State;
	m_lpApp->m_Signal_Wnd.ShowGraphic(m_IEMG_State, 5);
}

void CSignalFrame::OnUpdateTbShowIemg(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_IEMG_State);
	
}

void CSignalFrame::OnTbShowRaw() 
{
	m_RAW_State = !m_RAW_State;
    m_lpApp->m_Signal_Wnd.ShowGraphic(m_RAW_State, 0);
}

void CSignalFrame::OnUpdateTbShowRaw(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_RAW_State);
	
}

void CSignalFrame::OnTbShowReeg() 
{
	m_REEG_State = !m_REEG_State;
	m_lpApp->m_Signal_Wnd.ShowGraphic(m_REEG_State, 4);
	
}

void CSignalFrame::OnUpdateTbShowReeg(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_REEG_State);
	
}

void CSignalFrame::OnTbshowTemp() 
{
	
	m_Temp_State = !m_Temp_State;
	m_lpApp->m_Signal_Wnd.ShowGraphic(m_Temp_State, 1);
}

void CSignalFrame::OnUpdateTbshowTemp(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_Temp_State);
	
}

void CSignalFrame::OnViewFrec() 
{
	m_Frec_State = !m_Frec_State;
    m_lpApp->m_Signal_Wnd.ChangeViewFrec(m_Frec_State);	
}

void CSignalFrame::OnUpdateViewFrec(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_Frec_State);
}

void CSignalFrame::LoadClinician(CApp *pApp)
{

	if (!pApp->m_viewsig)
	{
		pApp->m_viewsig = new CSignalFrame();
		pApp->m_viewsig->SetAppPtr(pApp);

		pApp->m_viewsig->LoadFrame(IDR_MENU_CLINICIAN_DISPLAY,
			WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
			NULL);

		pApp->m_viewsig->ShowWindow(SW_SHOWMAXIMIZED);
		pApp->m_viewsig->UpdateWindow();
	}
	else
	{
		pApp->m_viewsig->ShowWindow(SW_RESTORE);
		pApp->m_viewsig->BringWindowToTop ();
	}

}
