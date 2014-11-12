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
	m_context = CertCreateCertificateContext(X509_ASN_ENCODING,cert_buffer,size);
	if (m_context == NULL) return SetError_Add_W32_code_msg(true,ERR_API,GetLastError(),"%s CertCreateCertificateContext ... failed ",fnc_name);
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

	if (m_context == NULL) return SetError(true,ERR_HANDLE,"%s failed .. Invalid handle",fnc_name);
	len = CertNameToStr(m_context->dwCertEncodingType,&(m_context->pCertInfo->Issuer),strType,NULL, 0); 
	if (issuer == NULL)
	{
		*maxsize = len;
		return ERR_OK;
	}
	if (len + 1 > *maxsize) return SetError(true,ERR_HANDLE,"%s failed .. Buffer to short need %d bytes",fnc_name,len+1);
	len = CertNameToStr(m_context->dwCertEncodingType,&(m_context->pCertInfo->Issuer),strType,issuer,*maxsize);
	if (len == 0) 
		return SetError_Add_W32_code_msg(true,ERR_API,GetLastError(),"%s CertNameToStr ... failed ",fnc_name);

	return ERR_OK;
}

DWORD CX509Cert::GetSubject(char *subject, DWORD *maxsize,DWORD strType)
{
	char	*fnc_name = "CX509Cert::GetSubject";
	DWORD	len;

	if (m_context == NULL) return SetError(true,ERR_HANDLE,"%s failed .. Invalid handle",fnc_name);
	len = CertNameToStr(m_context->dwCertEncodingType,&(m_context->pCertInfo->Subject),strType,NULL, 0); 
	if (subject == NULL)
	{
		*maxsize = len;
		return ERR_OK;
	}
	if (len + 1 > *maxsize) return SetError(true,ERR_HANDLE,"%s failed .. Buffer to short need %d bytes",fnc_name,len+1);
	len = CertNameToStr(m_context->dwCertEncodingType,&(m_context->pCertInfo->Subject),strType,subject,*maxsize);
	if (len == 0) 
		return SetError_Add_W32_code_msg(true,ERR_API,GetLastError(),"%s CertNameToStr ... failed ",fnc_name);

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

	if (m_context == NULL) return SetError(true,ERR_HANDLE,"%s failed .. Invalid handle",fnc_name);

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
	return SetError(true,ERR_FATAL,"%s Extension with oid = %s not found",fnc_name,oid);
}

DWORD CX509Cert::Extension_ByIndex(WORD eindex,char **oid,DATA_BLOB **ppData)
{
	char	*fnc_name = "CX509Cert::Extension_ByIndex";
	
	if (m_context == NULL) return SetError(true,ERR_HANDLE,"%s failed .. Invalid handle",fnc_name);
	if (eindex >= m_context->pCertInfo->cExtension) return SetError(true,ERR_FATAL,"%s Index %d out of bound",fnc_name,eindex);
	*ppData = &(m_context->pCertInfo->rgExtension[eindex].Value);
	*oid = m_context->pCertInfo->rgExtension[eindex].pszObjId;
	return ERR_OK;
}

DWORD CX509Cert::Extension_Get(char* oid,char *ext_str, DWORD *maxsize, DWORD strType)
{
	char	*fnc_name = "CX509Cert::Extension_Get";
	DWORD	len;
	DATA_BLOB *pData;
	if (Extension_ByOID(oid,&pData) != ERR_OK) return ERR_FATAL;
	/*
	len = CertNameToStr(m_context->dwCertEncodingType,pData,strType,NULL,*maxsize);
	if (ext_str == NULL)
	{
		*maxsize = len;
		return ERR_OK;
	}
	if (len + 1 > *maxsize) return SetError(true,ERR_HANDLE,"%s failed .. Buffer to short need %d bytes",fnc_name,len+1);
	*/
	len = CertNameToStr(m_context->dwCertEncodingType,pData,strType,ext_str,*maxsize);
	if (len == 0) 
		return SetError_Add_W32_code_msg(true,ERR_API,GetLastError(),"%s CertNameToStr ... failed ",fnc_name);
	return ERR_OK;
}

DWORD CX509Cert::Load_File(const char *file_name)
{
	CMemPage	file;
	char	*fnc_name = "CX509Cert::Load_File";
	file.SetLog(GetLog());
	if (file.LoadFile(file_name) != ERR_OK) return SetError(true,ERR_FATAL,"%s-->%s",fnc_name,file.GetErrorMsg());
	return Set((BYTE*)file.GetPage(),file.GetSize());
}

DWORD CX509Cert::Context_Get(PCERT_CONTEXT *pcontext)
{
	char	*fnc_name = "CX509Cert::Context_Get";
	if (m_context == NULL) return SetError(true,ERR_HANDLE,"%s failed .. Invalid handle",fnc_name);
	*pcontext = (PCERT_CONTEXT)m_context;
	return ERR_OK;
}

DWORD CX509Cert::Get_CertInfo(CERT_INFO **cert_info)
{
	char	*fnc_name = "CX509Cert::Get_CertInfo";
	if (m_context == NULL) return SetError(true,ERR_HANDLE,"%s failed .. Invalid handle",fnc_name);
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
			if (GetSubject(str,&len,CERT_OID_NAME_STR) != ERR_OK) return ERR_FATAL;
			if (parse.Parse_String(str) != ERR_OK) return SetError(false,ERR_FATAL,"%s-->%s",fnc_name,parse.GetErrorMsg());
			if (parse.Key_Look(cptr,&cptr) != ERR_OK) return SetError(false,ERR_FATAL,"%s-->%s",fnc_name,parse.GetErrorMsg());
			len = strlen(cptr);
			if (val == NULL)
			{
				*size = len + 1;
				break;
			}
			if (*size < len + 1) return SetError(true,ERR_HANDLE,"%s failed .. Buffer to short need %d bytes",fnc_name,len+1);
			strcpy(val,cptr);
			*size = len;
			break;
		}
	case 'O':
	case 'E': return Extension_Get(cptr,val,size);
	case 'I':
		{
			len = sizeof(str);
			if (GetIssuer(str,&len,CERT_OID_NAME_STR) != ERR_OK) return ERR_FATAL;
			if (parse.Parse_String(str) != ERR_OK) return SetError(false,ERR_FATAL,"%s-->%s",fnc_name,parse.GetErrorMsg());
			if (parse.Key_Look(cptr,&cptr) != ERR_OK) return SetError(false,ERR_FATAL,"%s-->%s",fnc_name,parse.GetErrorMsg());
			len = strlen(cptr);
			if (val == NULL)
			{
				*size = len + 1;
				break;
			}
			if (*size < len + 1) return SetError(true,ERR_HANDLE,"%s failed .. Buffer to short need %d bytes",fnc_name,len+1);
			strcpy(val,cptr);
			*size = len;
			break;
		}
	default:
		return SetError(true,ERR_FATAL,"%s invalid cert oid '%s'",fnc_name,oid);
	}
	return ERR_OK;

}
