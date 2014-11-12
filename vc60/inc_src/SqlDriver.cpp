// SqlDriver.cpp: implementation of the CSqlDriver class.
//
//////////////////////////////////////////////////////////////////////

#include "SqlDriver.h"
#include "logclient.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSqlDriver::CSqlDriver()
{
	m_ver =  "Class CSqlDriver " CLASS_VER;
	m_henv = NULL;
}

CSqlDriver::~CSqlDriver()
{
	Release();
}

DWORD CSqlDriver::Initialize()
{
	SQLRETURN	sr;
	sr = SQLAllocEnv(&m_henv);
	//sr = SQLAllocHandle(SQL_HANDLE_DBC, SQL_NULL_HANDLE, &m_henv);
	if (sr == SQL_SUCCESS) return ERR_OK;
	strcpy(m_err_msg,"CSqlDriver::Initialize->SQLAllocHandle Failed...");
	return ERR_FATAL;
}

DWORD CSqlDriver::Release()
{
	if (m_henv == NULL)	return ERR_OK;
	m_plog->log_strings(LOG_ERROR,"CSqlDriver::Release ...");
	SQLFreeHandle(SQL_HANDLE_ENV,m_henv);
	m_henv = NULL;
	return ERR_OK;
}

DWORD CSqlDriver::CreateConnection(SQLHENV *psqlenv)
{
	SQLRETURN	sr;
	sr = SQLAllocConnect(m_henv, psqlenv);
	//sr = SQLAllocHandle(SQL_HANDLE_DBC,m_henv, psqlenv);
	if (sr == SQL_SUCCESS) return ERR_OK;
	return Make_ErrorSTR("CSqlDriver::CreateConnection->SQLAllocHandle ");
}

DWORD CSqlDriver::SetVersion(DWORD version)
{
	SQLRETURN	sr;
	sr = SQLSetEnvAttr(m_henv, SQL_ATTR_ODBC_VERSION,(SQLPOINTER)version, SQL_IS_INTEGER);
	if (sr == SQL_SUCCESS) return ERR_OK;
	_snprintf(SSIZE(m_err_msg),"CSqlDriver::SetVersion->SQLSetEnvAttr failed version = %d",version); 
	return ERR_FATAL;
}

DWORD CSqlDriver::Make_ErrorSTR(char *msg)
{
	SQLRETURN	sr;
	SQLINTEGER  NativeError;
	int	n;
	char	err_msg[255];
	char	err_status[7];
	SQLSMALLINT	csize;
	err_msg[0] = 0;
	err_status[0] = 0;
	sr = SQLGetDiagRec(SQL_HANDLE_ENV,m_henv,1,(unsigned char*)err_status,&NativeError,(unsigned char*)err_msg,sizeof(err_msg),&csize);
	n = sprintf(m_err_msg,"%s failed with message = %s Status = [%s]",msg,err_msg,err_status);
	m_plog->log_strings(LOG_ERROR,m_err_msg);
	return ERR_FATAL;
}
