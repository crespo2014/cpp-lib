// LMem.h: interface for the CLMem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LMEM_H__FABFC504_6CB5_45EC_8DA2_7C69CDB8991D__INCLUDED_)
#define AFX_LMEM_H__FABFC504_6CB5_45EC_8DA2_7C69CDB8991D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define TYPE_STR_NONE		0
#define TYPE_STR_CHAR		1
#define TYPE_STR_UCHAR		2
#define TYPE_STR_UNICODE	3

#include "windows.h"

class CLMem 
{
public:
	DWORD SetUStr(unsigned short *ustr,int ilength = -1);
	DWORD GetSize() { return m_mem_size; };
	void *GetPtr() { return m_ptr; };
	void Clear();
	void SetSType(WORD wStrType);
	unsigned short* GetUStr();
	char* GetCStr();
	
	CLMem(WORD wStrType);
	DWORD Attach(void* pvoid);
	DWORD Set(void* pvoid,DWORD size);
	DWORD Set(char* cstr);
	void* Detach();
	void Release();
	DWORD New(DWORD dwSize);
	CLMem();
	virtual ~CLMem();
private:
	union
	{
		void*	m_ptr;
		char*	m_cstr;
		unsigned char	*m_ucstr;
		unsigned short  *m_ustr;
	};
//	HLOCAL	m_handle;
	BOOL	m_mem_fixed;	// indica que la memoria es fija 
	WORD	m_str_type;
	BOOL	m_mem_free;		// indica si debe o no liberar la memoria.
	DWORD	m_mem_size;		// tamaño de la memoria reservada
};

#endif // !defined(AFX_LMEM_H__FABFC504_6CB5_45EC_8DA2_7C69CDB8991D__INCLUDED_)
