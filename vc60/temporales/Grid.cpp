// Grid.cpp: implementation of the CGrid class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Grid.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define SCROLL_BYCELLS	1
#define SCROLL_BYPIXELS 2

#define NO_CELL			0
#define DATA_CELL		1
#define FIXEDTOP_CELL	2
#define FIXEDLEFT_CELL	3


#define EQUAL	0
#define LESS	1
#define GREATER	2

// mouse modes
#define M_NOTHING		0
#define M_SEL_ALL		1	// seleccionar todo
#define M_SEL_COL		2	// Seleccionar columna
#define M_SEL_ROW		3	// Seleccionar fila
#define M_SEL_CELL		4	// Seleccionar celda
#define M_COL_DIV_LEFT	5	// Sobre division de columnas
#define M_COL_DIV_RIGHT	6	// Sobre division de columnas
#define M_COL_SIZING	7	// Cambiando de tamaño una columna


CGrid::CGrid()
{
	m_ColumnDataOffset = 0;
	m_RowDataOffset = 0;
	m_hfont = NULL;
	m_IDBArray = NULL;
	m_MouseMode = M_NOTHING;
	m_bShowVScroll = true;
	m_bShowHScroll = true;
	InvalidateData();
	UpdateMargins();
}

CGrid::~CGrid()
{

}

DWORD CGrid::Create(DWORD dwStyle,DWORD dwExStyle,int x, int y, int nWidth, int nHeight,DWORD dwCtrlID,HWND hWndParent)
{
	CWind::CreateEx(NULL,dwStyle|WS_HSCROLL|WS_VSCROLL,dwExStyle,x,y,nWidth,nHeight,hWndParent,(HMENU)dwCtrlID,NULL);
	return 0;
}

LRESULT CGrid::WndProc(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_PAINT:			return OnPaint();
	case WM_VSCROLL:		return OnVScroll(wParam);
	case WM_HSCROLL:		return OnHScroll(wParam);
	case WM_LBUTTONDOWN:	return OnLButtonDown(wParam,GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam));
	case WM_LBUTTONUP:		return OnLButtonUp(wParam,GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam));
	case WM_SETFONT:		return OnSetFont((HFONT)wParam,(BOOL)lParam);
	case WM_SIZE:			return OnSize(wParam,LOWORD(lParam),HIWORD(lParam));
	case WM_MOUSEMOVE:		return OnMouseMove(wParam,GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam)); 
	case WM_LBUTTONDBLCLK:	return OnLButtonDblClk(wParam,GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam)); 
	
	default:
		return DefWindowProc(hWnd,uMsg,wParam,lParam);
	}
	return 0;
}

LRESULT CGrid::OnVScroll(WPARAM wParam)
{
	const BYTE step = 2;
	WORD avalHeight = (WORD)(m_cellsrect.bottom-m_cellsrect.top);
	DWORD	starty;
	switch (LOWORD(wParam))
	{
	case SB_LINEDOWN: 
		{
			starty = m_StartY+step;
			break;
		}
	case SB_PAGEDOWN: 
		{
			starty = m_StartY + avalHeight;
			break;
		}
	case SB_LINEUP: 
		{
			if (m_StartY < step) 
				starty = 0;
			else
				starty = m_StartY-step;
			break;
		}
	case SB_PAGEUP: 
		{
			if (m_StartY > avalHeight)
				starty = m_StartY - avalHeight;
			else
				starty = 0;
			break;
		}
	case SB_THUMBPOSITION:
	case SB_THUMBTRACK:
		{
			SCROLLINFO	sinfo;
			sinfo.cbSize = sizeof(sinfo);
			sinfo.fMask = SIF_TRACKPOS;
			::GetScrollInfo(*this,SB_VERT,&sinfo);
			starty = sinfo.nTrackPos;
			break;
		}
	default:
		return 0;
	}
	SetStartY(starty);
	return 0;
}

LRESULT CGrid::OnPaint()
{
	PAINTSTRUCT pStruct;
	HDC hdc = BeginPaint(*this,&pStruct);
	if (hdc == NULL) 
		return 0;
	DrawCells(NULL,NULL,hdc);
	if (!::EndPaint(*this,&pStruct)) 
		return 0;
	return 0;
}

