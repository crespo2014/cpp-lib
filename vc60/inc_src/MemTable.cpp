// MenTable.cpp: implementation of the CMemTable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MemTable.h"
#include "errorcodes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define DATACOLUMNOFFSET	ColumnIndex*(sizeof(COLUMNDATA)+m_ColumnExtraDataSize)
#define DATACOLUMN			(COLUMNDATA*)&m_MemArray->Mem[DATACOLUMNOFFSET]
#define COLUMNEXTRADATA		&m_MemArray->Mem[DATACOLUMNOFFSET+sizeof(COLUMNDATA)+dwOffset]

/*
struct MACOLUMNINFO
{
	DBTYPE	type;				
	DWORD	size;
	DWORD	dbIndex;
	DWORD	flags;
	DWORD	offset;					// Offset de la columna en el arreglo
	union
	{
		HACCESSOR	iAccessor;		// Inicialmente es el accesor y despues de ordenarse es ..
		DWORD		ColumnIndex;	// Columna en el paquete de datos
	};
};
*/
struct MAHEADER
{
	DWORD	ReservedMen;
	DWORD	CommitMen;
	BYTE	Mem[0];
};

CMemTable::CMemTable()
{
	m_ColumnCount = 0;
	m_ColumnExtraDataSize = 0;
	m_LastError = 0;
	m_MaxCommitMen = 5*1024*1024;	// 5 MB
	m_MemArray = NULL;
	m_RowCount = 0;
	m_RowExtraDataSize = 0;
}

CMemTable::~CMemTable()
{

}

//DEL DWORD CMemTable::AddColumn(char *name, WORD type, WORD len)
//DEL {
//DEL 	DWORD r;
//DEL 	if (m_lpTable == NULL)
//DEL 	{
//DEL 		r = CreateColumnsBlock();
//DEL 		if (r != 0) return r;
//DEL 	}
//DEL 	WORD tmp1;
//DEL 	tmp1 = len % ALING;
//DEL 	if (tmp1 !=0) len += (ALING-tmp1);
//DEL 	m_lpTable->columnsInfo[m_ColumnCount].size = len;
//DEL 	m_lpTable->columnsInfo[m_ColumnCount].type = type;
//DEL 	lstrcpyn(m_lpTable->columnsInfo[m_ColumnCount].name,name,NAMEMAXLEN);
//DEL 	m_lpTable->blockHeader.DataOffset += sizeof(COLUMNINFO);
//DEL 	m_ColumnCount++;
//DEL 	return 0;
//DEL 
//DEL }

//DEL DWORD CMemTable::CreateColumnsBlock()
//DEL {
//DEL 	if (m_lpTable != NULL) return 0;
//DEL 	m_lpTable = (TABLEHEADER*)VirtualAlloc(NULL,1,MEM_COMMIT,PAGE_READWRITE);
//DEL 	if (m_lpTable == NULL) return ERR_NOMEMORY;
//DEL 	MEMORY_BASIC_INFORMATION	mbi;
//DEL 	::VirtualQuery(m_lpTable,&mbi,sizeof(mbi));
//DEL 	m_lpTable->blockHeader.BlockSize = mbi.RegionSize;
//DEL 	m_lpTable->blockHeader.DataOffset = sizeof(TABLEHEADER);
//DEL 
//DEL 	return 0;
//DEL 	
//DEL }

//DEL DWORD CMemTable::GetDataPrtAt(DWORD pRow, DWORD pColumn, LPVOID *lplpData)
//DEL {
//DEL 	if ((pRow >= m_RowCount) || (pColumn >= m_ColumnCount))
//DEL 		return ERR_OUT_RANGE;
//DEL 	// Tamaño de una fila
//DEL 
//DEL 	MEMBLOCK* lpblock;
//DEL 	DWORD		pos;
//DEL 	DWORD		r;
//DEL 	*lplpData = NULL;
//DEL 	r = GetBlock(&lpblock,&pos,pColumn,pRow);
//DEL 	if (r != 0) return r;
//DEL 	*lplpData = &((BYTE*)lpblock)[pos];
//DEL 	return 0;
//DEL 	
//DEL }

//DEL DWORD CMemTable::AddRow()
//DEL {
//DEL 	MEMBLOCK*	lpblock;
//DEL 	DWORD		pos;
//DEL 	DWORD		r;
//DEL 	r = GetBlock(&lpblock,&pos,0,m_RowCount);
//DEL 	if (r != 0) return r;
//DEL 	return 0;	
//DEL }

