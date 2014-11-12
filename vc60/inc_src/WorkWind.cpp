// WorkWind.cpp: implementation of the CWorkWind class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WorkWind.h"
#include "errorcodes.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWorkWind::CWorkWind()
{
	m_IdbView = NULL;
}

CWorkWind::~CWorkWind()
{

}

LRESULT _stdcall CWorkWind::OnWindProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case UM_SETCONTENT	: return OnSetContent((IdbView*)wParam);
	case WM_ERASEBKGND	: return OnEraseBkgnd((HDC)wParam); 
	case UM_CLOSECONTENT: return OnCloseContent(wParam,(void*)lParam);
//	case UM_DELCONTENT  : return DeleteContent();
	case WM_SIZE		: return OnSize(LOWORD(lParam),HIWORD(lParam),wParam);		
	default:
		return OnDefWindowProc(uMsg,wParam,lParam);
		/*
		if (m_IdbView) 
			return m_IdbView->OnWindProc(hWnd,uMsg,wParam,lParam);
		else
			return DefWindowProc(hWnd,uMsg,wParam,lParam);
			*/
	}
	return ERR_NONE;
}

DWORD CWorkWind::Create(int x, int y, int nWidth, int nHeight, HWND hWndParent)
{
	CWind::CreateEx(NULL,WS_CHILD|WS_VISIBLE,0,x,y,nWidth,nHeight,hWndParent,NULL,NULL);
	return 0;
}

LRESULT CWorkWind::OnSetContent(IdbView *lpIdbView)
{
	DBGUI*		gui;
	WORD		i,j;
	DWORD		dr;
	HWND		hparent;
	::LockWindowUpdate(*this);
	if (m_IdbView) 
	{
		::ShowWindow(*m_IdbView,SW_HIDE);
	}
	lpIdbView->SetPrevPtr(m_IdbView);
	
	m_IdbView = lpIdbView;
	if (m_IdbView)
	{
		lpIdbView->GetGui(&gui);
		if (gui->hfont == NULL)
		{
			gui->hfont = ::CreateFontIndirect(&gui->font);
			// contruccion de ventanas
			for (i=0;i<gui->ctrlCount;i++)
			{
				hparent = *this;
				if (gui->ctrls[i].parentid != 0)
				{
					for (j=0;j<gui->ctrlCount;j++)
						if (gui->ctrls[j].id == gui->ctrls[i].parentid)
						{
							hparent = gui->ctrls[j].hwnd;
							break;
						}
				}
				char* className; 
				className = NULL;
				switch (gui->ctrls[i].type)
				{
				case CTRL_BUTTON:	className = "BUTTON";break;
				case CTRL_LABEL:	className = "STATIC";break;
				case CTRL_EDIT:		className = "EDIT";break;
				case CTRL_COMBOBOX:	className = "COMBOBOX";break;
				}
				if (className != NULL) gui->ctrls[i].hwnd = CreateWindowEx(gui->ctrls[i].exstyle,className,gui->ctrls[i].caption,gui->ctrls[i].style,gui->ctrls[i].x,gui->ctrls[i].y,gui->ctrls[i].width,gui->ctrls[i].height,hparent,(HMENU)gui->ctrls[i].id,(HINSTANCE)GetModuleHandle(NULL),NULL);
				lpIdbView->OnCreateCtrl(i);
				if (gui->ctrls[i].hwnd == NULL) return ERR_APIFAIL;
				::SendMessage(gui->ctrls[i].hwnd,WM_SETFONT,(WPARAM)gui->hfont,TRUE);
			}
		}
		::SendMessage(*m_IdbView,UM_DESKTOP_SIZE,0,0);
		::ShowWindow(*m_IdbView,SW_SHOW);
		::SetFocus(*m_IdbView);
		m_IdbView->OnInitView();
	}
	::LockWindowUpdate(NULL);
	return 0;
}

LRESULT CWorkWind::OnEraseBkgnd(HDC hdc)
{
	RECT	rect;
	HPEN	hPen;
	void*	hOldPen;
	int		radios;
	GetClientRect(*this,&rect);
	DWORD color = RGB(58,110,165);//RGB(0,0,0);//RGB(58,110,165);//::GetSysColor(COLOR_3DFACE);
	SetBkColor(hdc,color);
	::ExtTextOut(hdc,0,0,ETO_OPAQUE,&rect,NULL,0,NULL);
	
	hPen = ::CreatePen(PS_SOLID,1,RGB(255,255,255));
	hOldPen = SelectObject(hdc,hPen);
	radios = rect.right*rect.right + rect.bottom*rect.bottom;
	radios = (int)sqrt(radios);
	radios /= 2;
	int step = 10;
	for (int i = step;i< radios;i+=step)
	{
		::Arc(hdc,-i,-i,i,i,0,i,i,0);
		::Arc(hdc,rect.right-i,-i,rect.right+i,i,rect.right-i,0,rect.right,i);
		::Arc(hdc,-i,rect.bottom-i,i,rect.bottom+i,i,rect.bottom,0,rect.bottom-i);
		::Arc(hdc,-i,-i,i,i,0,i,i,0);
	}
	SelectObject(hdc,hOldPen);
	
	return TRUE;
}

LRESULT CWorkWind::OnSize(WORD wWidth, WORD wHeight, UINT uType)
{
	if ((m_IdbView) && (uType == SIZE_RESTORED))
		::SendMessage(*m_IdbView,UM_DESKTOP_SIZE,0,0);
	return 0;
}
// CBS_AUTOHSCROLL
// CBS_DISABLENOSCROLL

DWORD CWorkWind::OnCloseContent(DWORD dwCode, void *pParam)
{
	return 0;
}
