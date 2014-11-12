// bObject.cpp: implementation of the CbObject class.
//
//////////////////////////////////////////////////////////////////////

#include "bObject.h"

#define _FILENAME_ "bObject.c"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CbObject::CbObject()
{
	Init();
}

CbObject::~CbObject()
{
	bconstructed = false;
}

void CbObject::Clone(CbObject *pObject,WORD size)
{
	memcpy(this,pObject,size);
	bcloned = true;
	threadid = GetCurrentThreadId();
}

void CbObject::ptr_Adjust(BYTE *base1, BYTE *base2, BYTE *ptr1, BYTE **ptr2)
{
	if (ptr1 == NULL) { *ptr2 = NULL; return;}
	*ptr2 = base2 + (ptr1 - base1);
}

void CbObject::str_ptr_Adjust(char *base1, char *base2, char *ptr1, char **ptr2)
{
	if (ptr1 == NULL)	{ *ptr2 = NULL; return; }
	if (*ptr1 == 0)		{ *ptr2 = "";	return; }
	*ptr2 = base2 + (ptr1 - base1);
}

void CbObject::Release()
{
	Init();
}

void CbObject::Init()
{
	m_ver = "Class CbObject " CLASS_VER;
	m_plog = CLogClient::get();
	bconstructed = true;
	bcloned = false;
	threadid = GetCurrentThreadId();
}

WORD CbObject::strlen_cmp(const char *str1, WORD len, const char *str2)
{
	while (len>0)
	{
		if (*str2 == 0) return 1;
		if (*str1 != *str2) return 1;
		str1++;
		str2++;
		len--;
	}
	if (*str2 != 0) return 1;
	return 0;
}

WORD CbObject::strlen_icmp(const char *str1, WORD len, const char *str2)
{
	char	c1,c2;
	while (len>0)
	{
		c1 = *str1;
		c2 = *str2;
		if (c2 == 0) return 1;
		if ((c1 >= 'A') && (c1 <= 'Z')) 
			c1 = c1 - ('A' + 'a');
		else
			if (c1 == 'Ñ') c1 = 'ñ';
		//
		if ((c2 >= 'A') && (c2 <= 'Z')) 
			c2 = c2 - ('A' + 'a');
		else
			if (c2 == 'Ñ') c2 = 'ñ';

		if (c1 != c2) return 1;
		str1++;
		str2++;
		len--;
	}
	if (*str2 != 0) return 1;
	return 0;
}

DWORD CbObject::clen(char *str)
{
	DWORD len=0;
	while (*(str++)) len++;
	return len;
}

DWORD CbObject::wclen(WCHAR *wc)
{
	DWORD len=0;
	while (*(wc++)) len++;
	return len;
}