DWORD CGrid::Initialize()
{
	LOGFONT	FontInfo;
	memset(&FontInfo,0,sizeof(FontInfo));
	strcpy(FontInfo.lfFaceName,"MS Sans Serif");
	FontInfo.lfHeight=-8;
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

LRESULT CGrid::OnHScroll(WPARAM wParam)
{
	const BYTE step = 2;
	DWORD	avalWidth = m_cellsrect.right-m_cellsrect.left;
	DWORD	startx;
	switch (LOWORD(wParam))
	{
	case SB_LINERIGHT: 
		{
			startx = m_StartX + step;
			break;
		}
	case SB_PAGERIGHT:
		{
			startx = m_StartX + avalWidth;
			break;
		}
	case SB_LINELEFT:
		{
			if (m_StartX < step) startx = 0;
			else
				startx = m_StartX -step;
			break;
		}
	case SB_PAGELEFT:
		{
			if (m_StartX > avalWidth) startx = m_StartX - avalWidth;
			else
				startx = 0;
			break;
		}
	case SB_THUMBPOSITION:
	case SB_THUMBTRACK:
		{
			SCROLLINFO	sinfo;
			sinfo.cbSize = sizeof(sinfo);
			sinfo.fMask = SIF_TRACKPOS;
			::GetScrollInfo(*this,SB_HORZ,&sinfo);
			startx = sinfo.nTrackPos;
			break;
		}
	default: return 0;
	}
	SetStartX(startx);
	return 0;
}


LRESULT CGrid::OnLButtonDown(UINT nFlags,int x,int y)
{
	GCELL	gcell;
	DWORD	dr;
	WORD	mousepos;
	dr = GetMousePos(x,y,&gcell,&mousepos);
	//::SetCapture(*this);
	::SetFocus(*this);
	m_mousestartcell = gcell;
	m_mousestartx = x;
	m_mousestarty = y;
	if ((mousepos == M_COL_DIV_RIGHT) || (mousepos == M_COL_DIV_LEFT))
	{
		if (mousepos == M_COL_DIV_LEFT) 
		{
			m_mousestartcell.columnIndex--;
			dr = GetVisibleColumn(m_mousestartcell.columnIndex,NULL,&m_mousestartcell.arrayIndex);
		}
		m_MouseMode = M_COL_SIZING;
		RECT	rect;
		rect = m_cellsrect;
		rect.left = m_mousestartx;
		rect.right = rect.left+2;
		HDC	hdc = ::GetDC(*this);
		InvertRect(hdc,&rect);
		::ReleaseDC(*this,hdc);
		m_mouselastx = m_mousestartx;
		::SetCapture(*this);
	}
	if (m_MouseMode == M_NOTHING)
	{
		if (gcell.type != DATA_CELL) dr = SetFocus(NULL);
		if (gcell.type == DATA_CELL) dr = SetFocus(&gcell);
	}
	return 0;
}

DWORD CGrid::GetSelRow(DWORD* dwRowIndex)
{
	if (m_FocusRow == -1) return ERR_EOT;
	*dwRowIndex = m_FocusRow;
	return 0;
}

DWORD CGrid::GetFirstVisibleCell(GCELL *lpgcell)
{
	DWORD dr;
	dr = GetFirstVisibleRow(lpgcell);
	if (dr != ERR_NONE) return dr;
	dr = GetFirstVisibleColumn(lpgcell);
	return dr;
}

DWORD CGrid::GetNextVisibleCell(GCELL *lpgcell)
{
	DWORD	dr;

	dr = GetNextColumn(lpgcell);
	if (((lpgcell->right | lpgcell->left) != 0)  && (dr == 0))return 0;
	dr = GetFirstVisibleColumn(lpgcell);
	dr = GetNextRow(lpgcell);
	if (((lpgcell->top | lpgcell->bottom) != 0)  && (dr == 0))return 0;
	return ERR_EOT;
}

DWORD CGrid::UpdateRowHeight(DWORD dwRowIndex)
{
	WORD	column;
	DWORD	columncount;
	DWORD	rowcount;
	RECT	rect;
	DWORD	rowHeight;
	DWORD	dr;
	DWORD	i;
	HDC		hdc;
	void*	oldfont;
	WORD	minheight;	// menor tamaño que tiene una fila
	WORD	height1;
	char*	caption;
	DWORD	dbIndex;
	DWORD	dbFlags;
	BOOL	onCalcSize;
	GROWINFO*		rinfo;
	GCOLUMNINFO*	cinfo;
	ITEM_INFO		strinfo;
	TEXTMETRIC		textmetric;

	onCalcSize = false;
	
	columncount = m_IDBArray->GetColumnCount();
	rowcount	= m_IDBArray->GetRowCount();
	hdc			= GetDC(*this);
	oldfont		= SelectObject(hdc,m_hfont);

	// El menor alto es una fila de texto
	GetTextMetrics(hdc,&textmetric);
	m_HeaderHeight = (WORD)(textmetric.tmHeight+1+m_cellMargin.top+m_cellMargin.bottom+m_textMargin.top+m_textMargin.bottom);

	minheight = m_HeaderHeight;
	for (column=0;column < columncount;column++)
	{
		dr = m_IDBArray->GetColumnInfo(column,&dbIndex,&caption,&dbFlags);
		if (dr != ERR_NONE) break;
		// solo elementos de ancho fijo
		if ((dbFlags & F_ONMULTILINE)||(dbFlags & F_OWNERDRAW)) onCalcSize = true;
		if (!(dbFlags & F_DRAWFIXED)) continue;
		dr = m_IDBArray->GetSize(0,column,&rect);
		height1 = (WORD)(rect.bottom-rect.top + m_cellMargin.top + m_cellMargin.bottom);
		minheight = max(minheight,height1);
	}
	if (dwRowIndex >= rowcount)
		i= 0;
	else
		i = dwRowIndex;
	for (;(i<rowcount && i<dwRowIndex);i++)
	{
		dr = m_IDBArray->GetRowExtraDataPtr(i,m_RowDataOffset,(void**)&rinfo);
		height1 = minheight;
		if (onCalcSize)
		for (column=0;column < columncount;column++)
		{
			rowHeight = 0;
			dr = m_IDBArray->GetColumnInfo(column,&dbIndex,&caption,&dbFlags);
			dr = m_IDBArray->GetColumnExtraDataPtr(column,m_ColumnDataOffset,(void**)&cinfo);
			if (dbFlags & F_ONMULTILINE)
			{
				rect.bottom=0;
				rect.top=0;
				rect.left=0;
				rect.right = cinfo->width - (m_cellMargin.left+m_cellMargin.right+m_textMargin.left+m_textMargin.right+1); 
				dr = m_IDBArray->GetStrAt(i,column,&strinfo);
				::DrawText(hdc,strinfo.str,-1,&rect,DT_LEFT|DT_TOP|DT_WORDBREAK|DT_NOPREFIX|DT_CALCRECT);
				rect.bottom += (1+ m_textMargin.top+m_textMargin.bottom);
				rowHeight = rect.bottom-rect.top + m_cellMargin.top + m_cellMargin.bottom;	
			}
			if (dbFlags & F_OWNERDRAW)
			{
				dr = m_IDBArray->GetSize(i,column,&rect);
				rowHeight = rect.bottom-rect.top + m_cellMargin.top + m_cellMargin.bottom;	
			}
			height1 = (WORD)(max(height1,rowHeight));
		}
		rinfo->height = height1;
	}
	::SelectObject(hdc,oldfont);
	::ReleaseDC(*this,hdc);
	m_OnUpdateHeights = true;
	Calc_EndY();
	return 0;
}

DWORD CGrid::GetCellFromPoint(short x, short y, GCELL *lpgcell)
{
	DWORD	dr;
	if (!m_OnUpdateHeights) return ERR_EOT;
	dr = GetFirstVisibleCell(lpgcell);
	if (dr != ERR_NONE) return dr;
	if ((y < lpgcell->top) || ( x < lpgcell->left)) return ERR_EOT;
	// recorrer las filas
	for (;;)
	{
		if (y < lpgcell->bottom) break;
		dr = GetNextRow(lpgcell);
		if (dr != ERR_NONE) return dr;
	}
	// recorrer las columnas
	for (;;)
	{
		if (x < lpgcell->right) break;
		dr = GetNextColumn(lpgcell);
		if (dr != ERR_NONE) return dr;
	}
	return 0;
}

LRESULT CGrid::OnSetFont(HFONT hfont, BOOL bRedraw)
{
	// Invalidar height
	m_hfont = hfont;
	UpdateRowHeight(INVALID_INDEX);
	return 0;
}

DWORD CGrid::SetDBArray(IDBArray *lpIDBArray)
{
	m_IDBArray = lpIDBArray;
	lpIDBArray->AddColumnExtraData(sizeof(GCOLUMNINFO),&m_ColumnDataOffset);
	lpIDBArray->AddRowExtraData(sizeof(GROWINFO),&m_RowDataOffset);
	return 0;
}

/*
	Aqui se invalida todo
*/
DWORD CGrid::InvalidateData()
{
	DWORD	columncount;
	DWORD	i;
	DWORD	dr;
	DWORD	dbFlags;
	GCOLUMNINFO*	cinfo;
	// Invalidacion de los datos extras de las columnas y las filas
	m_VColumnCount = 0;
	if (m_IDBArray)
	{
		columncount = m_IDBArray->GetColumnCount();
		for(i=0;i<columncount;i++)
		{
			m_IDBArray->GetColumnInfo(i,NULL,NULL,&dbFlags);
			if (dbFlags & DB_F_INVISIBLE) continue;
			dr = m_IDBArray->GetColumnExtraDataPtr(i,m_ColumnDataOffset,(void**)&cinfo);
			cinfo->width = 100;
			cinfo->index  = m_VColumnCount;
			m_VColumnCount++;
		}
	}
	m_OnHScroll = false;
	m_OnUpdateHeights = false;
	m_OnVScroll = false;
	m_VerScrollMode = SCROLL_BYPIXELS;
	m_HorScrollMode = SCROLL_BYPIXELS;
	m_FocusColumn = -1;
	m_FocusRow = -1;
	m_StartX = 0;
	m_StartY = 0;
	m_HeaderHeight = 0;
	Calc_EndX();
	return ERR_NONE;
}

DWORD CGrid::SetFocus(GCELL *lpgcell)
{
	DWORD	focusrow;
	GCELL	start;
	GCELL	end;
	DWORD	rowcount = m_IDBArray->GetRowCount();
	if (lpgcell == NULL) focusrow = rowcount;
	else
		focusrow = lpgcell->rowIndex;
	if (m_FocusRow == focusrow) return 0;

	for (int i=0;i<2;i++)
	{
		if (m_FocusRow != rowcount)
		{
			start.columnIndex = 0;
			start.rowIndex = m_FocusRow;
			start.type = DATA_CELL;
			end.columnIndex = m_VColumnCount;
			end.rowIndex = m_FocusRow;
			end.type = DATA_CELL;
			m_FocusRow = focusrow;
			DrawCells(&start,&end,NULL);
		}
		m_FocusRow = focusrow;
	}
	return 0;
}

DWORD CGrid::SetStartY(DWORD dwStartY)
{
	DWORD avalHeight = m_cellsrect.bottom-m_cellsrect.top;
	if (m_EndY <=  avalHeight)
		dwStartY = 0;
	else
		if (dwStartY > m_EndY-avalHeight) dwStartY = m_EndY-avalHeight;
	if (m_OnVScroll) ::SetScrollPos(*this,SB_VERT,dwStartY,true);
	if (dwStartY == m_StartY) return 0;
	m_StartY = dwStartY;
	GCELL	gcell;
	gcell.rowIndex = 0;
	gcell.columnIndex = 0;
	gcell.type = DATA_CELL;
	DrawCells(&gcell,NULL,NULL);
	return 0;
}

DWORD CGrid::UpdateMargins()
{
	m_textMargin.left = 3;
	m_textMargin.right = 1;
	m_textMargin.top = 1;
	m_textMargin.bottom = 1;

	m_cellMargin.top = 1;
	m_cellMargin.left = 1;
	m_cellMargin.right = 1;
	m_cellMargin.bottom = 1;

	/*
		Margenes dentro del area cliente para el header y el grid
		El scroll no es parte del area cliente
	*/
	m_winMargin.left = 0;
	m_winMargin.right = 0;
	m_winMargin.top = 0;
	m_winMargin.bottom = 0;

	return 0;
}

LRESULT CGrid::OnSize(UINT nType, int cx, int cy)
{
	if (nType != SIZE_RESTORED) return 0;
	RECT	rect;
	::GetClientRect(*this,&rect);
	if (memcmp(&m_clientrect,&rect,sizeof(RECT)) == 0) return 0;
	m_clientrect = rect;
	CalcCellsRect();
	ShowScrolls();
	return 0;
}

DWORD CGrid::Get1stVisibleDataCell(GCELL *lpgcell)
{
	DWORD dr;
	dr = Get1stVisibleDataRow(lpgcell);
	if (dr) return dr;
	dr = Get1stVisibleDataColumn(lpgcell);
	return dr;
}

// Obtener rectangulo de las celdas
DWORD CGrid::CalcCellsRect()
{
	m_cellsrect = m_clientrect;
	m_cellsrect.top += (m_HeaderHeight+m_winMargin.top);
	m_cellsrect.bottom -= m_winMargin.bottom;
	m_cellsrect.right -= m_winMargin.right;
	m_cellsrect.left += m_winMargin.left;
	return 0;
}

// Visibilidad de los scrolls
DWORD CGrid::ShowScrolls()
{
	// Solousar showwscroll al final cuando ya se sabe cuanto espacio ocupan
	SCROLLINFO	sinfo;
	DWORD	rowcount;
	DWORD	avalHeight;
	DWORD	avalWidth; 

	if (!m_OnUpdateHeights) return 0;
	static bool one;
	if (one) return 0;
	one = true;
	ShowScrollBar(*this,SB_BOTH,FALSE);
	m_OnVScroll = false;
	m_OnHScroll = false;
	for (short i=0;i<2;i++)
	{
		if (m_VerScrollMode == SCROLL_BYPIXELS)
		{
			avalHeight = (WORD)(m_cellsrect.bottom-m_cellsrect.top);
			if (avalHeight < m_EndY) m_OnVScroll = TRUE;
		}
		else
			m_OnVScroll = TRUE;
		::ShowScrollBar(*this,SB_VERT,m_OnVScroll);

		if (m_OnHScroll == false)
		{
			avalWidth = (WORD)(m_cellsrect.right-m_cellsrect.left);
			if (avalWidth < m_EndX) m_OnHScroll = TRUE;
			::ShowScrollBar(*this,SB_HORZ,m_OnHScroll);
		}
		else
			break;
	}
	
	rowcount = m_IDBArray->GetRowCount();
	if (m_OnVScroll)
	{
		if (m_VerScrollMode == SCROLL_BYPIXELS)
		{
			sinfo.nMin = 0;
			sinfo.nPage = avalHeight;
			if (m_EndY)
				sinfo.nMax = m_EndY-1;
			else
				sinfo.nMax = 0;
		}
		else
		{
			sinfo.nMax = rowcount-1;
			sinfo.nMin = 0;
			sinfo.nPage = 1;
		}
		sinfo.cbSize = sizeof(sinfo);
		sinfo.fMask = SIF_RANGE|SIF_PAGE;
		::SetScrollInfo(*this,SB_VERT,&sinfo,true);
	}
	if (m_OnHScroll)
	{
		sinfo.cbSize = sizeof(sinfo);
		sinfo.nMin = 0;
		sinfo.nMax = m_EndX-1;
		sinfo.nPage = avalWidth;
		sinfo.fMask = SIF_RANGE|SIF_PAGE;
		SetScrollInfo(*this,SB_HORZ,&sinfo,true);
	}
	SetStartY(m_StartY);
	SetStartX(m_StartX);
	one = false;
	return 0;
}

DWORD CGrid::Get1stVisibleDataRow(GCELL *lpgcell)
{
	DWORD		 i;
	DWORD		 dr;
	DWORD		 offsetY;
	GROWINFO*	 rinfo;
	DWORD		 rowcount = m_IDBArray->GetRowCount();
	if (rowcount == 0) 
		return ERR_EOT;
	lpgcell->type = DATA_CELL;
	if (m_VerScrollMode == SCROLL_BYPIXELS)
	{
		offsetY = 0;
		for (i=0;i<rowcount;i++)
		{
			dr = m_IDBArray->GetRowExtraDataPtr(i,m_RowDataOffset,(void**)&rinfo);
			if (dr != ERR_NONE) return dr;
			offsetY += rinfo->height;
			if (offsetY > m_StartY) break;
		}
		lpgcell->rowIndex = i;
		lpgcell->hiddenTop = (WORD)(rinfo->height - (offsetY - m_StartY));
		lpgcell->top = m_cellsrect.top;
		if (offsetY - m_StartY + m_cellsrect.top > m_cellsrect.bottom)
		{
			lpgcell->bottom = m_cellsrect.bottom;
			lpgcell->hiddenBottom = (WORD)(offsetY - m_StartY + m_cellsrect.top - m_cellsrect.bottom);
		}
		else
		{
			lpgcell->bottom = offsetY - m_StartY + m_cellsrect.top;
			lpgcell->hiddenBottom = 0;
		}
	}
	if (m_VerScrollMode == SCROLL_BYCELLS)
	{
		dr = m_IDBArray->GetRowExtraDataPtr(m_StartY,m_RowDataOffset,(void**)&rinfo);
		lpgcell->rowIndex = m_StartY;
		lpgcell->hiddenTop = 0;
		lpgcell->top = m_cellsrect.top;
		lpgcell->bottom = min(lpgcell->top+rinfo->height,m_cellsrect.bottom);
		if (lpgcell->top + rinfo->height > m_cellsrect.bottom)
			lpgcell->hiddenBottom = lpgcell->top + rinfo->height - m_cellsrect.bottom;
		else
			lpgcell->hiddenBottom = 0;
	}
	return ERR_NONE;
}

DWORD CGrid::Get1stVisibleDataColumn(GCELL *lpgcell)
{
	DWORD	arrayIndex;
	WORD	i;
	DWORD	dr;
	DWORD	offsetX;
	GCOLUMNINFO* cinfo;
	// Recorrer todas las columnas
	if (m_VColumnCount == 0) return ERR_EOT;
	offsetX = 0;
	for(i=0;i<m_VColumnCount;i++)
	{
		dr = GetVisibleColumn(i,&cinfo,&arrayIndex);
		if (dr != ERR_NONE) return dr;
		offsetX += cinfo->width;
		if (offsetX > m_StartX) break;
	}
	lpgcell->columnIndex = i;
	lpgcell->arrayIndex = arrayIndex;
	lpgcell->hiddenLeft = (WORD)(cinfo->width - (offsetX - m_StartX));
	lpgcell->left = m_cellsrect.left;
	if (offsetX - m_StartX + m_cellsrect.left > m_cellsrect.right)
	{
		lpgcell->right = m_cellsrect.right;
		lpgcell->hiddenRight = (WORD)(offsetX - m_StartX + m_cellsrect.left - m_cellsrect.right);
	}
	else
	{
		lpgcell->right = offsetX - m_StartX + m_cellsrect.left;
		lpgcell->hiddenRight = 0;
	}
	return ERR_NONE;
}

DWORD CGrid::GetNextRow(GCELL *lpgcell)
{
	DWORD	dr;
	DWORD	rowcount;
	GROWINFO*		rinfo;
	rowcount = m_IDBArray->GetRowCount();
	if (lpgcell->type == FIXEDTOP_CELL)
	{
		if (lpgcell->rowIndex == 0)
		{
			return Get1stVisibleDataRow(lpgcell);
		}
		// proxima fila fixed
	}
	lpgcell->rowIndex ++;
	if (lpgcell->rowIndex == rowcount) return ERR_EOT;
	// proxima fila 
	if (lpgcell->bottom == m_cellsrect.bottom)
	{
		lpgcell->top = 0;
		lpgcell->bottom = 0;
		return 0;
	}
	dr = m_IDBArray->GetRowExtraDataPtr(lpgcell->rowIndex,m_RowDataOffset,(void**)&rinfo);
	lpgcell->top = lpgcell->bottom;
	lpgcell->hiddenTop = 0;
	lpgcell->bottom = lpgcell->top + rinfo->height;
	if (lpgcell->bottom > m_cellsrect.bottom)
	{
		lpgcell->bottom = m_cellsrect.bottom;
		lpgcell->hiddenBottom = (WORD)(lpgcell->bottom - m_cellsrect.bottom);
	}
	return 0;
}

DWORD CGrid::GetNextColumn(GCELL *lpgcell)
{
	DWORD	dr;
	GCOLUMNINFO*	cinfo;

	for(;;)
	{
		lpgcell->columnIndex++;
		if (lpgcell->columnIndex == m_VColumnCount) 
		{
			return ERR_EOT;
		}
		dr = GetVisibleColumn(lpgcell->columnIndex,&cinfo,&lpgcell->arrayIndex);
		lpgcell->hiddenRight = 0;
		lpgcell->hiddenLeft = 0;
		if (lpgcell->right == m_cellsrect.right)
		{
			lpgcell->left = 0;
			lpgcell->right = 0;
			return 0;
		}
		if (cinfo->width == 0) continue;
		lpgcell->left = lpgcell->right;
		lpgcell->right = lpgcell->left + cinfo->width;
		if (lpgcell->right > m_cellsrect.right)
		{
			lpgcell->hiddenRight = (WORD)(lpgcell->right - m_cellsrect.right);
			lpgcell->right = m_cellsrect.right;
		}
		return ERR_NONE;
	}
	return ERR_NONE;
}

DWORD CGrid::GetFirstVisibleRow(GCELL *lpgcell)
{
	// Header
	lpgcell->hiddenTop = 0;
	lpgcell->top = m_clientrect.top + m_winMargin.top;
	lpgcell->bottom = lpgcell->top + m_HeaderHeight;
	lpgcell->rowIndex = 0;
	lpgcell->hiddenBottom = 0;
	lpgcell->type = FIXEDTOP_CELL;
	return 0;
}

DWORD CGrid::GetFirstVisibleColumn(GCELL *lpgcell)
{
	return Get1stVisibleDataColumn(lpgcell);
}

DWORD CGrid::GetCellRect(GCELL *lpgcell)
{
	DWORD	dr;
	GCELL	gcell;
	WORD	colrel;
	WORD	rowrel;
	dr = GetFirstVisibleRow(&gcell);
	if (dr != 0) return dr;
	do
	{
		dr = CompareCells(lpgcell,&gcell,&colrel,&rowrel);
		if ((rowrel == LESS) || (colrel == LESS) ||
			(((gcell.top | gcell.bottom) & (gcell.left | gcell.right)) == 0))  
		{
			lpgcell->top = 0;
			lpgcell->bottom = 0;
			lpgcell->left = 0;
			lpgcell->right = 0;
			lpgcell->hiddenLeft = 0;
			lpgcell->hiddenRight = 0;
			lpgcell->hiddenTop = 0;
			lpgcell->hiddenBottom = 0;
			break;
		}
		if (rowrel == GREATER)
		{
			dr = GetNextRow(&gcell);continue;
		}
		if (colrel == GREATER)
		{
			dr = GetNextVisibleCell(&gcell);continue;
		}
		lpgcell->top = gcell.top;
		lpgcell->bottom = gcell.bottom;
		lpgcell->left = gcell.left;
		lpgcell->right = gcell.right;
		lpgcell->hiddenLeft = gcell.hiddenLeft;
		lpgcell->hiddenRight = gcell.hiddenRight;
		lpgcell->hiddenTop = gcell.hiddenTop;
		lpgcell->hiddenBottom = gcell.hiddenBottom;
		
	} while (dr == ERR_NONE);
	return dr;
}

DWORD CGrid::SetStartX(DWORD dwStartX)
{
	DWORD avalWidth = m_cellsrect.right-m_cellsrect.left;
	if (m_EndX <= avalWidth) 
		dwStartX = 0;
	else
		if (dwStartX > m_EndX-avalWidth) dwStartX = m_EndX-avalWidth;
	if (m_OnHScroll) ::SetScrollPos(*this,SB_HORZ,dwStartX,true);
	if (dwStartX == m_StartX) return 0;
	m_StartX = dwStartX;
	DrawCells(NULL,NULL,NULL);
	return ERR_NONE;
}

DWORD CGrid::DrawCells(GCELL *startcell, GCELL *endcell, HDC hdc)
{
	if (!m_OnUpdateHeights) UpdateRowHeight(INVALID_INDEX);
	RECT	rect;
	DWORD	dr;
	GCELL	gcell;
	HRGN	hrgn;
	DWORD	rowcount;
	DWORD	dbFlags;
	ITEM_INFO	strinfo;

	rowcount = m_IDBArray->GetRowCount();
	BOOL OnDc = true;	// Indica que el dc es valido
	if (hdc == NULL)
	{
		hdc = ::GetDC(*this);
		if (hdc == NULL) return 0;
		OnDc = false;
	}
	hrgn = CreateRectRgn(0,0,10,10);
	
	HPEN grispen = ::CreatePen(PS_SOLID,1,RGB(214,211,206));
	HPEN blackpen = ::CreatePen(PS_SOLID,1,RGB(0,0,0));
	HPEN whitepen = ::CreatePen(PS_SOLID,1,RGB(255,255,255));

	void* oldfont = SelectObject(hdc,m_hfont);
	void* oldpen  = SelectObject(hdc,grispen);
	SetBkMode(hdc,TRANSPARENT);


	dr = GetFirstVisibleCell(&gcell);
	while (dr == ERR_NONE)
	{
		rect = gcell;
		if (((rect.right | rect.left) && (rect.bottom | rect.top)) == 0) break;
		WORD colrel,rowrel;
		if (startcell)
		{
			dr = CompareCells(startcell,&gcell,&colrel,&rowrel);
			if (rowrel == GREATER)
			{
				dr = GetNextRow(&gcell);continue;
			}
			if (colrel == GREATER)
			{
				dr = GetNextVisibleCell(&gcell);continue;
			}
		}
		if (endcell)
		{
			dr = CompareCells(endcell,&gcell,&colrel,&rowrel);
			if ((rowrel == LESS)||
				((rowrel == EQUAL) && (colrel == LESS))) break;
			if (colrel == LESS) 
			{
				dr = GetNextVisibleCell(&gcell); continue;
			}
		}
		// Dibujar la celda obtenida
		::SetRectRgn(hrgn,gcell.left,gcell.top,gcell.right,gcell.bottom);
		::SelectClipRgn(hdc,hrgn);

		rect.top -= gcell.hiddenTop;	  // rectangulo real de la celda
		rect.left -= gcell.hiddenLeft;
		rect.right += gcell.hiddenRight;
		rect.bottom += gcell.hiddenBottom;

		// Background de la celda
		if (gcell.type == FIXEDTOP_CELL) 
			SetBkColor(hdc,RGB(214,211,206));
		else
			if (gcell.rowIndex == m_FocusRow)
				SetBkColor(hdc,RGB(0,0,255));
			else
				SetBkColor(hdc,RGB(255,255,255));
		
		::ExtTextOut(hdc,0,0,ETO_OPAQUE,&rect,NULL,0,NULL); // Background

		// Border de la celda
		if (gcell.type == FIXEDTOP_CELL)
		{
			// Border superior e izquierdo
			::SelectObject(hdc,whitepen);
			MoveToEx(hdc,rect.left,rect.bottom-1,NULL);
			LineTo(hdc,rect.left,rect.top);
			LineTo(hdc,rect.right-1,rect.top);
			// Border inferior y derecho
			::SelectObject(hdc,blackpen);
			LineTo(hdc,rect.right-1,rect.bottom-1);
			LineTo(hdc,rect.left-1,rect.bottom-1);
		}
		if (gcell.type == DATA_CELL)
		{
			::SelectObject(hdc,grispen);
			// linea vertical
			MoveToEx(hdc,rect.right-1,rect.top,NULL);
			LineTo(hdc,rect.right-1,rect.bottom-1);
			// Linea horizontal
			LineTo(hdc,rect.left-1,rect.bottom-1);
		}
		
		// Margen de la celda
		rect.left += m_cellMargin.left;
		rect.right -= m_cellMargin.right;
		rect.top += m_cellMargin.top;
		rect.bottom -= m_cellMargin.bottom;
		// Poner Clip Rgn
		::SetRectRgn(hrgn,max(rect.left,gcell.left),max(rect.top,gcell.top),min(rect.right,gcell.right),min(rect.bottom,gcell.bottom));
		::SelectClipRgn(hdc,hrgn);
		// desplazar
		dr = m_IDBArray->GetColumnInfo(gcell.arrayIndex,NULL,&strinfo.str,&dbFlags);
		if ((dbFlags & F_OWNERDRAW) && (gcell.type == DATA_CELL))
		{
			// Dibujar celda por la clase
		}
		else
		{
			// Texto
			if (gcell.type == DATA_CELL) dr = m_IDBArray->GetStrAt(gcell.rowIndex,gcell.arrayIndex,&strinfo);
			rect.left += m_textMargin.left;
			rect.top += m_textMargin.top;
			rect.right -= (m_textMargin.right+1);
			rect.bottom -= (m_textMargin.bottom+1);
			DrawText(hdc,strinfo.str,-1,&rect,strinfo.uFormat);
		}
		rect = gcell;
		dr = GetNextVisibleCell(&gcell);
		// Zona restante
		if ((dr == ERR_EOT) && (endcell == NULL))
		{
			::SelectClipRgn(hdc,NULL);
			RECT	crect;
			::GetClientRect(*this,&crect);
			SetBkColor(hdc,RGB(255,255,255));
			if (rect.bottom < crect.bottom)
			{
				int top = crect.top;
				crect.top = rect.bottom;
				::ExtTextOut(hdc,0,0,ETO_OPAQUE,&crect,NULL,0,NULL);
				crect.top = top;
			}
			if (rect.right < crect.right)
			{
				crect.left = rect.right;
				::ExtTextOut(hdc,0,0,ETO_OPAQUE,&crect,NULL,0,NULL);
			}
		}
	} // while 
	// liberar objetos
	::SelectObject(hdc,oldpen);
	::SelectObject(hdc,oldfont);
	::DeleteObject(grispen);
	::DeleteObject(blackpen);
	::DeleteObject(hrgn);
	if (!OnDc)	::ReleaseDC(*this,hdc);
	return 0;
}

DWORD CGrid::CompareCells(GCELL *lpgcell1, GCELL *lpgcell2, WORD* colrel, WORD* rowrel)
{
	// comparacion sencilla
	if (lpgcell1->rowIndex < lpgcell2->rowIndex) *rowrel = LESS;
	else
		if (lpgcell1->rowIndex > lpgcell2->rowIndex) *rowrel = GREATER;
		else
			*rowrel = EQUAL;

	if (lpgcell1->columnIndex < lpgcell2->columnIndex) *colrel = LESS;
	else
		if (lpgcell1->columnIndex > lpgcell2->columnIndex) *colrel = GREATER;
		else 
			*colrel = EQUAL;
	// si son iguales ya se comparo
	if (lpgcell1->type == lpgcell2->type) return 0;
	// si la uno es tope en row entonces menor
	if (lpgcell1->type == FIXEDTOP_CELL)
	{
		if (lpgcell2->type == DATA_CELL) *rowrel = LESS;
		if (lpgcell2->type == FIXEDLEFT_CELL)
		{
			*rowrel = LESS;
			*colrel = GREATER;
		}
		return 0;
	}
	if (lpgcell1->type == FIXEDLEFT_CELL)
	{
		if (lpgcell2->type == FIXEDTOP_CELL)
		{
			*colrel = LESS;
			*rowrel = GREATER;
		}
		if (lpgcell2->type == DATA_CELL) *colrel = LESS;
		return 0;
	}
	if (lpgcell1->type == DATA_CELL)
	{
		if (lpgcell2->type == FIXEDLEFT_CELL) *colrel = GREATER;
		if (lpgcell2->type == FIXEDTOP_CELL) *rowrel = GREATER;
	}
	return 0;
}

DWORD CGrid::OnMouseMove(UINT nFlags, int x, int y)
{
	GCELL	gcell;
	DWORD	dr;
	WORD	mousepos;
	if ((m_MouseMode == M_COL_SIZING)&&
		((x > m_cellsrect.left) || (x+2 < m_cellsrect.right)))
	{
		SetCursor(LoadCursor(NULL,IDC_SIZEWE));	
		RECT	rect;
		HDC	hdc = ::GetDC(*this);
		rect = m_cellsrect;
		rect.left = m_mouselastx;
		rect.right = rect.left+2;
		InvertRect(hdc,&rect);
		rect.left = x;
		rect.right = rect.left+2;
		InvertRect(hdc,&rect);
		::ReleaseDC(*this,hdc);
		m_mouselastx = x;
		return 0;
	}
	dr = GetMousePos(x,y,&gcell,&mousepos);
	if ((mousepos == M_COL_DIV_RIGHT) || (mousepos == M_COL_DIV_LEFT)) SetCursor(LoadCursor(NULL,IDC_SIZEWE));
	if (mousepos == M_NOTHING) SetCursor(LoadCursor(NULL,IDC_ARROW));
	return 0;
}

DWORD CGrid::GetMousePos(int x,int y,GCELL *lpgcell,WORD *lpmousepos)
{
	DWORD dr;
	dr = GetCellFromPoint(x,y,lpgcell);
	if (dr != ERR_NONE) lpgcell->type = NO_CELL;
	*lpmousepos = M_NOTHING;
	if (lpgcell->type == FIXEDTOP_CELL)
	{
		if ((x < lpgcell->left+5) && (lpgcell->columnIndex != 0)) *lpmousepos = M_COL_DIV_LEFT;
		if (x+5 > lpgcell->right) *lpmousepos = M_COL_DIV_RIGHT;
	}
	return 0;
}

LRESULT CGrid::OnLButtonUp(UINT nFlags, int x, int y)
{
	GCOLUMNINFO*	cinfo;
	DWORD		dr;
	WORD		width;
	//if (::GetCapture() == *this) ReleaseCapture();
	if (m_MouseMode == M_COL_SIZING)
	{
		RECT	rect;
		HDC	hdc = ::GetDC(*this);
		rect = m_cellsrect;
		rect.left = m_mouselastx;
		rect.right = rect.left+2;
		InvertRect(hdc,&rect);
		::ReleaseDC(*this,hdc);
		dr = m_IDBArray->GetColumnExtraDataPtr(m_mousestartcell.arrayIndex,m_ColumnDataOffset,(void**)&cinfo);
		width = cinfo->width;
		SetColumnWidth(m_mousestartcell.columnIndex,max (0,width+x-m_mousestartx));
		m_MouseMode = M_NOTHING;
		ReleaseCapture();
	}
	return 0;
}

LRESULT CGrid::OnLButtonDblClk(UINT nFlags, int x, int y)
{
	GCELL	gcell;
	DWORD	dr;
	WORD	mousepos;
	DWORD	id;

	dr = GetMousePos(x,y,&gcell,&mousepos);
	if (gcell.type == DATA_CELL)
	{
		id = ::GetWindowLong(*this,GWL_ID);
		::SendMessage(m_hNotifyWind,WM_COMMAND,MAKEWPARAM(id,GN_DBLCLK),gcell.rowIndex);
	}
	return 0;	
}

DWORD CGrid::SetNotifyWind(HWND hwnd)
{
	m_hNotifyWind = hwnd;
	return 0;
}

DWORD CGrid::Calc_EndX()
{
	DWORD i;
	DWORD dr;
	GCOLUMNINFO* cinfo;
	m_EndX = 0;
	for(i=0;i<m_VColumnCount;i++)
	{
		dr = GetVisibleColumn(i,&cinfo,NULL);
		if (dr != ERR_NONE) return dr;
		m_EndX += cinfo->width;
	}
	ShowScrolls();
	SetStartX(m_StartX);
	return 0;
}

DWORD CGrid::SetIdbClass(IDBClass *lpIdbClass)
{
	m_IdbClass = lpIdbClass;
	return 0;
}

DWORD CGrid::GetVisibleColumn(DWORD dwIndex,GCOLUMNINFO **lpgColumnInfo,DWORD* lpdwArrayIndex)
{
	// buscar la columna con el indixe correspondiente
	DWORD	columncount;
	DWORD	i;
	DWORD	dr;
	DWORD	dbFlags;
	GCOLUMNINFO*	cinfo;
	columncount = m_IDBArray->GetColumnCount();
	for(i=0;i<columncount;i++)
	{
		m_IDBArray->GetColumnInfo(i,NULL,NULL,&dbFlags);
		if (dbFlags & DB_F_INVISIBLE) continue;
		dr = m_IDBArray->GetColumnExtraDataPtr(i,m_ColumnDataOffset,(void**)&cinfo);
		if (cinfo->index == dwIndex)
		{
			if (lpgColumnInfo) *lpgColumnInfo = cinfo;
			if (lpdwArrayIndex) *lpdwArrayIndex = i;
			return ERR_NONE;
		}
	}
	return ERR_EOT;
}

DWORD CGrid::SetColumnWidth(DWORD dwColumnIndex, WORD width)
{
	DWORD	dbFlags;
	DWORD	dr;
	DWORD	arrayIndex;
	GCOLUMNINFO*	cinfo;
	DWORD	columncount = m_IDBArray->GetColumnCount();
	dr = GetVisibleColumn(dwColumnIndex,&cinfo,&arrayIndex);
	if (cinfo->width == width) return 0;
	cinfo->width = width;
	m_IDBArray->GetColumnInfo(arrayIndex,NULL,NULL,&dbFlags);
	if (dbFlags & F_ONMULTILINE)	UpdateRowHeight(-1);
	Calc_EndX();
	DrawCells(NULL,NULL,NULL);
	return 0;

}

DWORD CGrid::SetExtraDataOffset(DWORD dwRowExtraDataOffset, DWORD dwColumnExtraDataOffset)
{
	m_RowDataOffset = dwRowExtraDataOffset;
	m_ColumnDataOffset = dwColumnExtraDataOffset;
	return ERR_NONE;
}


DWORD CGrid::GetExtraDataSize(DWORD *lpdwRowExtraDataSize, DWORD *lpdwColumnExtraDataSize)
{
	*lpdwColumnExtraDataSize = sizeof(GCOLUMNINFO);
	*lpdwRowExtraDataSize= sizeof(GROWINFO);
	return ERR_NONE;
}

DWORD CGrid::Calc_EndY()
{
	DWORD	i;
	DWORD	dr;
	DWORD	rowcount;
	GROWINFO*	rinfo;
	rowcount = m_IDBArray->GetRowCount();
	m_EndY = 0;
	for(i=0;i<rowcount;i++)
	{
		dr = m_IDBArray->GetRowExtraDataPtr(i,m_RowDataOffset,(void**)&rinfo);
		if (dr != ERR_NONE) return dr;
		m_EndY += rinfo->height;
	}
	ShowScrolls();
	SetStartY(m_StartY);
	return 0;
}
