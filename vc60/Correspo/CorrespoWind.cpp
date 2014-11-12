// CorrespoWind.cpp: implementation of the CCorrespoWind class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CorrespoWind.h"
#include "errorcodes.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCorrespoWind::CCorrespoWind()
{

}

CCorrespoWind::~CCorrespoWind()
{

}

DWORD CCorrespoWind::Create_Window()
{
	DWORD r;
	r = CreateEx("Sistema de correspondencia (PerSoft®)",WS_CAPTION|WS_VISIBLE|WS_OVERLAPPEDWINDOW,0,0,0,600,400,NULL,NULL,NULL);
	if (r != ERR_NONE) return r;
	//
	RECT rect;
	::GetClientRect(*this,&rect);
	m_WorkWind.Create(rect.left,rect.top,rect.right-rect.left,rect.bottom-rect.top,*this);
	BROWSEINFO bi;
//	LPITEMIDLIST ilist;
//	char	str[200];
	bi.hwndOwner = *this;
	bi.pidlRoot  = NULL;
	bi.pszDisplayName = NULL;
	bi.lpszTitle  = "sonso";
	bi.ulFlags = BIF_RETURNONLYFSDIRS ;
	bi.lpfn = NULL;
	bi.lParam  = 0;
	//ilist = SHBrowseForFolder(&bi);
	//SHGetPathFromIDList(SHBrowseForFolder(&bi),str);
	m_StartView.Show(m_WorkWind);
	return 0;
}

LRESULT _stdcall CCorrespoWind::OnWindProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_GETMINMAXINFO: return OnGetMinMaxInfo(wParam,lParam);
	case WM_SIZE:	return OnSize(wParam,lParam);
	case WM_SETFOCUS:	return OnSetFocus((HWND)wParam);
	case WM_DESTROY:
		PostQuitMessage(0);
	default:
		return OnDefWindowProc(uMsg,wParam,lParam);
		//return DefWindowProc(hWnd,uMsg,wParam,lParam);
	}
	return ERR_NONE;
}

LRESULT CCorrespoWind::OnSize(WPARAM wParam, LPARAM lParam)
{
	WORD width = LOWORD(lParam);
	WORD height = HIWORD(lParam);
	MoveWindow(m_WorkWind,0,0,width,height,TRUE);
	return 0;
}

LRESULT CCorrespoWind::OnGetMinMaxInfo(WPARAM wParam, LPARAM lParam)
{
	LPMINMAXINFO MinMaxInfo = (LPMINMAXINFO)lParam;
	MinMaxInfo->ptMinTrackSize.x = 600;
	MinMaxInfo->ptMinTrackSize.y = 400;
	return 0;
}

LRESULT CCorrespoWind::OnSetFocus(HWND hOldWnd)
{
	if (m_WorkWind.m_IdbView) ::SetFocus(*m_WorkWind.m_IdbView);
	return 0;
}

DWORD CCorrespoWind::Initialize()
{
	Correspodb.Initialize();
	m_StartView.Initialize();
	return 0;
}

DWORD _stdcall CCorrespoWind::PreTranslateMessage(MSG *pMsg)
{
	if (m_WorkWind.m_IdbView) return m_WorkWind.m_IdbView->PreTranslateMessage(pMsg);
	return false;		
}
