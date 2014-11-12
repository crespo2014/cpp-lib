#if !defined(AFX_GLGAME_H__982AAB05_A46D_11D3_B87A_0000B490D4F4__INCLUDED_)
#define AFX_GLGAME_H__982AAB05_A46D_11D3_B87A_0000B490D4F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GLGame.h : header file
//

#include "Device.h"
#include "joystick.h"
#include "glfont.h"
#include "mmsystem.h"
#include "glclass.h"
#include "u_msg.h"

#define UM_ACK     (WM_USER+1)
#define UM_COMMAND (WM_USER+2)
#define MAX_FIRE   10
#define MAX_OBJECT 5

#define UC_BEGIN    1
#define UC_PAUSE    2
#define UC_END      3
#define UC_FIRE     4
/*
typedef struct S_GameParams
{
	// Intercambio de informacion
	HANDLE  m_hEvent;
	// posicion del lente en coordenadas de la pantalla
	int     m_MouseX;
	int		m_MouseY;
	
	// posicion del jostick en cada instante de tiempo coordenadas normalizadas
	BOOL m_IsJoystick;
	double m_JoystickX;
	double m_JoystickY;
	double m_JoystickZ;

	// coordenadas sin normalizar
	int m_JX;
	int m_JY;
	
	// OpenGl
	GLuint m_ListBase;
	// Disparos
	double   m_FireY;
	double   m_FireX;
	double   m_FireFarZ;
	double   m_FireVel;
	double   m_FirePosX1;
	double   m_FirePosX2;
	double   m_FirePosY;
	// Colimador
	double m_PosX;
	double m_PosY;
	double m_PosZ;
	double m_dPos;
	double m_ImpactDist;
	int m_Points;

	// Objetos Impactados
	DWORD m_PointID[10];
	// Tiempo de la condicion
    SYSTEMTIME  m_STime;
	DWORD       m_CondMin;

} GameParams;

typedef struct S_FireParams
{
	BOOL     m_OnValid;
	double   m_distz;
	double   m_LastY;
	double   m_LastX;
	double   m_angXZ;
	double   m_angYZ1;
	double   m_angYZ2;
} FireParams;
typedef struct S_ObjectParams
{
	double m_MaxZ;
	double m_PosZ;
	double m_Vel;
	double m_PosY;
	double m_PosX;
	BOOL   m_OnValid;
	BOOL   m_Dir;
	int    m_List;
	DWORD  m_ID;

} ObjectParams;
*/
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
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	int NewFire();
	CDevice* m_LPDevice;
	int SetDevice(CDevice* pDevice);
	int BeginGame();
	int PauseGame();
	int Close();
	int GenGLList();
	/*
	UINT ThreadMain();
	HCURSOR m_hCursor;
	virtual int Init();
	CJoystick m_Joystick;
	
	CWinThread* m_Thread;
	BOOL m_OnInit;
	*/
	BOOL m_OnDevice;
	
	virtual ~CGLGame();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGLGame)
		// NOTE - the ClassWizard will add and remove member functions here.
	afx_msg BOOL OnSetCursor( CWnd* pWnd, UINT nHitTest, UINT message );
	//}}AFX_MSG
public:
	CGLFont m_Font;
	int InitView();
	int GameInit();
	int MoveObjects();
	int CheckColision();
	/*
	// Usadas por el hilo
	FireParams   m_FireData[10];
	GameParams   m_GameParams;
	ObjectParams m_ObjectParams[10];
	int i,j;
	
	HANDLE m_hSound1,m_hSound2,m_lpSound1,m_lpSound2;
	*/
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/*
class CGLNumber : public CGLString  
{
public:
	void InToStr();
	int Paint();
	int m_Value;
	char m_String[20];
	void SetValue( int pValue);
	CGLNumber();
	virtual ~CGLNumber();

};
*/

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GLGAME_H__982AAB05_A46D_11D3_B87A_0000B490D4F4__INCLUDED_)
