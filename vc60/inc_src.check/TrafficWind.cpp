// TrafficWind.cpp: implementation of the CTrafficWind class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\include\TrafficWind.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTrafficWind::CTrafficWind()
{
	m_hFont = NULL;
	m_fontHeight = 0;
	m_fontWidth = 0;
	m_bpr = 16;
	m_Rows = 0;
	m_TopRow = 0;
}

CTrafficWind::~CTrafficWind()
{

}

LRESULT CTrafficWind::WndProc(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_PAINT		: return Paint();
	/*
	case WM_SETFOCUS	: return OnSetFocus();
	case WM_KILLFOCUS	: return OnKillFocus();break;
	case WM_LBUTTONDOWN	: return OnLButtonDown(wParam,lParam);
	//case WM_SETCURSOR	: return OnSetCursor(wParam,lParam);
	case WM_MOUSEMOVE	: return OnMouseMove(wParam,lParam);
	case WM_CHAR		: if (OnBinaryWindow) return OnChar(wParam,lParam);
	case WM_KEYDOWN		: if (OnBinaryWindow) return OnKeyDown(wParam,lParam);
	case WM_SIZE		: return OnSize(wParam,lParam);
	*/
	case WM_VSCROLL		: return OnVerticalScroll(wParam,lParam);
	default:
		return DefWindowProc(hWnd,uMsg,wParam,lParam);
	}
	return 0;

}

DWORD CTrafficWind::Paint()
{
	PAINTSTRUCT ps;
	HGDIOBJ tmphFont;
	HDC hdc;
	RECT	rt;
	char tmpStr[10];
	DWORD i,result,j,size;
	BYTE  type,val;
	BYTE  rowsize;	// de acuerdo al tipo cantidad de datos para completar una columna
	BYTE  datasize; // cantidad de caracteres que ocupa un dato

	/*
		Inicialización
	*/
	MoveTo(0);
	hdc = BeginPaint(m_hwnd, &ps);
	tmphFont = SelectObject(hdc,m_hFont);
	::GetClientRect(m_hwnd,&rt);
	/*
		Determinar el tamaño de un caracter
	*/
	if (m_fontHeight == 0)
	{
		SIZE	size;
		GetTextExtentPoint32(hdc,"0",1,&size);
		m_fontHeight = size.cy;
		m_fontWidth = size.cx;
		UpdateScroll();
	}
	// Avanzar hasta la primera fila visible
	DWORD Row=0,rows;
	while (Row < m_TopRow)
	{
		result = GetBufferInfo(&type,&size);
		GetBufferMetrics(type,&rowsize,&datasize);
		if (result != 0) goto paint_exit;
		CalcRows(type,size,&rows);
		if (Row+rows <= m_TopRow)
		{
			Row+=rows;
			Move(size);
		}
		else
		{
			// Avanzar una cantidad x de filas hasta llegar al comienzo
			Move((m_TopRow-Row)*rowsize);
			size -= (m_TopRow-Row)*rowsize; 
			goto draw_row;
		}
	}
	do
	{
		rt.left = 0;
		result = GetBufferInfo(&type,&size);
		if (result != 0) break;			//Fin del buffer
		if (type == END_BUF) break;		//Buffer por definir
		switch (type)
		{
		case SND_BUF: sprintf(tmpStr,"Snd");break;
		case RCV_BUF: sprintf(tmpStr,"Rcv");break;
		case COM_BUF: sprintf(tmpStr,"Cmt");break;
		}
		::DrawText(hdc,tmpStr,-1,&rt,DT_LEFT);
draw_row:
		j = 0;
		// cantidad de datos para completar la fila
		GetBufferMetrics(type,&rowsize,&datasize);
		//
		for (i=0;i<size;i++)
		{
			if (j >= rowsize)
			{
				rt.top += m_fontHeight;
				j = 0;
				if (rt.top > rt.bottom) break;
			}
			GetValueMoveNext(&val);
			
			// Obtener la cadena a imprimir
			switch (type)
			{
			case SND_BUF:
			case RCV_BUF:
				{
					// Imprimir ascii
					if (val < 32) tmpStr[0] = '.';
					else
						tmpStr[0] = val;
					tmpStr[1]=0;
					rt.left = m_fontWidth * (SP0+SP1+(2+SP2)*m_bpr+SP3+j);
					::DrawText(hdc,tmpStr,-1,&rt,DT_LEFT);
					// preparar numero
					tmpStr[0] = (val >> 4) + '0';
					tmpStr[1] = (val & 0x0F) + '0';
					if (tmpStr[0] > '9') tmpStr[0] += 7;
					if (tmpStr[1] > '9') tmpStr[1] += 7;
					tmpStr[2] = 0;
					break;					
				}
			case COM_BUF:
				{
					tmpStr[0]=val;
					tmpStr[1]=0;
					break;
				}
			}
			// Convertir numero a hex
			rt.left = m_fontWidth * (j*(datasize)+SP0+SP1);
			::DrawText(hdc,tmpStr,-1,&rt,DT_LEFT);
			j++;
		}
		rt.top += m_fontHeight;
	} while (rt.top < rt.bottom);
paint_exit:
	SelectObject(hdc,tmphFont);
	EndPaint(m_hwnd, &ps);
	return 0;
}

