// EditList.cpp: implementation of the CEditList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EditList.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
/*
	Indicaciones utiles.
		row - se cuenta de forma absoluta
			0 - Header
			1 - Primera fila mostrable 
			65535 - Ultima fila mostrable
*/

char* LBLCAMPO = "Campo";
char* LBLVALOR = "Valor";

// Estados del mouse
#define MOUSE_NONE 0
#define MOUSE_EDIT 1

CEditList::CEditList()
{
	m_FirstRow = 1;
	m_Column0Width = 100;
	m_IDBClass = NULL;
	m_FirstColumn = 0;

	m_cellTopMargin = 1;
	m_cellRigthMargin = 1;
	m_cellBottomMargin = 1;
	m_cellLeftMargin = 1;

	m_RightMargin = 0;	
	m_LeftMargin  = 0;

}

CEditList::~CEditList()
{

}

LRESULT CEditList::WndProc(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_PAINT:		 return OnPaint();
	case WM_VSCROLL:	 return OnVScroll(wParam);
	case WM_LBUTTONDOWN: return OnLButtonDown(wParam,lParam);
	case WM_LBUTTONUP:	 return OnLButtonUp(wParam,lParam);
	case WM_SIZE:		 return OnSize(wParam,lParam);
	case WM_COMMAND:	 return OnCommand(wParam,lParam);
	case WM_CREATE:		 return OnCreate((LPCREATESTRUCT)lParam);
	case WM_NOTIFY:		 return OnNotify((int)wParam,(LPNMHDR) lParam);
	default:
		return DefWindowProc(hWnd,uMsg,wParam,lParam);
	}
	return 0;
}

DWORD CEditList::Create(int x, int y, int nWidth, int nHeight, HWND hWndParent)
{
	CWind::Create(NULL,WS_CHILD|WS_VISIBLE|WS_VSCROLL|WS_BORDER,x,y,nWidth,nHeight,hWndParent,NULL,(HINSTANCE)GetModuleHandle(NULL),NULL);
	return 0;
}

LRESULT CEditList::OnPaint()
{
	PAINTSTRUCT pStruct;
	HDC hdc = BeginPaint(*this,&pStruct);
	if (hdc == NULL) return 0;
	DrawCells(-1,-1,NULL,hdc);
	if (!::EndPaint(*this,&pStruct)) return 0;
	return 0;
}

DWORD CEditList::SetDBInterfaz(IDBClass *lpIDBClass)
{
	// Contar la cantidad de filas validas
	DWORD		dr;
	DBDATAINFO*	dinfo;
	DWORD		dbcount = lpIDBClass->GetDBDataCount();
	WORD		i;
	m_IDBClass = lpIDBClass;
	m_RowCount = 0;
	for (i = 0;i < dbcount;i++)
	{
		dr = m_IDBClass->GetDBDataInfo(i,&dinfo);
		if (dinfo->flags & F_ONINVISIBLE) continue;
		m_RowCount++;
	}
	return ERR_NONE;
}

DWORD CEditList::Initialize()
{
	return 0;
}

DWORD CEditList::Refresh()
{
	UpdateRowHeight(-1);
	m_FocusRow = -1;

	SCROLLINFO	sinfo;
	sinfo.cbSize = sizeof(sinfo);
	sinfo.fMask = SIF_RANGE|SIF_PAGE;
	sinfo.nMax = m_RowCount-1;
	sinfo.nMin = 0;
	sinfo.nPage = 1;
	SetScrollInfo(*this,SB_VERT,&sinfo,true);
	return ERR_NONE;
}

LRESULT CEditList::OnLButtonDown(WPARAM wParam, WPARAM lParam)
{
	EDTCELLINFO cellinfo;
	DWORD	dr;
	WORD x = LOWORD(lParam);
	WORD y = HIWORD(lParam);
	SetFocus(*this);
	dr = CellFromPoint(x,y,&cellinfo);
	if (dr != ERR_NONE) 
	{
		SetFocusRow(-1);
		return 0;
	}
	if (cellinfo.column == 0) return 0;
	if (cellinfo.row != 0)
	{
		if (m_FocusRow == cellinfo.row)
			m_MouseStatus = MOUSE_EDIT;
		else 
			m_MouseStatus = MOUSE_NONE;
	}
	SetFocusRow(cellinfo.row);
	return 0;
}

