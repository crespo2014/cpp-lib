// X509Cert.h: interface for the CX509Cert class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_X509CERT_H__BAF2C5C3_19F8_4B49_8169_D8C1CE0212DC__INCLUDED_)
#define AFX_X509CERT_H__BAF2C5C3_19F8_4B49_8169_D8C1CE0212DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*
	Include library for windows are 
	Crypt32.lib
	Incluir la _Crypt32.lib de inc_src\sdk\lib para poder utilizar las nuevas funciones de la ask VS8.0
*/

#include "bObject.h"

#ifndef _WIN32_WINNT			// Permit use of features specific to Windows NT 4.0 or later.
#define _WIN32_WINNT 0x0400		// Change this to the appropriate value to target 
#endif	

#undef __WINCRYPT_H__ 

#if _MSC_VER > 1200 
	#include "Wincrypt.h"
#else
	#include "sdk\Wincrypt.h"
#endif

class CX509Cert : public CbObject  
{
public:
	DATA_BLOB* lookExtension(char *oid);
	DWORD getSubjectAlternateName();
	DWORD DecodeObject(LPCSTR lpszStructType,const BYTE *pbEncoded,DWORD cbEncoded, DWORD dwFlags, void *pvStructInfo,  DWORD *pcbStructInfo);
	DWORD getNameString(DWORD dwType,DWORD dwFlags,void *pvTypePara,LPTSTR pszNameString,DWORD *cchNameString);
	DWORD getKeyUsage(BYTE *pkeyusage);
	DWORD GetIntendedKeyUsage(BYTE *pbKeyUsage,DWORD cbKeyUsage);
	DWORD getEncodingType()	{ return (m_context != NULL)?m_context->dwCertEncodingType:NULL;	};
	PCCERT_CONTEXT Detach();
	void Attach(PCCERT_CONTEXT pcontext);
	DWORD OID_Get(char* oid,char* val, DWORD* size);
	DWORD Get_CertInfo(CERT_INFO **cert_info);
	DWORD Context_Get(PCERT_CONTEXT *pcontext);
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
	PCCERT_CONTEXT	getContext() {	return m_context;	};
	BOOL			IsValid()	 {	return (m_context != NULL); };				

private:
	PCCERT_CONTEXT	m_context;

};

#endif // !defined(AFX_X509CERT_H__BAF2C5C3_19F8_4B49_8169_D8C1CE0212DC__INCLUDED_)
