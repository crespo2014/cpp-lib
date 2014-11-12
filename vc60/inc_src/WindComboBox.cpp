// WindComboBox.cpp: implementation of the CWindComboBox class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WindComboBox.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define BS_PUSHED	1	// button style pushed
#define BS_UNPUSHED	2

CWindComboBox::CWindComboBox()
{
	m_SelID = DB_INVALID_ID;
	m_SelRow = INVALID_INDEX;
	m_pIdbArray = NULL;
	m_IDdbIndex = DB_ID_CINDEX;
	m_VisibledbIndex = DB_CAT_CINDEX;
	m_bPushed = false;
	SetBackgroundColor(RGB(255,255,255));
	m_bDropDown = false;
	m_bEraseBkgnd = false; 
}

CWindComboBox::~CWindComboBox()
{

}

LRESULT _stdcall CWindComboBox::OnWindProc(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lr;
	switch (uMsg)
	{
	case WM_PAINT:			return OnPaint();
	case WM_LBUTTONDOWN:	return OnLButtonDown(wParam,GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam));
	case WM_MOUSEMOVE:		return OnMouseMove(wParam,GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam)); 
	case WM_LBUTTONUP:		return OnLButtonUp(wParam,GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam));
	case UM_GET_INTERFAZ:	return OnGetInterfaz((char*)wParam,(_IUnknown**)lParam);
	case CB_GETIDSEL:		return OnGetSelID((DWORD*)wParam);
	case CB_SETIDSEL:		return OnSetSelID(wParam);
	case CB_SETDBINDEX:		return SetdbIndex(wParam,lParam);
	case CB_SETROWSEL:		return SetRowSel(wParam);
	case UM_CNOTIFY:		return OnChildNotify((CNTFDATA*)wParam,(GNOTIFY*)lParam);
	case WM_GETDLGCODE:		return OnGetDlgCode((MSG*)wParam);
	default:
		if ((m_bDropDown) && (uMsg >= WM_KEYFIRST)&&(uMsg <= WM_KEYLAST)) return SendMessage(m_grid,uMsg,wParam,lParam);
	}
	lr = OnDefWindowProc(uMsg,wParam,lParam);
	switch (uMsg)
	{
	case WM_SETFOCUS:
	case WM_KILLFOCUS:	DrawItem(NULL);break;
	case WM_ENABLE:		Draw(NULL);break;
	}
	return lr;
}

DWORD CWindComboBox::Draw(HDC hdc)
{
	BOOL	bDelDc = false;
	if (hdc == NULL)
	{
		hdc = ::GetDC(*this);
		if (hdc == NULL) return 0;
		bDelDc = true;
	}
	DrawItem(hdc);
	// Dibujar boton
	m_bPushed = false;
	DrawButtom(hdc);
	if (bDelDc) ::ReleaseDC(*this,hdc);
	return 0;
}

LRESULT CWindComboBox::OnPaint()
{
	PAINTSTRUCT pStruct;
	HDC hdc = BeginPaint(*this,&pStruct);
	if (hdc == NULL) return 0;
	Draw(hdc);
	if (!::EndPaint(*this,&pStruct)) return 0;
	return 0;
}