DWORD CTrafficWind::Initialize()
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
	m_hFont = CreateFontIndirect(&logFont);
	if (m_hFont == NULL) return 1;
	if (CVirtualMemory::Initialize() != 0) goto failed_1;
	return 0;
failed_1:
	::DeleteObject(m_hFont);
	m_hFont = NULL;
	return 1;
}


DWORD CTrafficWind::AddBuffer(BYTE *lpBuffer, DWORD dwSize)
{
	// Cantidad de columnas.
	DWORD*	size = (DWORD*)&lpBuffer[1];
	if (*size == 0) return 2;
	BYTE*	type = (BYTE*)&lpBuffer[0];
	DWORD	rows;
	CalcRows(*type,*size,&rows);
	m_Rows += rows;
	AddData(lpBuffer,*size+sizeof(BYTE)+sizeof(DWORD));
	if (m_hwnd)
	{
		UpdateScroll();
		InvalidateRect(m_hwnd,NULL,TRUE);
	}
	UpdateScroll();
	return 0;
}

DWORD CTrafficWind::UpdateScroll()
{
	WINDOW_METRICS wm;
	BOOL OnVScroll=FALSE;
	if (GetWindowMetrics(&wm) != 0)
		return 1;
	if (wm.WinRows < wm.RowCount)
		OnVScroll = TRUE;
	SetScrollRange(m_hwnd,SB_VERT,0,wm.RowCount-wm.WinRows-1,FALSE);
	SetScrollPos(m_hwnd,SB_VERT,wm.TopRow,TRUE);
	ShowScrollBar(m_hwnd,SB_HORZ,false);
	ShowScrollBar(m_hwnd,SB_VERT,OnVScroll);
	EnableScrollBar(m_hwnd,SB_VERT,ESB_ENABLE_BOTH);
	return 0;
}

DWORD CTrafficWind::GetWindowMetrics(WINDOW_METRICS *lpwindowmetrics)
{
	if (m_fontHeight == 0) return 1;
	RECT	rect;
	GetClientRect(m_hwnd,&rect);
	lpwindowmetrics->WinHeight = rect.bottom - rect.top;
	lpwindowmetrics->WinWidth  = rect.right - rect.left;
	lpwindowmetrics->ScrollHeight=GetSystemMetrics(SM_CYHSCROLL);
	lpwindowmetrics->ScrollWidth=GetSystemMetrics(SM_CXVSCROLL);
	lpwindowmetrics->RowCount = m_Rows;
	lpwindowmetrics->WinRows = lpwindowmetrics->WinHeight / m_fontHeight;
	lpwindowmetrics->TopRow = m_TopRow;
	return 0;
}


