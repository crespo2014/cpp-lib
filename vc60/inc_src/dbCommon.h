// dbCommon.h: interface for the CdbCommon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBCOMMON_H__6C01807A_CC03_4AAD_8ACB_AE01F621EF22__INCLUDED_)
#define AFX_DBCOMMON_H__6C01807A_CC03_4AAD_8ACB_AE01F621EF22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Oledb.h>
#include <msdadc.h>
#include "common.h"
#include "Wind.h"
#include "Unknown.h"
#include "_IUnknown.h"

extern "C" const CLSID CLSID_DataConvert;

#define DB_INV_DBINDEX	0	// Index no valido
#define DB_INV_CINDEX	0	// Index de columna no valido
#define DB_ID_CINDEX	1	// Index para los id de todas las tablas
#define DB_CAT_CINDEX	2	// Index para el elemento a mostrar en los catalogos

#define DB_INVALID_ID	0	// ID invalido

#define MAKEDBINDEX(t,c) MAKELONG(c,t)
/*
	Notas : dbIndex :	0 Index invalido
					:	1 ID de la tabla en cuestion
*/

/*
	Si el campo es string
	  si DB_F_STANDARD entonces no hay que pedir el string pero es posible que si el formato
*/

#define DB_F_STRING			0x1		// El elemento es un string
#define DB_F_SINGLELINE		0x2		// El string es de una sola linea
#define DB_F_EXTID			0x4		// Es un ID de otra tabla, catálogo
#define DB_F_INVISIBLE		0x8		// Campo no visible
#define DB_F_OWNERDRAW		0x10	// Se dibuja solo
#define DB_F_NODBDATA		0x20	// El campo no existe en la base de datos
#define DB_F_STANDARD		0x40	// Es un elemento comun y corriente, cumple el formato standard de datos a string
#define DB_F_FIXEDHEIGHT	0x80	// El alto del elemento es fijo
#define DB_F_FIXEDWIDTH		0x100	// El ancho del elemento es fijo

/*
	Controles en una interfaz gráfica
*/
#define CTRL_EDIT		1	// Edit
#define CTRL_LABEL		2	// Label
#define CTRL_STATIC		2	
#define CTRL_COMBOBOX	3	// Combobox
#define CTRL_CCOMBOBOX	4	// Custom Combobox catalogo
#define CTRL_DATE		5	// Date time control
#define CTRL_CHEKBOX	6	// Check box
#define CTRL_CUSTOM		7	// Custom control
#define CTRL_BUTTON		8	// Button
#define CTRL_LINE		9	// Linea horizontal o vertical

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
#define akLeft		1
#define akRight		2
#define akTop		4
#define akBottom	8 

struct DBGUI_CTRL
{
	int		x;
	int		y;
	int		width;
	int		height;
	//BYTE	anchors;
	DWORD	dbIndex;	// Si es -1	el control es un boton u otra cosa
	DWORD	style;
	DWORD	exstyle;
	DWORD	type;		// Tipo de control
	HWND	hwnd;		// Handle del control
	char	caption[255];
	DWORD	id;			// Identificador del control
	DWORD	parentid;	// Si es un control hijo de otro, si 0 no es hijo
	void*	lpvoid;
	
	/*
		El taborder lo define la posicion dentro del arreglo
		el id tambien lo define la posicion en el arreglo
	*/
};

struct DBGUI
{
	WORD		ctrlCount;
	LOGFONT		font;
	HFONT		hfont;
	DBGUI_CTRL* ctrls;
};

struct DBDATAINFO
{
	DWORD	dbIndex;		// Index en la base de datos (Tabla,columna) 0- invalido
	char	name[20];		// Nombre de la columna
	DBTYPE	type;			// Tipo de elemento				
	DWORD	size;			// Tamaño del tipo
	DWORD	tableIndex;		// Si es un ID, tabla a la que pertenece
	char	caption[20];	// Nombre a mostrar 
	DWORD	flags;
	BYTE	bPrecision;
	BYTE	bScale;
};

struct DBTABLEINFO
{
	WORD	index;
	WORD	dataCount;	// Cantidad de datos
	char	name[20];	// Nombre de la tabla
	DBDATAINFO* lpDataInfo;
};

struct ITEM_DATA
{
	char*	pzsText;
	UINT	uFormat;
	HFONT	hFont;
	BOOL	bEnable;	// Habilitado o desabilitado
	BOOL	bFocused;	// Tiene el focus pero puede que no este seleccionado
	BOOL	bSelected;	// Esta seleccionado
	WORD	wColumnIndex;
	DWORD	dwRowIndex;
	DWORD	dwdbIndex;
	RECT	rect;
	COLORREF	backColor;
	COLORREF	textColor;
};

// prototipo para funcion de comparacion
typedef DWORD (*LPCOMPFUNC)(_VARIANT*,_VARIANT*);

class IDBArray;

