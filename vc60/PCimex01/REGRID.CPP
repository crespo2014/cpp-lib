// ReGrid.cpp : implementation file
//

#include "stdafx.h"
#include "ReGrid.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReGrid

CReGrid::CReGrid()
{
	ArrayCount=0;
	ArrayStart=0;
	ViewRowStart=0;
	ViewColumnStart=0;
	ColumnCount=0;
	Columns=NULL;
	RecordCount=0;
	Recordset=NULL;
	RowSameHeight=true;
	RowHeight=20;
	OnHeader=true;
	Drag.On=false;
	memset(&DrawInfo,0,sizeof(DrawInfo));
	DrawInfo.factor=0.3;

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
	Font.CreateFontIndirect(&FontInfo);
}

CReGrid::~CReGrid()
{
	// Borrar todos los arreglos
	SetArrayCant(0);
	SetColumnCant(0);
}


BEGIN_MESSAGE_MAP(CReGrid, CWnd)
	//{{AFX_MSG_MAP(CReGrid)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CReGrid message handlers

/*
	Reserva espacio en memoria para la cantidad
	de columnas especificadas
*/
int CReGrid::SetColumnCant(DWORD pCant)
{
	if (Columns) delete Columns;
	ColumnCount=0;
	Columns=NULL;
	if (!pCant)
		return 0;
	Columns=new S_COLUMNINFO[pCant];
	if (!Columns)
		return -1;
	ColumnCount=pCant;
	// Inicializar los datos de las columnas
	DWORD i;
	for (i=0;i<ColumnCount;i++)
	{
		Columns[i].Data=NULL;
		Columns[i].Name[0]=0;
		Columns[i].OnShow=true;
		Columns[i].FieldName[0]=0;
		Columns[i].Size=0;
		Columns[i].Width=100;
	}
	UpdateScrolls();
	return 0;
}

/*
	Reserva espacio en memoria para tener un arreglo
	de elementos con la cantidad especifica
*/
int CReGrid::SetArrayCant(DWORD pCant)
{
	if (pCant== ArrayCount)
		return 0;
	// Borrar toda la memoria reservada y reasignar memoria
	ArrayCount=pCant;
	DWORD i;
	for (i=0;i<ColumnCount;i++)
		ColumnCreateArray(i);	
	return 0;
}

int CReGrid::SetColumnField(DWORD pColumn, char *Field)
{
	if (pColumn > ColumnCount) return -1;
	lstrcpyn(Columns[pColumn].FieldName,Field,49);
	return 0;
}

int CReGrid::SetColumnName(DWORD ColumnIndex, char *Name)
{
	if (ColumnIndex > ColumnCount) return -1;
	lstrcpyn(Columns[ColumnIndex].Name,Name,49);
	return 0;
}

int CReGrid::ShowColumn(DWORD Index)
{
	if (Index > ColumnCount) return -1;
	Columns[Index].OnShow =true;
	return 0;
}

/*
	Dada la posicion de un elemento en el RecordSet
	devuelve la posicion del elemento en el array
*/
long CReGrid::RecordToArray(DWORD RecordPos)
{
	if (RecordPos < ArrayStart)
	{
 		MoveArray(ArrayStart-RecordPos,false);
		return 0;
	}
	if (RecordPos > ArrayStart+ArrayCount-1)
	{
		MoveArray(RecordPos-(ArrayStart+ArrayCount-1),true);
		return ArrayCount-1;
	}
	return RecordPos-ArrayStart;
}