//DEL DWORD CMemTable::GetBlock(MEMBLOCK **lplpBlock, DWORD *lpdwPos,DWORD pColumn,DWORD pRow)
//DEL {
//DEL 	// Determinar el espacio ocupado por una fila 
//DEL 	DWORD rowsize = 0;
//DEL 	DWORD row = 0;
//DEL 	DWORD column = 0;
//DEL 	*lplpBlock = (MEMBLOCK*)m_lpTable;
//DEL 	*lpdwPos = (*lplpBlock)->DataOffset;
//DEL 	DWORD i;
//DEL 	for (i=0;i<m_ColumnCount;i++)
//DEL 	{
//DEL 		rowsize += m_lpTable->columnsInfo[i].size; 
//DEL 	//	if (i<pColumn) offset = rowsize;
//DEL 	}
//DEL 	// Comenzar el recorrido
//DEL 	while (true)
//DEL 	{
//DEL 		// Saltar la cantidad de filas que se pueda
//DEL 		DWORD rowstopass = ((*lplpBlock)->BlockSize-(*lpdwPos))/rowsize;
//DEL 		rowstopass = min(rowstopass,pRow-row);
//DEL 		(*lpdwPos) += rowstopass*rowsize;
//DEL 		row += rowstopass;
//DEL 		// Ver si estoy en la fila seleccionada
//DEL 		if (row == pRow)
//DEL 		{
//DEL 			// ver si estoy pasado
//DEL 			while (column > pColumn)
//DEL 			{
//DEL 				(*lpdwPos) -= m_lpTable->columnsInfo[column-1].size;
//DEL 				column--;
//DEL 				if (column == pColumn) return ERR_NONE;
//DEL 			}
//DEL 		}
//DEL 		// Mientras la columna quepa ver si es ella, si no lo es ir a la proxima
//DEL 		while (m_lpTable->columnsInfo[column].size < (*lplpBlock)->BlockSize-(*lpdwPos))
//DEL 		{
//DEL 			if ((column == pColumn) && (row == pRow)) return ERR_NONE;
//DEL 			(*lpdwPos) += m_lpTable->columnsInfo[column].size;
//DEL 			column++;
//DEL 			if (column == m_ColumnCount)
//DEL 			{
//DEL 				column = 0;
//DEL 				row++;
//DEL 			}
//DEL 		}
//DEL 		// pasar al proximo bloque
//DEL 		(*lplpBlock) = (MEMBLOCK*)(*lplpBlock)->lpNextBlock;
//DEL 		(*lpdwPos) = (*lplpBlock)->DataOffset;
//DEL 	}
//DEL }

//DEL DWORD CMemTable::AddBlock(MEMBLOCK* lpBlock)
//DEL {
//DEL 	lpBlock->lpNextBlock = (MEMBLOCK*)VirtualAlloc(NULL,1,MEM_COMMIT,PAGE_READWRITE);
//DEL 	if (lpBlock->lpNextBlock == NULL) return ERR_NOMEMORY;
//DEL 	MEMORY_BASIC_INFORMATION	mbi;
//DEL 	::VirtualQuery(lpBlock->lpNextBlock,&mbi,sizeof(mbi));
//DEL 	lpBlock->lpNextBlock->BlockSize = mbi.RegionSize;
//DEL 	lpBlock->lpNextBlock->DataOffset = sizeof(MEMBLOCK);
//DEL 	return 0;
//DEL }

DWORD CMemTable::CreateAccessors(IAccessor* lpAccessor)
{
	DWORD			i;
	DBBINDING		dbBinding;
	DBBINDSTATUS	dbBindStatus;
	COLUMNDATA*		cdata;
	for (i=0;i<m_ColumnCount;i++)
	{
		GetColumnData(i,&cdata);
		dbBinding.iOrdinal = i+1;
		dbBinding.obValue = 0;
		dbBinding.obLength = 0;
		dbBinding.obStatus = 0;
		dbBinding.pTypeInfo = NULL;
		dbBinding.pObject = NULL;
		dbBinding.pBindExt = NULL;
		dbBinding.dwPart = DBPART_VALUE;//|DBPART_LENGTH|DBPART_STATUS;
		dbBinding.dwMemOwner = DBMEMOWNER_CLIENTOWNED;
		dbBinding.eParamIO = DBPARAMIO_NOTPARAM;
		dbBinding.cbMaxLen = cdata->size;
		dbBinding.dwFlags = 0;
		dbBinding.wType = cdata->type;
		dbBinding.bPrecision = 0;
		dbBinding.bScale = 0;
		lpAccessor->CreateAccessor(DBACCESSOR_ROWDATA,1,&dbBinding,0,&cdata->iAccessor,&dbBindStatus);
	}
	return 0;
}

