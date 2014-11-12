// App.h: interface for the CApp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_APP_H__FEC7B9BD_BFA8_11D4_9126_0000E83D722B__INCLUDED_)
#define AFX_APP_H__FEC7B9BD_BFA8_11D4_9126_0000E83D722B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "neurofbdlldef.h"
#include "DataBaseAplication.h"
#include "medico.h"
#include "paciente.h"
#include "shlwapi.h" 
#include "changepass.h"
#include "..\ngsig\sigc03.h"
#include "..\ngsig\sigc07.h"
#include "..\g_01\g_01c06.h"
#include "GameDlg.h"


#define NUEVASESION 0
#define SESSIONSETTINGS 1



//-----------------------------------------------------

class AFX_EXT_CLASS CApp : public CDataBaseAplication  
{
public:
	void SetSerialPortSettings();
	bool Training();
	bool ChangePassword();
	CDaoDatabase database;
	bool EntrarSistema();
	CApp();
	virtual ~CApp();

	CMedico medico;
	CPaciente paciente;

//	CGameDlg Game_Dlg;
	CSignalDevice	m_device;
	CSignalFrame*	m_viewsig;
	C3DViewGame		m_3dgame;
	CSignalWnd	m_Signal_Wnd;

	struct parametros *pParam;
	struct datos** pDatos;

};

#endif // !defined(AFX_APP_H__FEC7B9BD_BFA8_11D4_9126_0000E83D722B__INCLUDED_)