/*
	Desplaza el arreglo la cantidad
	especificada si la direccion es true se desplaza hacia arriba
	es decir aumenta ArrayStart
*/
int CReGrid::MoveArray(DWORD Cant, BOOL Direction)
{
	DWORD i;
	if (ArrayCount >= RecordCount)
		return -1;
	if (Direction)
	{
		if (ArrayStart+Cant+ArrayCount > RecordCount)
			return -1;
		ArrayStart=ArrayStart+Cant;
		if (Cant > ArrayCount/2)
			return FillArray();
		// El arreglo se desplaza negativamente los elementos bajan
		for (i=0;i<ColumnCount;i++)
			memmove(Columns[i].Data,&Columns[i].Data[Columns[i].Size*Cant],Columns[i].Size*(ArrayCount-Cant));
		// Hay que llenar el final porque el principio se perdiÛ
	}
	else
	{
		if (Cant > ArrayStart)
			Cant = ArrayStart;
		ArrayStart=ArrayStart-Cant;
		if (Cant > ArrayCount/2)
			return FillArray();
		// El arreglo disminuye su posicion los elementos suben
		for (i=0;i<ColumnCount;i++)
			memmove(&Columns[i].Data[Columns[i].Size*Cant],Columns[i].Data,Columns[i].Size*(ArrayCount-Cant));
	}
	UpdateArray(Cant,!Direction);
	return 0;
}
/*
	Transfiere toda la informacion del recordset
	para los arreglos en memoria comenzando desde ArrayStart
*/
int CReGrid::FillArray()
{
	long Count;
	if (ArrayCount < RecordCount)
		Count=ArrayCount;
	else
		Count=RecordCount;
	return UpdateArray(Count,true);
}
/*
	Esta funcion es llamada despues de mover los 
	arreglos Start indica si se llenan desde el inicio
*/
int CReGrid::UpdateArray(long Cant, BOOL Start)
{
	DWORD i,j;
	COleVariant Valor;
	if (Start)
	{
		i=0;
		Recordset->SetAbsolutePosition(ArrayStart);
	}
	else
	{
		Recordset->SetAbsolutePosition(ArrayStart+ArrayCount-1);
		i=ArrayCount-1;
	}
	for(;Cant>0;Cant--,(Start)?(i++):(i--))
	{
		// Recorrer todas las columnas
		for (j=0;j<ColumnCount;j++)
			if (Columns[j].OnShow)
			{
				Recordset->GetFieldValue(Columns[j].FieldName,Valor);
				SetArrayValue(j,i,&Valor);
			}
		if (Start)
			Recordset->MoveNext();
		else
			Recordset->MovePrev();
	}
	return 0;
}


/*
	Dada la fila y la columna 
	devuelve un char* que contiene el texto de la casilla
*/

char* CReGrid::GetText(long Column, long Row)
{
	long ArrayPos=RecordToArray(Row);
	// Obtener el dato y convertirlo a cadena
	switch(Columns[Column].Type)
	{
	case VT_BSTR:
		return (char*)&Columns[Column].Data[Columns[Column].Size*ArrayPos];
	case VT_I2:
		short*	SNumber;
		SNumber=(short*)Columns[Column].Data;
		sprintf(TempString,"%d",SNumber[ArrayPos]);
		break;
	case VT_I4:
	case VT_BOOL:
		long*	LNumber;
		LNumber=(long*)Columns[Column].Data;
		sprintf(TempString,"%d",LNumber[ArrayPos]);
		break;
	case VT_R4:
		float*	FNumber;
		FNumber=(float*)Columns[Column].Data;
		sprintf(TempString,"%f",FNumber[ArrayPos]);
		break;
	case VT_R8:
		double*	DNumber;
		DNumber=(double*)Columns[Column].Data;
		sprintf(TempString,"%f",DNumber[ArrayPos]);
		break;
	case VT_DATE:
		/*
		DATE*	DTNumber;
		DTNumber=(DATE*)Columns[Column].Data;
		VarBstrFromDate(DTNumber[ArrayPos],NULL,0,
		*/
		strcpy(TempString,"Fecha");
		break;
	default:
		break;
	}
	return TempString;
}

int CReGrid::SetRecordSet(CDaoRecordset *pRecordset)
{
	Recordset= pRecordset;
	if (!Recordset) return 0;
	Recordset->MoveLast();
	RecordCount = Recordset->GetAbsolutePosition()+1;
	UpdateScrolls();
	ScrollVertical.SetScrollRange(0,RecordCount-1);
	ScrollVertical.SetScrollPos(0);
	return FillArray();
}

