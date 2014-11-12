#if !defined(AFX_DX01C01_H__B48179E7_F306_11D4_948D_00D0093D4380__INCLUDED_)
#define AFX_DX01C01_H__B48179E7_F306_11D4_948D_00D0093D4380__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "gdef.h"

class CDirectXGame  
{
public:
	virtual DWORD VFDrawFrame();
	virtual LRESULT VFWindProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
	DWORD Run();
	DWORD D3DCreateZBuffer(REFCLSID rclsid);
	DWORD D3DReleaseZBuffer();
	DWORD CreateZBuffer(REFCLSID rclsid);
	DWORD InitScene();
	DWORD RenderScene();

	DWORD ReleaseDirectX();
	DWORD CreateDirectX();
	DWORD MainLoop();
	DWORD CreateDirectXWindow();
	LRESULT WindowProc(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);
	DWORD RegisterClass();
	CDirectXGame();
	virtual ~CDirectXGame();
	HWND	m_hWnd;
	LPDIRECTDRAW7			m_DDraw;
	LPDIRECTDRAWSURFACE7	m_DDSurface;
	LPDIRECTDRAWSURFACE7	m_DDBackSurface;
	LPDIRECTDRAWSURFACE7	m_DDZBuffer;
	LPDIRECT3D7				m_D3D;
	LPDIRECT3DDEVICE7		m_D3DDevice;
	DDPIXELFORMAT			m_ZBPF;
	BOOL	m_OnZBuffer; //Indica que m_ZBPF posee datos validos
	BOOL	m_OnPause;	//Indica que el render esta pausado
	BOOL	m_OnActive;
	BOOL	m_OnDirectX;
	float	ang,radio;
	//Render
//	D3DVERTEX	g_pvTriangleVertices[6];
};

#endif // !defined(AFX_DX01C01_H__B48179E7_F306_11D4_948D_00D0093D4380__INCLUDED_)
