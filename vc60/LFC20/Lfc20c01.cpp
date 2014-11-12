// LFC20C01.cpp: implementation of the CLFCWnd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LFC20C01.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLFCWnd::CLFCWnd()
{
	m_hWnd=NULL;	
}

CLFCWnd::~CLFCWnd()
{

}

DWORD CLFCWnd::SetlpParam(LPVOID pParam)
{
	m_lpParam=pParam;
	return 0;
}

LPVOID CLFCWnd::GetlpParam()
{
	return m_lpParam; 
}

LRESULT CLFCWnd::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return 0;
}

DWORD CLFCWnd::Create(const char *lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
	SetlpParam(lpParam);
	m_hWnd=CreateWindow(LFC_CLASSNAME,lpWindowName,dwStyle,x,y,nWidth,nHeight,hWndParent,hMenu,hInstance,this);
	if (m_hWnd != NULL)
		return 0;
	return 1;
}
