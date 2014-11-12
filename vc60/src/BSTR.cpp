// BSTR.cpp: implementation of the CbBSTR class.
//
//////////////////////////////////////////////////////////////////////

#include "BSTR.h"

#define _FILENAME_ "bsrt.c"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CbBSTR::CbBSTR()
{
	m_bstr = NULL;
	m_bstr_size = 0;
}

CbBSTR::~CbBSTR()
{
	Release();
}

void CbBSTR::Attach(BSTR bstr)
{
	Release();
	m_bstr = bstr;
	m_bstr_size = SysStringLen(bstr);
}

BSTR CbBSTR::Dettach()
{
	BSTR	bstr = m_bstr;
	m_bstr = NULL;
	m_bstr_size = 0;	
	return bstr;
}

void CbBSTR::Release()
{
	SysFreeString(m_bstr);
	m_bstr = NULL;
	m_bstr_size = 0;
}

DWORD CbBSTR::GetCharString(char *cstr, WORD maxsize)
{
	int	i;
	cstr[0] = 0;
	if (m_bstr == NULL) return ERR_OK;
	if (m_bstr_size == 0) m_bstr_size = SysStringLen(m_bstr);
	if (m_bstr_size == 0) return ERR_OK;

	i = WideCharToMultiByte(CP_ACP,0,(LPCWSTR)m_bstr,m_bstr_size,cstr,maxsize,NULL,NULL);
	if ((i == 0) || (i ==  maxsize))
	{
		cstr[maxsize-1] = 0;
		return LOG_TERROR ERR_FATAL,"WideCharToMultiByte string has been truncate");
	}
	if (m_bstr_size != -1) cstr[i] = 0;	// si se especifica el tamaño del string entonces hay que poner el cero
	return ERR_OK;
}

char* CbBSTR::GetChar()
{
	GetCharString(SSIZE(m_cstr));
	return 	m_cstr;
}

DWORD CbBSTR::SetCharString(char *str)
{
	Release();
	//if (str[0] == 0) return NULL;
	int	i;
	int	len = strlen(str);
	m_bstr = SysAllocStringByteLen(NULL,(len)*2); if (m_bstr == NULL) return log_w32error GetLastError(),ERR_API,"SysAllocStringByteLen %d",len*2);
	m_bstr_size = len;
	i = MultiByteToWideChar(CP_ACP,0,str,len,m_bstr,len);
	if (i == len) return ERR_OK;
	Release();
	return log_w32error GetLastError(),ERR_API,"MultiByteToWideChar ");
}

CbBSTR::CbBSTR(char *cstr)
{
	CbBSTR();
	SetCharString(cstr);
}

CbBSTR::CbBSTR(WCHAR* wchar)
{
	CbBSTR();
	SetWCharString(wchar);
}

DWORD CbBSTR::SetWCharString(WCHAR *wchar)
{
	Release();
	m_bstr = SysAllocString(wchar);
	if (m_bstr == NULL) return log_w32error GetLastError(),ERR_API,"SysAllocString ");
	m_bstr_size = SysStringLen(m_bstr);
	return ERR_OK;
}

BSTR* CbBSTR::GetNewPtr()
{
	Release();
	return &m_bstr;
}

char* CbBSTR::toChar(LPWSTR str, DWORD cbMultiByte, IMem *mem)
{
	int size,ir;
	char	*pchar;
	if (!cbMultiByte) size = -1; else size = cbMultiByte;
	ir = WideCharToMultiByte(CP_ACP,0,str,size,NULL,0,NULL,NULL);
	if (mem->get(ir+1,(void**)&pchar) != ERR_OK) return NULL;
	ir = WideCharToMultiByte(CP_ACP,0,str,size,pchar,ir+1,NULL,NULL);
	return pchar;

}

LPWSTR CbBSTR::toUnicode(char *str, IMem *mem)
{
	int ir;
	LPWSTR	pchar;
	ir = MultiByteToWideChar(CP_ACP,0,str,-1,NULL,0);	//incluye el null cuando dice el tamaño
	if (mem->get(ir*2,(void**)&pchar) != ERR_OK) return NULL;
	ir = MultiByteToWideChar(CP_ACP,0,str,-1,pchar,ir*2);
	return pchar;

}

char* CbBSTR::getASCII(IMem* mem)
{
	int ir;
	char	*pchar;
	ir = WideCharToMultiByte(CP_ACP,0,m_bstr,m_bstr_size,NULL,0,NULL,NULL);
	if (mem->getU(ir+1,(void**)&pchar) != ERR_OK) return NULL;
	ir = WideCharToMultiByte(CP_ACP,0,m_bstr,m_bstr_size,pchar,ir+1,NULL,NULL);
	return pchar;
}

WCHAR* CbBSTR::getWCHAR(IMem *mem)
{
	return NULL;
	/*
	WCHAR	*str;
	if (mem->add(m_bstr,(m_bstr_size+1)*2
	if (mem->get(,&str)) != ERR_OK) return NULL;
	*/
}
