// Unknown.cpp: implementation of the CUnknown class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Unknown.h"
#include "common.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUnknown::CUnknown(BOOL bDynamic)
{
	m_bDynamic = bDynamic;
	m_bInitialize = false;
	m_cRef = 0;
}

DWORD _stdcall CUnknown::QueryInterface(char *lpName, void **lpInterfaz)
{
	DWORD dr;
	dr = GetInterfaz(lpName,lpInterfaz);
	if (dr == 0) AddRef();
	return dr;
}

DWORD _stdcall CUnknown::Initialize()
{
	return 0;
}

DWORD _stdcall CUnknown::Release()
{
	if(!m_bDynamic) return ERR_INV_FUNC;	// esta clase es una instancia
	if (InterlockedDecrement((long*)&m_cRef) == 0) 
	{
		UnInitialize();
		if (m_bDynamic) DeleteObject();
		return 0;
	}
	return m_cRef;
}

DWORD _stdcall CUnknown::AddRef()
{
	InterlockedIncrement((long*)&m_cRef);
	return 0;
}

DWORD _stdcall CUnknown::GetInterfaz(char* lpName,void** lpInterfaz)
{
	return ERR_INV_FUNC;
}

DWORD _stdcall CUnknown::DeleteObject()
{
	return 0;
}

DWORD _stdcall CUnknown::UnInitialize()
{
	return 0;
}