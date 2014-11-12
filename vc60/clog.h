// LogClient.h: interface for the CLogClient class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGCLIENT_H__D912EBCF_19B9_4323_95C7_E73C5C711DC6__INCLUDED_)
#define AFX_LOGCLIENT_H__D912EBCF_19B9_4323_95C7_E73C5C711DC6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "platform.h"
#include "file.h"
#include "cconsole.h"
#include "itext.h"
#include "ctime.h"

/*
 * 2012 - 06

  TODO
  	y la linea de, hay que definir _FILENAME_ al comienzo de todos los ficheros .cpp que son los unicos que pueden escribir logs
	no se puede escribir logs desde un fichero .h, hay que utilizar bien el subversion para poder encontrar los errores facil
 */


#define SSIZE(stra)	stra,sizeof(stra)		// cuando se usan arreglos de char se envia el arreglo y tamaño
#define SPSIZE(x)	&x,sizeof(x)
#define ZERO(x)	memset(&x,0,sizeof(x));

#define COMMENT SLASH(/)
#define SLASH(s) /##s
/*
#define _AT_ ;/ ## /

#if _DEBUG
#define DEBUG_ONLY
#else
#define DEBUG_ONLY COMMENT
#endif
 */
#if _NTEST
#define TEST_ONLY COMMENT
#else
#define TEST_ONLY 
#endif

// Niveles de Log
#define LOG_LERROR		0	// solo los logs de error
#define LOG_LWARNING	1	// log de fallo pero poco criticos
#define LOG_LINFO		2	// log con informacion de los pasos que se estan realizando
#define LOG_LDEBUG		3	// log con los datos de entrada a las funciones Valores de variables intermedios y en procesamiento + puntos de entrada en las funciones
#define LOG_LLAST		4

// Validar una condicion, si no se cumple se abandona el metodo
//#define _CHECK_EXIT(a)	if (!a)	return _LOG_AT;

class ILog 
{
public:
	// Peticiones de log
	virtual DWORD Write(WORD level,char* fnc_name,int line,DWORD retval,char* format , ...) = 0;
	// Monitorizar el log
	virtual DWORD Log(WORD level,char* fnc_name,int line,char* strlog) = 0;
	//virtual DWORD Out(char* strlog) = 0;
};

/*
 * TODO	: Implementar ITube, para que pueda recivir una trama de por ejemplo un buffer log
 * porque si invocamos al buffer con poca memoria tendremos que usar un buffer con estado
 * en cuyo caso debe ser como un tubo de lectura.
 */
class clog 
{
public:
	/*
	 * valida el nivel y las salidas activas y devuelve this o null
	 */
	inline clog* checkOut(BYTE level)
	{
		return ((level <= m_log_level) && (mOnFile || mOnConsole || m_ilog )) ? this : NULL;
	};
	/*
	 * Define el formato de la cabecera de cada linea de log
	 */
	DWORD	setHeadFormat(const char* fmt);

	// funcion de log con validacion de this
	DWORD log(WORD level,const char *file,DWORD line,DWORD retval,IText *ptext,const char* format , ...);

	DWORD createLogFile();
	DWORD setFilePath(const char* file_path,BOOL tryOpen);

	void setILog(ILog* pILog)					{ m_ilog = pILog; };
	void SetLevel(DWORD log_level)				{ m_log_level = log_level;	};
	void consoleEnable();
	void consoleDisable();

	DWORD EventsClose();
	DWORD SetFileEvent(BOOL bstate)		{ return SetEvent(m_hfileevent,bstate);		}
	DWORD SetConsoleEvent(BOOL bstate)	{ return SetEvent(m_hconsoleevent,bstate);	}

	clog();
	~clog();

	// Definir el nombre del fichero de log a partir del directorio y un formato
	bool	setFileName(const char* folder, const char* format);

private:
	void SetConsoleOutput(BOOL status);
	DWORD CheckEvents();
	DWORD CreateEvents();
	DWORD SetEvent(HANDLE m_hevent,BOOL bstate);

