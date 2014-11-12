// _inifile.h: interface for the _inifile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX__INIFILE_H__D463FA83_F7AC_40FB_A229_01FAEB986347__INCLUDED_)
#define AFX__INIFILE_H__D463FA83_F7AC_40FB_A229_01FAEB986347__INCLUDED_

#define DWORD	unsigned long
#define WORD	unsigned short	

#define MAXINILINE		255		//longitud maxima de una linea en el fichero ini
#define MAXINIKEYS		100
#define MAXFILESIZE		2048

typedef struct {
	struct {
		char*	name;
		char*	value;
		char*	section;
	}		key[MAXINIKEYS];
	WORD	keycount;
	char	data[MAXFILESIZE];
	
}_INIFILE;


#ifdef __cplusplus
extern "C" {
#endif

	DWORD strcasecmp(char* str1,char* str2);
	void uppercase (char* str);
	DWORD _inifileInit(_INIFILE* pthis);
	DWORD _inifileRelease( _INIFILE* pthis);
	DWORD _inifileReadFromFile( _INIFILE* pthis,char* file_path);
	DWORD _inifileGetFromFile(char* file_path,char* section, char* keyword,char* value, WORD maxlen);

#ifdef __cplusplus
}
#endif

#endif // !defined(AFX__INIFILE_H__D463FA83_F7AC_40FB_A229_01FAEB986347__INCLUDED_)
