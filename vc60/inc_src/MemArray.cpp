// MemArray.cpp: implementation of the CMemArray class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MemArray.h"
#include "errorcodes.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define ALING			4	// Constante de alineacion de los datos 4 bytes (32bits)

#define MA_CINFOOFFSET	ColumnIndex*(sizeof(MACOLUMNINFO)+m_ColumnExtraDataSize)
#define MA_CINFOPTR		((MACOLUMNINFO*)&(Data()[MA_CINFOOFFSET]))
#define MA_CEDATAPTR	&(MA_CINFOPTR->extraData[Offset])
#define MA_ROWOFFSET	m_ColumnCount*(sizeof(MACOLUMNINFO)+m_ColumnExtraDataSize)+(m_RowSize+m_RowExtraDataSize)*RowIndex
#define MA_ROWPTR		&(Data()[MA_ROWOFFSET])
#define MA_REDATAPTR	&(Data()[MA_ROWOFFSET+m_RowSize+Offset])
#define MA_ROWCOLUMNPTR &(Data()[MA_ROWOFFSET+MA_CINFOPTR->memOffset])

char	MemArrayStr[100];

CMemArray::CMemArray()
{
	m_ColumnCount = 0;
	m_ColumnExtraDataSize = 0;
	m_hResult = 0;
	SetMaxSize(5*1024*1024);
	m_RowCount = 0;
	m_RowExtraDataSize = 0;
	m_RowSize = 0;
	m_prgInfo	= NULL;
	m_gridColumnDataOffset = -1;
	m_gridRowDataOffset = -1;
	m_ChangeNo = 0;
	m_IDBClass = NULL;
	m_pIDataConvert = NULL;
}

CMemArray::~CMemArray()
{
	
}

DWORD CMemArray::AddColumnExtraData(WORD dwSize, WORD *lpdwOffset)
{
	WORD tmp1;
 	tmp1 = dwSize % ALING;
 	if (tmp1 !=0) dwSize += (ALING-tmp1);	// Alineacion de datos
	*lpdwOffset = m_ColumnExtraDataSize;
	m_ColumnExtraDataSize += dwSize;
	return ERR_NONE;
}

DWORD CMemArray::AddRowExtraData(WORD dwSize, WORD *lpdwOffset)
{
	WORD tmp1;
 	tmp1 = dwSize % ALING;
 	if (tmp1 !=0) dwSize += (ALING-tmp1);
	*lpdwOffset = m_RowExtraDataSize;
	m_RowExtraDataSize += dwSize;
	return ERR_NONE;
}

DWORD CMemArray::AddRow()
{
	DWORD dr;
	DWORD RowIndex = m_RowCount+1;
	dr = SetSize(MA_ROWOFFSET);
	if (dr == ERR_NONE) m_RowCount++;
	return dr;
}

DWORD _stdcall CMemArray::GetColumnExtraDataPtr(WORD ColumnIndex, DWORD Offset, LPVOID *lplpData)
{
	*lplpData = NULL;
	if ((ColumnIndex >= m_ColumnCount)||(-1 == Offset)) return ERR_OUT_RANGE;
	*lplpData = MA_CEDATAPTR;
	return ERR_NONE;
}

DWORD _stdcall CMemArray::GetRowExtraDataPtr(DWORD RowIndex, DWORD Offset, LPVOID *lplpData)
{
	if (RowIndex >= m_RowCount)
 		return ERR_OUT_RANGE;
	*lplpData = MA_REDATAPTR;
	return ERR_NONE;
}

DWORD _stdcall CMemArray::GetDataPrtAt(DWORD RowIndex, WORD ColumnIndex, LPVOID *lplpData)
{
	if ((RowIndex >= m_RowCount) || (ColumnIndex >= m_ColumnCount))
		return ERR_OUT_RANGE;
	*lplpData = MA_ROWCOLUMNPTR;
	return ERR_NONE;
}

DWORD _stdcall CMemArray::GetColumnCount()
{
	return m_ColumnCount;
}

DWORD _stdcall CMemArray::GetRowCount()
{
	return m_RowCount;

}

DWORD _stdcall CMemArray::GetColumn(DWORD dbIndex,WORD* lpdwColumnIndex)
{
	*lpdwColumnIndex = INVALID_INDEX;
	DWORD ColumnIndex;
	DWORD _dbIndex;
	MACOLUMNINFO* cinfo;
	for(ColumnIndex=0;ColumnIndex<m_ColumnCount;ColumnIndex++)
	{
		cinfo = MA_CINFOPTR;
		if (HIWORD(dbIndex))
			_dbIndex = cinfo->dbIndex;
		else
			_dbIndex = LOWORD(cinfo->dbIndex);
		if (_dbIndex == dbIndex)
		{
			*lpdwColumnIndex = ColumnIndex;
			return ERR_NONE;
		}
	}
	return ERR_INVARG;
}