	ctime	time;
	// salidas activas
	BOOL	mOnFile;
	BOOL	mOnConsole;
	DWORD	m_log_level;
	HANDLE	m_hconsoleevent;	// Handle del evento que permite el uso de la consola
	HANDLE	m_hfileevent;		// Evento usado para crear un fichero log
	BOOL	m_bAddEndFile;		// Situa el puntero al final del fichero antes de adicionar un log

	// Monitorizacion de trazas
	ILog		*m_ilog;
	cconsole	mconsole;
	cfile		mfile;
	BOOL		mbeventfile;	// indica que el fichero fue creado por un evento
};

extern clog	slog;
#define safelog(x)	((x) ? x : (&slog))

#define log_e(rcode, ...)			safelog(mlog)->checkOut(LOG_LERROR)->log(LOG_LERROR,_FILENAME_,__LINE__,rcode,NULL,__VA_ARGS__);
#define log_etext(rcode,ptext, ...)	safelog(mlog)->checkOut(LOG_LERROR)->log(LOG_LERROR,_FILENAME_,__LINE__,rcode,ptext,__VA_ARGS__);

#define slog_e(rcode, ...)				slog.checkOut(LOG_LERROR)->log(LOG_LERROR,_FILENAME_,__LINE__,rcode,NULL,__VA_ARGS__);
#define slog_etext(rcode,ptext, ...)	slog.checkOut(LOG_LERROR)->log(LOG_LERROR,_FILENAME_,__LINE__,rcode,ptext,__VA_ARGS__);

#define log_exit(rcode)				log_e(rcode,"function exit with code %d",rcode);
#define slog_exit(rcode)			slog_e(rcode,"function exit with code %d",rcode);

#ifdef NLOG

#define log_w(...)	COMMENT
#define log_i(...) COMMENT
#define log_p(...) COMMENT
#define log_d(...) COMMENT

#define slog_w(...)	COMMENT
#define slog_i(...) COMMENT
#define slog_p(...) COMMENT
#define slog_d(...) COMMENT

#else


// Tracear log con determinado nivel funciones a ejucutar solas en una linea
#define log_w(...)		if (safelog(mlog)->checkOut(LOG_LWARNING)) safelog(mlog)->log(LOG_LWARNING,_FILENAME_,__LINE__,ERR_OK,NULL,__VA_ARGS__); else {};
#define log_i(...)		if (safelog(mlog)->checkOut(LOG_LINFO))  safelog(mlog)->log(LOG_LWARNING,_FILENAME_,__LINE__,ERR_OK,NULL,__VA_ARGS__); else {};
#define log_p(...)		if (safelog(mlog)->checkOut(LOG_LPARAM)) safelog(mlog)->log(LOG_LWARNING,_FILENAME_,__LINE__,ERR_OK,NULL,__VA_ARGS__); else {};
#define log_d(...)		if (safelog(mlog)->checkOut(LOG_LDEBUG)) safelog(mlog)->log(LOG_LWARNING,_FILENAME_,__LINE__,ERR_OK,NULL,__VA_ARGS__); else {};

#define slog_w(...)		if (slog.checkOut(LOG_LWARNING)) slog.log(LOG_LWARNING,_FILENAME_,__LINE__,ERR_OK,NULL,__VA_ARGS__); else {};
#define slog_i(...)		if (slog.checkOut(LOG_LINFO))    slog.log(LOG_LINFO,_FILENAME_,__LINE__,ERR_OK,NULL,__VA_ARGS__); else {};
#define slog_p(...)		if (slog.checkOut(LOG_LPARAM))   slog.log(LOG_LPARAM,_FILENAME_,__LINE__,ERR_OK,NULL,__VA_ARGS__); else {};
#define slog_d(...)		if (slog.checkOut(LOG_LDEBUG))   slog.log(LOG_LDEBUG,_FILENAME_,__LINE__,ERR_OK,NULL,__VA_ARGS__); else {};

#endif

#endif // !defined(AFX_LOGCLIENT_H__D912EBCF_19B9_4323_95C7_E73C5C711DC6__INCLUDED_)