DWORD CMemTable::DestroyAccessors(IAccessor* lpAccessor)
{
	DWORD i;
	COLUMNDATA* cdata;
	for (i=0;i<m_ColumnCount;i++)
	{
		GetColumnData(i,&cdata);
		lpAccessor->ReleaseAccessor(cdata->iAccessor,NULL);
	}
	return 0;
}

//DEL DWORD CMemTable::SetData(IRowset* lpIRowset)
//DEL {
//DEL 	HROW		hRow;
//DEL 	HROW*		lphRow = &hRow;
//DEL 	ULONG		pRowsObtained;
//DEL 	DWORD		i;
//DEL 	HRESULT		hr;
//DEL 	MEMBLOCK*	lpBlock = (MEMBLOCK*)m_lpTable;
//DEL 	DWORD		pos = lpBlock->DataOffset;
//DEL 	IAccessor*	lpIAccessor=NULL;
//DEL 	hr = lpIRowset->QueryInterface(IID_IAccessor,(void**)&lpIAccessor);
//DEL 	if (hr != S_OK) return ERR_FAIL;
//DEL 	CreateAccessors(lpIAccessor);
//DEL 	m_RowCount = 0;
//DEL 	while (true)
//DEL 	{
//DEL 		hr = lpIRowset->GetNextRows(DB_NULL_HCHAPTER,0,1,&pRowsObtained,&lphRow);
//DEL 		if (hr == DB_S_ENDOFROWSET) break;
//DEL 		if (hr != S_OK) break;
//DEL 		for (i=0;i<m_ColumnCount;i++)
//DEL 		{
//DEL 			// ver si la columna cabe
//DEL 			if (m_lpTable->columnsInfo[i].size > lpBlock->BlockSize - pos)
//DEL 			{
//DEL 				// Pasar al proximo bloque o adicionarlo
//DEL 				AddBlock(lpBlock);
//DEL 				lpBlock = lpBlock->lpNextBlock;
//DEL 				pos = lpBlock->DataOffset;
//DEL 			}
//DEL 			hr = lpIRowset->GetData(hRow,(HACCESSOR)m_lpTable->columnsInfo[i].lpvoid,&((BYTE*)lpBlock)[pos]);
//DEL 			// Incrementar posicion para la proxima columna
//DEL 			pos += m_lpTable->columnsInfo[i].size;
//DEL 			if (hr != S_OK) break;
//DEL 		}
//DEL 		hr = lpIRowset->ReleaseRows(1,&hRow,NULL,NULL,NULL);
//DEL 		m_RowCount ++;
//DEL 	}
//DEL 	DestroyAccessors(lpIAccessor);
//DEL 	return 0;
//DEL }

//DEL DWORD CMemTable::GetColumnInfo(DWORD dwIndex, COLUMNINFO *lpColumInfo)
//DEL {
//DEL 	if (m_ColumnCount <= dwIndex) return ERR_OUT_RANGE;
//DEL 	*lpColumInfo = m_lpTable->columnsInfo[dwIndex];
//DEL 	return ERR_NONE;
//DEL }

//DEL DWORD CMemTable::AddColumn(COLUMNINFO* pColumnInfo)
//DEL {
//DEL 	DWORD r;
//DEL 	if (m_lpTable == NULL)
//DEL 	{
//DEL 		r = CreateColumnsBlock();
//DEL 		if (r != 0) return r;
//DEL 		m_ColumnCount = 0;
//DEL 	}
//DEL 	WORD tmp1;
//DEL 	tmp1 = pColumnInfo->size % ALING;
//DEL 	if (tmp1 !=0) pColumnInfo->size += (ALING-tmp1);
//DEL 	m_lpTable->columnsInfo[m_ColumnCount] = *pColumnInfo;
//DEL 	m_lpTable->blockHeader.DataOffset += sizeof(COLUMNINFO);
//DEL 	m_ColumnCount++;
//DEL 	return 0;	
//DEL }

