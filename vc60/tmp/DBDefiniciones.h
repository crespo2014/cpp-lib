// DBDefiniciones.h: interface for the CDBDefiniciones class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBDEFINICIONES_H__8555F325_7B21_4CE5_996C_E5085AA383DE__INCLUDED_)
#define AFX_DBDEFINICIONES_H__8555F325_7B21_4CE5_996C_E5085AA383DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define F_ONMULTILINE	1	// Campo texto multilinea
#define F_ONINVISIBLE	2	// El campo no es visible
#define F_ONEXTID		4	// Es un ID de otra tabla, catálogo
#define F_OWNERDRAW		16	// El elemento es un dibujo o algo que se muestra el mismo, getsize
#define F_DRAWFIXED		8	// El height es fijo y se dibuja solo

#define EDT_EDIT		1	// Edit de windows
#define EDT_COMBOBOX	2	// Windows Combobox
#define	EDT_CUST_CMB	3	// Custom Combobox catalogo
#define	EDT_CUST_CTRL	4	// Custom control ligado con F_OWNERSHOW
#define EDT_DATE		5	// Control de tipo fecha
#define EDT_CHKBOX		6	// Control CheckBox

/*
	Controles en una interfaz gráfica
*/

#define CTRL_EDIT		1	// Edit
#define CTRL_LABEL		2	// Label
#define CTRL_COMBOBOX	3	// Combobox
#define CTRL_CCOMBOBOX	4	// Custom Combobox catalogo
#define CTRL_DATE		5	// Date time control
#define CTRL_CHEKBOX	6	// Check box
#define CTRL_CUSTOM		7	// Custom control

#define UM_SETCONTENT	WM_USER+1
#define UM_DELCONTENT	WM_USER+2

extern char SqlStr[];
extern DWORD CharToWChar();
extern DWORD WCharToChar();

struct EDITINFO
{
	HWND	hWnd;
	RECT	rect;
	DWORD	dbIndex;
};

/*
	Notas:
		Si el control es un checkBox entonces no hay label y toma el caption
*/
struct DBGUI_CTRL
{
	int		x;
	int		y;
	int		width;
	int		height;
	DWORD	index;		// Indice del control
	DWORD	dbIndex;	// Si es -1	el control es un boton u otra cosa
	DWORD	style;
	DWORD	exstyle;
	DWORD	type;		// Tipo de control
	HWND	hwnd;		// Handle del control
	char	caption[30];
	DWORD	id;
	/*
		El taborder lo define la posicion dentro del arreglo
		el id tambien lo define la posicion en el arreglo
	*/
};

struct DBGUI
{
	DBGUI_CTRL* ctrls;
	WORD		ctrlCount;
	LOGFONT		font;
	HFONT		hfont;
};

typedef struct 
{
	DWORD	dbIndex;	// Index en la base de datos (Tabla,columna) 0- invalido
	char*	name;		// Nombre de la columna
	DBTYPE	type;		// Tipo de elemento				
	DWORD	size;		// Tamaño del tipo
	DWORD	tableID;	// Si es un ID, tabla a la que pertenece
	char*	caption;	// Nombre a mostrar 
	DWORD	flags;
	WORD	width;
	// Interfaz gráfica
	WORD	edittype;	// Tipo de control usado para la edicion del elemento
	WORD	editpos;	// Usada para ordenar los elementos en el edit 1-
	WORD	gridpos;	// Orden de los elementos en el grid
	//WORD	gridwidth;	// Ancho de las columnas en el grid
	union
	{
		void*	itemdata;	// De proposito general
		WORD	height;		// usda por el edit list
	};
} DBDATAINFO;

class IdbView  
{
public:
	virtual DWORD _stdcall OnCreateCtrl(WORD ctrlIndex)=0;
	virtual DWORD _stdcall GetGui(DBGUI** dbgui)=0;
	virtual LRESULT _stdcall OnWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)=0;
};

class IDBClass  
{
public:
	virtual DWORD _stdcall GetDBDataCount()=0;
	virtual DWORD _stdcall GetDBDataStrPtr(DWORD dbIndex,char** lplpchar)=0;
	virtual DWORD _stdcall GetDBDataInfo(WORD dbIndex,DBDATAINFO** lpdbDataInfo)=0;
	virtual DWORD _stdcall OnEndEdit(HWND hWnd,WORD dbIndex,BOOL OnUpdate)=0;
	virtual DWORD _stdcall OnStartEdit(EDITINFO* lpEditInfo)=0;
	virtual DWORD _stdcall GetStr(void* lpvoid,DWORD dbIndex,DWORD RowIndex,char** lplpchar) = 0;
	virtual DWORD _stdcall GetGui(DBGUI** dbgui)=0;
	virtual DWORD _stdcall SetParentWindow(HWND hwnd)=0;
	virtual DWORD _stdcall OnCreateCtrl(WORD ctrlIndex)=0;
	virtual DWORD _stdcall GetSize(void* lpvoid,DWORD dbIndex,DWORD dwRowIndex,WORD wColumnIndex) = 0;
	virtual LRESULT _stdcall OnWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)=0;
};


class IDBArray
{
public:
	virtual DWORD _stdcall AddRowExtraData(DWORD dwSize, DWORD *lpdwOffset)=0;
	virtual DWORD _stdcall AddColumnExtraData(DWORD dwSize, DWORD *lpdwOffset)=0;
	virtual DWORD _stdcall GetStrPtrAt(DWORD RowIndex,DWORD ColumnIndex,char** lplpchar)=0;
	virtual DWORD _stdcall GetDataPrtAt(DWORD RowIndex, DWORD ColumnIndex, LPVOID *lplpData)=0;
	virtual DWORD _stdcall GetRowCount()=0;
	virtual DWORD _stdcall GetColumnCount()=0;
	virtual DWORD _stdcall GetRowExtraDataPtr(DWORD RowIndex, DWORD Offset, LPVOID *lplpData)=0;
	virtual DWORD _stdcall GetColumnExtraDataPtr(DWORD ColumnIndex, DWORD Offset, LPVOID *lplpData)=0;
	virtual DWORD _stdcall GetColumnDBDataInfo(DWORD ColumnIndex,DBDATAINFO** lpdbDataInfo)=0;
	virtual DWORD _stdcall GetSize(DWORD dwRowIndex, WORD wColumnIndex,RECT* lprect)=0;
};


#endif // !defined(AFX_DBDEFINICIONES_H__8555F325_7B21_4CE5_996C_E5085AA383DE__INCLUDED_)
