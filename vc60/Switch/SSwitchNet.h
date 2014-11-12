// SSwitchNet.h: interface for the CSSwitchNet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SSWITCHNET_H__BD954C07_D0ED_4A2C_99DC_F13530F7BDD1__INCLUDED_)
#define AFX_SSWITCHNET_H__BD954C07_D0ED_4A2C_99DC_F13530F7BDD1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Unknown.h"
#include "ISerialBus.h"

class CSSwitchNet : private CUnknown,
					private ISSwitchNet  
{
	virtual DWORD _stdcall QueryInterface(char* lpName,void** lpInterfaz)	{return CUnknown::QueryInterface(lpName,lpInterfaz);}
	virtual DWORD _stdcall AddRef()											{return CUnknown::AddRef();}
	virtual DWORD _stdcall Release()										{return CUnknown::Release();}
	virtual DWORD _stdcall Initialize()										{return CUnknown::Initialize();}
	virtual DWORD _stdcall GetInterfaz(char* lpName,void** lpInterfaz)		{return CUnknown::GetInterfaz(lpName,lpInterfaz);}
	virtual DWORD _stdcall DeleteObject()									{return CUnknown::DeleteObject();}
	virtual DWORD _stdcall UnInitialize()									{return CUnknown::UnInitialize();}
public:
	CSSwitchNet(BOOL bDynamic = FALSE);
	virtual ~CSSwitchNet();

};

#endif // !defined(AFX_SSWITCHNET_H__BD954C07_D0ED_4A2C_99DC_F13530F7BDD1__INCLUDED_)