DWORD CMemArray::SetData(IRowset *lpIRowset,DWORD dwReadFlags)
{
 	HROW			hRow;
 	HROW*			lphRow = &hRow;
 	ULONG			pRowsObtained;
	DWORD			dr;
	void*			lpdata;
	ULONG			pColumnsCant,i;
	DWORD			RowIndex;
	HACCESSOR		hAccessor;
 	IAccessor*		lpIAccessor;
	MACOLUMNINFO	cinfo;
	OLECHAR*		pStringsBuffer;
	IColumnsInfo*	pIColumnsInfo;
	DBDATAINFO*		lpdbDataInfo;
	dr = ERR_NONE;
	hAccessor = NULL;
	lpIAccessor = NULL;
	pStringsBuffer	= NULL;
	pIColumnsInfo	= NULL;
	lpdbDataInfo = NULL;
	if (!lpIRowset) return ERR_INVARG;
	for (;;)
	{
		// recoger la informacion de las columnas del recordset
		m_hResult = lpIRowset->QueryInterface(IID_IColumnsInfo,(void**)&pIColumnsInfo);
		if (m_hResult != S_OK) break;
		if (m_prgInfo) {CoTaskMemFree(m_prgInfo);m_prgInfo = NULL;}
		m_hResult = pIColumnsInfo->GetColumnInfo(&pColumnsCant,&m_prgInfo,&pStringsBuffer);
		if (m_hResult != S_OK) break;
		for (i=0;i<pColumnsCant;i++)
		{
			db_WCharToChar(m_prgInfo[i].pwszName);
			// Datos de la columna
			cinfo.dbtype = 0;
			cinfo.dbIndex = 0;
			cinfo.dbflags = DB_F_STANDARD|DB_F_STRING|DB_F_SINGLELINE|DB_F_FIXEDHEIGHT;
			cinfo.lpvoid = NULL;
			cinfo.dbSize = m_prgInfo[i].ulColumnSize;
			cinfo.iOrdinal = m_prgInfo[i].iOrdinal;
			cinfo.caption = (char*)m_prgInfo[i].pwszName;
			cinfo.bPrecision = m_prgInfo[i].bPrecision;
			cinfo.bScale = m_prgInfo[i].bScale;
			if ((dwReadFlags & MA_F_NO_READ_DBINFO) || (m_IDBClass == NULL))
			{
				switch (m_prgInfo[i].wType)
				{
				case DBTYPE_I2:
				case DBTYPE_I4:
				case DBTYPE_R4:
				case DBTYPE_R8:
				case DBTYPE_UI1:
				case DBTYPE_I1:
				case DBTYPE_UI2:
				case DBTYPE_UI4:
				case DBTYPE_STR:
				case DBTYPE_DBDATE:
				case DBTYPE_DBTIME:
				case DBTYPE_DBTIMESTAMP:
				case DBTYPE_BOOL:
				case DBTYPE_DECIMAL:
				case DBTYPE_ERROR:
				case DBTYPE_NUMERIC:
				case DBTYPE_CY:
				case DBTYPE_I8:
				case DBTYPE_UI8:
				case DBTYPE_GUID:
					{
						cinfo.dbtype = m_prgInfo[i].wType;
						break;
					}
				case DBTYPE_BSTR:
				case DBTYPE_WSTR:
					{
						cinfo.dbtype = DBTYPE_STR;
						break;
					}
				case DBTYPE_DATE:
					{
						cinfo.dbtype = DBTYPE_DBDATE;
						break;
					}
					/*
   				case DBTYPE_EMPTY:
				case DBTYPE_NULL:
				case DBTYPE_IDISPATCH:
				case DBTYPE_VARIANT:
				case DBTYPE_IUNKNOWN:
				case DBTYPE_VECTOR:
				case DBTYPE_FILETIME:
				case DBTYPE_RESERVED:
				case DBTYPE_UDT:
				default:
					{
						break;
					}
					*/
				}
			} else
			{
				dr = db_GetdbDataInfo((char*)m_prgInfo[i].pwszName,m_IDBClass,&lpdbDataInfo);
				if (dr == ERR_NONE) 
				{
					FillColumnInfo(&cinfo,lpdbDataInfo);
				}
				dr = ERR_NONE;
			}// else
			if (cinfo.dbtype != 0)
			{
				dr = AddColumn(&cinfo);
				if (dr != ERR_NONE) break;
			}
		}// for columns
		if (dr != ERR_NONE) break;	// No se adicionaron todas las columnas
		m_hResult = lpIRowset->QueryInterface(IID_IAccessor,(void**)&lpIAccessor);
		if (m_hResult != S_OK) break;
		dr = CreateAccessor(lpIAccessor,&hAccessor);
		if (dr != ERR_NONE) break;
		// recoger datos del recordset
		m_RowCount = 0;
		for (;;)
		{
			m_hResult = lpIRowset->GetNextRows(DB_NULL_HCHAPTER,0,1,&pRowsObtained,&lphRow);
			if (m_hResult == DB_S_ENDOFROWSET) 
			{
				m_hResult = S_OK;
				break;
			}
			if (m_hResult != S_OK) break;
			dr = AddRow();
			if (dr != ERR_NONE) {dr = ERR_NONE;break;}
			RowIndex = m_RowCount-1;
			lpdata = MA_ROWPTR;
			m_hResult = lpIRowset->GetData(hRow,hAccessor,lpdata);
			lpIRowset->ReleaseRows(1,&hRow,NULL,NULL,NULL);
			if (m_hResult != S_OK) break;
		}
		break;
	} // for (;;)
	if (hAccessor) lpIAccessor->ReleaseAccessor(hAccessor,NULL);
	if (lpIAccessor) lpIAccessor->Release();
	if (pIColumnsInfo) pIColumnsInfo->Release();
	if (m_hResult != S_OK) ResetContent();
	return dr;
}


