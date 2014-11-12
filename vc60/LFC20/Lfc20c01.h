/*
	Esta clase es un soporte para el uso de 
	ventanas en windows
	Su unica funcion permitir el procesamiento de
	mensajes a traves del procedimento 
	WindProc
*/
#if !defined(AFX_LFC20C01_H__FFB7F796_D3A8_11D4_8637_00D0093D4380__INCLUDED_)
#define AFX_LFC20C01_H__FFB7F796_D3A8_11D4_8637_00D0093D4380__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "lfc20.h"

#define LFC_CLASSNAME "lfc20wnd"

class LFC20_API  CLFCWnd  
{
public:
	DWORD Create(const char* lpWindowName,DWORD dwStyle,int x,int y,int nWidth,int nHeight,HWND hWndParent,HMENU hMenu,HINSTANCE hInstance,LPVOID lpParam);
	LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LPVOID GetlpParam();
	DWORD SetlpParam(LPVOID pParam);
	LPVOID m_lpParam;
	HWND m_hWnd;
	CLFCWnd();
	virtual ~CLFCWnd();

};

#endif // !defined(AFX_LFC20C01_H__FFB7F796_D3A8_11D4_8637_00D0093D4380__INCLUDED_)