LRESULT CTrafficWind::OnVerticalScroll(WPARAM wParam, LPARAM lParam)
{
	WINDOW_METRICS	wm;
	GetWindowMetrics(&wm);

	switch (LOWORD(wParam))
	{
	case SB_LINEDOWN:
		{
			if(wm.TopRow + wm.WinRows < wm.RowCount)
			{
				m_TopRow += 1;
				InvalidateRect(m_hwnd,NULL,TRUE);
			}
			break;
		}
	case SB_LINEUP:
		{
			if (wm.TopRow > 0)
			{
				m_TopRow -= 1;
				InvalidateRect(m_hwnd,NULL,TRUE);
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
				HDC hdc=::GetDC(m_hWnd);
				GridPaint(hdc);
				::ReleaseDC(m_hWnd,hdc);
			}
			*/
			break;
		}
	}
	::SetScrollPos(m_hwnd, SB_VERT,m_TopRow, TRUE);
	return 0;
}

DWORD CTrafficWind::CalcRows(BYTE bType, DWORD dwSize, DWORD *dwRows)
{
	switch (bType)
	{
	case SND_BUF:
	case RCV_BUF:
		{
			*dwRows = (dwSize-1)/m_bpr+1;
			break;
		}
	case COM_BUF:
		{
			*dwRows = (dwSize-1)/(m_bpr*3)+1;
			break;
		}
	}
	return 0;
}

DWORD CTrafficWind::GetBufferInfo(BYTE *lpbType, DWORD *lpdwSize)
{
	DWORD result;
	BYTE  i,val;
	result = GetValueMoveNext(lpbType);
	if (result != 0)
		return result;
	// Tamaño del buffer
	for (i=0,*lpdwSize=0;i<sizeof(*lpdwSize);i++)
	{
		result = GetValueMoveNext(&val);
		if (result != 0)
			return result;
		*lpdwSize += val << (i*8);
	}
	return 0;
}

DWORD CTrafficWind::ShowLastBuffer()
{
	WINDOW_METRICS	wm;
	if (GetWindowMetrics(&wm) != 0)
		return 1;
	if ((wm.RowCount > wm.WinRows) && (wm.TopRow + wm.WinRows < wm.RowCount))
	{
		m_TopRow = wm.RowCount-wm.WinRows;
		UpdateScroll();
		InvalidateRect(m_hwnd,NULL,TRUE);
	}
	return 0;
}

DWORD CTrafficWind::Create_Window(int x, int y, int nWidth, int nHeight, HWND hWndParent)
{
	DWORD result;
	result = Create("Ventana 2",WS_VSCROLL|WS_HSCROLL|WS_BORDER|WS_CHILD|WS_VISIBLE,x,y,nWidth,nHeight,hWndParent,NULL,(HINSTANCE)GetModuleHandle(NULL),NULL);
	return result;
}

DWORD CTrafficWind::RowsToSize(BYTE btype, DWORD dwRows, DWORD *dwSize)
{
	switch (btype)
	{
	case SND_BUF:
	case RCV_BUF:
		{
			*dwSize = dwRows*m_bpr;
			break;
		}
	case COM_BUF:
		{
			*dwSize = dwRows*m_bpr*(2+SP2);
			break;
		}
	}
	return 0;
}

/*
	Determinar la cantidad de bytes por fila y la cantidad de caracteres por byte

*/
DWORD CTrafficWind::GetBufferMetrics(BYTE bType, BYTE *bBytesRow, BYTE *bCharsByte)
{
	switch (bType)
	{
	case SND_BUF:
	case RCV_BUF:
		{
			*bBytesRow = m_bpr;
			*bCharsByte = 2+SP2;
			break;
		}
	case COM_BUF:
		{
			*bBytesRow = m_bpr*(2+SP2);
			*bCharsByte = 1;
			break;
		}
	}
	return 0;
}

DWORD CTrafficWind::Clear()
{
	SetSize(0);
	m_Rows = 0;
	m_TopRow = 0;
	UpdateScroll();
	Invalidate();
	return 0;
}
