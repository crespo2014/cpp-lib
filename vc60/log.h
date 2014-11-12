// log.h: interface for the log class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(LOG_H_INCLUDED_)
#define LOG_H_INCLUDED_

#include "sys.c"
#include <time.h>
#include <stdarg.h>

// Niveles de Log

#define LOG_LERROR		0	// solo los logs de error
#define LOG_LWARNING	1	// log de fallo pero no criticos
#define LOG_LINFO		2	// log informativo indicando las actuaciones que se realizan
#define LOG_LPARAM		3	// log con los datos de entrada a las funciones
#define LOG_LDATA		4	// Valores de variables intermedios y en procesamiento 
#define LOG_LDEBUG		5	// toma de decisiones del programa basado en valores, muy potente para depurar fallos de comportamiento	
#define LOG_LFNC		6	// puntos de entrada en las funciones
#define LOG_LLAST		7
// Codigos de error comunes

#define ERR_OK			0	// Operacion satisfactoria
#define ERR_API			1	// Una funcion externa o API no pudo completar la operacion 
#define ERR_PARAM		2	// No se procedio porque faltaron parametros o eran invalidos
#define ERR_HANDLE		3	// No se tiene un handle valido para la operacion, dispositivo cerrado
#define ERR_FATAL		4	// no se pudo completar la operacion
#define ERR_TRUE		5	// la funcion devolvio true
#define ERR_FALSE		6	// La funcion bool devolvio false
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
#define LOG_SHOW_FNC_NAME	64
#define LOG_SHOW_FILE_LINE	128
#define LOG_SHOW_UNIX		256		// indica que el fichero de logs sera mostrado en formato unix
#define LOG_SHOW_ALL		255

/*
	Stack Trace Error	: Permite tracear la pila de llamdas.
	Cuando un metodo invoca otro y este falla se utiliza para saber quien invoco al metodo fallido.
	Se puede utilizar tambien runtimeerror.
*/
#define LOG_TSOCK_ERROR		Write_SockError(__FILE__,fnc_name,__LINE__,
#define LOG_TW32_ERROR		Write_W32Error(__FILE__,fnc_name,__LINE__,
#define LOG_TERROR			log_write(&glog,LOG_LERROR,__FILE__,fnc_name,__LINE__,
#define LOG_TRUNTIME_ERROR	log_write(&glog,LOG_LERROR,__FILE__,fnc_name,__LINE__,ERR_FATAL,"Run Time Error at %s.%d",fnc_name,__LINE__);
#define LOG_TSTACK			log_write(&glog,LOG_LERROR,__FILE__,fnc_name,__LINE__,ERR_FATAL,"at %s.%d",fnc_name,__LINE__);


#define LOG_TTIMECOUNT	ElapseTime_Show(fnc_name,__LINE__,ERR_OK,			 
#define LOG_TTIMERESET	ElapseTime_Reset(fnc_name,__LINE__,ERR_OK,			 

#ifdef NLOG
	#define LOG_TLAST	COMMENT
	#define LOG_TFNC	COMMENT
	#define LOG_TDATA	COMMENT
	#define LOG_TPARAM	COMMENT
	#define LOG_TWARNING	COMMENT
	#define FNC_START	COMMENT
	#define FNC_END		COMMENT
	#define LOG_TINFO	COMMENT
#else 
	#define LOG_TWARNING	log_write(&glog,LOG_LWARNING ,__FILE__,fnc_name,__LINE__,ERR_OK,
	#define LOG_TINFO		log_write(&glog,LOG_LINFO	   ,__FILE__,fnc_name,__LINE__,ERR_OK,
	#define LOG_TPARAM		log_write(&glog,LOG_LPARAM   ,__FILE__,fnc_name,__LINE__,ERR_OK,
	#define LOG_TDATA		log_write(&glog,LOG_LDATA	   ,__FILE__,fnc_name,__LINE__,ERR_OK,
	#define LOG_TDEBUG		log_write(&glog,LOG_LDEBUG	   ,__FILE__,fnc_name,__LINE__,ERR_OK,
	#define FNC_START		LOG_TFNC "Start");
	#define FNC_END			LOG_TFNC "End");
	#define LOG_TFNC		log_write(&glog,LOG_LFNC	   ,__FILE__,fnc_name,__LINE__,ERR_OK,
	#define LOG_TLAST		log_write(&glog,LOG_LLAST    ,__FILE__,fnc_name,__LINE__,ERR_OK,
#endif

struct _LOG
{
	char	*file_path;	
	DWORD	level;
	FILE	*hfile;			// Fichero de logs
	DWORD	dwlasttime;		// usado para medir el tiempo que transcurre 
	BOOL	bconsole_ouput;
	DWORD	show_flag;		// indica la informacion que se muestra en cada linea de log
};

#endif

