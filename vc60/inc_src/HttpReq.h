// HttpReq.h: interface for the CHttpReq class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HTTPREQ_H__FC61F868_7772_4459_8E27_2F1FC4834ACE__INCLUDED_)
#define AFX_HTTPREQ_H__FC61F868_7772_4459_8E27_2F1FC4834ACE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bObject.h"

class CHttpReq : public CbObject
{
public:
	DWORD Connect(WCHAR* agent,WCHAR* proxy,WCHAR* server,WORD port);
	CHttpReq();
	virtual ~CHttpReq();

private:
	WCHAR	*mAgent;
	WCHAR	*mProtocol;
	WCHAR	*mProxy;
	WCHAR	*mLanguage;

};

#endif // !defined(AFX_HTTPREQ_H__FC61F868_7772_4459_8E27_2F1FC4834ACE__INCLUDED_)