/*
	Actualiza una columna
*/
int CReGrid::UpdateColumn(long Column,long Cant, BOOL Start)
{
	return 0;
}
/*
	Dada la posicion en el arreglo, la columna y un valor de tipo variant
	llena dicha posicion
*/
int CReGrid::SetArrayValue(long Column,long Pos, COleVariant *Value)
{
	switch(Value->vt)
	{
	case VT_BSTR:
		char* Text;
		Text=(char*)&Columns[Column].Data[Columns[Column].Size*Pos];
		lstrcpyn(Text,(char*)Value->bstrVal,Columns[Column].Size);
		break;
	case VT_I2:
		short*	SNumber;
		SNumber=(short*)Columns[Column].Data;
		SNumber[Pos]=Value->iVal;
		break;
	case VT_I4:
	case VT_BOOL:
		long*	LNumber;
		LNumber=(long*)Columns[Column].Data;
		LNumber[Pos]=Value->lVal;
		break;
	case VT_R4:
		float*	FNumber;
		FNumber=(float*)Columns[Column].Data;
		FNumber[Pos]=Value->fltVal;
		break;
	case VT_R8:
		double*	DNumber;
		DNumber=(double*)Columns[Column].Data;
		DNumber[Pos]=Value->dblVal;
		break;
	case VT_DATE:
		DATE*	DTNumber;
		DTNumber=(DATE*)Columns[Column].Data;
		DTNumber[Pos]=Value->date;
		break;
	default:
		return -1;
		break;
	}
	return 0;
}
/*
	actualiza todos los parametros de una columna
*/
int CReGrid::SetColumnParam(long Column, short Type, long Size, long ID, char *FieldName, char *Name)
{
	if (Column > ColumnCount) return -1;
	lstrcpyn(Columns[Column].FieldName,FieldName,FIELD_MAX_TEXT);
	lstrcpyn(Columns[Column].Name,Name,NAME_MAX_TEXT);
	Columns[Column].Size=Size;
	Columns[Column].ID=ID;
	Columns[Column].Type=Type;
	UpdateScrolls();
	return 0;
}

/*
	Reserva la memoria del arreglo de dicha columna	
*/
int CReGrid::ColumnCreateArray(long Column)
{
	long DataSize=0;
	switch (Columns[Column].Type)
	{
	case VT_UI1:
		{
			DataSize=1;
			break;
		}
	case VT_I2:
	case VT_BOOL:
		{
			DataSize=2;
			break;
		}
	case VT_I4:
	case VT_R4:
		{
			DataSize=4;
			break;
		}
	case VT_R8:
	case VT_CY:
	case VT_DATE:
		{
			DataSize=8;
			break;
		}
	case VT_BSTR:
		{
			DataSize=Columns[Column].Size;
			break;
		}

	}
	delete Columns[Column].Data;
	if (DataSize*ArrayCount)
		Columns[Column].Data= new BYTE[DataSize*ArrayCount];
	else
		Columns[Column].Data=NULL;
	return 0;	
}

/*
	La vista se desplaza para abajo
*/
int CReGrid::GridMoveDown()
{
	if (ViewRowStart < RecordCount)
	{
		ViewRowStart++;
		Invalidate();
		return 0;
	}
	return -1;
}

int CReGrid::GridMoveUp()
{
	if (ViewRowStart)
	{
		ViewRowStart--;
		Invalidate();
		return 0;
	}
	return -1;
}

int CReGrid::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	CRect Rect;
	GetClientRect(&Rect);
	ScrollVertical.Create(WS_CHILD|WS_VISIBLE|SBS_VERT|SBS_RIGHTALIGN,Rect,this,1000);
	ScrollHorizontal.Create(WS_CHILD|WS_VISIBLE|SBS_HORZ|SBS_BOTTOMALIGN,Rect,this,1001);
	SCROLLINFO Info;
	Info.cbSize= sizeof(Info);
	Info.fMask = SIF_PAGE;
	Info.nPage=1;
	ScrollVertical.SetScrollInfo(&Info,false);
	ScrollHorizontal.SetScrollInfo(&Info,false);
	ScrollVertical.EnableScrollBar(ESB_ENABLE_BOTH);
	ScrollHorizontal.EnableScrollBar(ESB_ENABLE_BOTH);
	return 0;
}

