// LogClient.h: interface for the CLogClient class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGCLIENT_H__D912EBCF_19B9_4323_95C7_E73C5C711DC6__INCLUDED_)
#define AFX_LOGCLIENT_H__D912EBCF_19B9_4323_95C7_E73C5C711DC6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "comdef.h"
#include "stdio.h"
#include "stdarg.h"

/* TODO
	Hay que eliminar el nombre de la funcion de los logs, en su lugar utilizar el nombre reducido del fichero
	y la linea de, hay que definir _FILENAME_ al comienzo de todos los ficheros .cpp que son los unicos que pueden escribir logs
	no se puede escribir logs desde un fichero .h, hay que utilizar bien el subversion para poder encontrar los errores facil
	
	cambiar la definicio de logs
	#define log_debug(ecode,...)    write(ecode,__VA_ARGS_);
	log_warning(ecode, ...) if (!m_plog) || (m_plog->level < LOG_LWARNING)){} else m_plog->Write(LOG_LWARNING ,_FILENAME_,__LINE__,ecode,__VA_ARGS_);
*/

// para que compilen los proyectos con includes de la sdk 8
typedef ULONG ULONG_PTR;
typedef ULONG_PTR DWORD_PTR, *PDWORD_PTR;

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
#define LOG_LPARAM		2	// log con los datos de entrada a las funciones
#define LOG_LINFO		3	// log con informacion de los pasos que se estan realizando
#define LOG_LDATA		4	// Valores de variables intermedios y en procesamiento 
#define LOG_LFNC		5	// puntos de entrada en las funciones
#define LOG_LLAST		6

// Codigos de error comunes
#define ERR_OK			0	// Operacion satisfactoria o es TRUE
#define ERR_API			1	// Una funcion externa o API no pudo completar la operacion 
#define ERR_PARAM		2	// No se procedio porque faltaron parametros o eran invalidos
#define ERR_HANDLE		3	// No se tiene un handle valido para la operacion, dispositivo cerrado
#define ERR_FATAL		4	// no se pudo completar la operacion
#define ERR_FALSE		6	// La funcion bool devolvio false no se cumple la condicion pero no hay error
#define ERR_EOF			7	// Fin del fichero o no hay mas elementos a enumerar
#define ERR_NULL		8	// No hay resultados por devolver
#define ERR_TRUNCD		9	// Los datos han sido truncados
#define ERR_OP			10	// la operacion no se puede realizar
#define ERR_PENDING		11	// operacion pendiente, revisar el estado del evento
#define ERR_TIMEOUT		12	// sobrepasado el tiempo permitido para realizar la operacion
#define ERR_NOT_FOUND	13	// el elemento no se encontro
#define ERR_PASSWORD	14	// la contraseña o las crdenciales no son validas
#define ERR_NOMEMORY	15	// Error de memoria
#define ERR_ABORT		16	// La operacion ha sido cancelada o abortada
#define ERR_UNSUPPORTED	17	// Funcion u operacion no soportada o no implementada
#define ERR_UNEXPECTED	18	// situacion no esperada o codigo corrupto, es una situacion no esperada
#define ERR_IS_LOCK		19	// el recurso esta bloqueado
#define ERR_OVERFLOW	20	// la operacion no se puede aplicar porque hay desbordamiento de memoria
#define ERR_LAST		100	// permite definir a partir de aqui los errores propios de la aplicación

// formas de crear el fichero de log valores a incluir en el nombre del fichero 
#define LOG_FILE_RANDOM		0
#define LOG_FILE_PID		1	// pid del proceso
#define LOG_FILE_PNAME		2	// nombre del proceso
#define LOG_FILE_DATE		4	// fecha año,mes,dia, 
#define LOG_FILE_TIME		8	// hora,minutos,segundos
#define LOG_FILE_TICK		16	// tickcount de windows

// Informacion a incluir en cada linea del log
#define LOG_SHOW_NONE		0
#define LOG_SHOW_DATE		1
#define LOG_SHOW_TIME		2
#define LOG_SHOW_DATETIME	3
#define LOG_SHOW_LEVEL		4
#define LOG_SHOW_PID		8
#define LOG_SHOW_THREAD		16
#define LOG_SHOW_FILE_NAME	32
//#define LOG_SHOW_FNC_NAME	64
#define LOG_SHOW_FILE_LINE	128


// Validar una condicion, si no se cumple se abandona el metodo
//#define _CHECK_EXIT(a)	if (!a)	return _LOG_AT;

