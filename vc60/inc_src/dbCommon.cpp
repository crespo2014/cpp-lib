// dbCommon.cpp: implementation of the CdbCommon class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dbCommon.h"
#include "errorcodes.h"
#include "dbGuiInfProcess.h"
#include "dbDataInfoInfProcess.h"

DWORD _stdcall db_WCharToChar(LPWSTR lpWideCharStr)
{
	BYTE* str = (BYTE*)lpWideCharStr;
	size_t size=wcslen(lpWideCharStr);
	for (size_t i = 0;i<=size;i++)
	{
		str[i] = (BYTE)lpWideCharStr[i];
	}
	return 0;
}

DWORD _stdcall db_CharToWChar(LPSTR lpCharStr)
{
	LPWSTR str = (LPWSTR)lpCharStr;
	for (int i = strlen(lpCharStr);i>=0;i--)
	{
		str[i] = lpCharStr[i];
	}
	return 0;
}

DWORD _stdcall db_GetdbDataInfo(DWORD dwdbIndex,IDBClass* lpIdbClass,DBDATAINFO** lpdbDataInfo)
{
	WORD i;
	DWORD	dbIndex;
	DBTABLEINFO* dbTableInfo;
	lpIdbClass->GetdbTableInfo(&dbTableInfo);
	for (i=0;i<dbTableInfo->dataCount;i++)
	{
		if (HIWORD(dwdbIndex) == 0)
			dbIndex = LOWORD(dbTableInfo->lpDataInfo[i].dbIndex);
		else
			dbIndex = dbTableInfo->lpDataInfo[i].dbIndex;
		if (dbIndex == dwdbIndex)
		{
			*lpdbDataInfo = &dbTableInfo->lpDataInfo[i];
			return ERR_NONE;
		}
	}
	return ERR_OUT_RANGE;
}

DWORD _stdcall db_GetdbDataInfo(char* lpDataName,IDBClass* lpIdbClass,DBDATAINFO** lpdbDataInfo)
{
	WORD i;
	DBTABLEINFO* dbTableInfo;
	lpIdbClass->GetdbTableInfo(&dbTableInfo);
	for (i=0;i<dbTableInfo->dataCount;i++)
	{
		if (strcmp(dbTableInfo->lpDataInfo[i].name,lpDataName) == 0)
		{
			*lpdbDataInfo = &dbTableInfo->lpDataInfo[i];
			return ERR_NONE;
		}
	}
	return ERR_OUT_RANGE;
}

DWORD _stdcall db_GetGuiFromResource(char* lpzsRecourceName,DBGUI* lpdbGui)
{
	CdbGuiInfProcess dbGuiInfProcess;
	dbGuiInfProcess.SetGui(lpdbGui);
	dbGuiInfProcess.ProcessResource(lpzsRecourceName);
	return ERR_NONE;
}

DWORD _stdcall db_GetdbTableInfoFromResource(char* lpzsRecourceName,DBTABLEINFO* lpdbTableInfo)
{
	CdbDataInfoInfProcess dbDataInfoInfProcess;
	dbDataInfoInfProcess.SetdbTableInfo(lpdbTableInfo);
	dbDataInfoInfProcess.ProcessResource(lpzsRecourceName);
	return ERR_NONE;
}

DWORD _stdcall db_GetCtrlIndexFromID(DWORD dwId,DBGUI* lpdbGui,WORD* wIndex)
{
	WORD i;
	for (i=0;i<lpdbGui->ctrlCount;i++)
	{
		if (lpdbGui->ctrls[i].id == dwId)
		{
			*wIndex = i;
			return ERR_NONE;
		}
	}
	return ERR_NOTFOUND;
}

// Clases
CdbClass::CdbClass()
{
	m_pIdbDatabase = NULL;
}

CdbClass::~CdbClass()
{

}

DWORD _stdcall CdbClass::SetDatabase(IdbDatabase *lpIdbDatabase)
{
	m_pIdbDatabase = lpIdbDatabase;
	return 0;
}

DWORD _stdcall CdbClass::SetTableInfo(DBTABLEINFO *lpTableInfo)
{
	m_pdbTableInfo = lpTableInfo;
	return 0;
}

DWORD _stdcall CdbClass::GetItemSize(HDC hdc, ITEM_DATA *lpItemData)
{
	return ERR_INV_FUNC;
};

DWORD _stdcall CdbClass::GetItemText(ITEM_DATA *lpItemData)
{
	return ERR_INV_FUNC;
};

DWORD _stdcall CdbClass::GetSize(HDC hdc,void* lpvoid,WORD wdbIndex,DWORD dwRowIndex,WORD wColumnIndex,RECT* lprect)
{
	return ERR_INV_FUNC;
};

DWORD _stdcall CdbClass::Draw(HDC hdc,void* lpvoid,WORD wdbIndex,DWORD dwRowIndex,WORD wColumnIndex,RECT* lprect)
{
	return ERR_INV_FUNC;
};

DWORD _stdcall CdbClass::SetValue(WORD wdbIndex,_VARIANT* lpVariant)
{
	return ERR_INV_FUNC;
};

DWORD _stdcall CdbClass::GetValue(WORD wdbIndex,_VARIANT* lpVariant)
{
	return ERR_INV_FUNC;
};

DWORD _stdcall CdbClass::SetValue(WORD wdbIndex,HWND hControl)
{
	return ERR_INV_FUNC;
};

DWORD _stdcall CdbClass::GetValue(WORD wdbIndex, HWND hControl)
{
	return ERR_INV_FUNC;
};

DWORD _stdcall CdbClass::Clear()
{
	return ERR_INV_FUNC;
};

DWORD _stdcall CdbClass::GetIndexVisibility(DWORD dwdbIndex,BOOL* bShow)
{
	return ERR_INV_FUNC;
};

DWORD _stdcall CdbClass::GetRowVisibility(IDBArray* pIdbArray,DWORD dwRowIndex,BOOL* bShow)
{
	return ERR_INV_FUNC;
};

