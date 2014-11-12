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
	Objeto basico usado por todas las clases, 
	Implementa mensajes de error
	auto trace de errores, etc
	GetErrorMsg
	SetErrorMsg	: protected
	SystemErrorMsg :: 
	m_err_msg
	m_err_code
	Posee metodos para llenar el mensaje de error y retornar con un valor indicado.
	con trace se envia el mensaje al log.
*/

// indica la version de las clases
#define CLASS_VER " Modified : " __TIMESTAMP__ " Compiled : " __DATE__ " " __TIME__ " File : " __FILE__;

class CbObject  
{
public:
	
	void	EnableTraceAll(BOOL bstatus = true) { m_btrace_all = bstatus; };
	DWORD	Error_Add(BOOL trace, DWORD retval, const char *format,...);
	DWORD	SetError_Add_W32_code_msg(BOOL trace,DWORD retval,DWORD w32_ecode,const char* format,...);
	DWORD	SetError(BOOL trace,DWORD retval,const char *format,...);
	
	DWORD	Error_Add_W32_msg(DWORD retval,DWORD w32_ecode,const char *format, ...);
	DWORD	Error(DWORD retval,const char *format, ...);			// el error no es enviado al log
	
	// quedaran obsoletas dentro de poco
	DWORD	ErrorMsg_code(DWORD ret_val,DWORD err_code,char *str1,char *str2 = "",char *str3 = "",char *str4 = "",char *str5 = "",char *str6 = "");

	void	Func_Start(char* fnc_name)	{ m_plog->_log(LOG_FNC,"%s Start",fnc_name); };
	void	Show_Version()				{ m_plog->_log(LOG_DEBUG,"%s",m_ver); };
	char*	GetErrorMsg()				{ return m_err_msg;	};
	DWORD	GetErrorCode()				{ return m_err_code;}
	void	SetLog(CLogClient* plog)	{ m_plog = plog;	};
	CLogClient*	GetLog()				{ return m_plog;	};

	CbObject();
	virtual ~CbObject();

protected:
	BOOL		m_btrace_all;		// indica que todos los errores seran trazeados, pueden repetirse si tambien se tracean en la clase que usa esta
	DWORD		m_err_code;			// codigo y mensaje del ultimo error
	char		m_err_msg[1024];
	CLogClient*	m_plog;
	char		*m_ver;				// version de la clase
};

#endif // !defined(AFX_BOBJECT_H__425DE737_42DF_415D_83F6_DB6DBD52A108__INCLUDED_)
