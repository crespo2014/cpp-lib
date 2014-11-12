// LMem.cpp: implementation of the CLMem class.
//
//////////////////////////////////////////////////////////////////////

#include "LMem.h"
#include "logclient.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLMem::CLMem()
{
	m_ptr = NULL;
	m_mem_free = false;
	m_mem_size = 0;
	m_mem_fixed = true;
	m_str_type = TYPE_STR_NONE;
}

CLMem::~CLMem()
{
	Release();
}

DWORD CLMem::New(DWORD dwSize)
{
	if (m_ptr != NULL) Release();
	m_ptr = LocalAlloc(LMEM_FIXED,dwSize); if (m_ptr == NULL) return ERR_API;
	m_mem_free = true;
	m_mem_size = LocalSize(m_ptr);
	return ERR_OK;
}

void CLMem::Release()
{
	if (m_mem_free) LocalFree(m_ptr);
	m_mem_size = 0;
	m_mem_free = false;
	m_ptr = NULL;
}

void* CLMem::Detach()
{
	m_mem_free = false;
	m_mem_size = 0;
	return m_ptr;
}

DWORD CLMem::Set(char *cstr)
{
	// verificar el tipo de str que almacena para ver si se convierte o no
	int		len;
	DWORD	dwr;

	Release();
	if (cstr == NULL) return ERR_OK;
	len = strlen(cstr);
	if (m_str_type == TYPE_STR_UNICODE)
	{
		if (len == 0)
		{
			m_ustr = L"";
			m_mem_free = false;
			return ERR_OK;
		}
		len = MultiByteToWideChar(CP_ACP,0,cstr,-1,NULL,0);	if (len == 0)	return ERR_API;
		dwr = New(len+2); if (dwr != ERR_OK) return dwr;
		len = MultiByteToWideChar(CP_ACP,0,cstr,-1,m_ustr,m_mem_size);	if (len == 0)	return ERR_API;
		return ERR_OK;
	}
	m_str_type = TYPE_STR_CHAR;
	if (len == 0)
	{
		m_cstr = "";
		m_mem_free = false;
		return ERR_OK;
	}
	dwr = New(len+1); if (dwr != ERR_OK) return dwr;
	strcpy(m_cstr,cstr);	
	return ERR_OK;
}

DWORD CLMem::Set(void *vptr, DWORD size)
{
	DWORD	dwr;

	Release();
	if (vptr == NULL) return ERR_OK;
	dwr = New(size); if (dwr != ERR_OK) return dwr;
	m_str_type = TYPE_STR_NONE;
	memcpy(m_ptr,vptr,size);
	return ERR_OK;
}

DWORD CLMem::Attach(void *pvoid)
{
	Release();
	m_str_type = TYPE_STR_NONE;
	m_ptr = pvoid;
	m_mem_fixed = true;
	m_mem_free = true;
	m_mem_size = LocalSize(pvoid);
	return ERR_OK;
}

char* CLMem::GetCStr()
{
	switch (m_str_type)
	{
	//case TYPE_STR_NONE:
	case TYPE_STR_CHAR:	return m_cstr;
	default:
		return NULL;
	}
}

CLMem::CLMem(WORD wStrType)
{
	CLMem();
	m_str_type = wStrType;
}

unsigned short* CLMem::GetUStr()
{
	switch (m_str_type)
	{
	//case TYPE_STR_NONE:
	case TYPE_STR_UNICODE:	return m_ustr;
	default:
		return NULL;
	}
}

void CLMem::SetSType(WORD wStrType)
{
	Release();
	m_str_type = wStrType;
}

void CLMem::Clear()
{
	if ((m_ptr != NULL) && (m_mem_size != 0)) memset(m_ptr,0,m_mem_size);
}


DWORD CLMem::SetUStr(unsigned short *ustr, int ilength)
{
	DWORD	dwr;
	int		len;
	Release();
	if (ustr == NULL) return ERR_OK;
	if (ilength == -1) ilength = wcslen(ustr);
	if (m_str_type == TYPE_STR_UNICODE)
	{
		if (ilength == 0)
		{
			m_ustr = L"";
			m_mem_free = false;
			return ERR_OK;
		}
		dwr = New((ilength+1)*2); if (dwr != ERR_OK) return dwr;
		memcpy(m_ptr,ustr,(ilength+1)*2);
		m_ustr[ilength] = 0;
		return ERR_OK;
	}
	m_str_type = TYPE_STR_CHAR;
	if (ilength == 0) 
	{
		m_cstr = "";
		m_mem_free = false;
		return ERR_OK;
	}
	len = WideCharToMultiByte(CP_ACP,0,(LPCWSTR)ustr,ilength,NULL,0,NULL,NULL);if (len == 0)	return ERR_API;
	dwr = New(len+1); if (dwr != ERR_OK) return dwr;
	len = WideCharToMultiByte(CP_ACP,0,(LPCWSTR)ustr,ilength,m_cstr,len+1,NULL,NULL); if (len == 0) return ERR_API;
	m_cstr[ilength] = 0;
	return ERR_OK;
}