LRESULT CReGrid::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	switch (message)
	{
	case WM_SIZE:
		{
			DrawInfo.CA_Height =HIWORD(lParam);
			DrawInfo.CA_Width  =LOWORD(lParam);
			UpdateScrolls();
			break;
		}
	case WM_CREATE:
		{
			CClientDC dc(this);
			MemDC.Create(&dc);
			CPen* Pen=new CPen(PS_SOLID,0,(COLORREF)0x00);
			oldp=MemDC.SelectObject(Pen);
			MemDC.SetBkMode(TRANSPARENT);
			oldf=MemDC.SelectObject(&Font);
			GridCalcHeaderHeight();
			break;
		}
	case WM_DESTROY:
		{
			delete MemDC.SelectObject(oldp);
			MemDC.SelectObject(oldf);
			break;
		}
	case WM_PAINT:
		{
			CPaintDC dc(this);
			CFont* olf=dc.SelectObject(&Font);
			GridPaint(dc);
			dc.SelectObject(olf);
			return 0;
		}
	case WM_LBUTTONDOWN:
	case WM_MOUSEMOVE:
	case WM_LBUTTONUP:
		{
			IsMouseHeader(message,LOWORD(lParam),HIWORD(lParam));
			return 0;
			break;
		}
	case WM_VSCROLL:
		{
			switch (LOWORD(wParam))
			{
			case SB_LINEDOWN:
				{
					if (GridMoveDown(1)==0)
						ScrollVertical.SetScrollPos(ViewRowStart);
					break;
				}
			case SB_LINEUP:
				{
					if (GridMoveUp(1)==0)
						ScrollVertical.SetScrollPos(ViewRowStart);
					break;
				}
			case SB_PAGEUP:
				{
					if (GridMoveUp(10)==0)
						ScrollVertical.SetScrollPos(ViewRowStart);
					break;
				}
			case SB_PAGEDOWN:
				{
					if (GridMoveDown(10)==0)
						ScrollVertical.SetScrollPos(ViewRowStart);
					break;
				}
			case SB_THUMBPOSITION:
			case SB_THUMBTRACK:
				{
					DWORD Pos=HIWORD(wParam);
					if (Pos != ViewRowStart)
					{
						ViewRowStart=Pos;
						ScrollVertical.SetScrollPos(ViewRowStart);
						HDC hdc=::GetDC(m_hWnd);
						GridPaint(hdc);
						::ReleaseDC(m_hWnd,hdc);
					}
					break;
				}

			}
			return 0;
		}
	}
	return CWnd::WindowProc(message, wParam, lParam);
}

/*
	Esta Funcion es usada para subir una pagina
*/
int CReGrid::GridMoveUp(long Cant)
{
	if (!ViewRowStart)
		return -1;
	if (ViewRowStart < Cant)
		ViewRowStart=0;
	else
		ViewRowStart-=Cant;
	Invalidate();
	return 0;
}

int CReGrid::GridMoveDown(long Cant)
{
	if (ViewRowStart == RecordCount-1)
		return -1;
	if (Cant + ViewRowStart > RecordCount-1)
		ViewRowStart = RecordCount-1;
	else 
		ViewRowStart+=Cant;
	Invalidate();
	return 0;
}

/*
	Determina que scroll debe mostrarse y cual no
	llamado cuando varia el tamano de la ventana, o de las columnas
*/
int CReGrid::UpdateScrolls()
{
	RECT	rt;
	CRect	rect;
	::GetClientRect(m_hWnd,&rt);
	LONG Width=rt.right-rt.left;
	LONG Height=rt.bottom-rt.top;
	DWORD i;
	DWORD GridWidth=0;
	DWORD GridHeight=0;
	OnVScroll=0;
	OnHScroll=0;
	DWORD ScrollHeight=GetSystemMetrics(SM_CYHSCROLL);
	DWORD ScrollWidth=GetSystemMetrics(SM_CXVSCROLL);
	for (i=0;i<ColumnCount;i++)
		GridWidth+=Columns[i].Width;
	if (GridWidth > Width)
	{
		OnHScroll=true;
		Height-=ScrollHeight;
	}
	if (RecordCount < Height)
		GridHeight = RecordCount*RowHeight;
	else
		GridHeight = RecordCount;
	if (GridHeight > Height)
	{
		OnVScroll=true;
		Width-=ScrollWidth;
		if (GridWidth > Width)
			OnHScroll=true;
	}
	if (OnVScroll)
	{
		::SetWindowPos(ScrollVertical.m_hWnd,NULL,rt.right-ScrollWidth,0,ScrollWidth,Height,SWP_NOZORDER);
	}
	if (OnHScroll)
	{
		::SetWindowPos(ScrollHorizontal.m_hWnd,NULL,rt.left,rt.bottom-ScrollHeight,Width,ScrollHeight,SWP_NOZORDER);
	}
	ScrollVertical.ShowScrollBar(OnVScroll);
	ScrollHorizontal.ShowScrollBar(OnHScroll);
	return 0;
}

