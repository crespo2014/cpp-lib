// LogClient.h: interface for the CLogClient class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGCLIENT_H__D912EBCF_19B9_4323_95C7_E73C5C711DC6__INCLUDED_)
#define AFX_LOGCLIENT_H__D912EBCF_19B9_4323_95C7_E73C5C711DC6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "windows.h"
#include "comdef.h"
#include "stdio.h"
#include "stdarg.h"

#define LOG_ERROR	0	// solo los logs de error
#define LOG_WARNING 1	// log de fallo pero poco criticos
#define LOG_DATA	2	// Valores de variables intermedios y en procesamiento 
#define LOG_PARAM	3	// log con los datos de entrada a las funciones
#define LOG_FNC		4	// puntos de entrada en las funciones
#define LOG_TRACE	4	// usado para tracear funciones nivel altisimo
#define LOG_DEBUG	5	// este nivel puede indicar puntos de entrada a funciones, ejecuciones de operacions, etc,
#define LOG_LAST	6


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

#define SSIZE(stra)	stra,sizeof(stra)		// cuando se usan arreglos de char se envia el arreglo y tamaño
#define SPSIZE(x)	&x,sizeof(x)
#define ZERO(x)	memset(&x,0,sizeof(x));

// formas de crear el fichero de log valores a incluir en el nombre del fichero 
#define LOG_FILE_RANDOM		0
#define LOG_FILE_PID		1	// pid del proceso
#define LOG_FILE_PNAME		2	// nombre del proceso
#define LOG_FILE_DATE		4	// fecha año,mes,dia, 
#define LOG_FILE_TIME		8	// 	hora,minutos,segundos
#define LOG_FILE_TICK		16	// tickcount de windows

// el orden de creacion del nombre es pname_pid_date_time_tick

//#define LOG(x)		glog.log_strings(LOG_DATA,x)
/*
	Se puede definir una funcion estatica de log que permita modificar el comportamiento del log
	si esta funcion esta definida, el log puede efectuarse aun sin existe fichero ni consola.
	la funcion necesita un parametro void* y un char* con el mensaje de log
	es recomendable desactivar la generacion de fecha, y de pid si ya se dispone de dicha funcionalidad 
*/

/*
	Funcion de traceo externa
	ext_log(char* str);
*/


class CLogClient 
{
private:
	DWORD CreateEvents();
	//
	BOOL		m_bCloseFile;	// indica que el fichero de log se genero con el evento y puede cerrarse
	HANDLE		m_hFile;		// Fichero de logs
	BOOL		m_bDeleteStd;
	HANDLE		m_hStdOut;
	DWORD		m_dwlasttime;		// usado para medir el tiempo que transcurre 
	BOOL		m_bShowTime;		// Muestra la fecha y hora de la traza
	BOOL		m_bShowThread;		// muestra el id del hilo que genero el log
	BOOL		m_bAddEndFile;		// Situa el puntero al final del fichero antes de adicionar un log
	HANDLE		m_hconsoleevent;	// Handle del evento que permite el uso de la consola
	HANDLE		m_hfileevent;		// Evento usado para crear un fichero log
	WORD		m_log_level;
	BOOL		m_bconsole_ouput;
	BOOL		m_bShowPID;
	// Monitorizacion de trazas
	void*		m_logfnc;
	void*		m_logfnc_prm;
	
public:
	DWORD log_buffer(int level,BYTE* buffer,WORD size,BYTE width ,BYTE base = 16 ,char separator = ' ',bool browpos = true);
	DWORD log(int level,char *str) {return _log(level,"%s",str);};
	DWORD _log(int level,char *format ,...);
	DWORD log_uint(int log_level,char* str1,unsigned long ul,char* str2="",char* str3="",char* str4="",char* str5="") { return _log(log_level,"%s%u%s%s%s%s",str1,ul,str2,str3,str4,str5);};
	DWORD log_sint(int log_level,char* str1,signed long sl,char* str2="",char* str3="",char* str4 = "",char* str5="") { return _log(log_level,"%s%d%s%s%s%s",str1,sl,str2,str3,str4,str5);};
	DWORD log_strings(int log_level,char *str1,char *str2 = "",char *str3 = "",char *str4 = "",char *str5 = "",char *str6 = "") { return _log(log_level,"%s%s%s%s%s%s",str1,str2,str3,str4,str5,str6);};

	void SetConsoleOutput(BOOL status = true);
	void SetLevel(WORD log_level)				{ m_log_level = log_level;};
	void ShowThread(BOOL bShow = true)			{ m_bShowThread = bShow;}
	void ShowPID(BOOL bShow = true)				{ m_bShowPID = bShow;}
	void ShowDateTime(BOOL bShow = true)		{ m_bShowTime = bShow;}

	
	DWORD EventsClose();
	DWORD ElapsedTime_Reset(DWORD* time = NULL);
	DWORD ElapsedTime_Show(DWORD starttime = 0);
	DWORD SetEvent(HANDLE m_hevent,BOOL bstate);
	DWORD SetFileEvent(BOOL bstate)		{ return SetEvent(m_hfileevent,bstate);		}
	DWORD SetConsoleEvent(BOOL bstate)	{ return SetEvent(m_hconsoleevent,bstate);	}
	DWORD OpenConsole();
	DWORD CheckEvents();
	BOOL  HasLogFile();
	DWORD CreateLogFile(char *lpName = NULL,BOOL bOpen = false);
	DWORD CloseFile();

	CLogClient();
	virtual ~CLogClient();

	BSTR GetBSTR(char* str);
	void _rtrim(char* str);
private:
	DWORD CloseConsole();

};

extern CLogClient	glog;


#endif // !defined(AFX_LOGCLIENT_H__D912EBCF_19B9_4323_95C7_E73C5C711DC6__INCLUDED_)
