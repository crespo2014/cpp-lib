// X509Cert.cpp: implementation of the CX509Cert class.
//
//////////////////////////////////////////////////////////////////////

#include "X509Cert.h"
#include "string.h"
#include "mempage.h"
#include "dnparse.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CX509Cert::CX509Cert()
{
	m_context = NULL;
	m_ver = "Class CX509Cert " CLASS_VER;
}

CX509Cert::~CX509Cert()
{
	Release();
}

DWORD CX509Cert::Set(BYTE *cert_buffer, DWORD size)
{
	char	*fnc_name = "CX509Cert::Set";
	Release();
	if ((size == 0) || (cert_buffer == NULL)) return LOG_TERROR ERR_FATAL,"Invalid Certificate buffer");
	m_context = CertCreateCertificateContext(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,cert_buffer,size);
	if (m_context == NULL) return LOG_TW32_ERROR  GetLastError(),ERR_API,"CertCreateCertificateContext ");
	return ERR_OK;
}

void CX509Cert::Release()
{
	if (m_context != NULL) CertFreeCertificateContext(m_context);
	m_context = NULL;
}

DWORD CX509Cert::GetIssuer(char *issuer, DWORD* maxsize,DWORD strType)
{
	char	*fnc_name = "CX509Cert::GetIssuer";
	DWORD	len;

	if (m_context == NULL) return LOG_TERROR ERR_HANDLE,"Invalid handle");
	len = CertNameToStr(m_context->dwCertEncodingType,&(m_context->pCertInfo->Issuer),strType,NULL, 0); 
	if (issuer == NULL)
	{
		*maxsize = len;
		return ERR_OK;
	}
	if (len + 1 > *maxsize) return LOG_TERROR ERR_HANDLE,"Buffer to short need %d bytes",len+1);
	len = CertNameToStr(m_context->dwCertEncodingType,&(m_context->pCertInfo->Issuer),strType,issuer,*maxsize);
	if (len == 0) 
		return LOG_TW32_ERROR  GetLastError(),ERR_API,"CertNameToStr");

	return ERR_OK;
}

DWORD CX509Cert::GetSubject(char *subject, DWORD *maxsize,DWORD strType)
{
	char	*fnc_name = "CX509Cert::GetSubject";
	DWORD	len;

	if (m_context == NULL) return LOG_TERROR ERR_HANDLE,"Invalid handle");
	len = CertNameToStr(m_context->dwCertEncodingType,&(m_context->pCertInfo->Subject),strType,NULL, 0); 
	if (subject == NULL)
	{
		*maxsize = len;
		return ERR_OK;
	}
	if (len + 1 > *maxsize) return LOG_TERROR ERR_HANDLE,"Buffer to short need %d bytes",len+1);
	len = CertNameToStr(m_context->dwCertEncodingType,&(m_context->pCertInfo->Subject),strType,subject,*maxsize);
	if (len == 0) 
		return LOG_TW32_ERROR GetLastError(),ERR_API,"CertNameToStr ... failed ");

	return ERR_OK;
}

DWORD CX509Cert::Test()
{
	char	text[1024];
	DWORD	len;
	
	len = CertNameToStr(m_context->dwCertEncodingType,&(m_context->pCertInfo->Subject),CERT_SIMPLE_NAME_STR/*CERT_X500_NAME_STR*/,text,sizeof(text));

	return ERR_OK;
}

DWORD CX509Cert::Extension_ByOID(char *oid, DATA_BLOB **ppData)
{
	char	*fnc_name = "CX509Cert::Extension_ByOID";
	DWORD		i;
	PCERT_EXTENSION	p;

	if (m_context == NULL) return LOG_TERROR ERR_HANDLE,"Invalid handle");

	p = m_context->pCertInfo->rgExtension;
	for (i=0;i<m_context->pCertInfo->cExtension;i++,p++)
	{
		//p = &(m_context->pCertInfo->rgExtension[i]);
		if (stricmp(oid,p->pszObjId) == 0)
		{
			*ppData = &p->Value;
			return ERR_OK;
		}
	}
	return LOG_TERROR ERR_FATAL,"Extension with oid = %s not found",oid);
}

DWORD CX509Cert::Extension_ByIndex(WORD eindex,char **oid,DATA_BLOB **ppData)
{
	char	*fnc_name = "CX509Cert::Extension_ByIndex";
	
	if (m_context == NULL) return LOG_TERROR ERR_HANDLE,"%s failed .. Invalid handle",fnc_name);
	if (eindex >= m_context->pCertInfo->cExtension) return LOG_TERROR ERR_FATAL,"Index %d out of bound",eindex);
	*ppData = &(m_context->pCertInfo->rgExtension[eindex].Value);
	*oid = m_context->pCertInfo->rgExtension[eindex].pszObjId;
	return ERR_OK;
}