DWORD CMemArray::CreateAccessor(IAccessor* lpAccessor,HACCESSOR* hAccessor)
{
	CVirtualMem	bindings;
	bindings.SetMaxSize(sizeof(DBBINDING)*m_ColumnCount+sizeof(DBBINDSTATUS)*m_ColumnCount);

	// se crea un solo accessor 
	DWORD			ColumnIndex;
	WORD			bindingCount;
	DBBINDING*		dbBinding;
	DBBINDSTATUS*	dbBindStatus;
	MACOLUMNINFO*	cinfo;
	bindingCount = 0;
	for (ColumnIndex=0;ColumnIndex<m_ColumnCount;ColumnIndex++)
	{
		cinfo = MA_CINFOPTR;
		if (cinfo->iOrdinal == 0) continue;
		if (cinfo->dbflags & DB_F_NODBDATA) continue;
		bindingCount++;
		bindings.SetSize(sizeof(DBBINDING)*bindingCount);
		dbBinding = (DBBINDING*)&(bindings.Data()[sizeof(DBBINDING)*(bindingCount-1)]);
		ZeroMemory(dbBinding,sizeof(DBBINDING));
		
		dbBinding->iOrdinal = cinfo->iOrdinal;
		dbBinding->obValue = cinfo->memOffset;
		dbBinding->obLength = 0;
		dbBinding->obStatus = 0;
		dbBinding->dwFlags = 0;
		dbBinding->pTypeInfo = NULL;
		dbBinding->pObject = NULL;
		dbBinding->pBindExt = NULL;
		dbBinding->dwPart = DBPART_VALUE;
		dbBinding->dwMemOwner = DBMEMOWNER_CLIENTOWNED;
		dbBinding->eParamIO = DBPARAMIO_NOTPARAM;
		dbBinding->cbMaxLen = cinfo->dbSize;
		dbBinding->wType = cinfo->dbtype;
		dbBinding->bPrecision = cinfo->bPrecision;
		dbBinding->bScale = cinfo->bScale;
	}
	dbBinding = (DBBINDING*)bindings.Data();
	dbBindStatus = (DBBINDSTATUS*)&(bindings.Data()[sizeof(DBBINDING)*(bindingCount)]); 
	ZeroMemory(dbBindStatus,sizeof(DBBINDSTATUS)*bindingCount);
	m_hResult = lpAccessor->CreateAccessor(DBACCESSOR_ROWDATA,bindingCount,dbBinding,0,hAccessor,dbBindStatus);
	if (m_hResult != S_OK) return ERR_OLEDBFAIL;
	return ERR_NONE;
}

DWORD CMemArray::SetDBInterfaz(IDBClass *lpIDBClass)
{
	m_IDBClass = lpIDBClass;
	return 0;
}

DWORD _stdcall CMemArray::GetSize(HDC hdc,DWORD dwRowIndex, WORD wColumnIndex, RECT *lprect)
{
	return 0;
}

DWORD _stdcall CMemArray::GetColumnInfo(WORD dwColumnIndex,DWORD* lpdwdbIndex,char** lplpszcaption, DWORD* lpdwFlags)
{
	DWORD			ColumnIndex;
	MACOLUMNINFO*	cinfo;
	if (dwColumnIndex >= m_ColumnCount)	return ERR_OUT_RANGE;
	ColumnIndex = dwColumnIndex;
	cinfo = MA_CINFOPTR;
	if (lpdwdbIndex) *lpdwdbIndex = cinfo->dbIndex;
	if (lplpszcaption) *lplpszcaption = cinfo->caption;
	if (lpdwFlags) *lpdwFlags = cinfo->dbflags;
	return ERR_NONE;
}

