// X509Cert.h: interface for the CX509Cert class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_X509CERT_H__BAF2C5C3_19F8_4B49_8169_D8C1CE0212DC__INCLUDED_)
#define AFX_X509CERT_H__BAF2C5C3_19F8_4B49_8169_D8C1CE0212DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bObject.h"

#ifndef _WIN32_WINNT	// Permit use of features specific to Windows NT 4.0 or later.
#define _WIN32_WINNT 0x0400	// Change this to the appropriate value to target 
#endif	

#undef __WINCRYPT_H__ 

#include <Wincrypt.h>

class CX509Cert : public CbObject  
{
public:
	DWORD OID_Get(char* oid,char* val, DWORD* size);
	DWORD Get_CertInfo(CERT_INFO **cert_info);
	DWORD Context_Get(CERT_CONTEXT **pcontext);
	DWORD Load_File(const char* file_name);
	DWORD Extension_Get(char* oid,char *ext_str, DWORD *maxsize,DWORD strType = CERT_X500_NAME_STR);
	DWORD Extension_ByIndex(WORD eindex,char **oid,DATA_BLOB **ppData);
	DWORD Extension_ByOID(char* oid,DATA_BLOB** ppData);
	DWORD Test();
	DWORD GetSubject(char *subject, DWORD* maxsize,DWORD strType = CERT_X500_NAME_STR);
	DWORD GetIssuer(char* issuer,DWORD* maxsize,DWORD strType = CERT_X500_NAME_STR);	// set issuer = null to get size 
	void Release();
	DWORD Set(BYTE* cert_buffer,DWORD size);
	CX509Cert();
	virtual ~CX509Cert();

private:
	PCCERT_CONTEXT	m_context;

};

#endif // !defined(AFX_X509CERT_H__BAF2C5C3_19F8_4B49_8169_D8C1CE0212DC__INCLUDED_)
