// g3dc02.cpp: implementation of the C3DDXViewGame class.
//
//////////////////////////////////////////////////////////////////////

#include "g3dc02.h"


LRESULT CALLBACK ViewGameWndProc(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam)
{
	C3DDXViewGame*	lpWnd;
	if ((Msg == WM_CREATE) || (Msg == WM_NCCREATE))
	{
		CREATESTRUCT*	lpcs;
		lpcs = (CREATESTRUCT*)lParam;
		lpWnd = (C3DDXViewGame*) lpcs->lpCreateParams;
		::SetWindowLong(hWnd,GWL_USERDATA,(long)lpWnd);
	}
	else
		lpWnd = (C3DDXViewGame*)::GetWindowLong(hWnd,GWL_USERDATA);
	if (lpWnd)
		return lpWnd->WindowProc(hWnd,Msg,wParam,lParam);
	else
		return DefWindowProc(hWnd,Msg,wParam,lParam);
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

C3DDXViewGame::C3DDXViewGame()
{

}

C3DDXViewGame::~C3DDXViewGame()
{

}

DWORD C3DDXViewGame::Initialize()
{
	return 0;
}

DWORD C3DDXViewGame::Release()
{
	return 0;
}

DWORD C3DDXViewGame::RegisterClass()
{
	return 0;
}

DWORD C3DDXViewGame::CreateDirectX()
{
	return 0;
}

LRESULT C3DDXViewGame::WindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	return 0;
}

DWORD C3DDXViewGame::CreateWnd()
{
	return 0;
}
