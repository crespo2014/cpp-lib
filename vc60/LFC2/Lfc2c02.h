// lfc2c02.h: interface for the CShareSignalDevice class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LFC2C02_H__BE46B5C7_FDB5_11D4_8D3A_00D0093D4380__INCLUDED_)
#define AFX_LFC2C02_H__BE46B5C7_FDB5_11D4_8D3A_00D0093D4380__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "lfc2c01.h"

class CShareSignalDevice  
{
public:
	DWORD Create();
	DWORD Open();
	DWORD Release();
	DWORD Initialize();
	CSignalDevice* GetSignalDevice();
	CSignalDevice* lpSignalDevice;
	CShareSignalDevice();
	virtual ~CShareSignalDevice();
	HANDLE	hMapObject;
	BOOL	OnCreate;
};

#endif // !defined(AFX_LFC2C02_H__BE46B5C7_FDB5_11D4_8D3A_00D0093D4380__INCLUDED_)
