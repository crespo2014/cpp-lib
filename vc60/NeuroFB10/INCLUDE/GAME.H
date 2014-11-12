// Game.h: interface for the CGame class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAME_H__8DEF9203_9742_11D3_A036_0000E8DE4B3B__INCLUDED_)
#define AFX_GAME_H__8DEF9203_9742_11D3_A036_0000E8DE4B3B__INCLUDED_

#include "OpenGl10.h" 
#include "Device.h"
#include "Formas.h"
#include "GLBmp.h"	// Added by ClassView
#include "Joystick.h"	// Added by ClassView
#include "glview.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct tGameParams
{
	HGLRC   m_GLContext;
	HDC     m_DContext;
	HANDLE  m_hEvent;
	int     m_MouseX;
	int		m_MouseY;
	UINT    m_JfwButton;
} DataExchange;

typedef struct FireParams
{
	double m_angXZ;
	double m_angYZ1;
	double m_angYZ2;
	double m_distz;
	double m_LastY;
	double m_LastX;
	BOOL m_OnValid;
} FireData;

typedef struct ObjectParams
{
	double m_PosX;
	double m_PosY;
	double m_PosZ;
	double m_Vel;
	double m_MaxZ;
	BOOL m_OnValid;

} ObjectData;

class CGame : public CGLView  
{
public:
	LRESULT MyWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	int BeginGame();
	int Close();
	CDevice* m_Device;
	int SetDevice(CDevice* pDevice);
	virtual int GlInit();
	CGame();
	virtual ~CGame();
protected:
	DataExchange m_ThreadData;
	CWinThread* m_RenderThread;
protected:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
public:
	HANDLE m_hSound1;
	HANDLE m_hSound2;
	void*  m_lpSound1;
	void*  m_lpSound2;
	void NewFire();
	static UINT CThread(LPVOID pParam);
	
	virtual int Init();
	CJoystick m_Joystick;
	CGLBmp m_GLBmp;
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()

};

UINT RenderThread(LPVOID pParam);

#endif // !defined(AFX_GAME_H__8DEF9203_9742_11D3_A036_0000E8DE4B3B__INCLUDED_)
