// Hash.cpp: implementation of the CHash class.
//
//////////////////////////////////////////////////////////////////////

#include "Hash.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHash::CHash()
{
	m_hCryptProv = NULL;
	m_hash = NULL;	
}

CHash::~CHash()
{
	Release();
}

DWORD CHash::Hash_Data(const BYTE *buffer, DWORD size)
{
	char	*fnc_name = "CHash::Generate_SHA1";
	if (m_hash == NULL) return SetError(true,ERR_FATAL,"%s invalid handle",fnc_name);
	
	if(!CryptHashData(m_hash,buffer,size,0))
		return SetError_Add_W32_code_msg(true,ERR_FATAL,GetLastError(),"%s-->CryptHashData",fnc_name);
	return ERR_OK;
}

void CHash::Release()
{
	if (m_hash != NULL) CryptDestroyHash(m_hash);
	if (m_hCryptProv != NULL)  CryptReleaseContext(m_hCryptProv,0);
	m_hCryptProv = NULL;
	m_hash = NULL;
}

DWORD CHash::CreateHash(ALG_ID Algid)
{
	char	*fnc_name = "CHash::CreateHash";
	DWORD	dwr;
	Release();
	
	if(!CryptAcquireContext(&m_hCryptProv,"contendor",NULL,PROV_RSA_FULL,0))
	{
		dwr = GetLastError();
		SetError_Add_W32_code_msg(true,ERR_FATAL,dwr,"%s-->CryptAcquireContext",fnc_name);
		if (dwr == NTE_BAD_KEYSET)
		{
			if(!CryptAcquireContext(&m_hCryptProv,"contendor",NULL,PROV_RSA_FULL,CRYPT_NEWKEYSET)) 
				return SetError_Add_W32_code_msg(true,ERR_FATAL,GetLastError(),"%s-->CryptAcquireContext",fnc_name);
		}
		else
			return ERR_FATAL;
		
	}
	if(!CryptCreateHash(m_hCryptProv,Algid,0,0,&m_hash)) 
		return SetError_Add_W32_code_msg(true,ERR_FATAL,GetLastError(),"%s-->CryptCreateHash",fnc_name);
	return ERR_OK;

}

DWORD CHash::GetHash(BYTE *pdata, DWORD *pSize)
{
	char	*fnc_name = "CHash::GetHash";
	DWORD	size;
	if (m_hash == NULL) return SetError(true,ERR_FATAL,"%s invalid handle",fnc_name);
	if (!CryptGetHashParam(m_hash,HP_HASHVAL,NULL,&size,0))	
		return SetError_Add_W32_code_msg(true,ERR_FATAL,GetLastError(),"%s-->CryptGetHashParam",fnc_name);
	if (pdata == NULL)
	{
		*pSize = size;
		return ERR_OK;
	}
	if (*pSize < size) 
		return SetError(true,ERR_FATAL,"%s buffer to short most be %d bytes",fnc_name,size);
	if (!CryptGetHashParam(m_hash,HP_HASHVAL,pdata,pSize,0)) 	
		return SetError_Add_W32_code_msg(true,ERR_FATAL,GetLastError(),"%s-->CryptGetHashParam",fnc_name);
	return ERR_OK;
}