LRESULT CEditList::OnSize(WPARAM wParam, LPARAM lParam)
{
	if (*this) UpdateRowHeight(-1);
	return 0;
}

DWORD CEditList::GetFirstVisibleCell(EDTCELLINFO *cellinfo)
{
	::GetClientRect(*this,cellinfo);
	cellinfo->bottom = cellinfo->top + m_Row0Height;
	cellinfo->left += m_LeftMargin;
	cellinfo->right = cellinfo->left + m_Column0Width;
	cellinfo->row = 0;
	cellinfo->dbIndex = -1;
	cellinfo->column = 0;
	return ERR_NONE;
}

DWORD CEditList::GetNextVisibleCell(EDTCELLINFO *cellinfo)
{
	RECT		rect;
	DWORD		dr;
	DBDATAINFO*	dinfo;
	DWORD		dbcount = m_IDBClass->GetDBDataCount();
	DWORD		row;
	DWORD		i;
	::GetClientRect(*this,&rect);
	if (cellinfo->column == 0)
	{
		/*
			Pasar a la columna 1, 
		*/
		cellinfo->column = 1;
		cellinfo->left = cellinfo->right;
		cellinfo->right = rect.right - m_RightMargin;
		return ERR_NONE;
	}

	if (cellinfo->row == 0) 
		row = m_FirstRow;
	else 
		row = cellinfo->row+1;
	/*
		Buscar la row especificada
	*/
	for (i = 0;i < dbcount;i++)
	{
		dr = m_IDBClass->GetDBDataInfo(LOWORD(i),&dinfo);
		if (dinfo->flags & F_ONINVISIBLE) continue;
		if (dinfo->editpos == row) break;
	}
	if (i == dbcount) return ERR_EOT;
	cellinfo->left = rect.left + m_LeftMargin;
	cellinfo->right = cellinfo->left + m_Column0Width;
	cellinfo->top = cellinfo->bottom;
	cellinfo->bottom = cellinfo->top + dinfo->height;
	cellinfo->row = row;
	cellinfo->column = 0;
	cellinfo->dbIndex = LOWORD(i);
	if (cellinfo->top > rect.bottom) return ERR_EOT;
	return ERR_NONE;
}

DWORD CEditList::CellFromPoint(short x, short y, EDTCELLINFO* cellinfo)
{
	RECT	rect;
	DWORD	dr;
	::GetClientRect(*this,&rect);
	if ((x <0) || (y<0) || (x >= rect.right) || (y >= rect.bottom))
		return ERR_EOT;
	dr = GetFirstVisibleCell(cellinfo);
	while (dr == ERR_NONE)
	{
		if ((y < cellinfo->bottom) && 
			(x <= cellinfo->right) &&
			(x >= cellinfo->left)) return ERR_NONE;
		dr = GetNextVisibleCell(cellinfo);
	};
	return dr;
}

LRESULT CEditList::OnLButtonUp(WPARAM wParam, WPARAM lParam)
{
	EDTCELLINFO cellinfo;
	DWORD	dr;
	WORD x = LOWORD(lParam);
	WORD y = HIWORD(lParam);
	dr = CellFromPoint(x,y,&cellinfo);
	if (cellinfo.column == 0) return 0;
	if (dr == ERR_NONE)
	{
		if ((m_FocusRow == cellinfo.row) && (m_MouseStatus == MOUSE_EDIT))
			OnEditCell(&cellinfo);
	}
	m_MouseStatus = MOUSE_NONE;
	return 0;
}

LRESULT CEditList::OnCommand(WPARAM wParam, LPARAM lParam)
{
	switch HIWORD(wParam)
	{
	//case EN_KILLFOCUS: return OnEndEditCell();
	}
	return 0;
}

