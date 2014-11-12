// BinaryWnd.cpp: implementation of the CBinaryWnd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BinaryWnd.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------------------------------------------------
CBinaryWnd::CBinaryWnd()
{
	m_hFont = NULL;
	m_fontHeight = 0;
	m_fontWidth = 0;
	m_topIndex = 0;
	m_bpr = 16;
	m_flags &= ~ON_HI_CHAR;	// Reset flag HI_CHAR
	m_CareIndex = 0;
	SetMaxSize(1*1024*1024);
}

//------------------------------------------------------------------------------------------------------------------------
CBinaryWnd::~CBinaryWnd()
{

}

//------------------------------------------------------------------------------------------------------------------------
LRESULT CBinaryWnd::OnWindProc(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_PAINT		: return Paint();
	case WM_SETFOCUS	: return OnSetFocus();
	case WM_KILLFOCUS	: return OnKillFocus();break;
	case WM_LBUTTONDOWN	: return OnLButtonDown(wParam,lParam);
	//case WM_SETCURSOR	: return OnSetCursor(wParam,lParam);
	case WM_MOUSEMOVE	: return OnMouseMove(wParam,lParam);
	case WM_CHAR		: return OnChar(wParam,lParam);
	case WM_KEYDOWN		: return OnKeyDown(wParam,lParam);
	case WM_SIZE		: return OnSize(wParam,lParam);
	case WM_VSCROLL		: return OnVerticalScroll(wParam,lParam);
	default:
		return DefWindowProc(hWnd,uMsg,wParam,lParam);
	}
	return 0;
}


//------------------------------------------------------------------------------------------------------------------------
DWORD CBinaryWnd::Initialize()
{
	LOGFONT logFont;
	memset(&logFont,0,sizeof(logFont));
	strcpy(logFont.lfFaceName,"Courier");
	logFont.lfHeight=-12;
	logFont.lfWidth=0;
	logFont.lfWeight=FW_NORMAL;
	logFont.lfOutPrecision= OUT_CHARACTER_PRECIS;
	logFont.lfClipPrecision= CLIP_CHARACTER_PRECIS;
	logFont.lfQuality= DEFAULT_QUALITY;
	logFont.lfPitchAndFamily= DEFAULT_PITCH | FF_DONTCARE;
	logFont.lfCharSet=ANSI_CHARSET;
	logFont.lfItalic = false;
	for (;;)
	{
		m_hFont = CreateFontIndirect(&logFont);
		if (m_hFont == NULL) break;
		return 0;
	}
	::DeleteObject(m_hFont);
	m_hFont = NULL;
	return 1;
}

//------------------------------------------------------------------------------------------------------------------------
LRESULT CBinaryWnd::Paint()
{
	PAINTSTRUCT ps;
	HGDIOBJ tmphFont;
	HDC hdc;
	RECT	rt;
	BYTE	val;
	char tmpStr[10];
	DWORD tmpj;
	DWORD	index;
	DWORD	buffsize = GetSize();

	SIZE	size;		// Tamaño de las letras
	/*
		Inicialización
	*/
	index = m_topIndex;
	hdc = BeginPaint(*this, &ps);
	tmphFont = SelectObject(hdc,m_hFont);
	::GetClientRect(*this,&rt);
	/*
		Determinar el tamaño de un caracter
	*/
	if (m_fontHeight == 0)
	{
		GetTextExtentPoint32(hdc,"0",1,&size);
		m_fontHeight = size.cy;
		m_fontWidth = size.cx;
		// Actualizar ScrollBar
		UpdateScrolls();
	}
	do
	{
		rt.left = 0;
		// Imprimir posicion del buffer
		sprintf(tmpStr,"%06X",index);
		::DrawText(hdc,tmpStr,-1,&rt,DT_LEFT);
		for (tmpj=0;tmpj<m_bpr;tmpj++,index++)
		{
			if (index == buffsize) break;
			val = Data()[index];
			rt.left = m_fontWidth * (tmpj*3+6+SPC1);
			// Convertir numero a hex
			tmpStr[0] = (val >> 4) + '0';
			tmpStr[1] = (val & 0x0F) + '0';
			if (tmpStr[0] > '9') tmpStr[0] += 7;
			if (tmpStr[1] > '9') tmpStr[1] += 7;
			tmpStr[2] = 0;
			::DrawText(hdc,tmpStr,-1,&rt,DT_LEFT);
			if (val < 32) tmpStr[0] = '.';
			else
				tmpStr[0] = val;
			tmpStr[1]=0;
			rt.left = m_fontWidth * (6+SPC1+(2+SPC2)*m_bpr+SPC3+tmpj);
			::DrawText(hdc,tmpStr,-1,&rt,DT_LEFT);
		}
		rt.top += m_fontHeight;
		// repetir mientras se pueda escribir y se hallan llenados todos los bytes 
	} while ((rt.top < rt.bottom) && (tmpj == m_bpr));	

	SelectObject(hdc,tmphFont);
	EndPaint(*this, &ps);
	return 0;	
}