#define LOG_TTIMECOUNT	if (m_plog == NULL)	{} else m_plog->ElapseTime_Show(fnc_name,__LINE__,ERR_OK,			 
#define LOG_TTIMERESET	if (m_plog == NULL)	{} else m_plog->ElapseTime_Reset(fnc_name,__LINE__,ERR_OK,			 

#ifdef NLOG
	#define LOG_TLAST		COMMENT
	#define LOG_TFNC		COMMENT
	#define LOG_TDATA		COMMENT
	#define LOG_TPARAM		COMMENT
	#define LOG_TWARNING	COMMENT
	#define FNC_START		COMMENT
	#define FNC_END			COMMENT
	#define LOG_TINFO		COMMENT
	#define _LOG_WARNING
#else 
	#define LOG_TLAST		if ((m_plog != NULL) && (m_plog->getLevel() >= LOG_LLAST))		m_plog->Write(LOG_LLAST    ,_FILENAME_,__LINE__,ERR_OK,
	#define LOG_TFNC		if ((m_plog != NULL) && (m_plog->getLevel() >= LOG_LFNC))		m_plog->Write(LOG_LFNC	   ,_FILENAME_,__LINE__,ERR_OK,
	#define LOG_TDATA		if ((m_plog != NULL) && (m_plog->getLevel() >= LOG_LDATA))		m_plog->Write(LOG_LDATA	   ,_FILENAME_,__LINE__,ERR_OK,
	#define LOG_TPARAM		if ((m_plog != NULL) && (m_plog->getLevel() >= LOG_LPARAM))		m_plog->Write(LOG_LPARAM   ,_FILENAME_,__LINE__,ERR_OK,
	#define LOG_TWARNING	if ((m_plog != NULL) && (m_plog->getLevel() >= LOG_LWARNING))	m_plog->Write(LOG_LWARNING ,_FILENAME_,__LINE__,ERR_OK,
	#define LOG_TINFO		if ((m_plog != NULL) && (m_plog->getLevel() >= LOG_LINFO))		m_plog->Write(LOG_LINFO	   ,_FILENAME_,__LINE__,ERR_OK,
	#define FNC_START	LOG_TFNC "Start");
	#define FNC_END		LOG_TFNC "End");

    #define _LOG_WARNING	if ((m_plog == NULL) || (m_plog->getLevel() < LOG_LWARNING)){} else m_plog->Write(LOG_LWARNING ,_FILENAME_,__LINE__,ERR_OK,
	#define _LOG_INFO		if ((m_plog == NULL) || (m_plog->getLevel() < LOG_LINFO))	{} else m_plog->Write(LOG_LINFO ,_FILENAME_,__LINE__,ERR_OK,
	#define _LOG_DATA		if ((m_plog == NULL) || (m_plog->getLevel() < LOG_LDATA))	{} else m_plog->Write(LOG_LDATA ,_FILENAME_,__LINE__,ERR_OK,
#endif

// hay que usar el nombre del fichero preferentemente sobre la funcion porque oculta mas la estructura del programa y 
// reduce el tamaño final del programa

class ILog 
{
public:
	// Peticiones de log
	virtual DWORD Write(WORD level,char* fnc_name,int line,DWORD retval,char* format , ...) = 0;
	// Monitorizar el log
	virtual DWORD Log(WORD level,char* fnc_name,int line,char* strlog) = 0;
	//virtual DWORD Out(char* strlog) = 0;
};

class CLogClient 
{
public:
	BOOL getConsoleOutput();
	static CLogClient* get();
	DWORD Write_W32Error(char *file,int line,DWORD w32_ecode,DWORD retval,char* format , ...);
	DWORD Write(WORD level,char	*file,int line,DWORD retval,char* format , ...);
	DWORD CreateFile(char* file_name = NULL,BOOL bOpen = false);
	DWORD CreateFile(char* file_name,char* end_str,char* file_ext = ".log",BOOL bOpen = false);
	DWORD log_buffer(WORD level,BYTE* buffer,WORD size,BYTE width ,BYTE base = 16 ,char separator = ' ',bool browpos = true);