DWORD CEditList::OnEditCell(EDTCELLINFO *cellinfo)
{
	EDITINFO	editInfo;
	DWORD		dr;
	DWORD		dwStyle=0;
	DBDATAINFO*	dinfo;
	RECT		rect;
	GetClientRect(*this,&rect);
	dr = m_IDBClass->GetDBDataInfo(cellinfo->dbIndex,&dinfo);
	editInfo.dbIndex = cellinfo->dbIndex;
	editInfo.rect = *cellinfo;
	switch (dinfo->edittype)
	{
	case EDT_EDIT:
		{
			if (dinfo->flags & F_ONMULTILINE) dwStyle |= ES_MULTILINE|ES_AUTOVSCROLL;
			m_hEdit = ::CreateWindow("EDIT",NULL,WS_BORDER|WS_CHILD|WS_VISIBLE|dwStyle,
										cellinfo->left,cellinfo->top,cellinfo->right-cellinfo->left,
										cellinfo->bottom-cellinfo->top,
										*this,NULL,(HINSTANCE)GetModuleHandle(NULL),0);
			char*	str;
			m_IDBClass->GetDBDataStrPtr(cellinfo->dbIndex,&str);
			SetWindowText(m_hEdit,str);
			
			break;
		}
	case EDT_COMBOBOX:
		{
			// Poner la celda de primera
			SetFirstRow(cellinfo->row);
			GetCellAt(cellinfo->row,1,cellinfo);
			m_hEdit =  ::CreateWindow("COMBOBOX",NULL,
										CBS_DROPDOWNLIST|WS_CHILD|WS_VISIBLE|CBS_NOINTEGRALHEIGHT,
										cellinfo->left,cellinfo->top,cellinfo->right-cellinfo->left,
										rect.bottom-cellinfo->top,
										*this,NULL,(HINSTANCE)GetModuleHandle(NULL),0);
			break;
		}
	case EDT_DATE:
		{
			m_hEdit = ::CreateWindow(DATETIMEPICK_CLASS,NULL,WS_CHILD|WS_VISIBLE,
										cellinfo->left,cellinfo->top,cellinfo->right-cellinfo->left,
										cellinfo->bottom-cellinfo->top,
										*this,NULL,(HINSTANCE)GetModuleHandle(NULL),0);
			break;
		}
	}
	editInfo.hWnd = m_hEdit;
	::SendMessage(m_hEdit,WM_SETFONT,(WPARAM)m_hfont,FALSE);
	::SetFocus(m_hEdit);
	m_IDBClass->OnStartEdit(&editInfo);
	m_OnEditUpdate = TRUE;
	if (dinfo->edittype == EDT_DATE) return 0;
	// Subclass edit para recepcionar enter.
	::SetWindowLong(m_hEdit,GWL_USERDATA,(LONG)this);
	m_EditWndProc = (WNDPROC)::SetWindowLong(m_hEdit,GWL_WNDPROC,(LONG)EditWndProc);
	return ERR_NONE;
}

LRESULT CEditList::EditWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CEditList*	lpEditList;
	lpEditList = (CEditList*)::GetWindowLong(hWnd,GWL_USERDATA);
	return lpEditList->OnEditWndProc(hWnd,uMsg,wParam,lParam);
}

LRESULT CEditList::OnEditWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_KILLFOCUS : return OnEndEditCell();
	case WM_CHAR : 
		{
			switch (wParam)
			{
			case 27:
				{
					m_OnEditUpdate = false;
					m_OnEditNext = false;
					SetFocus(*this);
				}
			case 13:
				{
					m_OnEditUpdate = true;
					m_OnEditNext = false;
					SetFocus(*this);
				}
			}
			break;
		}
	}
	return ::CallWindowProc(m_EditWndProc,hWnd,uMsg,wParam,lParam);
}

DWORD CEditList::OnEndEditCell()
{
	DBDATAINFO*	dinfo;
	EDTCELLINFO	cellinfo;
	GetCellAt(m_FocusRow,1,&cellinfo);
	m_IDBClass->GetDBDataInfo(cellinfo.dbIndex,&dinfo);
	SetWindowLong(m_hEdit,GWL_WNDPROC,(LONG)m_EditWndProc);
	if (m_OnEditUpdate) 
	{
		m_IDBClass->OnEndEdit(m_hEdit,dinfo->dbIndex,m_OnEditUpdate);
		if (dinfo->flags & F_ONMULTILINE)
		{
			UpdateRowHeight(dinfo->dbIndex);
			DrawCells(-1,-1,NULL,NULL);
		}
		else
			DrawCells(-1,-1,&cellinfo,NULL);
	}
	DestroyWindow(m_hEdit);
	m_hEdit = NULL;
	return 0;
}

