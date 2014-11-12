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
#define LT_NONE		4

#define	KW_TYP_NONE		0		// 
#define KW_TYP_I1_P		1		//  CHAR*
#define KW_TYP_I4		2		//	LONG
#define KW_TYP_UI1		3		//	BYTE
#define KW_TYP_I2		4		//	SHORT	short
#define KW_TYP_R4		5		//	FLOAT
#define KW_TYP_R8		6		//	DOUBLE
#define KW_TYP_CY		7		//	CY
#define KW_TYP_DATE		8		//	DATE	double
#define KW_TYP_I1		9		//	CHAR	char
#define KW_TYP_UI2		10		//	USHORT	unsigned short
#define KW_TYP_UI4		11		//	ULONG	unsigned long
#define KW_TYP_INT		12		//	INT		int
#define KW_TYP_UINT		13		//	UINT	unsigned int
#define KW_TYP_I1_A		14		//  CHAR ARRAY
#define KW_TYP_BOOL		15		//  BOOL

#define KW_FLG_MANDATORY	1
#define KW_FLG_LOG_FILE		2	// indica que el valor de la keyword sera usado para crear el fichero de trazas, se debe asignar al log activo
#define KW_FLG_LOG_LEVEL	4	// utilizar el valor para asignarselo al log

// p = pointer, a = array, 
typedef struct
{
union {
		char				c;
		char				*pc;
		WORD				ui2;
		//char				ac[1];
		//unsigned char		auc[1];
		BOOL				b;
		short int			si;
		unsigned short int	usi;
		long int			li;
		long				l;
		unsigned long int	uli;
		float				f;
		double				d;
		unsigned char		uc;
		signed char			sc;
		_int64				i64;
		unsigned _int64		ui64;
//		DATE_STRUCT			dts;
//		TIMESTAMP_STRUCT	tss;
	};
}S_KWD_VAL;		// valor de la keyword

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
	WORD	type;		// tipo de dato
	WORD	flags;
	void*	value;		// puntero al valor;
}S_KWD_DEF;

// return other than ERR_OK for abort			
class IConf {
public:
	virtual  void  _stdcall Conf_Reset() = 0;
	virtual  void  _stdcall Conf_Log() = 0;
	/*
	virtual  DWORD _stdcall Conf_NewSection(const char *name) = 0;
	virtual  DWORD _stdcall Conf_NewKey(const char *name,const char *value) = 0;
	virtual  DWORD _stdcall Conf_NewLine(const char *line) = 0;
	*/
	
	virtual	 DWORD _stdcall Conf_NewKey(const char* key,WORD key_size,const char *val,WORD val_size) = 0;
	virtual	 DWORD _stdcall Conf_NewSection(const char* name,WORD name_size) = 0;
	
};

// para la edicion de ficheros INI hay que crear un fichero temporal

class CKeywords  : public CbObject
{
private:
	DWORD StrLine_GetInfo(char *str_line,WORD *wtype, char **key_name, char **val);
	DWORD StrLine_Process(char *str, char *section,WORD section_size,S_KWD_DEF *keyword, WORD max_keyword, CMemPage *pMemPage);
	DWORD ParseLine(const char *str_line, WORD line_size,WORD *wtype, char **key_name, WORD *pkey_size, char **val, WORD *pval_size);

	KEYWORD	m_keys[MAX_KEYWORDS];
	WORD	m_key_count;			// cantidad de keys
	BOOL	m_bUpperCase;			// usar uppercase o no

	CMemPage	m_page;
	DWORD		m_data_size;		// tamaño maximo disponible
	CMemPage	*m_mem_page;

public:
	DWORD ParseFileBuffer(const char *file,WORD len,IConf* conf);
	DWORD ParseIniFile(const char *file_name,IConf*	conf);

	DWORD Process_IniFile(char *file_name, S_KWD_DEF *keyword, WORD max_keyword, CMemPage *pMemPage);
	DWORD Process_IniFile_Buffer(char* file_buffer,WORD file_size, S_KWD_DEF *keyword,WORD max_keyword,CMemPage* pMemPage = NULL);
	DWORD Load_Res(char *res_ptr, S_KWD_DEF *key, int max_key);
	DWORD GetLineInfo(char *str_line, WORD line_size,WORD *wtype, char **key_name, WORD *pkey_size, char **val, WORD *pval_size);
	DWORD Process_lineV1(char* line, WORD *ltype,char **key,char **val);
	DWORD Keyword_Look(char** val,char* keyword,char* section="");
	DWORD Keyword2_Get(char *value, int maxsize,char* keyword,char* section = "",char *defval = "");
	DWORD Keyword1_Get(char* keyword,char *value, int maxsize,char *defval = "");
	DWORD Process_IniBuffer(char* buffer);
	DWORD IniFile_SetKey(char *file_path, char*key, char* val,char* section = "");
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
	
	CKeywords();
	virtual ~CKeywords();
protected:
	
};

#endif // !defined(AFX_KEYWORDS_H__132E7532_083F_4B0E_8014_B1F97B375CD8__INCLUDED_)