DWORD CMemArray::AddColumn(MACOLUMNINFO *lpColumnInfo)
{
	DWORD dr;
	DWORD ColumnIndex = m_ColumnCount+1;
	dr = SetSize(MA_CINFOOFFSET);
	if (dr != ERR_NONE) return dr;
	m_ColumnCount++;
	MACOLUMNINFO*	cinfo;
	ColumnIndex--;
	cinfo = MA_CINFOPTR;
	*cinfo = *lpColumnInfo;
	DWORD tmp1;
 	tmp1 = cinfo->dbSize % ALING;
 	if (tmp1 !=0) 
		cinfo->memSize = cinfo->dbSize + (ALING-tmp1);
	else
		cinfo->memSize = cinfo->dbSize;
	if (ColumnIndex == 0) cinfo->memOffset =0;
	else
	{
		ColumnIndex--;
		MACOLUMNINFO*	cinfo2;
		cinfo2 = MA_CINFOPTR;
		cinfo->memOffset = cinfo2->memOffset+cinfo2->memSize;
	}
	m_RowSize+= cinfo->memSize;
	return 0;
}

// Usada para adicionar elementos que no aparecen en el recordset
DWORD CMemArray::AddColumn(DBDATAINFO *lpdbDataInfo,void* lpvoid)
{
	MACOLUMNINFO cinfo;
	FillColumnInfo(&cinfo,lpdbDataInfo);
	cinfo.iOrdinal = 0;
	cinfo.lpvoid = lpvoid;
	return AddColumn(&cinfo);
}

DWORD _stdcall CMemArray::ResetContent()
{
	SetSize(0);
	m_ColumnCount = 0;
	m_hResult = 0;
	m_RowCount = 0;
	m_RowSize = 0;
	if (m_prgInfo) CoTaskMemFree(m_prgInfo);
	m_prgInfo = NULL;
	return ERR_NONE;
}

DWORD _stdcall CMemArray::GetData(DWORD dwRowIndex)
{
	// Transfiere la informacion de la fila a IdbClass
	WORD		ColumnIndex;
	DWORD		RowIndex = dwRowIndex;
	_VARIANT*	lpvariant;
	MACOLUMNINFO*	cinfo;
	if (RowIndex >= m_RowCount) return ERR_EOT;
	for (ColumnIndex=0;ColumnIndex<m_ColumnCount;ColumnIndex++)
	{
		cinfo = MA_CINFOPTR;
		lpvariant = (_VARIANT*)MA_ROWCOLUMNPTR;
		m_IDBClass->SetValue(cinfo->dbIndex,lpvariant);
	}
	return 0;
}

DWORD CMemArray::SetExtraDataSize(BYTE bType, WORD wSize)
{
	switch(bType)
	{
	case MA_GRID_ROW_DATA: return AddRowExtraData(wSize,&m_gridRowDataOffset);
	case MA_GRID_COLUMN_DATA: return AddColumnExtraData(wSize,&m_gridColumnDataOffset);
	}
	return ERR_INVARG;
}

DWORD _stdcall CMemArray::GetExtraDataOffset(BYTE bType, WORD *lpwOffset)
{
	switch(bType)
	{
	case MA_GRID_ROW_DATA: *lpwOffset = m_gridRowDataOffset;break;
	case MA_GRID_COLUMN_DATA: *lpwOffset = m_gridColumnDataOffset;break;
	default: return ERR_INVARG;
	}
	return 0;	
}

DWORD _stdcall CMemArray::GetChangeNo()
{
	return m_ChangeNo;
}

DWORD _stdcall CMemArray::GetInterfaz(char* pzsName,void** ppInterfaz)
{
	*ppInterfaz = NULL;
	if (strcmp(pzsName,IDBARRAY_NAME) == 0)	*ppInterfaz = (IDBArray*)this;
	if (strcmp(pzsName,IDBCLASS_NAME) == 0) *ppInterfaz = m_IDBClass;
	if (*ppInterfaz == NULL) return ERR_NOINTERFACE;
	return ERR_NONE;
}

