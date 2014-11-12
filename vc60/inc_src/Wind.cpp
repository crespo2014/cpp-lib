// Wind.cpp: implementation of the CWind class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Wind.h"
#include "errorcodes.h"

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
		lpBWnd->m_hwnd = hWnd;
	}
	else
		lpBWnd = (CWind*)::GetWindowLong(hWnd,GWL_USERDATA);
	if (lpBWnd)
		return lpBWnd->OnWindProc(hWnd,Msg,wParam,lParam);
	else
		return DefWindowProc(hWnd,Msg,wParam,lParam);
}

DWORD RegisterCWind()
{
	WNDCLASSEX	wcx;
	wcx.cbSize=sizeof(wcx);
	wcx.cbClsExtra=0;
	wcx.cbWndExtra=DLGWINDOWEXTRA;
	wcx.hbrBackground= HBRUSH (COLOR_WINDOW+1);
	wcx.hCursor=0;
	wcx.hIcon=0;
	wcx.hIconSm=0;
	wcx.hInstance=(HINSTANCE)GetModuleHandle(NULL);
	wcx.lpfnWndProc=CWindProc;
	wcx.lpszClassName=CWindClassName;
	wcx.lpszMenuName=0;
	wcx.style=CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS ;
	if (RegisterClassExA(&wcx) == 0)
		return ERR_APIFAIL;
	return ERR_NONE;
}


CWind::CWind()
{
	m_hwnd = NULL;
	m_lpParam = NULL;
	m_hOldFocusWind = 0;
	m_BkgndColor = ::GetSysColor(COLOR_3DFACE);
	m_bEnable = false;
	m_bCapture = false;
	m_bEraseBkgnd = true;
	m_Pos = 0;
}

CWind::~CWind()
{

}

DWORD CWind::Create(LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu,LPVOID lpParam)
{
	return CreateEx(lpWindowName,dwStyle,0,x,y,nWidth,nHeight,hWndParent,hMenu,lpParam);
}

DWORD CWind::Invalidate()
{
	if (m_hwnd) ::InvalidateRect(m_hwnd,NULL,true);
	return 0;
}

DWORD CWind::EnableWindow(BOOL bEnable)
{
	if (m_hwnd) ::EnableWindow(m_hwnd,bEnable);
	return 0;
}

DWORD CWind::CreateEx(LPCTSTR lpWindowName, DWORD dwStyle, DWORD dwExStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu,LPVOID lpParam)
{
	if (m_hwnd != NULL) DestroyWindow(m_hwnd);
	m_lpParam = lpParam;
	m_hwnd = CreateWindowEx(dwExStyle,CWindClassName,lpWindowName,dwStyle,x,y,nWidth,nHeight,hWndParent,hMenu,(HINSTANCE)GetModuleHandle(NULL),this);
	if (m_hwnd == NULL)
		return 1;
	m_hNotifyWind = hWndParent;
	return 0;
}

DWORD CWind::CenterWindow()
{
	RECT	windowrect;
	RECT	parentrect;
	int		parentWidth;
	int		parentHeight;
	int		windowHeight;
	int		windowWidth;
	HWND hParent;
	hParent = GetParent(*this);
	if (!hParent) return 0;
	::GetWindowRect(hParent,&parentrect);
	::GetWindowRect(*this,&windowrect);
	windowWidth = windowrect.right-windowrect.left;
	windowHeight = windowrect.bottom-windowrect.top;
	parentWidth = parentrect.right-parentrect.left;
	parentHeight = parentrect.bottom-parentrect.top;
	::MoveWindow(*this,(parentWidth-(windowWidth))/2,(parentHeight-(windowHeight))/2,windowWidth,windowHeight,true);
	return 0;
}