DWORD CWindComboBox::DrawButtom(HDC hdc)
{
	RECT	rect;
	void*	oldpen;
	int		sx = 0;
	int		sy = 0;
	HPEN grispen = ::CreatePen(PS_SOLID,1,RGB(214,211,206));
	HPEN blackpen = ::CreatePen(PS_SOLID,1,RGB(0,0,0));
	HPEN whitepen = ::CreatePen(PS_SOLID,1,RGB(255,255,255));
	HPEN disablePen1 = ::CreatePen(PS_SOLID,1,RGB(132,130,132));
	HPEN disablePen2 = ::CreatePen(PS_SOLID,1,RGB(255,255,255));
	GetClientRect(*this,&rect);
	rect.left = rect.right - 16;
	oldpen = ::SelectObject(hdc,blackpen);
	// background
	SetBkColor(hdc,GetSysColor(COLOR_3DFACE));
	::ExtTextOut(hdc,0,0,ETO_OPAQUE,&rect,NULL,0,NULL);
	if (m_bPushed)
	{
		::SelectObject(hdc,blackpen);
		::MoveToEx(hdc,rect.left,rect.top,NULL);
		::LineTo(hdc,rect.right-1,rect.top);
		::LineTo(hdc,rect.right-1,rect.bottom-1);
		::LineTo(hdc,rect.left,rect.bottom-1);
		::LineTo(hdc,rect.left,rect.top);
		sx = 5+rect.left;
		sy = (rect.bottom -rect.top)/2-1;
	}
	else
	{
		::SelectObject(hdc,blackpen);
		::MoveToEx(hdc,rect.right-1,rect.top,NULL);
		::LineTo(hdc,rect.right-1,rect.bottom-1);
		::LineTo(hdc,rect.left,rect.bottom-1);
		::LineTo(hdc,rect.left+1,rect.bottom-2);
		::LineTo(hdc,rect.right-2,rect.bottom-2);
		::LineTo(hdc,rect.right-2,rect.top);
		::SelectObject(hdc,grispen);
		::LineTo(hdc,rect.left,rect.top);
		::LineTo(hdc,rect.left,rect.bottom-2);
		::LineTo(hdc,rect.left+1,rect.bottom-3);
		::SelectObject(hdc,whitepen);
		::LineTo(hdc,rect.left+1,rect.top+1);
		::LineTo(hdc,rect.right-2,rect.top+1);
		sx = 4+rect.left;
		sy = (rect.bottom -rect.top)/2-2;
	}
	if (m_bEnable) 
		::SelectObject(hdc,blackpen);
	else 
		::SelectObject(hdc,disablePen1);
	::MoveToEx(hdc,sx,sy,NULL);
	::LineTo(hdc,sx+6,sy);
	::LineTo(hdc,sx+5,sy+1);
	::LineTo(hdc,sx+1,sy+1);
	::LineTo(hdc,sx+2,sy+2);
	::LineTo(hdc,sx+4,sy+2);
	::LineTo(hdc,sx+2,sy+4);
	if (!m_bEnable)
	{
		::SelectObject(hdc,disablePen2);
		::MoveToEx(hdc,sx+7,sy+1,NULL);
		::LineTo(hdc,sx+4,sy+4);
		::LineTo(hdc,sx+4,sy+3);
		::LineTo(hdc,sx+6,sy+1);
		::LineTo(hdc,sx+7,sy+1);
	}
	::SelectObject(hdc,oldpen);
	::DeleteObject(grispen);
	::DeleteObject(blackpen);
	::DeleteObject(whitepen);
	::DeleteObject(disablePen1);
	::DeleteObject(disablePen2);
	return 0;
}

DWORD CWindComboBox::SetMemArray(IDBArray* pIdbArray)
{
	m_pIdbArray = pIdbArray;
	m_grid.SetDBArray(pIdbArray);
	return ERR_NONE;
}

LRESULT CWindComboBox::OnLButtonDown(UINT nFlags, int x, int y)
{
	SetFocus(*this);
	RECT rect;
	GetClientRect(*this,&rect);	
	if ((x > rect.right - 16) && 
		(x < rect.right) &&
		(y > rect.top)&&
		(y < rect.bottom))
	{
		SetCapture();
		m_bPushed = true;
		HDC hdc = GetDC(*this);
		DrawButtom(hdc);
		ReleaseDC(*this,hdc);
		m_grid.OnSetFont(m_hFont,true);
		m_grid.ShowPopup(*this,200);
		m_bDropDown = true;
	}
	return 0;
}

LRESULT CWindComboBox::OnMouseMove(UINT nFlags, int x, int y)
{
	RECT rect;
	GetClientRect(*this,&rect);	
	if (m_bPushed)
	{
		if ((x < rect.right - 16)||
			(x > rect.right)||
			(y < rect.top)||
			(y > rect.bottom))
		{
			UnPush();
		}
	}
	return 0;
}

LRESULT CWindComboBox::OnLButtonUp(UINT nFlags, int x, int y)
{
	if (m_bPushed) UnPush();
	return 0;
}

LRESULT CWindComboBox::OnGetInterfaz(char *lpzsName, _IUnknown **lplpIUnknown)
{
	if (m_pIdbArray) return ((_IUnknown *)m_pIdbArray)->GetInterfaz(lpzsName,(void**)lplpIUnknown);
	*lplpIUnknown = NULL;
	return ERR_NOINTERFACE;
}

LRESULT CWindComboBox::OnGetSelID(DWORD *lpdwSelID)
{
	*lpdwSelID = m_SelID;
	return 0;
}

DWORD CWindComboBox::CheckTrackChange()
{
	DWORD	dr;
	DWORD	trackChange;
	if (!m_pIdbArray) return 0;
	trackChange = m_pIdbArray->GetChangeNo();
	if (trackChange != m_TrackChange)
	{
		if (m_SelID == DB_INVALID_ID) return 0;
		// buscar row 
		dr = m_pIdbArray->Find(0,DB_ID_CINDEX,(_VARIANT*)&m_SelID,&m_SelRow);
	}
	return 0;
}

DWORD CWindComboBox::SetdbIndex(DWORD dwIDIndex, DWORD dwVisibleIndex)
{
	m_IDdbIndex = dwIDIndex;
	m_VisibledbIndex = dwVisibleIndex;
	return 0;
}