DWORD _stdcall CMemArray::Look(WORD dwColumnIndex, _VARIANT *pVariant,DWORD *lpdwRowIndex,LPCOMPFUNC pCompFunc)
{
	LPCOMPFUNC Func;
	MACOLUMNINFO* cinfo;
	DWORD RowIndex;
	DWORD ColumnIndex = dwColumnIndex;
	_VARIANT* pvariant;
	// ver el tipo de columna
	cinfo = MA_CINFOPTR;
	switch (cinfo->dbtype)
	{
		case DBTYPE_BOOL:
		case DBTYPE_I2:			Func = CmpShort;break;
		case DBTYPE_I4:			Func = CmpLong;break;
		case DBTYPE_R4:			Func = CmpFloat;break;
		case DBTYPE_R8:			Func = CmpDouble;break;
		case DBTYPE_UI1:		Func = CmpUnsignedChar;break;
		case DBTYPE_I1:			Func = CmpChar;break;
		case DBTYPE_UI2:		Func = CmpUnsignedShort;break;
		case DBTYPE_UI4:		Func = CmpUnsignedLong;break;
		case DBTYPE_BSTR:		
		case DBTYPE_STR:		Func = CmpStr;break;
		
	}
	for (RowIndex=0;RowIndex<m_RowCount;RowIndex++)
	{
		pvariant = (_VARIANT*)MA_ROWCOLUMNPTR;
		if (Func(pVariant,pvariant)==0)
		{
			*lpdwRowIndex = RowIndex;
			return ERR_NONE;
		}
	}
	return ERR_EOT;
}

DWORD CMemArray::FillColumnInfo(MACOLUMNINFO *pcinfo, DBDATAINFO *pdbDataInfo)
{
	pcinfo->caption = pdbDataInfo->caption;
	pcinfo->dbIndex = pdbDataInfo->dbIndex;
	pcinfo->dbflags = pdbDataInfo->flags;
	pcinfo->dbSize = pdbDataInfo->size;
	pcinfo->dbtype = pdbDataInfo->type;
	pcinfo->bPrecision = pdbDataInfo->bPrecision;
	pcinfo->bScale = pdbDataInfo->bScale;
	return 0;

}

DWORD _stdcall CMemArray::Release()
{
	if (m_pIDataConvert)	m_pIDataConvert->Release();
	if (m_prgInfo)			CoTaskMemFree(m_prgInfo);
	m_ColumnCount = 0;
	m_ColumnExtraDataSize = 0;
	m_hResult = 0;
	m_RowCount = 0;
	m_RowExtraDataSize = 0;
	m_RowSize = 0;
	m_prgInfo	= NULL;
	m_gridColumnDataOffset = -1;
	m_gridRowDataOffset = -1;
	m_ChangeNo = 0;
	m_IDBClass = NULL;
	m_pIDataConvert = NULL;
	CVirtualMem::Release();
	return 0;
}

DWORD _stdcall CMemArray::SetRowCount(DWORD dwRowCount)
{
	DWORD dr;
	DWORD RowIndex = dwRowCount;
	dr = SetSize(MA_ROWOFFSET);
	if (dr == ERR_NONE) m_RowCount = dwRowCount;
	return dr;	
}

DWORD _stdcall CMemArray::SetMaxParams(WORD wmaxColumns, DWORD dwmaxRows, WORD wmaxRowSize)
{
	DWORD maxSize;
	SetSize(0);
	maxSize = wmaxColumns*(sizeof(MACOLUMNINFO)+m_ColumnExtraDataSize)+dwmaxRows*(wmaxRowSize + m_RowExtraDataSize);
	SetMaxSize(maxSize);
	return 0;
}

DWORD _stdcall CMemArray::SetIdbClass(IDBClass *pIdbClass)
{
	m_IDBClass = pIdbClass;
	return 0;
}

DWORD _stdcall CMemArray::DrawItem(HDC hdc, ITEM_DATA *lpItemData)
{
	WORD ColumnIndex = lpItemData->wColumnIndex;
	DWORD RowIndex = lpItemData->dwRowIndex;
	if ((RowIndex >= m_RowCount) || (ColumnIndex >= m_ColumnCount))	return ERR_OUT_RANGE;
	
	MACOLUMNINFO*	cinfo;
	cinfo = MA_CINFOPTR;
	if (cinfo->dbflags & DB_F_OWNERDRAW)
	{
		if (m_IDBClass != NULL) m_IDBClass->Draw(hdc,MA_ROWCOLUMNPTR,cinfo->dbIndex,RowIndex,ColumnIndex,&lpItemData->rect);
		return 0;
	}
	if (cinfo->dbflags & DB_F_STRING)
	{
		COLORREF backcolor = lpItemData->backColor;
		GetItemText(lpItemData);
		SetTextColor(hdc,lpItemData->textColor);
		SetBkColor(hdc,lpItemData->backColor);
		SelectObject(hdc,lpItemData->hFont);
		// si cambio el color de fondo redibujar el fondo
		if (lpItemData->backColor != lpItemData->backColor)
		{
			::ExtTextOut(hdc,0,0,ETO_OPAQUE,&lpItemData->rect,NULL,0,NULL);
		}
		DrawText(hdc,lpItemData->pzsText,-1,&lpItemData->rect,lpItemData->uFormat);
	}
	return 0;
}

