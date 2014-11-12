// Unknown.h: interface for the CUnknown class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UNKNOWN_H__5240117C_FF84_4B07_AFD8_88864D19DE4D__INCLUDED_)
#define AFX_UNKNOWN_H__5240117C_FF84_4B07_AFD8_88864D19DE4D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "_IUnknown.h"

class CUnknown : virtual public _IUnknown  
{
protected:
	virtual DWORD _stdcall QueryInterface(char* lpName,void** lpInterfaz);
	virtual DWORD _stdcall AddRef();
	virtual DWORD _stdcall Release();
	virtual DWORD _stdcall Initialize();
	virtual DWORD _stdcall GetInterfaz(char* lpName,void** lpInterfaz);
	virtual DWORD _stdcall DeleteObject();
	virtual DWORD _stdcall UnInitialize();
	CUnknown(BOOL bDynamic = FALSE);
private:
	BOOL	m_bDynamic;
	BOOL	m_bInitialize;
	DWORD	m_cRef;
};

#endif // !defined(AFX_UNKNOWN_H__5240117C_FF84_4B07_AFD8_88864D19DE4D__INCLUDED_)
