// bObject.h: interface for the CbObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BOBJECT_H__425DE737_42DF_415D_83F6_DB6DBD52A108__INCLUDED_)
#define AFX_BOBJECT_H__425DE737_42DF_415D_83F6_DB6DBD52A108__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if !defined (INVALID_FILE_ATTRIBUTES) 
#define INVALID_FILE_ATTRIBUTES ((DWORD)-1) 
#endif

#include "logclient.h"

/*
	Objeto basico usado por todas las clases, con soporte para trazas.
*/

// indica la version de las clases
#define CLASS_VER " Modified : " __TIMESTAMP__ " Compiled : " __DATE__ " " __TIME__ //" File : " __FILE__;

class CbObject  
{
public:
//	void	Show_Version()				{ m_plog->_log(LOG_LVL_DEBUG,"%s",m_ver); };
	__inline void			setLog(CLogClient* plog){ m_plog = plog; };
	__inline CLogClient*	getLog()		{ return m_plog; };

	CbObject();
	virtual ~CbObject();

protected:
	CLogClient*	m_plog;
	char		*m_ver;				// version de la clase

	// soporte para la creacion dinamica de clases
	BOOL		bconstructed;		// indica que el objeto esta construido
	BOOL		bcloned;			// indica que el objeto a sido clonado y no se puede liberar ninguna de sus estructuras
	DWORD		threadid;			// indica el hilo de creacion del objeto
	CbObject	*pnext;

public:
	static DWORD wclen(WCHAR* wc);
	static DWORD clen(char* str);
	void Init();
	void Release();
	void str_ptr_Adjust(char *base1, char *base2, char *ptr1, char **ptr2);
	void ptr_Adjust(BYTE* base1,BYTE* base2,BYTE* ptr1,BYTE** ptr2);
	void Clone(CbObject* pObject,WORD size);

	static WORD  strlen_icmp(const char *str1, WORD len, const char *str2);
	static WORD  strlen_cmp(const char *str1,WORD len, const char * str2);
};

#endif // !defined(AFX_BOBJECT_H__425DE737_42DF_415D_83F6_DB6DBD52A108__INCLUDED_)
