#if !defined(AFX_REGRID_H__0F764D4F_A341_11D4_8633_00D0093D4380__INCLUDED_)
#define AFX_REGRID_H__0F764D4F_A341_11D4_8633_00D0093D4380__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReGrid.h : header file
//
#include "..\lfc10\lfc10c05.h"
/*
	Estructuras utilizadas por el  CRecordGrid
*/
#define FIELD_MAX_TEXT 50
#define NAME_MAX_TEXT 50

typedef struct
{
	unsigned short Type;	// Tipo de variable
	LONG	Width;			// Ancho de la columna 
	LONG	Size;			// Cantidad de bytes que ocupa el string
	BYTE*	Data;			// Puntero al arreglo de datos
	char	Name[NAME_MAX_TEXT];		// Nombre de la columna
	char	FieldName[FIELD_MAX_TEXT];	// Nombre del campo en el recordset
	LONG	ID;				// Identifica a una columna donde quiera que se encuentre
	BOOL	OnShow;
} S_COLUMNINFO;

typedef struct 
{
	BOOL  On;
	POINT Start;
	POINT End;
	DWORD param;
	HDC	  hdc;
} S_DRAGINFO;
/////////////////////////////////////////////////////////////////////////////
// CReGrid window

class CReGrid : public CWnd
{
// Construction
public:
	CReGrid();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReGrid)
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	void GridPaintRows(HDC hdc);
	BYTE GridCalcHeaderHeight();
	BYTE IsMouseHeader(DWORD Action,long x,long y);
	BYTE CanMouseDragColumn(long x, long y,DWORD* Column);
	DWORD GetDrawRect(RECT* rt);
	DWORD GridPaint(HDC hdc);
	DWORD PrintToPaper(HDC hdc);
	DWORD GetRowHeight(DWORD Row,HDC hdc);
	LONG DrawRow(UINT Row,HDC hdc);
	int DrawHeader(CDC* dc);
	int UpdateScrolls();
	int GridMoveDown(LONG Cant);
	int GridMoveUp(LONG Cant);
	int GridMoveUp();
	int GridMoveDown();
	int ColumnCreateArray(LONG Column);
	int SetColumnParam(LONG Column,short Type,LONG Size,LONG ID,char* FieldName,char* Name);
	int SetArrayValue(LONG Column,LONG Pos,COleVariant* Value);
	int UpdateColumn(LONG Column,LONG Cant, BOOL Start);
	int SetRecordSet(CDaoRecordset* pRecordset);
	char* GetText(LONG Column, LONG Row);
	int UpdateArray(LONG Cant,BOOL Start);
	int FillArray();
	int MoveArray(DWORD Cant,BOOL Direction);
	LONG RecordToArray(DWORD RecordPos);
	int ShowColumn(DWORD Index);
	int SetColumnName(DWORD ColumnIndex, char *Name);
	int SetColumnField(DWORD pColumn,char* Field);
	int SetArrayCant(DWORD pCant);
	int SetColumnCant(DWORD pCant);
	DWORD ColumnCount;			// Cantidad de columnas
	DWORD ColumnsWidth;			// Ancho que acupan todas las columnas
	DWORD ArrayStart;			// Posicion en el record del elemento 0 del arreglo
	DWORD ArrayCount;			// Cantidad de elementos del Array
	DWORD ViewRowStart;			// Primera fila visible
	DWORD ViewColumnStart;		// Primera Columna que se ve
	DWORD RecordCount;			// Cantidad de elementos del recordset
	char TempString[20];		// Usada temporalmente para almacenar el valor de la casilla
	BOOL RowSameHeight;			// Indica si todas las filas poseen el mismo alto
	UINT RowHeight;				// Este es el alto que tendrian
	S_COLUMNINFO* Columns;		// Puntero a las columnas
	CDaoRecordset* Recordset;	// Puntero al recordset 
	CScrollBar	ScrollVertical; // 
	CScrollBar	ScrollHorizontal;
	BOOL	OnHScroll,OnVScroll;
	CMemDC	MemDC;
	LONG	FontHeight;			// Alto de las letras 
	LOGFONT	FontInfo;			// estructura con los parametros del font
	CFont	Font;
	CFont*	oldf;
	CPen*	oldp;
	LONG	GridHeight,GridWidth;
	LONG	GridHeight_LU,GridWidth_LU;
	BOOL	OnHeader;			// Indica que se debe dibujar la cabecera
	// Parametros usados para dibujar 
	LONG DrawSX;	// Puntos de comienzo
	LONG DrawSY;
	signed char DrawDY;	// Direccion del eje	
	signed char DrawDX;
	LONG DrawMX;		// Dimensiones maximas
	LONG DrawMY;
	// Calculado cuando se crea la ventana o se cambia el font
	WORD HeaderHeight;
	S_DRAGINFO	Drag;
	virtual ~CReGrid();

	// Generated message map functions
protected:
	//{{AFX_MSG(CReGrid)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGRID_H__0F764D4F_A341_11D4_8633_00D0093D4380__INCLUDED_)