DWORD CMemArray::GetItemText(ITEM_DATA *lpItemData)
{
	HRESULT	hr;
	WORD ColumnIndex = lpItemData->wColumnIndex;
	DWORD RowIndex = lpItemData->dwRowIndex;
	if (ColumnIndex >= m_ColumnCount)	return ERR_OUT_RANGE;
	if (!m_pIDataConvert)
	{
		hr = CoCreateInstance(CLSID_DataConvert, NULL, CLSCTX_INPROC_SERVER,IID_IDataConvert, (void **)&m_pIDataConvert);
	}
	lpItemData->pzsText = NULL;
	// Procesamiento de datos sencillos
	MACOLUMNINFO*	cinfo;
	cinfo = MA_CINFOPTR;
	lpItemData->dwdbIndex = cinfo->dbIndex;
	// Fijar un posible formato
	if (cinfo->dbflags & DB_F_SINGLELINE)  
		lpItemData->uFormat = DT_LEFT|DT_END_ELLIPSIS|DT_SINGLELINE|DT_TOP;
	else
		lpItemData->uFormat = DT_LEFT|DT_TOP|DT_WORDBREAK|DT_NOPREFIX;
	// obtener formato, color, font y string
	if (m_IDBClass)
		m_IDBClass->GetItemText(lpItemData); 
	else
		lpItemData->pzsText = MemArrayStr;
	if (RowIndex == INVALID_INDEX) return 0;
	if (RowIndex >= m_RowCount) return ERR_OUT_RANGE;
	// Llenar el string si es standar por que la clase no lo lleno
	if (cinfo->dbflags & DB_F_STANDARD)
	{
		// ver el tipo de dato en cuestion
		_VARIANT* lpvariant;
		lpvariant = (_VARIANT*)MA_ROWCOLUMNPTR;
		// Obtener string
		switch (cinfo->dbtype)
		{
		case DBTYPE_I2:sprintf(lpItemData->pzsText,"%d",lpvariant->iVal);break;
		case DBTYPE_I4:sprintf(lpItemData->pzsText,"%d",lpvariant->lVal);break;
		case DBTYPE_R4:sprintf(lpItemData->pzsText,"%f",lpvariant->fltVal);break;
		case DBTYPE_R8:sprintf(lpItemData->pzsText,"%f",lpvariant->dblVal);break;
		case DBTYPE_UI1:sprintf(lpItemData->pzsText,"%d",lpvariant->bVal);break;
		case DBTYPE_I1:sprintf(lpItemData->pzsText,"%c",lpvariant->cVal);break;
		case DBTYPE_UI2:sprintf(lpItemData->pzsText,"%d",lpvariant->uiVal);break;
		case DBTYPE_UI4:sprintf(lpItemData->pzsText,"%d",lpvariant->ulVal);break;
		case DBTYPE_STR:lpItemData->pzsText = lpvariant->pzsVal;break;
		case DBTYPE_DBDATE:sprintf(lpItemData->pzsText,"%d/%d/%d",lpvariant->dbdate.day,lpvariant->dbdate.month,lpvariant->dbdate.year);break;
		case DBTYPE_DBTIME:sprintf(lpItemData->pzsText,"%d:%d:%d",lpvariant->dbtime.hour,lpvariant->dbtime.minute,lpvariant->dbtime.second);break;
		case DBTYPE_ERROR:sprintf(lpItemData->pzsText,"ERROR - %d",lpvariant->ulVal);break;
		case DBTYPE_BOOL: 
			{
				if (lpvariant->boolVal)
					strcpy(lpItemData->pzsText,"TRUE");
				else
					strcpy(lpItemData->pzsText,"FALSE");
					break;
			}
		case DBTYPE_NUMERIC:
		case DBTYPE_CY:
		case DBTYPE_I8:
		case DBTYPE_DECIMAL:
		case DBTYPE_UI8:
		case DBTYPE_GUID:
			{
				ULONG	dstSize = sizeof(MemArrayStr);
				DBSTATUS dstStatus = DBSTATUS_S_OK;
				m_pIDataConvert->DataConvert(cinfo->dbtype,DBTYPE_STR,cinfo->dbSize,&dstSize,lpvariant,MemArrayStr,sizeof(MemArrayStr),DBSTATUS_S_OK,&dstStatus,cinfo->bPrecision,cinfo->bScale,DBDATACONVERT_SETDATABEHAVIOR);
				break;
			}
		default:strcpy(lpItemData->pzsText,"????");break;
		}
	}
	return 0;
}