LRESULT CWindComboBox::OnChildNotify(CNTFDATA *pCNData, GNOTIFY *pgNotify)
{
	switch (pCNData->message)
	{
	case GN_SELCHANGE:
		{
			SetRowSel(pgNotify->rowIndex);
			break;
		}
	default: return CWind::OnChildNotify(pCNData,pgNotify);
	}
	return 0;	
}

DWORD CWindComboBox::SetRowSel(DWORD dwRowIndex)
{
	DWORD		dr;
	WORD		ColumnIndex;
	_VARIANT*	pvariant;
	DWORD		tmpID = m_SelID;

	m_SelID = DB_INVALID_ID;
	m_SelRow = INVALID_INDEX;
	dr = m_pIdbArray->GetColumn(m_IDdbIndex,&ColumnIndex);
	if (dr != ERR_NONE) return dr;
	dr = m_pIdbArray->GetDataPrtAt(dwRowIndex,ColumnIndex,(void**)&pvariant);
	if (dr != ERR_NONE) return dr;
	m_SelID = pvariant->ulVal;
	m_SelRow = dwRowIndex;
	if (tmpID == m_SelID) return 0;
	// Notificar
	::SendMessage(m_hNotifyWind,WM_COMMAND,MAKEWPARAM(GetDlgCtrlID(*this),CBN_SELCHANGE),(WPARAM)m_hwnd);
	Invalidate();
	return 0;
}

DWORD CWindComboBox::DrawItem(HDC hdc)
{
	// Nota usar rectangle
	ITEM_DATA	itemData;
	RECT		rect;
	DWORD		dr;
	WORD		ColumnIndex;
	BOOL		bDelDc = false;
	COLORREF	windowColor;
	if (hdc == NULL)
	{
		hdc = ::GetDC(*this);
		if (hdc == NULL) return 0;
		bDelDc = true;
	}
	GetClientRect(*this,&rect);
	void*	holdfont = ::SelectObject(hdc,m_hFont);
	rect.right -= 16;	// boton
	if (!m_bEnable) 
	{
		itemData.backColor = GetSysColor(COLOR_3DFACE);
		itemData.textColor = RGB(0,0,0);
		windowColor = itemData.backColor;
	}
	else
	{
		windowColor = GetSysColor(COLOR_WINDOW);
		if (m_bOnFocus) 
		{
			itemData.backColor = GetSysColor(COLOR_HIGHLIGHT);
			itemData.textColor = GetSysColor(COLOR_HIGHLIGHTTEXT);
		}
		else
		{
			itemData.backColor = GetSysColor(COLOR_WINDOW);
			itemData.textColor = GetSysColor(COLOR_WINDOWTEXT);
		}
	}
	// dibujar borde
	SetBkColor(hdc,windowColor);
	::ExtTextOut(hdc,0,0,ETO_OPAQUE,&rect,NULL,0,NULL);
	
	// item
	rect.bottom --; rect.right--;rect.left++;rect.top++;
	itemData.hFont = m_hFont;
	itemData.bEnable = m_bEnable;
	itemData.bFocused = m_bOnFocus;
	itemData.bSelected = m_bOnFocus;
	itemData.pzsText = NULL;
	itemData.uFormat = 0;
	itemData.rect = rect;

	SetBkColor(hdc,itemData.backColor);
	SetTextColor(hdc,itemData.textColor);
	if (windowColor != itemData.backColor)
	{	
		::ExtTextOut(hdc,0,0,ETO_OPAQUE,&rect,NULL,0,NULL);
	}
	
	do
	{
		if (m_SelID == DB_INVALID_ID) break;
		if (!m_pIdbArray) break;
		CheckTrackChange();
		dr = m_pIdbArray->GetColumn(m_VisibledbIndex,&ColumnIndex);
		itemData.dwRowIndex = m_SelRow;
		itemData.wColumnIndex = ColumnIndex;
		m_pIdbArray->DrawItem(hdc,&itemData);
	} while(false);
	::SelectObject(hdc,holdfont);
	if (bDelDc) ::ReleaseDC(*this,hdc);
	return 0;
}

DWORD CWindComboBox::UnPush()
{
	m_bPushed = false;
	HDC hdc = GetDC(*this);
	DrawButtom(hdc);
	ReleaseDC(*this,hdc);
	m_grid.SetCapture();
	return 0;
}


DWORD CWindComboBox::OnSetSelID(DWORD dwSelID)
{
	DWORD	dr;
	DWORD	trackChange;
	m_SelID = dwSelID;
	if (!m_pIdbArray) return 0;
	if (m_SelID != DB_INVALID_ID)
	{
		// buscar row 
		dr = m_pIdbArray->Find(0,DB_ID_CINDEX,(_VARIANT*)&m_SelID,&m_SelRow);
	}
	DrawItem(NULL);
	return 0;
}

LRESULT CWindComboBox::OnGetDlgCode(MSG *pMsg)
{
	return DLGC_WANTARROWS|DLGC_WANTCHARS;
}