LRESULT CWind::OnDefWindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg >= WM_LAST) return ERR_INV_FUNC;
	// procesamiento por defecto cuando es un dialogo
	switch(uMsg)
	{
	case WM_CAPTURECHANGED: {m_bCapture = false;break;}
	case WM_COMMAND :		return OnCommand(HIWORD(wParam),LOWORD(wParam),(HWND)lParam);
	case WM_SETFOCUS:		return OnSetFocus((HWND)wParam);
	case WM_KILLFOCUS:		return OnKillFocus();
	case WM_ERASEBKGND:		return OnEraseBkgnd((HDC)wParam);
	case UM_DESKTOP_SIZE:	return CenterWindow();
	case WM_MOUSEMOVE:		return OnMouseMove(wParam,LOWORD(lParam),HIWORD(lParam));
	case WM_SETFONT:		return OnSetFont((HFONT)wParam,(BOOL)lParam);
	case UM_CNOTIFY:		return OnChildNotify((CNTFDATA*)wParam,(void*)lParam);
	case WM_ENABLE:			return OnEnable(wParam);
	case WM_DESTROY:		return OnDestroy();	
	case DM_SETDEFID:	
	case DM_GETDEFID:	
	case WM_NEXTDLGCTL:		return DefDlgProc(*this,uMsg,wParam,lParam);
	}
	return DefWindowProc(*this,uMsg,wParam,lParam);
}

LRESULT CWind::OnCommand(WORD wCode, WORD wId, HWND hWind)
{
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
	return 0;
}

LRESULT CWind::OnSetFocus(HWND hOldWnd)
{
	if (m_hOldFocusWind) 
	{
		::SetFocus(m_hOldFocusWind);
		return 0;
	}
	if (m_hNotifyWind)
	{
		CNTFDATA cNtfData;
		cNtfData.ctrlID = GetWindowLong(*this,GWL_ID);
		cNtfData.hwnd = *this;
		cNtfData.message = CN_SETFOCUS;
		::SendMessage(m_hNotifyWind,UM_CNOTIFY,(WPARAM)&cNtfData,NULL);
	}
	m_bOnFocus = true;
	return 0;
}

LRESULT CWind::OnEraseBkgnd(HDC hdc)
{
	if (!m_bEraseBkgnd) return 0;
	RECT rect;
	GetClientRect(*this,&rect);
	SetBkColor(hdc,m_BkgndColor);
	::ExtTextOut(hdc,0,0,ETO_OPAQUE,&rect,NULL,0,NULL);
	return TRUE;
}

DWORD CWind::SetBackgroundColor(COLORREF crBckgndColor)
{
	m_BkgndColor = crBckgndColor;
	return 0;
}

LRESULT CWind::OnMouseMove(UINT uFlags, WORD x, WORD y)
{
	SetCursor(LoadCursor(NULL,IDC_ARROW));
	return 0;
}

LRESULT CWind::OnSetFont(HFONT hfont, BOOL bRedraw)
{
	m_hFont = hfont;
	if (bRedraw) Invalidate();
	return 0;
}

LRESULT CWind::OnChildNotify(CNTFDATA* pCNData, void *pvoid)
{
	switch (pCNData->message)
	{
	case CN_SETFOCUS: m_hOldFocusWind = pCNData->hwnd;break;
	}
	return 0;
}

LRESULT CWind::OnEnable(BOOL bEnable)
{
	m_bEnable = bEnable;
	return 0;
}

LRESULT CWind::OnDestroy()
{
	m_hwnd = NULL;
	return 0;
}

DWORD CWind::SetCapture()
{
	::SetCapture(m_hwnd);
	m_bCapture = true;
	return 0;
}

LRESULT CWind::OnKillFocus()
{
	m_bOnFocus = false;
	return 0;
}

DWORD CWind::DecPos(DWORD dwMinPos)
{
	if (m_Pos > dwMinPos) m_Pos--;
	return 0;
}

DWORD CWind::SetPos(DWORD dwPos)
{
	m_Pos = dwPos;
	return 0;
}

DWORD CWind::GetPos(DWORD *pdwPos)
{
	*pdwPos = m_Pos;
	return 0;
}

DWORD CWind::SetPrevPtr(void* pvoid)
{
	return 0;
}
