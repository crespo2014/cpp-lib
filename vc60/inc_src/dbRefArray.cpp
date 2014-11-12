// dbRefArray.cpp: implementation of the CdbRefArray class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dbRefArray.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define RA_ROWDWORDPTR (DWORD*)&(Data()[RowIndex*sizeof(DWORD)])

CdbRefArray::CdbRefArray()
{
	SetMaxSize(1000*sizeof(DWORD));
	m_RowCount = 0;
	m_pIdbArray = NULL;
	m_ChangeNo = 0;
}

CdbRefArray::~CdbRefArray()
{

}

DWORD _stdcall CdbRefArray::AddRow()
{
	return ERR_INV_FUNC;
}

DWORD _stdcall CdbRefArray::GetData(DWORD dwRowIndex)
{
	DWORD RowIndex = dwRowIndex;
	return m_pIdbArray->GetData(*RA_ROWDWORDPTR);
}

DWORD _stdcall CdbRefArray::SetData(DWORD dwRowIndex)
{
	DWORD RowIndex = dwRowIndex;
	return m_pIdbArray->SetData(*RA_ROWDWORDPTR);
}

DWORD _stdcall CdbRefArray::ResetContent()
{
	m_RowCount = 0;
	SetSize(0);
	return ERR_NONE;
}

DWORD _stdcall CdbRefArray::SetIdbClass(IDBClass *pIdbClass)
{
	return ERR_INV_FUNC;
}

DWORD _stdcall CdbRefArray::AddColumn(DBDATAINFO* lpdbDataInfo,void* lpvoid)
{
	return ERR_INV_FUNC;
}

DWORD _stdcall CdbRefArray::SetRowCount(DWORD dwRowCount)
{
	SetSize(0);
	SetSize(dwRowCount*sizeof(DWORD));
	m_RowCount = dwRowCount;
	return ERR_NONE;
}

DWORD _stdcall CdbRefArray::GetChangeNo(DWORD* lpdwChangeNo)
{
	*lpdwChangeNo = m_ChangeNo;
	return ERR_NONE;
}

DWORD _stdcall CdbRefArray::Look(WORD dwColumnIndex, _VARIANT *pVariant,DWORD *lpdwRowIndex,LPCOMPFUNC pCompFunc)
{
	return ERR_INV_FUNC;
}

DWORD _stdcall CdbRefArray::AddRowExtraData(WORD dwSize, WORD *lpdwOffset)
{
	return ERR_INV_FUNC;
}

DWORD _stdcall CdbRefArray::AddColumnExtraData(WORD dwSize, WORD *lpdwOffset)
{
	return ERR_INV_FUNC;
}

DWORD _stdcall CdbRefArray::GetSize(HDC hdc,DWORD dwRowIndex, WORD wColumnIndex,RECT* lprect)
{
	if (!m_pIdbArray) return ERR_NOINTERFACE;
	DWORD RowIndex = dwRowIndex;
	return m_pIdbArray->GetSize(hdc,*RA_ROWDWORDPTR,wColumnIndex,lprect);
}

DWORD _stdcall CdbRefArray::GetDataPrtAt(DWORD RowIndex, WORD ColumnIndex,void** lplpData)
{
	if (!m_pIdbArray) return ERR_NOINTERFACE;
	return m_pIdbArray->GetDataPrtAt(*RA_ROWDWORDPTR,ColumnIndex,lplpData);
}

DWORD _stdcall CdbRefArray::GetRowCount()
{
	return m_RowCount;
}

DWORD _stdcall CdbRefArray::GetRowExtraDataPtr(DWORD RowIndex, DWORD Offset, LPVOID *lplpData)
{
	if (!m_pIdbArray) return ERR_NOINTERFACE;
	return m_pIdbArray->GetRowExtraDataPtr(*RA_ROWDWORDPTR,Offset,lplpData);
}

DWORD _stdcall CdbRefArray::GetColumn(DWORD dbIndex,WORD* lpdwColumnIndex)
{
	if (!m_pIdbArray) return ERR_NOINTERFACE;
	return m_pIdbArray->GetColumn(dbIndex,lpdwColumnIndex);
}