LRESULT CEditList::OnVScroll(WPARAM wParam)
{
	::SetFocus(*this);
	switch (LOWORD(wParam))
	{
	case SB_LINEDOWN:
	case SB_PAGEDOWN:
		{
			SetFirstRow(m_FirstRow+1);
			break;
		}
	case SB_LINEUP: 
	case SB_PAGEUP:
		{
			SetFirstRow(m_FirstRow-1);
			break;
		}
	case SB_THUMBPOSITION:
	case SB_THUMBTRACK:
		{
			WORD Pos=HIWORD(wParam);
			SetFirstRow(Pos+1);
			break;
		}
	}
	return 0;
}

DWORD CEditList::UpdateRowHeight(DWORD dbIndex)
{
	DBDATAINFO*	dinfo;
	DWORD		dr;
	HDC			hdc;
	void*		holdfont;
	DWORD		dbcount;
	WORD		i;
	UINT		uFormat;
	char*		str;
	RECT		clientRect;
	TEXTMETRIC	textmetric;
	
	hdc = GetDC(*this);
	::GetClientRect(*this,&clientRect);
	holdfont = SelectObject(hdc,m_hfont);
	GetTextMetrics(hdc,&textmetric);
	m_Row0Height = textmetric.tmHeight+1+m_cellTopMargin+TEXTTOPMARGIN+m_cellBottomMargin;
	
	if (dbIndex != ULONG_MAX) 
	{
		i = dbIndex;
		dbcount = dbIndex+1;
	}
	else 
	{ 
		i = 0;
		dbcount = m_IDBClass->GetDBDataCount();
	}
	for (;i<dbcount;i++)
	{
		dr = m_IDBClass->GetDBDataInfo(i,&dinfo);
		if (dr != ERR_NONE) break;
		if (!(dinfo->flags & F_ONMULTILINE))
		{
			dinfo->height = m_Row0Height;
			continue;
		}
		dr = m_IDBClass->GetDBDataStrPtr(i,&str);
		if (dr != ERR_NONE) break;
		uFormat = DT_LEFT|DT_TOP|DT_WORDBREAK|DT_NOPREFIX|DT_CALCRECT;
		clientRect.bottom = clientRect.top;
		clientRect.left += (m_LeftMargin + m_Column0Width + m_cellLeftMargin + TEXTLEFTMARGIN);
		clientRect.right -= (m_RightMargin + m_cellRigthMargin);
 		::DrawText(hdc,str,-1,&clientRect,uFormat);
		dinfo->height = clientRect.bottom - clientRect.top +1 + m_cellTopMargin + TEXTTOPMARGIN + m_cellBottomMargin;
		if (dbIndex != ULONG_MAX) break;
	}
	SelectObject(hdc,holdfont);
	ReleaseDC(*this,hdc);
	return dr;

}

LRESULT CEditList::OnCreate(CREATESTRUCT *lpCreateStruct)
{
	// Crear el font si se puede
	LOGFONT	FontInfo;
	memset(&FontInfo,0,sizeof(FontInfo));
	strcpy(FontInfo.lfFaceName,"Arial");
	FontInfo.lfHeight=-12;
	FontInfo.lfWidth=0;
	FontInfo.lfWeight=FW_NORMAL;
	FontInfo.lfOutPrecision=3;
	FontInfo.lfClipPrecision=2;
	FontInfo.lfQuality=1;
	FontInfo.lfPitchAndFamily=34;
	FontInfo.lfCharSet=ANSI_CHARSET;
	FontInfo.lfItalic = false;
	m_hfont = ::CreateFontIndirect(&FontInfo);
	return 0;
}