//DEL DWORD CMemTable::SetColumnInfo(DWORD dwIndex, COLUMNINFO *pColumnInfo)
//DEL {
//DEL 	if (m_ColumnCount <= dwIndex) return ERR_OUT_RANGE;
//DEL 	m_lpTable->columnsInfo[dwIndex] = *pColumnInfo;
//DEL 	return ERR_NONE;
//DEL }

DWORD CMemTable::GetColumnCount()
{
	return m_ColumnCount;
}

DWORD CMemTable::GetRowCount()
{
	return m_RowCount;
}

DWORD CMemTable::AddColumnExtraData(DWORD dwSize, DWORD *lpdwOffset)
{
	WORD tmp1;
 	tmp1 = dwSize % ALING;
 	if (tmp1 !=0) dwSize += (ALING-tmp1);	// Alineacion de datos
	*lpdwOffset = m_ColumnExtraDataSize;
	m_ColumnExtraDataSize += dwSize;
	return ERR_NONE;
}

DWORD CMemTable::AddColumn(MACOLUMNINFO* pColumnInfo)
{
	DWORD err;
	COLUMNDATA* cdata;
	err = SetColumnCount(m_ColumnCount+1);
	if (err != ERR_NONE) return err;
	GetColumnData(m_ColumnCount-1,&cdata);
	if (err != ERR_NONE) return err;
	*cdata = *lpColumnData;
	return ERR_NONE;
}

DWORD CMemTable::RequestMemory(DWORD dwSize)
{
	MEMORY_BASIC_INFORMATION	mbi;
	if (m_MemArray == NULL) 
	{
		m_MemArray = (MEMARRAY*)VirtualAlloc(NULL,m_MaxCommitMen,MEM_RESERVE,PAGE_READWRITE);
		if (m_MemArray == NULL) 
		{
			m_LastError = GetLastError();
			return ERR_APIFAILD;
		}
		::VirtualQuery(m_MemArray,&mbi,sizeof(mbi));
		if (::VirtualAlloc(m_MemArray,1,MEM_COMMIT,PAGE_READWRITE)== NULL)
		{
			m_LastError = GetLastError();
			return ERR_APIFAILD;
		}
		m_MemArray->CommitMen = mbi.RegionSize;
		::VirtualQuery(m_MemArray,&mbi,sizeof(mbi));
		m_MemArray->ReservedMen = mbi.RegionSize;
	}
	if (dwSize > m_MemArray->CommitMen)
		return ERR_NOMEMORY;
	if (m_MemArray->ReservedMen < dwSize)
	{
		if (VirtualAlloc(m_MemArray,dwSize,MEM_COMMIT,PAGE_READWRITE) == NULL)
		{
			m_LastError = GetLastError();
			return ERR_APIFAILD;
		}
		::VirtualQuery(m_MemArray,&mbi,sizeof(mbi));
		m_MemArray->ReservedMen = mbi.RegionSize;
	}
	return ERR_NONE;
}


DWORD CMemTable::AddRowExtraData(DWORD dwSize, DWORD *lpdwOffset)
{
	WORD tmp1;
 	tmp1 = dwSize % ALING;
 	if (tmp1 !=0) dwSize += (ALING-tmp1);
	*lpdwOffset = m_RowExtraDataSize;
	m_RowExtraDataSize += dwSize;
	return ERR_NONE;
}

DWORD CMemTable::GetDataPrtAt(DWORD dwRow, DWORD dwColumn, LPVOID *lplpData)
{
	if ((pRow >= m_RowCount) || (pColumn >= m_ColumnCount))
 		return ERR_OUT_RANGE;
 	// Tamaño de una fila
	DWORD offset = GetRowSize();
	offset *= pRow;
	offset += GetColumnOffset(pColumn);
	*lplpData = &m_MemArray->Mem[offset];
	return ERR_NONE;
}

DWORD CMemTable::GetRowSize()
{
	DWORD i;
	DWORD RowSize=m_RowExtraDataSize;
	COLUMNDATA* pColumnData;
	for (i=0;i<m_ColumnCount;i++)
	{
		pColumnData = (COLUMNDATA*)&m_MemArray->Mem[i*(sizeof(COLUMNDATA)+m_ColumnExtraDataSize)];
		RowSize += pColumnData->size;
	}
	return RowSize;
}

DWORD CMemTable::GetColumnOffset(DWORD dwColumn)
{
	DWORD i;
	DWORD ColumnOffset=0;
	COLUMNDATA* pColumnData;
	for (i=0;i<dwColumn;i++)
	{
		pColumnData = (COLUMNDATA*)&m_MemArray->Mem[i*(sizeof(COLUMNDATA)+m_ColumnExtraDataSize)];
		ColumnOffset += pColumnData->size;
	}
	return ColumnOffset;
}