//------------------------------------------------------------------------------------------------------------------------
DWORD CBinaryWnd::OnCreate()
{
	return 0;
}

//------------------------------------------------------------------------------------------------------------------------
DWORD CBinaryWnd::OnSetFocus()
{
	CreateCaret(*this,NULL,2,m_fontHeight);
	UpdateCaret(); 
	return 0;
}

//------------------------------------------------------------------------------------------------------------------------
DWORD CBinaryWnd::OnKillFocus()
{ 
	DestroyCaret();
	return 0;
}

//------------------------------------------------------------------------------------------------------------------------
DWORD CBinaryWnd::OnLButtonDown(WPARAM wParam, LPARAM lParam)
{
	SetFocus(*this);
	int xPos = LOWORD(lParam); 
	int yPos = HIWORD(lParam);
	if ((xPos < 0) || (yPos <0))
		return 0;
	DWORD I;
	switch (PosToIndex(xPos,yPos,&I))
	{
	case 0 : m_flags &= ~ON_ASCII_CARET;break;
	case 3 : m_flags |= ON_ASCII_CARET;break;
	default: return 1;
	}
	MoveCaret(I);
	return 0;
}

//------------------------------------------------------------------------------------------------------------------------
LRESULT CBinaryWnd::OnSetCursor(WPARAM wParam, LPARAM lParam)
{
	long Px = LOWORD(lParam);
	long Py = HIWORD(lParam);
	return 0;
}

//------------------------------------------------------------------------------------------------------------------------
LRESULT CBinaryWnd::OnMouseMove(WPARAM wParam, LPARAM lParam)
{
	SetCursor(LOWORD(lParam),HIWORD(lParam));
	return 0;
}