DWORD CEditList::GetCellAt(DWORD dwRow, DWORD dwColumn, EDTCELLINFO *lpcellinfo)
{
	DWORD	dbcount = m_IDBClass->GetDBDataCount();
	RECT	rect;
	DWORD	row;
	DWORD	dr;
	DBDATAINFO*	dinfo;
	::GetClientRect(*this,&rect);
	/*
		row		0 - Header
		column	0 - Caption
		Pasos:
			Empezar con el header y sus dimensiones
			- Moverse hasta encontrar la row especifica,
			si nos pasamos del tamaño de la ventana el RECT se hace 0
			- Si el rect es cero moverse hasta la fila especificada
			- Si llegamos a firstrow y rect = 0 llenar el rect
	*/
	// Header
	lpcellinfo->left = rect.left + m_LeftMargin;
	lpcellinfo->right = rect.right - m_RightMargin;
	lpcellinfo->top = rect.top;
	lpcellinfo->bottom = m_Row0Height;
	lpcellinfo->row = 0;
	lpcellinfo->dbIndex = -1;
	// Empèzar la busqueda de la fila especificada
	if (dwRow < m_FirstRow)
	{
		row = dwRow;
		memset(lpcellinfo,0,sizeof(*lpcellinfo));
	}
	else
	{
		row = m_FirstRow;
	}
	// Recorrer desde row
	for (DWORD j = row;j <= dwRow;j++)
	{
		for (WORD i = 0;i < dbcount;i++)
		{
			dr = m_IDBClass->GetDBDataInfo(i,&dinfo);
			if (dinfo->flags & F_ONINVISIBLE) continue;
			if (dinfo->editpos == j) break;
		}
		if (i == dbcount) return ERR_EOT;
		// Incremento rect si >= m_FirstRow y Rect != 0
		if ((j >= m_FirstRow) && 
			((lpcellinfo->right | lpcellinfo->left | lpcellinfo->bottom | lpcellinfo->top) != 0))
		{
			// Incrementar rect
			lpcellinfo->top = lpcellinfo->bottom;
			lpcellinfo->bottom = lpcellinfo->top + dinfo->height;
			// ver si estamos pasados de la ventana
			if (lpcellinfo->top > rect.bottom)
			{
				lpcellinfo->right = 0;
				lpcellinfo->left = 0;
				lpcellinfo->bottom = 0;
				lpcellinfo->top = 0;
				j = dwRow-1;
			}
		} 

	}
	// llenar las propiedades de la celda
	lpcellinfo->row = dwRow;
	lpcellinfo->column = dwColumn;
	lpcellinfo->row = dwRow;
	lpcellinfo->dbIndex = dinfo->dbIndex;
	if ((lpcellinfo->right | lpcellinfo->left | lpcellinfo->bottom | lpcellinfo->top) != 0)
	{
		if (dwColumn == 0)
		{
			lpcellinfo->right = lpcellinfo->left+m_Column0Width;
		}
		else
		{
			lpcellinfo->left = lpcellinfo->left+m_Column0Width;
		}
	}
	return 0;
}


