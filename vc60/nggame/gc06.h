#if !defined(AFX_G_01C06_H__702BAAA2_C8B6_11D4_8636_00D0093D4380__INCLUDED_)
#define AFX_G_01C06_H__702BAAA2_C8B6_11D4_8636_00D0093D4380__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// g_01c06.h : header file
//
#include "gdef.h"

//#include "..\lfc10\lfc10c02.h"
#include "gc07.h"
#include "gc01.h"

class C3DMesh;
class C3DObject;
class C3DCohete;
class C3DNave;

/////////////////////////////////////////////////////////////////////////////
// C3DViewGame window

class C3DViewGame : public CDirectXGame
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
public:
	virtual DWORD VFDrawFrame();
	virtual HRESULT VFWindProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
	DWORD Run();
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
	DWORD GameAdd3dObject(C3DObject* p3dobject);
	DWORD GameDestroy();
	DWORD OglDestroyRC();
	DWORD OglRenderContext();
	DWORD OglInitialize();
	DWORD OglSwapBuffer();
	DWORD GameInitialize();
	HGLRC	m_hrc;
	HDC		m_hdc;
	HBITMAP	m_hbitmap,m_holdbitmap;
	PIXELFORMATDESCRIPTOR m_pfd;
	DWORD	m_start_time;
	DWORD	m_last_time;
	C3DObject*	m_first_cohete;
	C3DObject*	m_first_nave;
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
	BOOL					m_online;
	C3DMesh*				m_tierra;
	
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_G_01C06_H__702BAAA2_C8B6_11D4_8636_00D0093D4380__INCLUDED_)
