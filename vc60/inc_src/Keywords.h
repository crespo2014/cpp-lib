// Keywords.h: interface for the CKeywords class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KEYWORDS_H__132E7532_083F_4B0E_8014_B1F97B375CD8__INCLUDED_)
#define AFX_KEYWORDS_H__132E7532_083F_4B0E_8014_B1F97B375CD8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logclient.h"
#include "bobject.h"
#include "mempage.h"

/*
	Mantiene una estructura de keywords y valores de tipo char*
	posee funciones para convertir a diferentes tipos de estructuras
*/

#define MAX_KEYWORDS	30

// tipos de linea en ficheros de configuracion
#define LT_ERROR	0	// linea erronea por overflow o caracteres no validos
#define LT_COMMENT	1	// linea de comentario
#define LT_SECTION	2	// inicio de seccion
#define LT_KEY		3	// clave con valor

typedef struct
{
	char*	section;
	char*	name;
	char*	value;
}KEYWORD;

typedef struct
{
	char*	section;
	char*	name;
	char**	value;
}KEYWORD_DF;

// para la edicion de ficheros INI hay que crear un fichero temporal

class CKeywords  : public CbObject
{
public:
	DWORD Keyword_Look(char** val,char* keyword,char* section="");
	DWORD Keyword2_Get(char *value, int maxsize,char* keyword,char* section = "",char *defval = "");
	DWORD Keyword1_Get(char* keyword,char *value, int maxsize,char *defval = "");
	DWORD Process_IniBuffer(char* buffer);
	DWORD IniFile_SetKey(char *file_path, char*key, char* val,char* section = "");
	DWORD Process_IniFile2(char *file_path,KEYWORD_DF* keys,char* defval = "");	// cargar solo las keywords indicadas,
	DWORD Key_Get(char* val, WORD valsize, char* key, char* section = "");
	DWORD GetKeyword(WORD index, char **keyword,char** value,char** section = NULL);
	void  Key_UpperCaseEnable(BOOL benable = true) { m_bUpperCase = benable; };
	DWORD ProcessCmdLine_UNIX(char* cmd_line);
	DWORD Process_Line(char* line,char delimiter);
	char* GetKey(WORD index);
	DWORD GetCount(){return m_key_count;};
	DWORD IniParam_Look(char* keyword,char** val,char* section = "");
	DWORD Process_IniFile(char* file_path);
	DWORD BreakLine(char* line,char delimiter,char** next_line);
	DWORD ProcessArgLine(char* arg[], int count);
	DWORD GetEnv(char* keyword,char** cptr, bool trace = false);
	DWORD LookKeyword(char* keyword,char** cptr, bool trace = false);
	DWORD AddToCmdLine(char **sptr, char *key, char *value);
	DWORD ExtractKeywords();
	DWORD ProcessCmdLine(char* cmd_line);
	DWORD Process_lineV1(char* line, WORD *ltype,char **key,char **val);
	CKeywords();
	virtual ~CKeywords();
	
private:
	
	KEYWORD	m_keys[MAX_KEYWORDS];
	WORD	m_key_count;			// cantidad de keys
	BOOL	m_bUpperCase;			// usar uppercase o no

	CMemPage	m_page;
	DWORD		m_data_size;		// tamaño maximo disponible
};

#endif // !defined(AFX_KEYWORDS_H__132E7532_083F_4B0E_8014_B1F97B375CD8__INCLUDED_)
