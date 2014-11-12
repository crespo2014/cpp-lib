// Wind.cpp: implementation of the CWind class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\include\Wind.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


LRESULT CALLBACK CWindProc(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam)
{
	CWind*	lpBWnd;
	if ((Msg == WM_CREATE) || (Msg == WM_NCCREATE))
	{
		CREATESTRUCT*	lpcs;
		lpcs = (CREATESTRUCT*)lParam;
		lpBWnd = (CWind*) lpcs->lpCreateParams;
		::SetWindowLong(hWnd,GWL_USERDATA,(LONG)lpBWnd);
	}
	else
		lpBWnd = (CWind*)::GetWindowLong(hWnd,GWL_USERDATA);
	if (lpBWnd)
		return lpBWnd->WndProc(hWnd,Msg,wParam,lParam);
	else
		return DefWindowProc(hWnd,Msg,wParam,lParam);
}

DWORD RegisterCWind()
{
	WNDCLASSEX	wcx;
	wcx.cbSize=sizeof(wcx);
	wcx.cbClsExtra=0;
	wcx.cbWndExtra=0;
	wcx.hbrBackground= HBRUSH (COLOR_WINDOW+1);
	wcx.hCursor=0;
	wcx.hIcon=0;
	wcx.hIconSm=0;
	wcx.hInstance=(HINSTANCE)GetModuleHandle(NULL);
	wcx.lpfnWndProc=CWindProc;
	wcx.lpszClassName=CWindClassName;
	wcx.lpszMenuName=0;
	wcx.style=CS_HREDRAW|CS_VREDRAW;
	if (RegisterClassExA(&wcx) == 0)
		return 1;
	return 0;
}


CWind::CWind()
{
	m_hwnd = NULL;
	m_lpParam = NULL;
}

CWind::~CWind()
{

}
/*
LRESULT CWind::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return 0;
}
*/

DWORD CWind::Create(LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
	m_lpParam = lpParam;
	m_hwnd = CreateWindow(CWindClassName,lpWindowName,dwStyle,x,y,nWidth,nHeight,hWndParent,hMenu,hInstance,this);
	if (m_hwnd != NULL)
		return 0;
	return 0;
}


DWORD CWind::Invalidate()
{
	if (m_hwnd) ::InvalidateRect(m_hwnd,NULL,true);
	return 0;
}
