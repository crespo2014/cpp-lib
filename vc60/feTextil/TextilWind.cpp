// TextilWind.cpp: implementation of the CTextilWind class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TextilWind.h"
#include "textildb.h"
#include "resource.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTextilWind::CTextilWind()
{

}

CTextilWind::~CTextilWind()
{

}

DWORD CTextilWind::Create_Window()
{
	DWORD r;
	r = CreateEx("Sistema de gestion textil (PerSoft®)",WS_CAPTION|WS_VISIBLE|WS_OVERLAPPEDWINDOW,0,0,0,600,400,
		NULL,LoadMenu(NULL,"main_menu"),NULL);
	if (r != ERR_NONE) return r;
	//
	RECT rect;
	::GetClientRect(*this,&rect);
	m_WorkWind.Create(rect.left,rect.top,rect.right-rect.left,rect.bottom-rect.top,*this);
	return 0;
}

LRESULT _stdcall CTextilWind::OnWindProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_GETMINMAXINFO:	return OnGetMinMaxInfo(wParam,lParam);
	case WM_COMMAND:		return OnCommand(HIWORD(wParam),LOWORD(wParam),(HWND)lParam);
	case WM_SIZE:			return OnSize(wParam,lParam);
	case WM_SETFOCUS:		return OnSetFocus((HWND)wParam);
	case WM_DESTROY:
		PostQuitMessage(0);
	default:
		return OnDefWindowProc(uMsg,wParam,lParam);
	}
	return ERR_NONE;
}

LRESULT CTextilWind::OnSize(WPARAM wParam, LPARAM lParam)
{
	WORD width = LOWORD(lParam);
	WORD height = HIWORD(lParam);
	MoveWindow(m_WorkWind,0,0,width,height,TRUE);
	return 0;
}

LRESULT CTextilWind::OnGetMinMaxInfo(WPARAM wParam, LPARAM lParam)
{
	LPMINMAXINFO MinMaxInfo = (LPMINMAXINFO)lParam;
	MinMaxInfo->ptMinTrackSize.x = 600;
	MinMaxInfo->ptMinTrackSize.y = 400;
	return 0;
}

LRESULT CTextilWind::OnSetFocus(HWND hOldWnd)
{
	if (m_WorkWind.m_IdbView) ::SetFocus(*m_WorkWind.m_IdbView);
	return 0;
}

DWORD CTextilWind::Initialize()
{
	Textildb.Initialize();
	return 0;
}

DWORD _stdcall CTextilWind::PreTranslateMessage(MSG *pMsg)
{
	if (m_WorkWind.m_IdbView) return m_WorkWind.m_IdbView->PreTranslateMessage(pMsg);
	return false;		
}

LRESULT CTextilWind::OnCommand(WORD wCode, WORD wId, HWND hWind)
{
	/*
	switch(wCode)
	{
	case EN_KILLFOCUS:
	case BN_KILLFOCUS:
	case CBN_KILLFOCUS:
	case LBN_KILLFOCUS:
		{
			m_hOldFocusWind = hWind;
		}
	}
	*/
	if (wCode != 0) return 0;
	switch(wId)
	{
	case CAT_CLIENTES:
		{
			Textildb.Open();
			break;
		}
	}
	return 0;
}