DWORD CX509Cert::Extension_Get(char* oid,char *ext_str, DWORD *maxsize, DWORD strType)
{
	char	*fnc_name = "CX509Cert::Extension_Get";
	DWORD	len;
	DATA_BLOB *pData;
	if (Extension_ByOID(oid,&pData) != ERR_OK) return LOG_TSTACK;
	/*
	len = CertNameToStr(m_context->dwCertEncodingType,pData,strType,NULL,*maxsize);
	if (ext_str == NULL)
	{
		*maxsize = len;
		return ERR_OK;
	}
	if (len + 1 > *maxsize) return LOG_TERROR true,ERR_HANDLE,"%s failed .. Buffer to short need %d bytes",fnc_name,len+1);
	*/
	len = CertNameToStr(m_context->dwCertEncodingType,pData,strType,ext_str,*maxsize);
	if (len == 0) 
		return LOG_TW32_ERROR GetLastError(),ERR_API,"CertNameToStr");
	return ERR_OK;
}

DWORD CX509Cert::Load_File(const char *file_name)
{
	CMemPage	file;
	char	*fnc_name = "CX509Cert::Load_File";
	file.SetLog(GetLog());
	if (file.LoadFile(file_name) != ERR_OK) return LOG_TSTACK;
	return Set((BYTE*)file.GetPage(),file.GetSize());
}

DWORD CX509Cert::Context_Get(PCERT_CONTEXT *pcontext)
{
	char	*fnc_name = "CX509Cert::Context_Get";
	if (m_context == NULL) return LOG_TERROR ERR_HANDLE,"Invalid handle");
	*pcontext = (PCERT_CONTEXT)m_context;
	return ERR_OK;
}

DWORD CX509Cert::Get_CertInfo(CERT_INFO **cert_info)
{
	char	*fnc_name = "CX509Cert::Get_CertInfo";
	if (m_context == NULL) return LOG_TERROR ERR_HANDLE,"Invalid handle");
	*cert_info = m_context->pCertInfo;
	return ERR_OK;
}

/*
	El primer caracter indica de donde tomar el OID S - Subject, I - Issuer, E - Extension
*/
DWORD CX509Cert::OID_Get(char *oid, char *val, DWORD *size)
{
	char	*fnc_name = "CX509Cert::OID_Get";
	char	*cptr;
	char	str[1025];
	DWORD	len;
	CDNParse	parse;

	//Func_Start(fnc_name);
	if (val != NULL) *val = 0;	//dejar limpia la cadena
	cptr = oid+1;
	switch (oid[0])
	{
	case 'S':
		{
			len = sizeof(str);
			if (GetSubject(str,&len,CERT_OID_NAME_STR)	!= ERR_OK) return LOG_TSTACK;
			if (parse.Parse_String(str)					!= ERR_OK) return LOG_TSTACK;
			if (parse.Key_Look(cptr,&cptr)				!= ERR_OK) return LOG_TSTACK;
			len = strlen(cptr);
			if (val == NULL)
			{
				*size = len + 1;
				break;
			}
			if (*size < len + 1) return LOG_TERROR ERR_HANDLE,"Buffer to short need %d bytes",len+1);
			strcpy(val,cptr);
			*size = len;
			break;
		}
	case 'O':
	case 'E': return Extension_Get(cptr,val,size);
	case 'I':
		{
			len = sizeof(str);
			if (GetIssuer(str,&len,CERT_OID_NAME_STR)	!= ERR_OK) return LOG_TSTACK;
			if (parse.Parse_String(str)					!= ERR_OK) return LOG_TSTACK;
			if (parse.Key_Look(cptr,&cptr)				!= ERR_OK) return LOG_TSTACK;
			len = strlen(cptr);
			if (val == NULL)
			{
				*size = len + 1;
				break;
			}
			if (*size < len + 1) return LOG_TERROR ERR_HANDLE,"Buffer to short need %d bytes",len+1);
			strcpy(val,cptr);
			*size = len;
			break;
		}
	default:
		return LOG_TERROR ERR_FATAL,"Invalid cert oid '%s'",oid);
	}
	return ERR_OK;

}

void CX509Cert::Attach(PCCERT_CONTEXT pcontext)
{
	char	*fnc_name = "CX509Cert::Attach";
	FNC_START
	if (m_context != NULL) Release();
	m_context = pcontext;	
}