DWORD CMemArray::GetItemSize(HDC hdc, ITEM_DATA *lpItemData)
{
	MACOLUMNINFO*	cinfo;
	TEXTMETRIC		textmetric;
	RECT rect;

	WORD ColumnIndex = lpItemData->wColumnIndex;
	DWORD RowIndex = lpItemData->dwRowIndex;
	if (ColumnIndex >= m_ColumnCount) return ERR_OUT_RANGE;

	cinfo = MA_CINFOPTR;
	if (cinfo->dbflags & DB_F_OWNERDRAW)
	{
		if (m_IDBClass != NULL) m_IDBClass->GetItemSize(hdc,lpItemData);
		return 0;
	}
	if (cinfo->dbflags & DB_F_STRING)
	{
		// Fijar un posible formato
		if (cinfo->dbflags & DB_F_SINGLELINE)  
			lpItemData->uFormat = DT_LEFT|DT_END_ELLIPSIS|DT_SINGLELINE|DT_TOP;
		else
			lpItemData->uFormat = DT_LEFT|DT_TOP|DT_WORDBREAK|DT_NOPREFIX;
		// Tomar datos del texto
		GetItemText(lpItemData);
		if (cinfo->dbflags & DB_F_SINGLELINE)
		{
			// Alto del texto
			SelectObject(hdc,lpItemData->hFont);
			if (lpItemData->rect.top == lpItemData->rect.bottom)
			{
				GetTextMetrics(hdc,&textmetric);
				lpItemData->rect.top = 0;
				lpItemData->rect.bottom = textmetric.tmHeight+1;
			}
			if (lpItemData->rect.left == lpItemData->rect.right)
			{
				
				DrawText(hdc,lpItemData->pzsText,-1,&rect,lpItemData->uFormat|DT_CALCRECT);
				lpItemData->rect.left = 0;
				lpItemData->rect.right = rect.right - rect.left +1; 
			}
			return 0;	
		}
		// Multiline
		if (lpItemData->rect.top == lpItemData->rect.bottom)
		{
			rect = lpItemData->rect;
			DrawText(hdc,lpItemData->pzsText,-1,&rect,lpItemData->uFormat|DT_CALCRECT);
			lpItemData->rect.top = 0;
			lpItemData->rect.bottom = rect.bottom - rect.top +1;
		}
		if (lpItemData->rect.left == lpItemData->rect.right)
		{
			DrawText(hdc,lpItemData->pzsText,-1,&rect,lpItemData->uFormat|DT_CALCRECT|DT_SINGLELINE);
			lpItemData->rect.left = 0;
			lpItemData->rect.right = rect.right - rect.left +1; 
		}
	}
	return 0;
}

DWORD CMemArray::CmpStr(_VARIANT *pVariant1, _VARIANT *pVariant2)
{
	int ir = strcmp(pVariant1->pzsVal,pVariant2->pzsVal);
	if (ir < 0) ir = 2;
	return ir;
}

DWORD CMemArray::CmpShort(_VARIANT *pVariant1, _VARIANT *pVariant2)
{
	if (pVariant1->iVal == pVariant2->iVal) return 0;
	if (pVariant1->iVal > pVariant2->iVal) return 1;
	return 2;
}

DWORD CMemArray::CmpLong(_VARIANT *pVariant1, _VARIANT *pVariant2)
{
	if (pVariant1->lVal == pVariant2->lVal) return 0;
	if (pVariant1->lVal > pVariant2->lVal) return 1;
	return 2;
}

DWORD CMemArray::CmpFloat(_VARIANT *pVariant1, _VARIANT *pVariant2)
{
	if (pVariant1->fltVal == pVariant2->fltVal) return 0;
	if (pVariant1->fltVal > pVariant2->fltVal) return 1;
	return 2;
}


DWORD CMemArray::CmpDouble(_VARIANT *pVariant1, _VARIANT *pVariant2)
{
	if (pVariant1->dblVal == pVariant2->dblVal) return 0;
	if (pVariant1->dblVal > pVariant2->dblVal) return 1;
	return 2;
}


DWORD CMemArray::CmpChar(_VARIANT *pVariant1, _VARIANT *pVariant2)
{
	if (pVariant1->cVal == pVariant2->cVal) return 0;
	if (pVariant1->cVal > pVariant2->cVal) return 1;
	return 2;
}

DWORD CMemArray::CmpUnsignedShort(_VARIANT *pVariant1, _VARIANT *pVariant2)
{
	if (pVariant1->uiVal == pVariant2->uiVal) return 0;
	if (pVariant1->uiVal > pVariant2->uiVal) return 1;
	return 2;
}

DWORD CMemArray::CmpUnsignedChar(_VARIANT *pVariant1, _VARIANT *pVariant2)
{
	if (pVariant1->bVal == pVariant2->bVal) return 0;
	if (pVariant1->bVal > pVariant2->bVal) return 1;
	return 2;
}

