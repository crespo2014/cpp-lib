// Cliente.cpp: implementation of the CCliente class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Cliente.h"
#include "textildb.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCliente::CCliente()
{
	SetDatabase(&Textildb);
	SetTableInfo(&ClienteTI);
}

CCliente::~CCliente()
{

}

DWORD _stdcall CCliente::GetdbTableInfo(DBTABLEINFO** lpdbTableInfo)
{
	*lpdbTableInfo = &ClienteTI;
	return 0;
}

DWORD _stdcall CCliente::GetItemText(ITEM_DATA *lpItemData)
{
	return 0;
}

DWORD _stdcall CCliente::SetValue(WORD wdbIndex,_VARIANT* lpVariant)
{
	return 0;
}

DWORD _stdcall CCliente::GetValue(WORD wdbIndex,_VARIANT* lpVariant)
{
	return 0;
}

DWORD _stdcall CCliente::SetValue(WORD wdbIndex,HWND hControl)
{
	return 0;
}

DWORD _stdcall CCliente::Clear()
{
	return 0;
}

DWORD _stdcall CCliente::GetValue(WORD wdbIndex, HWND hControl)
{
	return 0;
}