PCCERT_CONTEXT CX509Cert::Detach()
{
	char	*fnc_name = "CX509Cert::Detach";
	PCCERT_CONTEXT	pcontext;
	FNC_START
	pcontext = m_context;
	m_context = NULL;
	return pcontext;
}


DWORD CX509Cert::GetIntendedKeyUsage(BYTE *pbKeyUsage, DWORD cbKeyUsage)
{
	char	*fnc_name = "CX509Cert::GetIntendedKeyUsage";
	if (m_context == NULL) {
		return LOG_TERROR ERR_HANDLE,"Invalid handle");
	}
	CertGetIntendedKeyUsage(X509_ASN_ENCODING|PKCS_7_ASN_ENCODING,m_context->pCertInfo,pbKeyUsage,cbKeyUsage);
	return ERR_OK;
}

DWORD CX509Cert::getKeyUsage(BYTE *pkeyusage)
{
	char	*fnc_name = "CX509Cert::GetIntendedKeyUsage";
	if (m_context == NULL) {
		return LOG_TERROR ERR_HANDLE,"Invalid handle");
	}
	*pkeyusage = CERT_DATA_ENCIPHERMENT_KEY_USAGE | CERT_DIGITAL_SIGNATURE_KEY_USAGE | 
				CERT_KEY_AGREEMENT_KEY_USAGE	  | CERT_KEY_CERT_SIGN_KEY_USAGE |
				CERT_KEY_ENCIPHERMENT_KEY_USAGE   | CERT_NON_REPUDIATION_KEY_USAGE |
				CERT_OFFLINE_CRL_SIGN_KEY_USAGE;
	CertGetIntendedKeyUsage(X509_ASN_ENCODING|PKCS_7_ASN_ENCODING,m_context->pCertInfo,pkeyusage,1);
	return ERR_OK;

}

DWORD CX509Cert::getNameString(DWORD dwType, DWORD dwFlags, void *pvTypePara, LPTSTR pszNameString, DWORD *cchNameString)
{
	char 	*fnc_name = "CX509Cert::GetNameString";
	DWORD	dwr;
	if (m_context == NULL) return LOG_TERROR ERR_HANDLE,"Invalid handle");

	dwr = CertGetNameString(m_context,dwType,dwFlags,pvTypePara,pszNameString,*cchNameString);
	*cchNameString = dwr;
	return ERR_FATAL;
}

DWORD CX509Cert::DecodeObject(LPCSTR lpszStructType, const BYTE *pbEncoded, DWORD cbEncoded, DWORD dwFlags, void *pvStructInfo, DWORD *pcbStructInfo)
{
	char	*fnc_name = "CX509Cert::DecodeObject";
	if (CryptDecodeObject(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,lpszStructType,pbEncoded,
						cbEncoded,dwFlags,pvStructInfo,pcbStructInfo)) return ERR_OK;
	return LOG_TW32_ERROR GetLastError(),ERR_API,"CryptDecodeObject ");
}

/*
DWORD CX509Cert::getSubjectAlternateName(CERT_ALT_NAME_INFO *pInfo,DWORD *size)
{
	char	*fnc_name = "CX509Cert::getSubjectAlternateName";
	DATA_BLOB *pData;
	pData = lookExtension("2.5.29.17");
	if (pData == NULL) return LOG_TERROR ERR_FATAL,"Extension with oid = %s not found",oid);

	if (!CryptDecodeObject(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,szOID_SUBJECT_ALT_NAME,pData->pbData,
						pData->cbData,CRYPT_UNICODE_NAME_DECODE_DISABLE_IE4_UTF8_FLAG,
						pInfo,size))
	{
		return LOG_TW32_ERROR GetLastError(),ERR_API,"CryptDecodeObject ");
	}
	return ERR_OK;
}
*/

DATA_BLOB* CX509Cert::lookExtension(char *oid)
{
	char	*fnc_name = "CX509Cert::lookExtension";
	DWORD		i;
	PCERT_EXTENSION	p;

	if (m_context == NULL) 
	{
		LOG_TERROR ERR_HANDLE,"Invalid handle");
		return NULL;
	}

	p = m_context->pCertInfo->rgExtension;
	for (i=0;i<m_context->pCertInfo->cExtension;i++,p++)
	{
		//p = &(m_context->pCertInfo->rgExtension[i]);
		if (stricmp(oid,p->pszObjId) == 0)
		{
			return &p->Value;
		}
	}
	return NULL;
}