/*
	Impresion del grid en la impresora o en pantalla
*/
//DEL int CReGrid::Print(CDC* dc)
//DEL {
//DEL 	CPen	Pen(PS_SOLID,0,(COLORREF)0x00);
//DEL 	CPen*	OldPen = dc->SelectObject(&Pen);
//DEL 	dc->SetBkMode(TRANSPARENT);
//DEL 	CFont* OldF=dc->SelectObject(&Font);
//DEL 	if (OnHeader)
//DEL 	{
//DEL 		// Dibujar la cabecera
//DEL 
//DEL 	}
//DEL 	CRect rect;
//DEL 
//DEL 	if (!Recordset)
//DEL 		return 0;
//DEL 	// Dibujando todas las filas del Grid
//DEL 	/*
//DEL 		Empezar por el primer elemento visible 
//DEL 		y terminar cuando se llege al ultimo
//DEL 		o se llege al final de la pantalla
//DEL 	*/
//DEL 	long ViewTop=0;		// Indica la posicion en la cual se dibujara el siguiente elemento
//DEL 	long ViewLeft=0;
//DEL 	long CurrentRow=ViewRowStart;	// Indica la fila que se dibujara
//DEL 	long CurrentColumn=ViewColumnStart; //Indica la columna que se esta dibujando
//DEL 	while ((ViewTop < WindowHeight) && (CurrentRow < RecordCount))
//DEL 	{
//DEL 		ViewLeft=0;
//DEL 		CurrentColumn=ViewColumnStart;
//DEL 		rect.top=0;
//DEL 		rect.bottom=GetRowHeight(CurrentRow,dc);
//DEL 		dc->FillSolidRect(0,0,WindowWidth,GetRowHeight(CurrentRow,dc),0xffffff);
//DEL 		while ((ViewLeft < WindowWidth) && (CurrentColumn < ColumnCount))
//DEL 		{
//DEL 			rect.left=ViewLeft;
//DEL 			rect.right=rect.left+Columns[CurrentColumn].Width;
//DEL 			dc->DrawText(GetText(CurrentColumn,CurrentRow),&rect,0);
//DEL 			CurrentColumn++;
//DEL 			ViewLeft=rect.right;
//DEL 		}
//DEL 		ViewTop+=rect.bottom;
//DEL 		CurrentRow++;
//DEL 	}
//DEL 	if (ViewTop < WindowHeight)
//DEL 	{
//DEL 		CClientDC dc(this);
//DEL 		dc.FillSolidRect(0,ViewTop,WindowWidth,WindowHeight,0xffffff);
//DEL 	}
//DEL 	dc->SelectObject(OldPen);
//DEL 	dc->SelectObject(OldF);
//DEL 	return 0;
//DEL }
/*
	Dibuja la cabecera en el dc especificado
	Devuelve la posicion a partir de la cual
	debe dibujarse lo demas
*/
int CReGrid::DrawHeader(CDC *dc)
{
	RECT	rt;
	memset(&rt,0,sizeof(rt));
	rt.left=DrawSX;
	rt.top=DrawSY;
	DrawText(*dc,"—j‹,",-1,&rt,DT_SINGLELINE|DT_CALCRECT);
	long i;
	long StartX=DrawSX;     
	for (i=0;i<ColumnCount;i++)
	{
		if (DrawDX*StartX >= DrawDX*DrawMX) break;
		rt.left=StartX;
		rt.right =StartX+(Columns[i].Width-1)*DrawDX;
		dc->DrawText(Columns[i].Name,&rt,DT_SINGLELINE|DT_END_ELLIPSIS);
		dc->MoveTo(rt.right-DrawDX,rt.top);
		dc->LineTo(rt.right-DrawDX,rt.bottom);
		StartX=StartX+(Columns[i].Width)*DrawDX;
	}
	dc->MoveTo(DrawSX,rt.bottom);
	dc->LineTo(DrawMX,rt.bottom);
	DrawSY=rt.bottom+DrawDY;
	return 0;
}

LONG CReGrid::DrawRow(UINT Row, HDC hdc)
{
	CDC	dc;
	dc.Attach(hdc);
	DWORD	i;
	RECT	rt;
	DWORD	DY=GetRowHeight(Row,hdc);
	long	SX=DrawSX;
	rt.top=DrawSY;
	rt.bottom=rt.top+DY*DrawDY;
	for (i=ViewColumnStart;i<ColumnCount;i++)
	{
		rt.left=SX;
		rt.right=rt.left+Columns[i].Width*DrawDX;
		dc.DrawText(GetText(i,Row),&rt,0);
		SX=rt.right;
	}
	DrawSY=rt.bottom;
	dc.Detach();
	return 0;
}

