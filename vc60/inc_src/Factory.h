// Factory.h: interface for the CFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FACTORY_H__F459DC30_EE7C_44F5_AB81_9F0754FEEB16__INCLUDED_)
#define AFX_FACTORY_H__F459DC30_EE7C_44F5_AB81_9F0754FEEB16__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "_IUnknown.h"

DWORD CreateInstance(char* lpDllName,char* lpInstanceName,_IUnknown** lpInstance);
DWORD DeleteInstance(_IUnknown* lpInstance);

#endif // !defined(AFX_FACTORY_H__F459DC30_EE7C_44F5_AB81_9F0754FEEB16__INCLUDED_)
