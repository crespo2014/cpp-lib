// TrafficWind.cpp: implementation of the CTrafficWind class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TrafficWind.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

typedef struct
{
	BYTE	type;
	DWORD	size;
	BYTE	data[0];
} BUFF_HEADER;


CTrafficWind::CTrafficWind()
{
	m_hFont = NULL;
	m_fontHeight = 0;
	m_fontWidth = 0;
	m_bpr = 16;
	m_Rows = 0;
	m_TopRow = 0;
	m_OnUpdateScrolls = FALSE;
	m_Buffer.SetMaxSize(5*1024*1024);
}

CTrafficWind::~CTrafficWind()
{
	Release();
}

LRESULT _stdcall CTrafficWind::OnWindProc(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam)
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
	HDC hdc;
	hdc = BeginPaint(*this, &ps);
	if (hdc == NULL) return 0;
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
	if (m_OnUpdateScrolls) UpdateScroll();
	Paint_Window(hdc,ps);
	EndPaint(*this, &ps);
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
	for (;;)
	{
		m_hFont = CreateFontIndirect(&logFont);
		if (m_hFont == NULL) break;
		if (CLockEvent::Initialize() != 0) break;
		return 0;
	}
	Release();
	return 1;
}

DWORD CTrafficWind::UpdateScroll()
{
	WINDOW_METRICS wm;
	BOOL OnVScroll=FALSE;
	if (GetWindowMetrics(&wm) != 0)
		return 1;
	if (wm.WinRows < wm.RowCount)
		OnVScroll = TRUE;
	SetScrollRange(*this,SB_VERT,0,wm.RowCount-wm.WinRows,FALSE);
	SetScrollPos(*this,SB_VERT,wm.TopRow,TRUE);
	ShowScrollBar(*this,SB_HORZ,false);
	ShowScrollBar(*this,SB_VERT,OnVScroll);
	EnableScrollBar(*this,SB_VERT,ESB_ENABLE_BOTH);
	m_OnUpdateScrolls = FALSE;
	return 0;
}

DWORD CTrafficWind::GetWindowMetrics(WINDOW_METRICS *lpwindowmetrics)
{
	if (m_fontHeight == 0) return 1;
	RECT	rect;
	GetClientRect(*this,&rect);
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
				InvalidateRect(*this,NULL,TRUE);
			}
			break;
		}
	case SB_LINEUP:
		{
			if (wm.TopRow > 0)
			{
				m_TopRow -= 1;
				InvalidateRect(*this,NULL,TRUE);
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
			DWORD Pos=HIWORD(wParam);
			if (Pos != wm.TopRow)
			{
				m_TopRow = Pos;
				UpdateScroll();
				Invalidate();
			}
			break;
		}
	}
	::SetScrollPos(*this, SB_VERT,m_TopRow, TRUE);
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
	if (m_MemIndex >= m_Buffer.GetSize()) return 1;
	BUFF_HEADER* header;
	header = (BUFF_HEADER*)&(m_Buffer.Data()[m_MemIndex]);
	m_MemIndex+= sizeof(BUFF_HEADER);
	*lpbType = header->type;
	*lpdwSize = header->size;
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
		InvalidateRect(*this,NULL,TRUE);
	}
	return 0;
}

DWORD CTrafficWind::Create_Window(int x, int y, int nWidth, int nHeight, HWND hWndParent)
{
	DWORD result;
	result = Create("Ventana 2",WS_VSCROLL|WS_HSCROLL|WS_BORDER|WS_CHILD|WS_VISIBLE,x,y,nWidth,nHeight,hWndParent,NULL,NULL);
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
	if (Lock() != 0) 
		return 1;
	m_Buffer.SetSize(0);
	m_Rows = 0;
	m_TopRow = 0;
	m_OnUpdateScrolls = TRUE;
	UpdateScroll();
	if (UnLock() != 0)
		return 1;
	return 0;
}

/*
	Adiciona buffer de envio
*/
DWORD CTrafficWind::AddSendBuffer(BYTE *buffer, DWORD dwsize)
{
	if (dwsize == 0) return 0;
	if (Lock() != 0) 
		return 1;
	DWORD dr;
	DWORD rows;
	BUFF_HEADER header;
	header.type = SND_BUF;
	header.size = dwsize;
	for (;;)
	{
		dr = m_Buffer.AddBuffer((BYTE*)&header,sizeof(header));
		if (dr != 0) break;
		dr = m_Buffer.AddBuffer(buffer,dwsize);
		if (dr != 0) break;
		CalcRows(SND_BUF,dwsize,&rows);		// Calcular cantidad de columnas que ocupa
		m_Rows += rows;
		m_OnUpdateScrolls = TRUE;
		break;
	}
	if (UnLock() != 0)
		return 1;
	return dr;
}