DWORD CReGrid::GetRowHeight(DWORD Row, HDC hdc)
{
	return 15;
}

/*
	Dibujar el grid en una o varias hojas
	los valores de Draw deben estar actualizados
*/
DWORD CReGrid::PrintToPaper(HDC hdc)
{
	DWORD	SY=DrawSY;  
	DWORD	Row=0;
	// Almacenar pto de comienzo
	CDC	dc;
	dc.Attach(hdc);
	// Crear Objeto CDC
	CFont* OldF=dc.SelectObject(&Font);
	dc.SetBkMode(TRANSPARENT);
	// Inicializar el DC
	DrawHeader(&dc);
	// Dibujar cabecera
	while ((Row < RecordCount) && ((DrawSY+GetRowHeight(Row,hdc)*DrawDY)*DrawDY< DrawMY*DrawDY))
	{
		DrawRow(Row,hdc);
		Row++;
	}
	dc.SelectObject(OldF);
	dc.Detach();
	return 0;
}

/*
	Dibuja todo el grid la ultima columna visible es dibujada
	y el espacio que sobra es rellenado
	usa DC en memoria
*/
DWORD CReGrid::GridPaint(HDC hdc)
{
	RECT rt;
	DWORD Row=ViewRowStart;
	DWORD SY=0;
	DWORD SX=0;
	DWORD RowHeight=0;
	DrawMY = DrawInfo.CA_Height*DrawInfo.factor;
	DrawMX = DrawInfo.CA_Width*DrawInfo.factor;
	CDC	dc;
	dc.Attach(hdc);
	rt.left=0;rt.right=DrawInfo.CA_Width;rt.bottom=DrawInfo.CA_Height;
	::SetBkColor(dc,0xffffff);
	::ExtTextOut(dc, 0, 0, ETO_OPAQUE, &rt, NULL, 0, NULL);
	dc.SetMapMode(MM_ANISOTROPIC);
	::SetViewportExtEx(dc,DrawInfo.CA_Width,DrawInfo.CA_Height,NULL);
	::SetWindowExtEx(dc,DrawMX,DrawMY,NULL);
	DrawSX=0;
	DrawSY=0;
	DrawDY=1;
	DrawDX=1;
	/*
	if (!::GetClientRect(m_hWnd,&rt))
		return 1;
	DrawMY=rt.bottom-rt.top;
	DrawMX=rt.right-rt.left;
	*/
	// Discriminar el area ocupada por los scrolls
	if (OnVScroll)
	{
		::GetWindowRect(ScrollVertical,&rt);
		DrawMX-=rt.right-rt.left;
	}
	if (OnHScroll)
	{
		::GetWindowRect(ScrollHorizontal,&rt);
		DrawMY-=rt.bottom-rt.top;
	}
	if ((DrawMX < 0)||(DrawMY < 0)) return 0;
	/*
	MemDC.SetSize(DrawMX,HeaderHeight);
	MemDC.Erase(0xffffff);
	DrawHeader(&MemDC);
	MemDC.Swap(SX,SY,&dc);
	*/
	DrawHeader(&dc);
	//GridPaintRows(dc);
	dc.Detach();
	return 0;
}
/*
	Devuelve el area de dibujo del grid 
	discrimina el area ocupada por los Scroll
*/
DWORD CReGrid::GetDrawRect(RECT *rt)
{
	RECT rt1;
	::GetClientRect(m_hWnd,&rt1);
	*rt=rt1;
	if (OnVScroll)
	{
		::GetWindowRect(ScrollVertical,&rt1);
		rt->right-=rt1.right-rt1.left;
	}
	if (OnHScroll)
	{
		::GetWindowRect(ScrollHorizontal,&rt1);
		rt->bottom-=rt1.bottom-rt1.top;
	}
	return true;
}

BYTE CReGrid::CanMouseDragColumn(long x, long y, DWORD *Column)
{
	long DY;
	float SX=0;
	DWORD	i;
	DY=HeaderHeight;
	if ((y >  0) && (y < DY))
	{
		// Ver si es sobre un separador
		for (i=ViewColumnStart;i<ColumnCount;i++)
		{
			SX+=Columns[i].Width;
			if (x < SX-5)
				return false;
			if (x < SX+5)
			{
				*Column=i;
				return true;
			}
		}
		
	}
	return false;
}

