// IUnknow.h: interface for the IUnknown class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IUNKNOW_H__8A25A337_736D_448E_9A46_B3DD966441BF__INCLUDED_)
#define AFX_IUNKNOW_H__8A25A337_736D_448E_9A46_B3DD966441BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class _IUnknown   
{
public:
	virtual DWORD _stdcall QueryInterface(char* lpName,void** lpInterfaz)=0;
	virtual DWORD _stdcall AddRef()=0;
	virtual DWORD _stdcall Release()=0;
	virtual DWORD _stdcall Initialize()=0;
	virtual DWORD _stdcall GetInterfaz(char* lpName,void** lpInterfaz)=0;
	virtual DWORD _stdcall UnInitialize()=0;
};

#endif // !defined(AFX_IUNKNOW_H__8A25A337_736D_448E_9A46_B3DD966441BF__INCLUDED_)