//------------------------------------------------------------------------------------------------------------------------
DWORD CBinaryWnd::IndexToCursor(DWORD Index, DWORD *lpdwx, DWORD *lpdwy)
{
	DWORD Px,Py;
	WINDOW_METRICS wm;
	GetWindowMetrics(&wm);

	if (Index < m_topIndex) return 1;
	if (Index > GetSize()) return 1;

	if (m_flags & ON_ASCII_CARET)
	{
		Px = m_fontWidth*(6+SPC1+m_bpr*(SPC2+2)+SPC3);	// primer ascii
		Px += (Index % m_bpr)*m_fontWidth;
	}
	else
	{
		Px = m_fontWidth*(6+SPC1);	// 6 Dir 1 space
		Px = Px + (Index % m_bpr)*m_fontWidth*3;
	}
	Py = ((Index - m_topIndex) / m_bpr)*m_fontHeight;
	if ((Px > wm.WinWidth) || (Py > wm.WinHeight)) return 1;
	*lpdwx = Px;
	*lpdwy = Py;
	return 0;
}
/*
	Dada la posicion del cursor obtener index
	0 - El esta dentro de los valores
*/
//------------------------------------------------------------------------------------------------------------------------
DWORD CBinaryWnd::PosToIndex(long lx, long ly, DWORD *lpdwIndex)
{
	DWORD result=0;
	DWORD Ix,Iy,I;
	if (m_fontHeight == 0) return 1;
	if ((lx < 0) || (ly < 0)) return 2;	// fuera de zona
	
	// Posicion en las x
	if (lx < m_fontWidth*(6+SPC1-0.5)) return 2; // Esta antes de la mitad del espacio del  byte 1
	if (lx < m_fontWidth*(6+SPC1))
		lx = 0;							// Esta en el espacio antes del primer byte
	else
		lx -= m_fontWidth*(6+SPC1);		// Ajustar posicion 0 es el primer byte

	if (lx > m_fontWidth*((2+SPC2)*m_bpr + 0.5))
	{
		// se paso del ultimo byte
		if (lx < m_fontWidth*((2+SPC2)*m_bpr+SPC3-0.5)) return 2;	// Esta entre los bytes y el ASCII
		if (lx < m_fontWidth*((2+SPC2)*m_bpr+SPC3))
			lx = 0;
		else
			lx -= m_fontWidth*((2+SPC2)*m_bpr+SPC3);
		if (lx > m_fontWidth*(m_bpr+0.5)) return 2;	//Esta mas alla de los ascii

		// Esta fuera de los bytes
		Ix = lx / m_fontWidth;
		if ((lx % m_fontWidth) > (m_fontWidth*0.5)) Ix++; // esta mas alla de la mitad
		if (Ix >= m_bpr) Ix = m_bpr-1;
		Iy = ly / m_fontHeight;
		I = Iy*m_bpr+Ix;
		if (I > GetSize() - m_topIndex) I= GetSize();
		else
			I = m_topIndex + I;
		*lpdwIndex = I;
		return 3;				// esta en la zona de los ascii

	} // garantizar que IndexX = 16 si esta 

	Ix = lx / (m_fontWidth*(SPC2+2));
	if ((lx % (m_fontWidth*(SPC2+2))) > (m_fontWidth*1.5)) Ix++;	// si esta mas alla de la mitad del segundo caracter y no es el ultimo pasar al siguiente	
	if (Ix >= m_bpr) Ix = m_bpr;
	Iy = ly / m_fontHeight;
	I = Iy*m_bpr+Ix;
	if (I > GetSize() - m_topIndex) 
	{
		I= GetSize();					// la posicion esta mas halla del ultimo byte visible
		result = 2;
	}
	else
		I = m_topIndex + I;
	*lpdwIndex = I;
	return result;
}

//------------------------------------------------------------------------------------------------------------------------
DWORD CBinaryWnd::SetCursor(long lx, long ly)
{
	LPCTSTR lpCursorName;
	if (lx < m_fontWidth*(6+SPC1-0.5)) lpCursorName = IDC_ARROW;
	else
		if (lx < m_fontWidth*(6+SPC1+m_bpr*(2+SPC2)-SPC2+0.5)) lpCursorName = IDC_IBEAM;
		else
			if (lx < m_fontWidth*(6.0f+SPC1+m_bpr*(2+SPC2)+SPC3)) lpCursorName = IDC_ARROW;
			else
				if (lx < m_fontWidth*(6+SPC1+m_bpr*(2+SPC2)+SPC3+m_bpr+0.5)) lpCursorName = IDC_IBEAM;
				else
					lpCursorName = IDC_ARROW;
	if ((m_fontHeight == 0) || (lx == 0) || (ly == 0))
		lpCursorName = IDC_ARROW;
	::SetCursor(LoadCursor(NULL,lpCursorName));
	return 0;
}

//------------------------------------------------------------------------------------------------------------------------
LRESULT CBinaryWnd::OnChar(WPARAM wParam,LPARAM lParam)
{
	unsigned char nChar = wParam;
	DWORD index;
	BYTE	val;
	DWORD dr = 0;
	if (nChar < 32) return 0;	// No se procesa aqui
	if (m_CareIndex == GetSize()) dr = SetSize(GetSize()+1);
	if (dr != 0) return 0;
	index = m_CareIndex;
	val = Data()[index];
	// Comprobar si la letra pertenece a los numeros o los ascii
	if (m_flags & ON_ASCII_CARET)
	{
		val = nChar;
		MoveCaret(m_CareIndex+1);
	}
	else

	if ((nChar >= '0' && nChar <= '9') || (nChar >= 'a' && nChar <= 'f') || (nChar >= 'A' && nChar <= 'F'))
	{
		if (nChar <= '9')
			nChar = nChar -'0';
		else
			if (nChar <= 'F')
				nChar = nChar -'A'+10;
			else
				nChar = nChar - 'a'+10;
		if (!(m_flags & ON_HI_CHAR))
		{
			val = nChar;
			m_flags |= ON_HI_CHAR;
		}
		else
		{
			val = (val * 0x10) + nChar;
			MoveCaret(m_CareIndex+1);
		}
	}
	Data()[index] = val;
	MakeIndexVisible(m_CareIndex);
	InvalidateRect(*this,NULL,TRUE);
	return 0;
}

