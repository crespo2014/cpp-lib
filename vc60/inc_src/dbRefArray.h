// dbRefArray.h: interface for the CdbRefArray class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBREFARRAY_H__1DC274FD_346D_4045_B8E6_136A95B8766D__INCLUDED_)
#define AFX_DBREFARRAY_H__1DC274FD_346D_4045_B8E6_136A95B8766D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VirtualMem.h"
#include "dbcommon.h"
//#include "memarray.h"

class CdbRefArray : private CVirtualMem,
					public IDBArray  
{
	DWORD		m_RowCount;
	DWORD		m_ChangeNo;
	IDBArray*	m_pIdbArray;

public:
	CdbRefArray();
	virtual ~CdbRefArray();
	DWORD _stdcall AddRow(DWORD dwRowIndex);
	DWORD _stdcall SetIdbArray(IDBArray* pIDBArray);
	DWORD _stdcall GetAllEqual(DWORD dwdbIndex, _VARIANT *pVariant,LPCOMPFUNC pCompFunc = NULL); 
	DWORD _stdcall SetMaxRows(DWORD dwMaxRows);

protected:
	virtual DWORD _stdcall AddRow();
	virtual DWORD _stdcall GetData(DWORD dwRowIndex);
	virtual DWORD _stdcall SetData(DWORD dwRowIndex);
	virtual DWORD _stdcall ResetContent();
	virtual DWORD _stdcall SetIdbClass(IDBClass *pIdbClass);
	virtual DWORD _stdcall AddColumn(DBDATAINFO* lpdbDataInfo,void* lpvoid);
	virtual DWORD _stdcall SetRowCount(DWORD dwRowCount);
	virtual DWORD _stdcall GetChangeNo(DWORD* lpdwChangeNo);
	virtual DWORD _stdcall Look(WORD dwColumnIndex, _VARIANT *pVariant,DWORD *lpdwRowIndex,LPCOMPFUNC pCompFunc = NULL);
	virtual DWORD _stdcall AddRowExtraData(WORD dwSize, WORD *lpdwOffset);
	virtual DWORD _stdcall AddColumnExtraData(WORD dwSize, WORD *lpdwOffset);
	virtual DWORD _stdcall GetSize(HDC hdc,DWORD dwRowIndex, WORD wColumnIndex,RECT* lprect);
	virtual DWORD _stdcall GetDataPrtAt(DWORD RowIndex, WORD ColumnIndex,void** lplpData);
	virtual DWORD _stdcall GetRowCount();
	virtual DWORD _stdcall GetRowExtraDataPtr(DWORD RowIndex, DWORD Offset, LPVOID *lplpData);
	virtual DWORD _stdcall GetColumn(DWORD dbIndex,WORD* lpdwColumnIndex);
	virtual DWORD _stdcall GetColumnCount();
	virtual DWORD _stdcall GetColumnExtraDataPtr(WORD ColumnIndex, DWORD Offset, LPVOID *lplpData);
	virtual DWORD _stdcall GetColumnInfo(WORD dwColumnIndex,DWORD* lpdwdbIndex,char** lplpszcaption, DWORD* lpdwFlags);
	virtual DWORD _stdcall DrawItem(HDC hdc,ITEM_DATA* lpItemData);
	virtual DWORD _stdcall GetItemSize(HDC hdc,ITEM_DATA* lpItemData);
	virtual DWORD _stdcall GetItemText(ITEM_DATA* lpItemData);
	virtual DWORD _stdcall GetExtraDataOffset(BYTE bType,WORD* lpwOffset);
	virtual DWORD _stdcall SetMaxParams(WORD wmaxColumns, DWORD dwmaxRows, WORD wmaxRowSize);

private:


};

#endif // !defined(AFX_DBREFARRAY_H__1DC274FD_346D_4045_B8E6_136A95B8766D__INCLUDED_)
