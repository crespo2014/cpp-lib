// bString.cpp: implementation of the CbString class.
//
//////////////////////////////////////////////////////////////////////

#include "bString.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CbString::CbString()
{
	m_str = NULL;
	m_len = 0;
}

CbString::~CbString()
{
	Release();
}

DWORD CbString::NewStr(WORD size)
{
	if (size < m_len) return ERR_OK;
	Release();
	m_str = new char[size+1];
	m_len = size;
	return ERR_OK;
}

char* CbString::GetStr()
{
	if (m_str == NULL) return "";
	return m_str;
}

DWORD CbString::SetStr(char *str)
{
	DWORD	len = strlen(str);
	if (NewStr(len) != ERR_OK) return ERR_FATAL;
	strcpy(m_str,str);
	return ERR_OK;
}

void CbString::Release()
{
	if (m_str != NULL) delete m_str;
	m_str = NULL;
	m_len = 0;
}