DWORD CMemArray::CmpUnsignedLong(_VARIANT *pVariant1, _VARIANT *pVariant2)
{
	if (pVariant1->ulVal == pVariant2->ulVal) return 0;
	if (pVariant1->ulVal > pVariant2->ulVal) return 1;
	return 2;
}

DWORD CMemArray::SetData(DWORD dwRowIndex)
{
	// Recoge los datos de la clase
	WORD		ColumnIndex;
	DWORD		RowIndex = dwRowIndex;
	_VARIANT*	lpvariant;
	MACOLUMNINFO*	cinfo;
	if (RowIndex >= m_RowCount) return ERR_EOT;
	for (ColumnIndex=0;ColumnIndex<m_ColumnCount;ColumnIndex++)
	{
		cinfo = MA_CINFOPTR;
		lpvariant = (_VARIANT*)MA_ROWCOLUMNPTR;
		m_IDBClass->GetValue(cinfo->dbIndex,lpvariant);
	}
	return 0;
}

DWORD CMemArray::Find(DWORD dwStartRow, DWORD dwdbIndex, _VARIANT *pVariant, DWORD *lpdwRowIndex, LPCOMPFUNC pCompFunc)
{
	DWORD	RowIndex;
	WORD	ColumnIndex;
	DWORD	dr;

	LPCOMPFUNC	CmpFunc;
	_VARIANT*	pvariant;

	dr = GetColumn(dwdbIndex,&ColumnIndex);
	if (dr != ERR_NONE) return dr;

	if (pCompFunc == NULL) 
		GetCmpFunc(ColumnIndex,&CmpFunc);
	else
		CmpFunc = pCompFunc;

	for (RowIndex = dwStartRow;RowIndex<m_RowCount;RowIndex++)
	{
		pvariant = (_VARIANT*)MA_ROWCOLUMNPTR;
		if (CmpFunc(pVariant,pvariant)==0)
		{
			*lpdwRowIndex = RowIndex;
			return ERR_NONE;
		}
	}
	return ERR_EOT;
}

DWORD CMemArray::GetAllEqual(DWORD dwdbIndex, _VARIANT *pVariant, CdbRefArray *pdbRefArray, LPCOMPFUNC pCompFunc)
{
	DWORD		RowIndex;
	WORD		ColumnIndex;
	DWORD		dr;
	LPCOMPFUNC	CmpFunc;
	_VARIANT*	pvariant;

	// Limpiar el arreglo referencia
	((IDBArray*)pdbRefArray)->ResetContent();
	pdbRefArray->SetIdbArray(this);
	pdbRefArray->SetMaxRows(m_RowCount);

	// Buscar columna y funcion de comparacion
	dr = GetColumn(dwdbIndex,&ColumnIndex);
	if (dr != ERR_NONE) return dr;
	if (pCompFunc == NULL) 
		GetCmpFunc(ColumnIndex,&CmpFunc);
	else
		CmpFunc = pCompFunc;

	// Recorrer todas las filas
	for (RowIndex = 0;RowIndex<m_RowCount;RowIndex++)
	{
		pvariant = (_VARIANT*)MA_ROWCOLUMNPTR;
		if (CmpFunc(pVariant,pvariant)==0)
		{
			pdbRefArray->AddRow(RowIndex);
		}
	}
	return 0;
}

DWORD CMemArray::GetCmpFunc(WORD wColumnIndex,LPCOMPFUNC *ppCmpFunc)
{
	WORD			ColumnIndex;
	MACOLUMNINFO*	cinfo;

	ColumnIndex = wColumnIndex;
	cinfo = MA_CINFOPTR;
	switch (cinfo->dbtype)
	{
		case DBTYPE_BOOL:
		case DBTYPE_I2:		*ppCmpFunc = CmpShort;break;
		case DBTYPE_I4:		*ppCmpFunc = CmpLong;break;
		case DBTYPE_R4:		*ppCmpFunc = CmpFloat;break;
		case DBTYPE_R8:		*ppCmpFunc = CmpDouble;break;
		case DBTYPE_UI1:	*ppCmpFunc = CmpUnsignedChar;break;
		case DBTYPE_I1:		*ppCmpFunc = CmpChar;break;
		case DBTYPE_UI2:	*ppCmpFunc = CmpUnsignedShort;break;
		case DBTYPE_UI4:	*ppCmpFunc = CmpUnsignedLong;break;
		case DBTYPE_BSTR:	
		case DBTYPE_STR:	*ppCmpFunc = CmpStr;break;
		default:
			return ERR_NOTFOUND;		
	}
	return ERR_NONE; 
}