/*
	Actualiza posicion y visibilidad del caret
*/
//------------------------------------------------------------------------------------------------------------------------
DWORD CBinaryWnd::UpdateCaret()
{
	DWORD Px,Py;
	// ver si el caret esta visible
	if (IndexToCursor(m_CareIndex,&Px,&Py) == 0)
	{
		SetCaretPos(Px,Py);
		ShowCaret(*this);
	}
	else
		HideCaret(*this);
	return 0;
}

/*
	Hace visible la posicion del caret
*/
//------------------------------------------------------------------------------------------------------------------------
DWORD CBinaryWnd::MoveCaret(DWORD dwIndex)
{
	if (dwIndex > GetSize()) return 1; 
	MakeIndexVisible(dwIndex);
	m_flags &= ~ON_HI_CHAR;
	m_CareIndex = dwIndex;
	return UpdateCaret();
}

//------------------------------------------------------------------------------------------------------------------------
LRESULT CBinaryWnd::OnKeyDown(WPARAM wParam, LPARAM lParam)
{
	DWORD	tmpTopIndex = m_topIndex;
	char nChar = wParam;
	switch (nChar)
	{
	case VK_RIGHT	: MoveCaret(m_CareIndex+1);break;
	case VK_LEFT	: if (m_CareIndex > 0) MoveCaret(m_CareIndex-1);break;
	case VK_UP		: if (m_CareIndex >= m_bpr) MoveCaret(m_CareIndex-m_bpr);break;
	case VK_DOWN	: if (GetSize() - m_bpr >= m_CareIndex) MoveCaret(m_CareIndex+m_bpr);break;
	case VK_DELETE	: 
		if ((m_CareIndex != GetSize()) && (GetSize() >0))
		{
			memmove(&Data()[m_CareIndex],&Data()[m_CareIndex+1],GetSize()-m_CareIndex-1);
			SetSize(GetSize() -1);
			tmpTopIndex = m_topIndex + 1;
		};break;
	case VK_BACK	:
		if (m_CareIndex != 0)
		{
			memmove(&Data()[m_CareIndex-1],&Data()[m_CareIndex],GetSize()-m_CareIndex);
			SetSize(GetSize() -1);
			MoveCaret(m_CareIndex-1);
			tmpTopIndex = m_topIndex + 1;
		};break;
	}
	UpdateScrolls();
	if (tmpTopIndex != m_topIndex)
		InvalidateRect(*this,NULL,TRUE);
	return 0;
}

void CBinaryWnd::UpdateScrolls()
{
	if (m_fontHeight == 0) return;
	// Habilitar-desabilitar los scrolls el vertical depende de la cantidad de columnas.
	/* Nota :
		No se puede quitar el scroll si la primera fila visible no es la 1
	*/
	WINDOW_METRICS wm;
	GetWindowMetrics(&wm);

	BOOL OnVScroll=FALSE,OnHScroll=FALSE;

	DWORD Width = (SPC0+6+SPC1+(2+SPC2)*m_bpr+SPC3+m_bpr)*m_fontWidth; // Pixel de ancho necesarios
	for (int i =0;i<2;i++)
	{
		if ((!OnVScroll) && (wm.WinRows <= wm.RowCount))
		{
			SetScrollRange(*this,SB_VERT,0,wm.RowCount - wm.WinRows,FALSE);
			SetScrollPos(*this,SB_VERT,wm.TopRow,TRUE);
			OnVScroll = TRUE;
			wm.WinWidth -= wm.ScrollWidth;
		}
		/*
		if ((!OnHScroll) && (wm.WinWidth < Width))
		{
			OnHScroll = TRUE;
			SetScrollRange(*this,SB_HORZ,0,Width - wm.WinWidth,FALSE);
			wm.WinHeight -= wm.ScrollHeight;
		}
		*/
	}
	ShowScrollBar(*this,SB_VERT,OnVScroll);
	ShowScrollBar(*this,SB_HORZ,OnHScroll);
}

