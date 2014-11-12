// g30c03.h: interface for the CGameWind class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_G30C03_H__D9449AAA_0999_11D5_94E2_00D0093D4380__INCLUDED_)
#define AFX_G30C03_H__D9449AAA_0999_11D5_94E2_00D0093D4380__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\lfc30\wind.h"
#include "g30def.h"
#include "g_01c07.h"	//C3DEscene
#include "g30c06.h"		// CDXEscene

class G30_API CGameWind : public CWind  
{
public:
	DWORD Run();
	DWORD Release();
	DWORD Initialize();
	virtual LRESULT WindProc(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);
	CGameWind();
	~CGameWind();
public:
	DWORD GameInitialize();
	DWORD KeyDown(WPARAM wParam,LPARAM lParam);
	DWORD UpDateFrame();
	DWORD DrawFrame();
	DWORD ProcessMessage(MSG* lpmsg);

	BOOL	m_OnActive;
	float	ang,radio;
	BOOL	m_OnRun;	//Indica cuando se estan mostrando frames de forma seguida
	BOOL	m_OnExit;	//Indica que ya se acabo el programa
	BOOL	m_OnPlay;	//Indica que le juego avanza y se cuenta el tiempo

	C3DEscene	m_3descene;
	CDXEscene	m_dxescene;

	// datos temporales
	float		m_angulo;
	CDXMesh*	m_lpmesh;
	
};

#endif // !defined(AFX_G30C03_H__D9449AAA_0999_11D5_94E2_00D0093D4380__INCLUDED_)
