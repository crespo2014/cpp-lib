// Wind.cpp: implementation of the CWind class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Wind.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWind::CWind()
{
	m_OnInit=FALSE;
	m_hWnd=NULL;
	m_lParam=NULL;
}

CWind::~CWind()
{

}

DWORD CWind::Initialize()
{
	m_OnInit=true;
	m_hWnd=NULL;
	m_lParam=NULL;
	return 0;
}


LRESULT CWind::WindProc(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam)
{
	return DefWindowProc(hWnd,Msg,wParam,lParam);
}

DWORD CWind::CreateWind(LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu,LPVOID lpParam)
{
	m_lParam=lpParam;
	m_hWnd=CreateWindow(CLASS_NAME,lpWindowName,dwStyle,x,y,nWidth,nHeight,hWndParent,hMenu,hProg,this);
	if (!m_hWnd)
		return 1;
	return 0;
}

DWORD CWind::CreateWindEx(DWORD dwExStyle, LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, LPVOID lpParam)
{
	m_lParam=lpParam;
	m_hWnd=CreateWindowEx(dwExStyle,CLASS_NAME,lpWindowName,dwStyle,x,y,nWidth,nHeight,hWndParent,hMenu,hProg,this);
	if (!m_hWnd)
		return 1;
	return 0;
}