DWORD CEditList::DrawCells(DWORD StartRow, DWORD EndRow,EDTCELLINFO *lpcellinfo,HDC hdc)
{
	char*		text;
	RECT		rect;
	DWORD		dr;
	UINT		uformat;
	DBDATAINFO*	dinfo;
	EDTCELLINFO	cellinfo;

	BOOL OnDc = true;	// Indica que el dc es valido
	if (hdc == NULL)
	{
		hdc = ::GetDC(*this);
		OnDc = false;
	}
	
	HPEN grispen = ::CreatePen(PS_SOLID,1,RGB(214,211,206));
	HPEN blackpen = ::CreatePen(PS_SOLID,1,RGB(0,0,0));
	HPEN whitepen = ::CreatePen(PS_SOLID,1,RGB(255,255,255));

	void* oldfont = SelectObject(hdc,m_hfont);
	void* oldpen  = SelectObject(hdc,grispen);
	SetBkMode(hdc,TRANSPARENT);

	// Dibujar solo la celda indicada 
	// Dibujar las celdas indicadas
	if (lpcellinfo != NULL)
		cellinfo = *lpcellinfo;
	else
		if (StartRow == -1) 
			GetFirstVisibleCell(&cellinfo);
		else
			GetCellAt(StartRow,0,&cellinfo);
	do
	{
		/*
			Dibujar la celda obtenida
		*/

		// Background de la celda
		if (cellinfo.row == 0) 
			SetBkColor(hdc,RGB(214,211,206));
		else
			if ((cellinfo.row == m_FocusRow) && (cellinfo.column == 1))
				SetBkColor(hdc,RGB(0,0,255));
			else
				SetBkColor(hdc,RGB(255,255,255));
		rect = cellinfo;
		::ExtTextOut(hdc,0,0,ETO_OPAQUE,&rect,NULL,0,NULL);

		// Border de la celda
		if ((cellinfo.row == 0)/* || (cellinfo.column == 0)*/)
		{
			// Border superior e izquierdo
			::SelectObject(hdc,whitepen);
			MoveToEx(hdc,cellinfo.left,cellinfo.bottom-1,NULL);
			LineTo(hdc,cellinfo.left,cellinfo.top);
			LineTo(hdc,cellinfo.right-1,cellinfo.top);
			// Border inferior y derecho
			::SelectObject(hdc,blackpen);
			LineTo(hdc,cellinfo.right-1,cellinfo.bottom-1);
			LineTo(hdc,cellinfo.left-1,cellinfo.bottom-1);
		}
		else
		{
			::SelectObject(hdc,grispen);
			// linea vertical
			MoveToEx(hdc,cellinfo.right-1,cellinfo.top,NULL);
			LineTo(hdc,cellinfo.right-1,cellinfo.bottom-1);
			// Linea horizontal
			LineTo(hdc,cellinfo.left-1,cellinfo.bottom-1);
		}
		// texto
		uformat = DT_LEFT|DT_END_ELLIPSIS|DT_SINGLELINE|DT_TOP;
		if (cellinfo.row == 0)
		{
			// Header
			if (cellinfo.column == 0)
				text = LBLCAMPO;
			else
				text = LBLVALOR;
		}
		else
		{
			dr = m_IDBClass->GetDBDataInfo(cellinfo.dbIndex,&dinfo);
			if (cellinfo.column == 0)
				text = dinfo->caption;
			else
			{
				if (dinfo->flags & F_ONMULTILINE)
					uformat = DT_LEFT|DT_TOP|DT_WORDBREAK|DT_NOPREFIX;
				dr = m_IDBClass->GetDBDataStrPtr(cellinfo.dbIndex,&text);
			}
		}
		rect.left = cellinfo.left+m_cellLeftMargin+TEXTLEFTMARGIN;
		rect.top = cellinfo.top+m_cellTopMargin+TEXTTOPMARGIN;
		rect.right = cellinfo.right-m_cellRigthMargin-TEXTRIGHTMARGIN-2;
		rect.bottom = cellinfo.bottom-m_cellBottomMargin-2;
		
		DrawText(hdc,text,-1,&rect,uformat);

		if (lpcellinfo != NULL) break;	// Solo se dibuja esta celda
		dr = GetNextVisibleCell(&cellinfo);
		if (cellinfo.row > EndRow) break;	// Hasta esta row
		if ((dr == ERR_EOT) && (EndRow == -1) && (StartRow == -1))
		{
			RECT	crect;
			::GetClientRect(*this,&crect);
			crect.top = cellinfo.bottom;
			SetBkColor(hdc,RGB(255,255,255));
			::ExtTextOut(hdc,0,0,ETO_OPAQUE,&crect,NULL,0,NULL);
		}
		if (dr != ERR_NONE) break;
	}
	while (true);

	// liberar objetos
	::SelectObject(hdc,oldpen);
	::SelectObject(hdc,oldfont);
	::DeleteObject(grispen);
	::DeleteObject(blackpen);
	if (!OnDc)	::ReleaseDC(*this,hdc);
	return 0;
}

DWORD CEditList::SetFocusRow(DWORD dwRow)
{
	EDTCELLINFO	cellinfo;
	if (dwRow == m_FocusRow) return 0;
	if (m_FocusRow != -1)
	{
		GetCellAt(m_FocusRow,1,&cellinfo);
		m_FocusRow = -1;
		DrawCells(-1,-1,&cellinfo,NULL);
	}
	m_FocusRow = dwRow;
	if (m_FocusRow != -1)
	{
		GetCellAt(m_FocusRow,1,&cellinfo);
		DrawCells(-1,-1,&cellinfo,NULL);
	}
	return 0;
}

DWORD CEditList::SetFirstRow(DWORD dwFirstRow)
{
	if (dwFirstRow == m_FirstRow) return 0;
	if ((dwFirstRow > m_RowCount) || (dwFirstRow < 1)) return 0;
	m_FirstRow = dwFirstRow;
	::SetScrollPos(*this,SB_VERT,m_FirstRow-1,true);
	DrawCells(-1,-1,NULL,NULL);
	return 0;
}

LRESULT CEditList::OnNotify(int idCtrl, LPNMHDR pnmh)
{
	if (pnmh->code == NM_KILLFOCUS)
	{
		return 0;
	}
	return 0;
}
