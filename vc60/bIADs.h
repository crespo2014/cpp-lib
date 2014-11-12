// bIADs.h: interface for the CbIADs class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BIADS_H__A1065812_4C26_4643_ABB0_C10601E86AE1__INCLUDED_)
#define AFX_BIADS_H__A1065812_4C26_4643_ABB0_C10601E86AE1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bObject.h"
#include <objbase.h>
#include <activeds.h>
#include <Adshlp.h>		//incluir el ActiveDS.lib y adsiid.lib
#include "bobject.h"

class CbIADs  : public CbObject
{
public:
	DWORD Get(BSTR prop,VARIANT* pvProp);
	void Attach(IADs *piads);
	DWORD QueryInterfaz(IADs *piads,REFIID riid,VOID** ppObject);
	DWORD GetObject(LPWSTR PathName,REFIID riid, VOID** ppObject);
	DWORD SetError_Add_iads_code_msg(HRESULT hr, char *format,...);
	DWORD OpenObject(LPWSTR lpszPathName, LPWSTR lpszUserName,LPWSTR lpszPassword, DWORD dwReserved, REFIID riid, VOID** ppObject);
	void Release();
	CbIADs();
	virtual ~CbIADs();

private:
	IADs *m_iads;

};

#endif // !defined(AFX_BIADS_H__A1065812_4C26_4643_ABB0_C10601E86AE1__INCLUDED_)