class IdbView : public CWind  
{
public:
	virtual DWORD _stdcall GetPos(DWORD* pdwPos)=0;
	virtual DWORD _stdcall OnInitView()=0;
	virtual DWORD _stdcall OnCreateCtrl(DWORD dwCtrlIndex)=0;
	virtual DWORD _stdcall GetGui(DBGUI** dbgui)=0;
	virtual DWORD _stdcall OnChildViewClose()=0;
	virtual DWORD _stdcall PreTranslateMessage(MSG *pMsg)=0;
};

class CdbView : public IdbView
				//, public CWind 			
{
public:
	virtual DWORD _stdcall GetPos(DWORD* pdwPos){return CWind::GetPos(pdwPos);};
	virtual DWORD _stdcall SetPos(DWORD dwPos){return CWind::SetPos(dwPos);};
	virtual DWORD _stdcall DecPos(DWORD dwMinPos){return CWind::GetPos(&dwMinPos);};
	virtual DWORD _stdcall OnInitView(){return 0;};
	virtual DWORD _stdcall OnCreateCtrl(DWORD dwCtrlIndex){return 0;};
	virtual DWORD _stdcall GetGui(DBGUI** dbgui){return 0;};
	virtual DWORD _stdcall OnChildViewClose(){return 0;};
	virtual DWORD _stdcall PreTranslateMessage(MSG *pMsg){return IsDialogMessage(*this,pMsg);};
private:
	DWORD	m_Pos;
};

class IdbDatabase
{
public:
	virtual ICommand* _stdcall _ICommand()=0;
};

#define IDBCLASS_NAME  "IdbClass"

class IDBClass : public _IUnknown 
{
public:
	virtual DWORD _stdcall GetdbTableInfo(DBTABLEINFO** lpdbTableInfo)=0;
	virtual DWORD _stdcall GetItemSize(HDC hdc, ITEM_DATA *lpItemData)=0;
	virtual DWORD _stdcall GetItemText(ITEM_DATA *lpItemData)=0;
	virtual DWORD _stdcall GetSize(HDC hdc,void* lpvoid,WORD wdbIndex,DWORD dwRowIndex,WORD wColumnIndex,RECT* lprect)=0;
	virtual DWORD _stdcall Draw(HDC hdc,void* lpvoid,WORD wdbIndex,DWORD dwRowIndex,WORD wColumnIndex,RECT* lprect)=0;
	virtual DWORD _stdcall SetValue(WORD wdbIndex,_VARIANT* lpVariant)=0;
	virtual DWORD _stdcall GetValue(WORD wdbIndex,_VARIANT* lpVariant)=0;
	virtual DWORD _stdcall SetValue(WORD wdbIndex,HWND hControl)=0;
	virtual DWORD _stdcall GetValue(WORD wdbIndex, HWND hControl)=0;
	virtual DWORD _stdcall Clear()=0;
	virtual DWORD _stdcall GetIndexVisibility(DWORD dwdbIndex,BOOL* bShow)=0;
	virtual DWORD _stdcall GetRowVisibility(IDBArray* pIdbArray,DWORD dwRowIndex,BOOL* bShow)=0;
};

#define IDBARRAY_NAME  "IdbArray"

class CdbRefArray;

class IDBArray : public CUnknown
{
public:
	virtual DWORD _stdcall AddRow()=0;
	virtual DWORD _stdcall GetData(DWORD dwRowIndex)=0;
	virtual DWORD _stdcall SetData(DWORD dwRowIndex)=0;
	virtual DWORD _stdcall ResetContent()=0;
	virtual DWORD _stdcall SetIdbClass(IDBClass *pIdbClass)=0;
	virtual DWORD _stdcall AddColumn(DBDATAINFO* lpdbDataInfo,void* lpvoid)=0;
	virtual DWORD _stdcall SetRowCount(DWORD dwRowCount)=0;
	virtual DWORD _stdcall GetChangeNo()=0;
	virtual DWORD _stdcall GetAllEqual(DWORD dwdbIndex, _VARIANT *pVariant,CdbRefArray* pdbRefArray,LPCOMPFUNC pCompFunc = NULL)=0;
	virtual DWORD _stdcall Find(DWORD dwStartRow,DWORD dwdbIndex, _VARIANT *pVariant,DWORD *lpdwRowIndex,LPCOMPFUNC pCompFunc = NULL)=0;
	virtual DWORD _stdcall AddRowExtraData(WORD dwSize, WORD *lpdwOffset)=0;
	virtual DWORD _stdcall AddColumnExtraData(WORD dwSize, WORD *lpdwOffset)=0;
	virtual DWORD _stdcall GetSize(HDC hdc,DWORD dwRowIndex, WORD wColumnIndex,RECT* lprect)=0;
	virtual DWORD _stdcall GetDataPrtAt(DWORD RowIndex, WORD ColumnIndex,void** lplpData)=0;
	virtual DWORD _stdcall GetRowCount()=0;
	virtual DWORD _stdcall GetRowExtraDataPtr(DWORD RowIndex, DWORD Offset, LPVOID *lplpData)=0;
	virtual DWORD _stdcall GetColumn(DWORD dbIndex,WORD* lpdwColumnIndex)=0;
	virtual DWORD _stdcall GetColumnCount()=0;
	virtual DWORD _stdcall GetColumnExtraDataPtr(WORD ColumnIndex, DWORD Offset, LPVOID *lplpData)=0;
	virtual DWORD _stdcall GetColumnInfo(WORD dwColumnIndex,DWORD* lpdwdbIndex,char** lplpszcaption, DWORD* lpdwFlags)=0;
	virtual DWORD _stdcall DrawItem(HDC hdc,ITEM_DATA* lpItemData) = 0;
	virtual DWORD _stdcall GetItemSize(HDC hdc,ITEM_DATA* lpItemData) = 0;
	virtual DWORD _stdcall GetItemText(ITEM_DATA* lpItemData) = 0;
	virtual DWORD _stdcall GetExtraDataOffset(BYTE bType,WORD* lpwOffset)=0;
	virtual DWORD _stdcall SetMaxParams(WORD wmaxColumns, DWORD dwmaxRows, WORD wmaxRowSize)=0;
};

