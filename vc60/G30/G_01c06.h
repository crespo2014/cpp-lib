#if !defined(AFX_G_01C06_H__702BAAA2_C8B6_11D4_8636_00D0093D4380__INCLUDED_)
#define AFX_G_01C06_H__702BAAA2_C8B6_11D4_8636_00D0093D4380__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// g_01c06.h : header file
//

#include "..\lfc30\lfc30c01.h"
#include "g_01c07.h"
#include "..\lfc30\wind.h"
#include "ddraw.h" 
#include "d3d.h"

class C3DMesh;
class C3DObject;
class C3DCohete;
class C3DNave;
class CApp;

/////////////////////////////////////////////////////////////////////////////
// C3DViewGame window

class C3DViewGame : public CWind
{
// Construction
public:
	C3DViewGame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C3DViewGame)
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	DWORD OglCreateRC();
	DWORD Destroy();
	DWORD Initialize();
	virtual ~C3DViewGame();

	// Generated message map functions
protected:
	//{{AFX_MSG(C3DViewGame)
	//}}AFX_MSG
	//DECLARE_MESSAGE_MAP()
public:
	DWORD SetGameMode(BOOL ponline);
	DWORD GameExitFullScreen();
	DWORD GameFullScreen();
	DWORD GameEndTime();
	DWORD GameEnd();
	DWORD GamePlay();
	DWORD GamePause();
	DWORD GameStop();
	DWORD GameAdd3DNave(C3DNave* lp3dnave);
	DWORD GameCheckColision(C3DCohete* p3dcohete);
	DWORD GameAdd3DCohete(C3DObject* pcohete);
	DWORD GameNewFire();
	DWORD ThreadProcessMessage();
	UINT ThreadMain();
	static DWORD WINAPI ThreadProc(LPVOID pParam);
	DWORD GameAdd3dObject(C3DObject* p3dobject);
	DWORD GameDestroy();
	DWORD OglDestroyRC();
	DWORD OglRenderContext();
	DWORD OglInitialize();
	DWORD OglSwapBuffer();
	DWORD GameInitialize();
	DWORD GameStart();
	HGLRC	m_hrc;
	HDC		m_hdc;
	HBITMAP	m_hbitmap,m_holdbitmap;
//	CWinThread*	m_thread;
	HANDLE	m_thread;
	DWORD	m_threadId;

	PIXELFORMATDESCRIPTOR m_pfd;
	DWORD	m_start_time;
	DWORD	m_last_time;
	C3DObject*	m_first_cohete;
	C3DObject*	m_first_nave;
	CMessage		m_message;
	C3DEscene		m_3descene;
	HCURSOR			m_hcursor;
	WORD			m_mousex,m_mousey;
	double			m_colimadorx,m_colimadory;
	double			m_mirax,m_miray;
	BOOL			m_play;
	DWORD			m_message_time;
	HPEN			m_linecolor;
	HFONT			m_font,m_font2;
	DWORD			m_score;
	BOOL			m_end_time;
	LPDIRECTDRAW			m_dd;
	LPDIRECTDRAWSURFACE     m_dds;
	LPDIRECTDRAWSURFACE     m_backdds;
//	CApp*					m_app;
	BOOL					m_online;
	C3DMesh*				m_tierra;
	
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_G_01C06_H__702BAAA2_C8B6_11D4_8636_00D0093D4380__INCLUDED_)
