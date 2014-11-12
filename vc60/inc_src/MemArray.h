// MemArray.h: interface for the CMemArray class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMARRAY_H__FAF0A8C6_8A9A_4D01_93BB_4D56E7EED8A6__INCLUDED_)
#define AFX_MEMARRAY_H__FAF0A8C6_8A9A_4D01_93BB_4D56E7EED8A6__INCLUDED_

#include "DBCommon.h"
#include "VirtualMem.h"
#include "common.h"
#include "dbRefArray.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Soporte para el grid
#define MA_GRID_ROW_DATA		2 // memarray grid row extra data 
#define MA_GRID_COLUMN_DATA		3 // memarray grid column extra data

// SetData
#define MA_F_RESET_COLUMNS	1	// borrar las columnas actuales del recordset
#define MA_F_NO_READ_DBINFO	4	// No leer dbDataInfo de IdbClass leer del recordset

// 
struct MACOLUMNINFO
{
	DWORD	memSize;		// Tamaño que ocupa en memoria
	DWORD	dbSize;		
	DWORD	dbIndex;	// Origen del dato
	DWORD	dbflags;
	DBTYPE  dbtype;		// Usada cuando no hay IdbClass
	BYTE	bPrecision;
	BYTE	bScale;
	char*	caption;	// Usada cuando no hay IdbClass
	DWORD	memOffset;	// Offset en el paquete de datos
	void*	lpvoid;		// dato extra
	union
	{
		DWORD		iOrdinal;
	};
	BYTE	extraData[0];
};


class CMemArray : public IDBArray,
				  public CVirtualMem 
{
	DWORD AddColumn(MACOLUMNINFO* lpColumnInfo);
	DWORD CreateAccessor(IAccessor* lpAccessor,HACCESSOR* hAccessor);
	DWORD GetCmpFunc(WORD wColumnIndex,LPCOMPFUNC* ppCmpFunc);
	DWORD FillColumnInfo(MACOLUMNINFO* pcinfo, DBDATAINFO *pdbDataInfo);
	
	static DWORD CmpUnsignedLong(_VARIANT *pVariant1, _VARIANT *pVariant2);
	static DWORD CmpUnsignedChar(_VARIANT *pVariant1, _VARIANT *pVariant2);
	static DWORD CmpUnsignedShort(_VARIANT *pVariant1, _VARIANT *pVariant2);
	static DWORD CmpChar(_VARIANT *pVariant1, _VARIANT *pVariant2);
	static DWORD CmpDouble(_VARIANT *pVariant1, _VARIANT *pVariant2);
	static DWORD CmpFloat(_VARIANT *pVariant1, _VARIANT *pVariant2);
	static DWORD CmpLong(_VARIANT *pVariant1, _VARIANT *pVariant2);
	static DWORD CmpShort(_VARIANT *pVariant1, _VARIANT *pVariant2);
	static DWORD CmpStr(_VARIANT *pVariant1, _VARIANT *pVariant2);
	
	WORD	m_gridRowDataOffset;
	WORD	m_gridColumnDataOffset;
	DWORD	m_hResult;		// Error de la api
	DWORD	m_RowSize;		// Se puede calcular pero se necesita velocidad
	DWORD	m_ColumnExtraDataSize;
	DWORD	m_RowExtraDataSize;
	DWORD	m_ColumnCount;
	DWORD	m_RowCount;
	DWORD	m_ChangeNo;
	IDBClass*		m_IDBClass;
	DBCOLUMNINFO*	m_prgInfo;
	IDataConvert*	m_pIDataConvert;

public:
	DWORD _stdcall GetAllEqual(DWORD dwdbIndex, _VARIANT *pVariant,CdbRefArray* pdbRefArray,LPCOMPFUNC pCompFunc = NULL);
	DWORD _stdcall Find(DWORD dwStartRow,DWORD dwdbIndex, _VARIANT *pVariant,DWORD *lpdwRowIndex,LPCOMPFUNC pCompFunc);
	DWORD _stdcall AddRow();
	DWORD _stdcall SetData(DWORD dwRowIndex);
	DWORD _stdcall GetItemSize(HDC hdc,ITEM_DATA* lpItemData);
	DWORD _stdcall GetItemText(ITEM_DATA* lpItemData);
	DWORD _stdcall DrawItem(HDC hdc,ITEM_DATA* lpItemData);
	DWORD _stdcall SetMaxParams(WORD wmaxColumns,DWORD dwmaxRows,WORD wmaxRowSize);
	DWORD _stdcall SetRowCount(DWORD dwRowCount);
	DWORD _stdcall Release();
	DWORD _stdcall SetExtraDataSize(BYTE bType,WORD wSize);
	DWORD _stdcall GetData(DWORD dwRowIndex);
	DWORD _stdcall SetDBInterfaz(IDBClass *lpIDBClass);
	DWORD _stdcall SetData(IRowset* lpIRowset,DWORD dwReadFlags = 0);

	// IDBArray interfaz
	virtual DWORD _stdcall GetExtraDataOffset(BYTE bType,WORD* lpwOffset);
	virtual DWORD _stdcall ResetContent();
	virtual DWORD _stdcall SetIdbClass(IDBClass *pIdbClass);
	virtual DWORD _stdcall AddColumn(DBDATAINFO* lpdbDataInfo,void* lpvoid);
	virtual DWORD _stdcall Look(WORD dwColumnIndex, _VARIANT *pVariant,DWORD *lpdwRowIndex,LPCOMPFUNC pCompFunc);
	virtual DWORD _stdcall GetChangeNo();
	virtual DWORD _stdcall GetColumn(DWORD dbIndex,WORD* lpdwColumnIndex);
	virtual DWORD _stdcall GetDataPrtAt(DWORD RowIndex, WORD ColumnIndex, LPVOID *lplpData);
	virtual DWORD _stdcall GetRowExtraDataPtr(DWORD RowIndex, DWORD Offset, LPVOID *lplpData);
	virtual DWORD _stdcall GetColumnExtraDataPtr(WORD ColumnIndex, DWORD Offset, LPVOID *lplpData);
	virtual DWORD _stdcall GetRowCount();
	virtual DWORD _stdcall GetColumnCount();
	virtual DWORD _stdcall AddRowExtraData(WORD dwSize, WORD *lpdwOffset);
	virtual DWORD _stdcall AddColumnExtraData(WORD dwSize, WORD* lpdwOffset);
	virtual DWORD _stdcall GetSize(HDC hdc,DWORD dwRowIndex, WORD wColumnIndex,RECT* lprect);
	virtual DWORD _stdcall GetColumnInfo(WORD dwColumnIndex,DWORD* lpdwdbIndex,char** lplpszcaption, DWORD* lpdwFlags);

	// IUnknown
	virtual DWORD _stdcall GetInterfaz(char* pzsName,void** ppInterfaz);

	CMemArray();
	virtual ~CMemArray();
private:
	
	
};

#endif // !defined(AFX_MEMARRAY_H__FAF0A8C6_8A9A_4D01_93BB_4D56E7EED8A6__INCLUDED_)