DWORD _stdcall db_WCharToChar(LPWSTR lpWideCharStr);
DWORD _stdcall db_CharToWChar(LPSTR lpCharStr);
DWORD _stdcall db_GetdbDataInfo(DWORD dwdbIndex,IDBClass* lpIdbClass,DBDATAINFO** lpdbDataInfo);
DWORD _stdcall db_GetdbDataInfo(char* lpDataName,IDBClass* lpIdbClass,DBDATAINFO** lpdbDataInfo);
DWORD _stdcall db_GetGuiFromResource(char* lpzsRecourceName,DBGUI* lpdbGui);
DWORD _stdcall db_GetdbTableInfoFromResource(char* lpzsRecourceName,DBTABLEINFO* lpdbTableInfo);
DWORD _stdcall db_GetCtrlIndexFromID(DWORD dwId,DBGUI* lpdbGui,WORD* wIndex);

// Clases virtuales implementadas

class CdbClass : public IDBClass,
				 public CUnknown
{
	virtual DWORD _stdcall QueryInterface(char* lpName,void** lpInterfaz)	{return CUnknown::QueryInterface(lpName,lpInterfaz);}
	virtual DWORD _stdcall AddRef()											{return CUnknown::AddRef();}
	virtual DWORD _stdcall Release()										{return CUnknown::Release();}
	virtual DWORD _stdcall Initialize()										{return CUnknown::Initialize();}
	virtual DWORD _stdcall GetInterfaz(char* lpName,void** lpInterfaz)		{return CUnknown::GetInterfaz(lpName,lpInterfaz);}
	virtual DWORD _stdcall DeleteObject()									{return CUnknown::DeleteObject();}
	virtual DWORD _stdcall UnInitialize()									{return CUnknown::UnInitialize();}
public:
	virtual DWORD _stdcall GetItemSize(HDC hdc, ITEM_DATA *lpItemData);
	virtual DWORD _stdcall GetItemText(ITEM_DATA *lpItemData);
	virtual DWORD _stdcall GetSize(HDC hdc,void* lpvoid,WORD wdbIndex,DWORD dwRowIndex,WORD wColumnIndex,RECT* lprect);
	virtual DWORD _stdcall Draw(HDC hdc,void* lpvoid,WORD wdbIndex,DWORD dwRowIndex,WORD wColumnIndex,RECT* lprect);
	virtual DWORD _stdcall SetValue(WORD wdbIndex,_VARIANT* lpVariant);
	virtual DWORD _stdcall GetValue(WORD wdbIndex,_VARIANT* lpVariant);
	virtual DWORD _stdcall SetValue(WORD wdbIndex,HWND hControl);
	virtual DWORD _stdcall GetValue(WORD wdbIndex, HWND hControl);
	virtual DWORD _stdcall Clear();
	virtual DWORD _stdcall GetIndexVisibility(DWORD dwdbIndex,BOOL* bShow);
	virtual DWORD _stdcall GetRowVisibility(IDBArray* pIdbArray,DWORD dwRowIndex,BOOL* bShow);
	virtual DWORD _stdcall SetDatabase(IdbDatabase *lpIdbDatabase);
	virtual DWORD _stdcall SetTableInfo(DBTABLEINFO *lpTableInfo);
protected:
	DWORD			m_ID;
	IdbDatabase*	m_pIdbDatabase;
	DBTABLEINFO*	m_pdbTableInfo;
public:
	CdbClass();
	virtual ~CdbClass();

};

#endif // !defined(AFX_DBCOMMON_H__6C01807A_CC03_4AAD_8ACB_AE01F621EF22__INCLUDED_)