DWORD _stdcall CdbRefArray::GetColumnCount()
{
	if (!m_pIdbArray) return ERR_NOINTERFACE;
	return m_pIdbArray->GetColumnCount();
}

DWORD _stdcall CdbRefArray::GetColumnExtraDataPtr(WORD ColumnIndex, DWORD Offset, LPVOID *lplpData)
{
	if (!m_pIdbArray) return ERR_NOINTERFACE;
	return m_pIdbArray->GetColumnExtraDataPtr(ColumnIndex,Offset,lplpData);
}

DWORD _stdcall CdbRefArray::GetColumnInfo(WORD dwColumnIndex,DWORD* lpdwdbIndex,char** lplpszcaption, DWORD* lpdwFlags)
{
	if (!m_pIdbArray) return ERR_NOINTERFACE;
	return m_pIdbArray->GetColumnInfo(dwColumnIndex,lpdwdbIndex,lplpszcaption,lpdwFlags);
}

DWORD _stdcall CdbRefArray::DrawItem(HDC hdc,ITEM_DATA* lpItemData)
{
	if (!m_pIdbArray) return ERR_NOINTERFACE;
	DWORD RowIndex = lpItemData->dwRowIndex;
	lpItemData->dwRowIndex = *RA_ROWDWORDPTR;
	return m_pIdbArray->DrawItem(hdc,lpItemData);
}

DWORD _stdcall CdbRefArray::GetItemSize(HDC hdc,ITEM_DATA* lpItemData)
{
	if (!m_pIdbArray) return ERR_NOINTERFACE;
	DWORD RowIndex = lpItemData->dwRowIndex;
	lpItemData->dwRowIndex = *RA_ROWDWORDPTR;
	return m_pIdbArray->GetItemSize(hdc,lpItemData);
}

DWORD _stdcall CdbRefArray::GetItemText(ITEM_DATA* lpItemData)
{
	if (!m_pIdbArray) return ERR_NOINTERFACE;
	DWORD RowIndex = lpItemData->dwRowIndex;
	lpItemData->dwRowIndex = *RA_ROWDWORDPTR;
	return m_pIdbArray->GetItemText(lpItemData);
}

DWORD _stdcall CdbRefArray::GetExtraDataOffset(BYTE bType,WORD* lpwOffset)
{
	if (!m_pIdbArray) return ERR_NOINTERFACE;
	return m_pIdbArray->GetExtraDataOffset(bType,lpwOffset);
}

DWORD _stdcall CdbRefArray::SetMaxParams(WORD wmaxColumns, DWORD dwmaxRows, WORD wmaxRowSize)
{
	return ERR_INV_FUNC;
}

DWORD _stdcall CdbRefArray::AddRow(DWORD dwRowIndex)
{
	DWORD dr;
	DWORD RowIndex;

	if (!m_pIdbArray) return ERR_NOINTERFACE;
	if (m_pIdbArray->GetRowCount() <= dwRowIndex) return ERR_OUT_RANGE;

	dr = SetSize((m_RowCount+1)*sizeof(DWORD));
	if (dr != ERR_NONE) return dr;
	RowIndex = m_RowCount;
	m_RowCount++;
	*RA_ROWDWORDPTR = dwRowIndex;
	return ERR_NONE;
}

DWORD _stdcall CdbRefArray::SetIdbArray(IDBArray* pIDBArray)
{
	m_pIdbArray = pIDBArray;
	return ERR_NONE;
}

DWORD _stdcall CdbRefArray::GetAllEqual(DWORD dwdbIndex, _VARIANT *pVariant,LPCOMPFUNC pCompFunc) 
{
	DWORD	RowPos;
	RowPos = 0;
	return ERR_INV_FUNC;
}

DWORD _stdcall CdbRefArray::SetMaxRows(DWORD dwMaxRows)
{
	return SetMaxSize(dwMaxRows*sizeof(DWORD));
}