	void setILog(ILog* pILog)					{ m_ilog = pILog; };
	void SetConsoleOutput(BOOL status = true);
	void SetLevel(DWORD log_level)				{ m_log_level = log_level;	};
	void ShowThread(BOOL bShow = true)			{ (bShow) ? (Show(LOG_SHOW_THREAD))		: (Hide(LOG_SHOW_THREAD));		};
	void ShowPID(BOOL bShow = true)				{ (bShow) ? (Show(LOG_SHOW_PID))		: (Hide(LOG_SHOW_PID));			};
	void ShowDateTime(BOOL bShow = true)		{ (bShow) ? (Show(LOG_SHOW_DATETIME))	: (Hide(LOG_SHOW_DATETIME));	};
	void ShowLevel(BOOL bShow = true)			{ (bShow) ? (Show(LOG_SHOW_LEVEL))		: (Hide(LOG_SHOW_LEVEL));		};
	void ShowFileLine(BOOL bShow = true)		{ (bShow) ? (Show(LOG_SHOW_FILE_LINE))	: (Hide(LOG_SHOW_FILE_LINE));	};
	void SetShowFlag(DWORD	dwFlag)				{ m_show_flag = dwFlag;		};
	void Show(DWORD dwFlag)						{ m_show_flag |= dwFlag;	};
	void Hide(DWORD dwFlag)						{ m_show_flag &= (~dwFlag);	};
	inline DWORD	getLevel()							{ return m_log_level; };
	
	DWORD EventsClose();
	DWORD ElapsedTime_Reset(char* fnc_name,int line,WORD level,DWORD* time = NULL);
	DWORD ElapsedTime_Show(char* fnc_name,int line,WORD level,DWORD starttime = 0);
	
	DWORD SetFileEvent(BOOL bstate)		{ return SetEvent(m_hfileevent,bstate);		}
	DWORD SetConsoleEvent(BOOL bstate)	{ return SetEvent(m_hconsoleevent,bstate);	}
	BOOL  HasLogFile();
	DWORD CloseFile();

	CLogClient();
	virtual ~CLogClient();

	void _rtrim(char* str);

private:
	BOOL IsActiveLogOutput();
	DWORD OpenConsole();
	DWORD CheckEvents();
	DWORD CloseConsole();
	DWORD CreateEvents();
	DWORD SetEvent(HANDLE m_hevent,BOOL bstate);
	DWORD Log_Write(DWORD retval,void *pBuffer,DWORD size);
	char* GetHeader(char* cstr,WORD size,WORD level,char *file, int line);

	//
	DWORD		m_log_level;
	HANDLE		m_hFile;			// Fichero de logs
	HANDLE		m_hStdOut;
	HANDLE		m_hconsoleevent;	// Handle del evento que permite el uso de la consola
	HANDLE		m_hfileevent;		// Evento usado para crear un fichero log
	DWORD		m_dwlasttime;		// usado para medir el tiempo que transcurre 
	BOOL		m_bCloseFile;		// indica que el fichero de log se genero con el evento y puede cerrarse
	BOOL		m_bDeleteStd;
	BOOL		m_bAddEndFile;		// Situa el puntero al final del fichero antes de adicionar un log
	BOOL		m_bconsole_ouput;
	DWORD		m_show_flag;		// indica la informacion que se muestra en cada linea de log
	// Monitorizacion de trazas
	ILog		*m_ilog;
};


#ifdef NLOG
	#define log		COMMENT
#else 
	#define log(level)		if ((m_plog) && (m_plog->getLevel() >= level))	m_plog->Write(##level,_FILENAME_,__LINE__,ERR_OK,__VA_ARGS_); else {};
#endif

/*
#define log_warning()			log(LOG_LWARNING,ERR_OK,__VA_ARGS_)
#define log_param()				log(LOG_LPARAM,ERR_OK,__VA_ARGS_)				// datos de parametros y valores intermedios
#define log_info()				log(LOG_LINFO,ERR_OK,__VA_ARGS_)				// informacion de pasos que se estan ralizando
#define log_func()				log(LOG_LFNC,ERR_OK,__VA_ARGS_)					// entrada y salida de funciones
#define log_debug()				log(LOG_LFNC,ERR_OK,__VA_ARGS_)					// ultimo nivel
*/


/*
	solo los log de error se pueden utilizar para abandonar una funcion.
	porque invocan al metodo write directamente el resto de logs utilizan un if
*/

#define log_error							m_plog->Write(LOG_LERROR,_FILENAME_,__LINE__,
#define log_w32error						m_plog->Write_W32Error(_FILENAME_,__LINE__,
#define log_exit(ecode)						log_error ecode,"exit with code %d",ecode);

// for compatibility
#define LOG_TW32_ERROR	log_w32error
#define LOG_TERROR		log_error	
#define _LOG_AT			log_exit(ERR_FATAL)	
#define _LOG_W32ERROR	log_w32error
#define _LOG_ERROR		log_error
#define _LOG_EXIT(x)	log_exit(##x)		

#endif // !defined(AFX_LOGCLIENT_H__D912EBCF_19B9_4323_95C7_E73C5C711DC6__INCLUDED_)
