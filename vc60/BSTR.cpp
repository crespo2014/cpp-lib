// BSTR.cpp: implementation of the CbBSTR class.
//
//////////////////////////////////////////////////////////////////////

#include "BSTR.h"

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
		return SetError(true,ERR_FATAL,"CbBSTR::GetCharString ... WideCharToMultiByte string has been truncate");
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
	m_bstr = SysAllocStringByteLen(NULL,(len)*2); if (m_bstr == NULL) return SetError_Add_W32_code_msg(true,ERR_API,GetLastError(),"CbBSTR::SetCharString ... SysAllocStringByteLen ");
	m_bstr_size = len;
	i = MultiByteToWideChar(CP_ACP,0,str,len,m_bstr,len);
	if (i == len) return ERR_OK;
	Release();
	return SetError_Add_W32_code_msg(true,ERR_API,GetLastError(),"CbBSTR::SetCharString ... MultiByteToWideChar ");
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
	if (m_bstr == NULL) return SetError_Add_W32_code_msg(true,ERR_API,GetLastError(),"CbBSTR::SetWCharString->SysAllocString ");
	m_bstr_size = SysStringLen(m_bstr);
	return ERR_OK;
}

BSTR* CbBSTR::GetNewPtr()
{
	Release();
	return &m_bstr;
}