/*
	Chequea cualquier estado del mouse
	sobre la cabecera
*/
BYTE CReGrid::IsMouseHeader(DWORD Action, long x, long y)
{
	if (!Drag.On)
	{
		if ((y > HeaderHeight) || (y < 0))
			return false;
	}
	RECT rt;
	GetDrawRect(&rt);
	switch (Action)
	{
	case WM_LBUTTONUP:
		{
			if (Drag.On)
			{
				ReleaseCapture();
				::MoveToEx(Drag.hdc,Drag.End.x,rt.top,NULL);
				::LineTo(Drag.hdc,Drag.End.x,rt.bottom);
				::ReleaseDC(m_hWnd,Drag.hdc);
				long Dx=Drag.End.x-Drag.Start.x;
				long Size=Columns[Drag.param].Width+Dx;
				if (Size < 0) Size=0;
				Columns[Drag.param].Width=Size;
				UpdateScrolls();
				Invalidate();
				Drag.On=false;
			}
			break;
		}
	case WM_LBUTTONDOWN:
		{
			DWORD pos;
			if (CanMouseDragColumn(x,y,&pos))
			{
				Drag.On=true;
				Drag.Start.x=x;
				Drag.Start.y=y;
				Drag.hdc=::GetDC(m_hWnd);
				SetROP2(Drag.hdc,R2_NOT);
				Drag.End = Drag.Start;
				Drag.param=pos;
				MoveToEx(Drag.hdc,x,rt.top,NULL);
				LineTo(Drag.hdc,x,rt.bottom);
				SetCapture();
			}
			break;
		}
	case WM_MOUSEMOVE:
		{
			if ((y > rt.bottom)||(x > rt.right))
				return true;
			TRACE2("Mouse Move %d %d \r\n",x,y);
			if (Drag.On)
			{
				MoveToEx(Drag.hdc,Drag.End.x,rt.top,NULL);
				LineTo(Drag.hdc,Drag.End.x,rt.bottom);
				MoveToEx(Drag.hdc,x,rt.top,NULL);
				LineTo(Drag.hdc,x,rt.bottom);				
				Drag.End.x=x;
				Drag.End.y=y;
				break;
			}
			DWORD t;
			if (CanMouseDragColumn(x,y,&t))
				SetCursor(::LoadCursor(NULL,IDC_SIZEWE));
			else
				SetCursor(::LoadCursor(NULL,IDC_ARROW));
			break;
		}
	}
	return true;
}

/*
	Calcula el ancho del encabezamiento tomando
	como referecia al DC de la ventana
*/
BYTE CReGrid::GridCalcHeaderHeight()
{
	CClientDC dc(this);
	HGDIOBJ	oldf = ::SelectObject(dc,Font);
	RECT	rt;
	memset(&rt,0,sizeof(rt));
	DrawText(dc,"—j‹,",-1,&rt,DT_SINGLELINE|DT_CALCRECT);
	::SelectObject(dc,oldf);
	HeaderHeight= rt.bottom-rt.top+1;
	return 0;
}
/*
	Dibuja todas las filas del grid
*/
void CReGrid::GridPaintRows(HDC hdc)
{
	CDC	dc;
	dc.Attach(hdc);
	DWORD Row=ViewRowStart;
	DWORD SY=DrawSY;
	DWORD SX=DrawSX;
	DrawSX=0;
	while ((Row < RecordCount) && (SY < DrawMY))
	{
		RowHeight=GetRowHeight(Row,MemDC);
		// No sobrepintar el scroll horizontal
		if ((SY + RowHeight) > DrawMY)
			RowHeight=DrawMY-SY;
		MemDC.SetHeight(RowHeight);
		MemDC.Erase(0xffffff);
		DrawSY=0;
		DrawRow(Row,MemDC);
		MemDC.Swap(SX,SY,&dc);
		SY+=DrawSY;
		Row++;
	}
	if (SY < DrawMY)
	{
		dc.FillSolidRect(SX,SY,DrawMX-SX,DrawMY-SY,0xffffff);
	}
	dc.Detach();

}

BOOL CReGrid::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;
	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	return TRUE;
}