DWORD CMemTable::GetColumnExtraData(DWORD pColumn, DWORD dwOffset, LPVOID *lplpData)
{
	if (pColumn >= m_ColumnCount)
 		return ERR_OUT_RANGE;
	*lplpData = COLUMNEXTRADATA;
	//&m_MemArray->Mem[pColumn*(sizeof(COLUMNDATA)+m_ColumnExtraDataSize)+sizeof(COLUMNDATA)+dwOffset];
	return ERR_NONE;
}

DWORD CMemTable::GetColumnData(DWORD dwColumn, COLUMNDATA *lpColumData)
{
	if (dwColumn >= m_ColumnCount)
 		return ERR_OUT_RANGE;
	DWORD DWORD ColumnIndex = dwColumn;
	COLUMNDATA*	cdata = DATACOLUMN;
	*lpColumData = *cdata;
	return ERR_NONE;
}

DWORD CMemTable::GetColumnData(DWORD dwColumn, COLUMNDATA **lpColumData)
{
	if (dwColumn >= m_ColumnCount)
 		return ERR_OUT_RANGE;
	DWORD ColumnIndex = dwColumn;
	*lpColumData = DATACOLUMN;// (COLUMNDATA*)&m_MemArray->Mem[dwColumn*(sizeof(COLUMNDATA)+m_ColumnExtraDataSize)];
	return ERR_NONE;
}

DWORD CMemTable::SetData(IRowset *lpIRowset, BOOL* bOnEndRowset)
{
 	HROW		hRow;
 	HROW*		lphRow = &hRow;
 	ULONG		pRowsObtained;
 	DWORD		i;
 	HRESULT		hr;
	DWORD		err;
 	IAccessor*	lpIAccessor=NULL;
	m_RowCount = 0;
	*bOnEndRowset = TRUE;
	
 	hr = lpIRowset->QueryInterface(IID_IAccessor,(void**)&lpIAccessor);
 	if (hr != S_OK) return ERR_FAIL;
 	CreateAccessors(lpIAccessor);
 	while (true)
 	{
 		hr = lpIRowset->GetNextRows(DB_NULL_HCHAPTER,0,1,&pRowsObtained,&lphRow);
 		if (hr == DB_S_ENDOFROWSET) break;
 		if (hr != S_OK) break;
		err = SetRowCount(m_RowCount+1); 
		if (err == ERR_NONE)
		{
 			for (i=0;i<m_ColumnCount;i++)
 			{
				void* lpvoid;
				COLUMNDATA	cdata;
				GetColumnData(i,&cdata);
				GetDataPrtAt(m_RowCount,i,&lpvoid);
				hr = lpIRowset->GetData(hRow,cdata.iAccessor,lpvoid);
 			}
		}
		else
			*bOnEndRowset = FALSE;
 		hr = lpIRowset->ReleaseRows(1,&hRow,NULL,NULL,NULL);
		if (err != ERR_NONE) break;
 	}
 	DestroyAccessors(lpIAccessor);
	for (i=0;i<m_ColumnCount;i++)
 	{
		COLUMNDATA*	cdata;
		GetColumnData(i,&cdata);
		cdata->ColumnIndex = i;
	}
 	return 0;
}

DWORD CMemTable::SetRowCount(DWORD dwRows)
{
	DWORD RowSize = GetRowSize();
	DWORD err;
	err = RequestMemory(sizeof(MEMARRAY)
			+ (m_ColumnCount)*(sizeof(COLUMNDATA)+m_ColumnExtraDataSize)
			+ dwRows*(RowSize+m_RowExtraDataSize)
			- 1);
	if (err != ERR_NONE) return err;
	m_RowCount = dwRows;
	return ERR_NONE;
}

DWORD CMemTable::SetColumnCount(DWORD dwColumns)
{
	DWORD err;
	DWORD ColumnIndex = dwColumns;
	//err = RequestMemory(COLUMNOFFSETsizeof(MEMARRAY)+(dwColumns)*(sizeof(COLUMNDATA)+m_ColumnExtraDataSize));
	err = RequestMemory(DATACOLUMNOFFSET);
	if (err != ERR_NONE) return err;
	m_ColumnCount = dwColumns;
	return 0;
}
