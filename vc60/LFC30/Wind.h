// Wind.h: interface for the CWind class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WIND_H__8D26D92A_0755_11D5_94D9_00D0093D4380__INCLUDED_)
#define AFX_WIND_H__8D26D92A_0755_11D5_94D9_00D0093D4380__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "lfc30def.h"



class LFC30_API CWind 
{
public:
	DWORD CreateWindEx(DWORD dwExStyle,LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu,LPVOID lpParam);
	DWORD CreateWind(LPCTSTR lpWindowName,DWORD dwStyle,int x,int y,int nWidth,int nHeight,HWND hWndParent,HMENU hMenu,LPVOID lpParam);
	virtual LRESULT WindProc(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);

	DWORD Initialize();
	BOOL	m_OnInit;
	HWND	m_hWnd;
	LPVOID	m_lParam;
	CWind();
	~CWind();
	/*
		Funciones virtuales
	*/
//	LPWINDPROC	VFWindProc;


};

#endif // !defined(AFX_WIND_H__8D26D92A_0755_11D5_94D9_00D0093D4380__INCLUDED_)