LRESULT CBinaryWnd::OnSize(WPARAM wParam, LPARAM lParam)
{
	UpdateScrolls();
	return 0;
}

LRESULT CBinaryWnd::OnVerticalScroll(WPARAM wParam, LPARAM lParam)
{
	WINDOW_METRICS	wm;
	GetWindowMetrics(&wm);

	switch (LOWORD(wParam))
	{
	case SB_LINEDOWN:
		{
			if(wm.TopRow + wm.WinRows < wm.RowCount)
			{
				m_topIndex += m_bpr;
				InvalidateRect(*this,NULL,TRUE);
				UpdateCaret();
			}
			break;
		}
	case SB_LINEUP:
		{
			if (m_topIndex  >= m_bpr)
			{
				m_topIndex -= m_bpr;
				InvalidateRect(*this,NULL,TRUE);
				UpdateCaret();
			}
			break;
		}
	case SB_PAGEUP:
		{
			break;
		}
	case SB_PAGEDOWN:
		{
			break;
		}
	case SB_THUMBPOSITION:
	case SB_THUMBTRACK:
		{
			/*
			DWORD Pos=HIWORD(wParam);
			if (Pos != ViewRowStart)
			{
				ViewRowStart=Pos;
				ScrollVertical.SetScrollPos(ViewRowStart);
				HDC hdc=::GetDC(*this);
				GridPaint(hdc);
				::ReleaseDC(*this,hdc);
			}
			*/
			break;
		}
	}
	::SetScrollPos(*this, SB_VERT, m_topIndex / m_bpr, TRUE);
	return 0;
}

/*
	Actualiza la posicion del primer elemento (m_topIndex) para que se haga visible 
	la posicion indicada (pIndex)
*/
DWORD CBinaryWnd::MakeIndexVisible(DWORD dwIndex)
{
	WINDOW_METRICS	wm;
	GetWindowMetrics(&wm);
	DWORD Row = dwIndex / m_bpr;	//fila que ocupa la posicion indicada
	if ((wm.TopRow <= Row) && (wm.TopRow + wm.WinRows - 1 >= Row)) return 0; // Nada que hacer
	if (Row < wm.TopRow) m_topIndex = Row * m_bpr;	// La columna esta mas arriba
	if ((wm.TopRow !=0) && (wm.TopRow + wm.WinRows - 1 >= wm.RowCount)) m_topIndex = (wm.RowCount <= wm.WinRows-1) ? (0) : ((wm.RowCount - wm.WinRows) * m_bpr);
	if (wm.TopRow + wm.WinRows - 1 < Row) m_topIndex = (Row - wm.WinRows + 1) * m_bpr;	// se resta 1 porque cantidad es 1 index
	UpdateScrolls();
	InvalidateRect(*this,NULL,TRUE);
	return 0;
}

DWORD CBinaryWnd::GetWindowMetrics(WINDOW_METRICS *lpwindowmetrics)
{
	RECT	rect;
	GetClientRect(*this,&rect);
	lpwindowmetrics->WinHeight = rect.bottom - rect.top;
	lpwindowmetrics->WinWidth  = rect.right - rect.left;
	lpwindowmetrics->ScrollHeight=GetSystemMetrics(SM_CYHSCROLL);
	lpwindowmetrics->ScrollWidth=GetSystemMetrics(SM_CXVSCROLL);
	lpwindowmetrics->RowCount = GetSize() / m_bpr + 1;
	lpwindowmetrics->WinRows = lpwindowmetrics->WinHeight / m_fontHeight;
	lpwindowmetrics->TopRow = m_topIndex / m_bpr;
	return 0;
}


DWORD CBinaryWnd::Create_Window(int x, int y, int nWidth, int nHeight,HWND hWndParent)
{
	return Create("Ventana 1",WS_VSCROLL|WS_HSCROLL|WS_BORDER|WS_CHILD|WS_VISIBLE,x,y,nWidth,nHeight,hWndParent,NULL,NULL);
}

DWORD CBinaryWnd::ClearAll()
{
	SetSize(0);
	return 0;
}
