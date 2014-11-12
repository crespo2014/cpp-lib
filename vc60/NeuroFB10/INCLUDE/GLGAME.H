#if !defined(AFX_GLGAME_H__982AAB05_A46D_11D3_B87A_0000B490D4F4__INCLUDED_)
#define AFX_GLGAME_H__982AAB05_A46D_11D3_B87A_0000B490D4F4__INCLUDED_

#include "Game.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GLGame.h : header file
//

#include "glview.h"
#include "Joystick.h"	// Added by ClassView
 
#include "Device.h"
#include "Formas.h"
#include "GLBmp.h"	// Added by ClassView


#define UM_ACK     (WM_USER+1)
#define UM_COMMAND (WM_USER+2)

#define UC_BEGIN    1
#define UC_PAUSE    2
#define UC_END      3

typedef struct S_GameParams
{
	// Intercambio de informacion
	HANDLE  m_hEvent;
	int     m_MouseX;
	int		m_MouseY;
	UINT    m_JfwButton;

	// posicion del jostick en cada instante de tiempo
	int m_JoystickX;
	int m_JoystickY;

	// OpenGl
	GLuint m_ListBase;

} GameParams;

/////////////////////////////////////////////////////////////////////////////
// CGLGame window

class CGLGame : public CGLView
{
// Construction
public:
	CGLGame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGLGame)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	CDevice* m_LPDevice;
	int SetDevice(CDevice* pDevice);
	int BeginGame();
	int PauseGame();
	int Close();
	int GenGLList();
	UINT ThreadMain();
	virtual int Init();
	CJoystick m_Joystick;
	GameParams m_GameParams;
	CWinThread* m_Thread;
	BOOL m_OnInit;
	static UINT Thread( LPVOID pParam );
	virtual ~CGLGame();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGLGame)
		// NOTE - the ClassWizard will add and remove member functions here.
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GLGAME_H__982AAB05_A46D_11D3_B87A_0000B490D4F4__INCLUDED_)