/*
	Adiciona buffer de lectura
*/
DWORD CTrafficWind::AddReadBuffer(BYTE *buffer, DWORD dwsize)
{
	if (dwsize == 0) return 0;
	if (Lock() != 0) 
		return 1;
	DWORD dr = 0;
	DWORD	rows;
	BUFF_HEADER header;
	header.type = RCV_BUF;
	header.size = dwsize;
	for (;;)
	{
		if (dwsize == 0) break;
		dr = m_Buffer.AddBuffer((BYTE*)&header,sizeof(header));
		if (dr != 0) break;
		dr = m_Buffer.AddBuffer(buffer,dwsize);
		if (dr != 0) break;
		CalcRows(RCV_BUF,dwsize,&rows);		// Calcular cantidad de columnas que ocupa
		m_Rows += rows;
		m_OnUpdateScrolls = TRUE;
		break;
	}
	if (UnLock() != 0)
		return 1;
	return 0;
}

/*
	Adiciona un comentario
*/
DWORD CTrafficWind::AddComment(char *comment)
{
	if (comment[0] == 0) return 0;
	if (Lock() != 0) 
		return 1;
	DWORD dr = 0;
	DWORD	rows;
	BUFF_HEADER header;
	header.type = COM_BUF;
	header.size = strlen(comment)+1;
	for (;;)
	{
		if (header.size == 0) break;
		dr = m_Buffer.AddBuffer((BYTE*)&header,sizeof(header));
		if (dr != 0) break;
		dr = m_Buffer.AddBuffer((BYTE*)comment,header.size);
		if (dr != 0) break;
		CalcRows(COM_BUF,header.size,&rows);		// Calcular cantidad de columnas que ocupa
		m_Rows += rows;
		m_OnUpdateScrolls = TRUE;
		break;
	}
	if (UnLock() != 0)
		return 1;
	return 0;
}

DWORD CTrafficWind::Paint_Window(HDC hdc,PAINTSTRUCT Paint)
{
	RECT	rt;
	char tmpStr[10];
	DWORD i,j,size;
	BYTE  type,val;
	BYTE  rowsize;	// de acuerdo al tipo cantidad de datos para completar una columna
	BYTE  datasize; // cantidad de caracteres que ocupa un dato
	DWORD result=0;
	HGDIOBJ tmphFont;

	tmphFont = SelectObject(hdc,m_hFont);
	::GetClientRect(*this,&rt);

	if (Lock() != 0) 
		return 1;
	// Avanzar hasta la primera fila visible
	m_MemIndex = 0;
	DWORD Row=0,rows;
	BOOL  OnSRow = TRUE;	//On Start Row Indica que la ventana comienza con una columna exacta
	while (Row < m_TopRow)
	{
		result = GetBufferInfo(&type,&size);
		if (result != 0) break;
		GetBufferMetrics(type,&rowsize,&datasize);
		CalcRows(type,size,&rows);
		if (Row+rows <= m_TopRow)
		{
			Row+=rows;
			m_MemIndex += size;
			OnSRow = TRUE;
		}
		else
		{
			// Avanzar una cantidad x de filas hasta llegar al comienzo
			m_MemIndex += ((m_TopRow-Row)*rowsize);
			size -= (m_TopRow-Row)*rowsize;
			OnSRow = FALSE;
			break;
		}
	}

	if (result == 0)
	do
	{
		rt.left = 0;
		if (OnSRow)
		{
			result = GetBufferInfo(&type,&size);
			if (result != 0) break;			//Fin del buffer
			if (type == END_BUF) break;		//Buffer por definir
			switch (type)
			{
			case SND_BUF: sprintf(tmpStr,"Snd");break;
			case RCV_BUF: sprintf(tmpStr,"Rcv");break;
			case COM_BUF: sprintf(tmpStr,"Cmt");break;
			default: sprintf(tmpStr,"Error");result = -1;break;
			}
			::DrawText(hdc,tmpStr,-1,&rt,DT_LEFT);
		}
		if (result != 0) break;
		OnSRow = true;
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
			val = m_Buffer.Data()[m_MemIndex];
			m_MemIndex++;
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
	if (UnLock() != 0)
		return 1;
	SelectObject(hdc,tmphFont);
	return 0;
}

DWORD CTrafficWind::Release()
{
	::DeleteObject(m_hFont);
	m_hFont = NULL;
	CLockEvent::UnInitialize();
	return 0;
}

DWORD CTrafficWind::SaveBIN(HANDLE hFile)
{
	DWORD dr;
	DWORD byteswritten;
	DWORD size;
	BYTE  type;
	m_MemIndex = 0;
	for (;;)
	{
		dr = GetBufferInfo(&type,&size);
		if (dr != 0) break;
		if (type == RCV_BUF)
		{
			WriteFile(hFile,&m_Buffer.Data()[m_MemIndex],size,&byteswritten,NULL);				
		}
		m_MemIndex += size;
	}
	return 0;
}
