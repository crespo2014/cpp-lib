// DNParse.h: interface for the CDNParse class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DNPARSE_H__8F8940C3_5F58_4ACF_A77A_357FE6148C8A__INCLUDED_)
#define AFX_DNPARSE_H__8F8940C3_5F58_4ACF_A77A_357FE6148C8A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bObject.h"
#include "mempage.h"

#define DN_MAXKEY	50

typedef struct
{
	char	*key;
	char	*val;
}_DNKEY;

class CDNParse : public CbObject  
{
public:
	DWORD Data_AddStr(char *str,char** pos,char* fnc_name, DWORD len = 0);
	DWORD KeyCount() { return m_key_count; };
	DWORD Key_ByIndex(WORD index,_DNKEY** pdnkey);
	
	DWORD Data_GetBuffer(char** buff, WORD len,char* fnc_name);
	DWORD Key_Look(char* key,char **val);
	DWORD Key_Get(char* key,char* val,WORD maxsize);
	DWORD Parse_String(char* str);
	void LogData();
	char* GetKey(char* key,char *defval = "");
	CDNParse();
	virtual ~CDNParse();

private:
	CMemPage	m_page;
	char		*m_data;			// puntero al buffer de datos
	char		*m_data_ptr;		// puntero donde se estan copiando los datos
	DWORD		m_data_size;		// tamaño maximo disponible

	_DNKEY	m_key[DN_MAXKEY];
	DWORD	m_key_count;
	

};

#endif // !defined(AFX_DNPARSE_H__8F8940C3_5F58_4ACF_A77A_357FE6148C8A__INCLUDED_)
