#if !defined(AFX_G_01C01_H__E325256C_C5B2_11D4_8636_00D0093D4380__INCLUDED_)
#define AFX_G_01C01_H__E325256C_C5B2_11D4_8636_00D0093D4380__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// G_01C01.h : header file
//
#include  "ddraw.h"
#include "..\ngsig\sigc02.h"
//#include "..\gl10\gl10c5.h" 

/////////////////////////////////////////////////////////////////////////////
// CViewGame window

class AFX_EXT_CLASS CViewGame : public CWnd
{
// Construction
public:
	CViewGame();
	// Variables
	
	// OpenGL Variables
	LPDIRECTDRAW			FrontDD;	//DirectDraw object
	LPDIRECTDRAWSURFACE     FrontDDS;
	LPDIRECTDRAWSURFACE     BackDDS;
	HDC						FrontDC;
	HDC						BackDC;
	int						BackDCPFI;
	PIXELFORMATDESCRIPTOR	BackDCPFD;
	HBITMAP					BackBmp;
	HBITMAP					BackOldBmp;
	HGLRC					BackRC;	
	// Intercambio de informacion con el hilo
	CMessageEvent			Message;
	CWinThread*				BackThread;
	BOOL					OnPlay;      //Indica cuando se esta jugando
	DWORD					WTime;		 // Tiempo que debe esperar el hilo por un mensaje

	LARGE_INTEGER			TimerFrec;
	LARGE_INTEGER			TimerStart,TimerCurrent; 
	CObList					Objetos3DList;
//	CEscena					Escena;

	double	Game_ColX;
	double	Game_ColY;
	double	Game_ColZ;		// Con su signo
	double	Game_Misil_SX;
	double	Game_Misil_SY;
	double	Game_Misil_SZ;

	double	angulo;
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewGame)
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	DWORD GameNewFire();
	DWORD RCInitialize();
	DWORD CreateRC();
	DWORD GameAdd3DObject(void* p3DObject);
	DWORD DestroyFrontDC();
	DWORD GameInitialize();
	DWORD Fly();
	DWORD CreateFrontDC();
	DWORD DestroyFullScreen();
	DWORD TProcessMessage();
	DWORD ThreadRenderScene();
	DWORD SetFullScreen();
	DWORD SwapBuffer();
	DWORD DestroyBackBuffer();
	DWORD Destroy();
	DWORD Initialize();
	DWORD CreateBackBuffer();
	DWORD Start();
	virtual ~CViewGame();

	// Generated message map functions
protected:
	static UINT ThreadProc(LPVOID pParam);
	//{{AFX_MSG(CViewGame)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	UINT ThreadMain();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_G_01C01_H__E325256C_C5B2_11D4_8636_00D0093D4380__INCLUDED_)
