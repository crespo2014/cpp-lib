// MenTable.h: interface for the CMemTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MENTABLE_H__4C92CA64_0F90_4E87_8574_8213E1D08368__INCLUDED_)
#define AFX_MENTABLE_H__4C92CA64_0F90_4E87_8574_8213E1D08368__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <oledb.h>
#include <oledberr.h>
#include "errorcodes.h"
#include "dbdefiniciones.h"

/*
	Mantiene una tabla en memoria
	Las columnas pueden tener datos extras, el tamaño de los datos extras se define
	mediante un procedimiento
	Hay que crear un accesor por columna
*/




#define ALING		4	// Constante de alineacion de los datos 32bits

/*
struct MEMBLOCK
{
	MEMBLOCK*	lpNextBlock;
	DWORD		BlockSize;		// Tamaño del bloque
	DWORD		DataOffset;		// Offset de comienzo de los datos
};

struct TABLEHEADER
{
	MEMBLOCK	blockHeader;
	COLUMNINFO	columnsInfo[0];

};	// Mem table header
*/
/*
struct MACOLUMNINFO
{
	DBTYPE	type;				
	DWORD	size;
	DWORD	dbIndex;
	DWORD	flags;
};
*/


class CMemTable  
{
public:
	DWORD SetColumnCount(DWORD dwColumns);
	DWORD SetData(IRowset* lpIRowset,BOOL* bOnEndRowset );
	DWORD GetColumnData(DWORD dwColumn, COLUMNDATA *lpColumData);
	DWORD GetColumnExtraData(DWORD pColumn,DWORD dwoffset,LPVOID *lplpData);
	DWORD GetDataPrtAt(DWORD dwRow, DWORD dwColumn, LPVOID *lplpData);
	DWORD AddRowExtraData(DWORD dwSize, DWORD *lpdwOffset);
	DWORD AddColumn(MACOLUMNINFO* pColumnInfo);
	DWORD AddColumnExtraData(DWORD dwSize, DWORD* lpdwOffset);
	DWORD GetRowCount();
	DWORD GetColumnCount();
	CMemTable();
	virtual ~CMemTable();
private:
	DWORD SetRowCount(DWORD dwRows);
	DWORD RequestMemory(DWORD dwSize);
	DWORD GetColumnData(DWORD dwColumn, COLUMNDATA **lpColumData);
	DWORD GetColumnOffset(DWORD dwColumn);
	DWORD GetRowSize();
	DWORD DestroyAccessors(IAccessor* lpAccessor);
	DWORD CreateAccessors(IAccessor* lpAccessor);

//	TABLEHEADER*	m_lpTable;
	DWORD	m_ColumnCount;
	DWORD	m_RowCount;
//	DWORD	m_ColumnExtraDataSize;
	DWORD	m_RowExtraDataSize;
	DWORD	m_MaxCommitMen;
	void*	m_MemArray;
	DWORD	m_LastError;
};

#endif // !defined(AFX_MENTABLE_H__4C92CA64_0F90_4E87_8574_8213E1D08368__INCLUDED_)
