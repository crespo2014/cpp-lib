// SqlConnection.cpp: implementation of the CSqlConnection class.
//
//////////////////////////////////////////////////////////////////////

#include "SqlConnection.h"
#include "logclient.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSqlConnection::CSqlConnection()
{
	Init();
}

CSqlConnection::CSqlConnection(CSqlDriver* pSqlDriver)
{
	Init();
	SetDriver(pSqlDriver);
}

CSqlConnection::~CSqlConnection()
{
	Release();
}

DWORD CSqlConnection::Initialize()
{
	DWORD	dwr;
	if (m_henv != NULL) return ERR_OK;
	dwr = m_sqldriver->CreateConnection(&m_henv);
	if (dwr == ERR_OK) return dwr;
	strcpy(m_err_msg,m_sqldriver->GetErrorStr());
	return ERR_FATAL;
}

DWORD CSqlConnection::CreateCommand(SQLHENV *psqlenv)
{
	SQLRETURN	sr;
	if (m_henv == NULL) return Make_ErrorSTR("CSqlConnection::CreateCommand ",SQL_INVALID_HANDLE);
	//sr = SQLAllocHandle(SQL_HANDLE_STMT,m_henv,psqlenv);
	sr = SQLAllocStmt(m_henv,psqlenv);
	if (sr == SQL_SUCCESS) return ERR_OK;
	Make_ErrorSTR("CSqlConnection::CreateCommand->SQLAllocStmt",sr);
//	strcpy(m_err_msg,"CSqlConnection::CreateCommand -> Failed");
	return ERR_FATAL;
}

DWORD CSqlConnection::ConnectTo(char *datasource, char *user, char *password)
{
	SQLRETURN	sr;
	if (m_henv == NULL) return Make_ErrorSTR("CSqlConnection::ConnectTo ",SQL_INVALID_HANDLE);
	if (m_connect) return SetError(true,ERR_FATAL,"Connection already open ...");
	//if (Disconnect() != ERR_OK) return ERR_FATAL;
	sr = SQLConnect(m_henv,(unsigned char*)datasource,SQL_NTS,(unsigned char*)user,SQL_NTS,(unsigned char*)password,SQL_NTS);
	if (sr == SQL_SUCCESS) 
	{
		m_connect = true;
		m_plog->_log(LOG_TRACE,"Open connection for dsn, user (%s,%s)",datasource,user);
		return ERR_OK;
	}
	m_plog->log_strings(LOG_ERROR,"For DSN = <",datasource,"> USER = <",user,">");
	return Make_ErrorSTR("CSqlConnection::ConnectTo->SQLConnect ",sr);
}

DWORD CSqlConnection::Make_ErrorSTR(char *msg,SQLRETURN	sr)
{
	SQLRETURN	sr1;
	SQLINTEGER  NativeError;
	int	n;
	char	err_msg[255];
	char	err_status[7];
	SQLSMALLINT	csize;
	err_msg[0] = 0;
	err_status[0] = 0;
	if (sr == SQL_INVALID_HANDLE)
	{
		_snprintf(SSIZE(m_err_msg),"%s failed Error code = %d that same Invalid Handle Value",msg,sr);
		m_plog->log_strings(LOG_ERROR,m_err_msg);
		return ERR_FATAL;
	}
		
	sr1 = SQLGetDiagRec(SQL_HANDLE_DBC,m_henv,1,(unsigned char*)err_status,&NativeError,(unsigned char*)err_msg,sizeof(err_msg),&csize);
	
	if (sr == SQL_SUCCESS_WITH_INFO)
	{
		n = sprintf(m_err_msg,"%s Success with info = <%s> Status = [%s]",msg,err_msg,err_status);
		m_plog->log_strings(LOG_ERROR,m_err_msg);
		return ERR_OK;
	}
	n = sprintf(m_err_msg,"%s failed with message = %s Status = [%s]",msg,err_msg,err_status);
	m_plog->log_strings(LOG_ERROR,m_err_msg);
	return ERR_FATAL;
}

DWORD CSqlConnection::Release()
{
	if (m_henv == NULL)	return ERR_OK;
	SQLRETURN	sr;
	Disconnect();
	m_plog->log_strings(LOG_TRACE,"CSqlConnection::Release ...");
	sr = SQLFreeHandle(SQL_HANDLE_DBC,m_henv);
	m_henv = NULL;
	return ERR_OK;
}

DWORD CSqlConnection::TransationEnable(BOOL bstate)
{
	SQLRETURN	sr;
	/*
	if (bstate)
		m_plog->log_strings(LOG_TRACE,"CSqlConnection::Transation Enable");
	else
		m_plog->log_strings(LOG_TRACE,"CSqlConnection::Transation Disable");
	*/

	if (bstate)
		sr = SQLSetConnectAttr(m_henv,SQL_ATTR_AUTOCOMMIT,(SQLPOINTER)SQL_AUTOCOMMIT_OFF,SQL_IS_INTEGER);
	else
		sr = SQLSetConnectAttr(m_henv,SQL_ATTR_AUTOCOMMIT,(SQLPOINTER)SQL_AUTOCOMMIT_ON,SQL_IS_INTEGER);
	if (sr == SQL_SUCCESS)
	{
		m_ontransation = bstate;
		return ERR_OK;
	}
	m_ontransation = false;
	return Make_ErrorSTR("CSqlConnection::TransationEnable->SQLSetConnectAttr ",sr);
}

DWORD CSqlConnection::Transation(SQLSMALLINT operation)
{
	SQLRETURN	sr;
	m_ontransation = false;			// indica que ya se efectua la terminacion de la transacion
	/*
	if (operation == SQL_COMMIT)
		m_plog->log_strings(LOG_TRACE,"CSqlConnection::Transation Commit");
	else
		m_plog->log_strings(LOG_TRACE,"CSqlConnection::Transation Rollback");
	*/
	sr = SQLEndTran(SQL_HANDLE_DBC,m_henv,operation);
	if (sr == SQL_SUCCESS) 
	{
		TransationEnable(false);	// desabilitar las transaciones al terminar
		return ERR_OK;
	}
	return Make_ErrorSTR("CSqlConnection::Transation->SQLEndTran ",sr);
}

DWORD CSqlConnection::Disconnect()
{
	SQLRETURN	sr;
	if (!m_connect) return ERR_OK;
	if (m_ontransation)	
		Transation_RollBack();
	else
		TransationEnable(false);
	sr = SQLDisconnect(m_henv);
	if (sr != SQL_SUCCESS) return Make_ErrorSTR("CSqlConnection::Disconnect->SQLDisconnect ",sr);
	m_connect = false;
	m_ontransation = false;
	return ERR_OK;	
}

void CSqlConnection::SetDriver(CSqlDriver* pSqlDriver)
{
	Release();
	m_sqldriver = pSqlDriver;
	SetLog(pSqlDriver->GetLog());
}


DWORD CSqlConnection::BrowseConnect(char *InConnectionString, char *OutConnectionString, SQLSMALLINT BufferLength, SQLSMALLINT *StringLength2Ptr)
{
	SQLRETURN	sr;
	sr = SQLBrowseConnect(m_henv,(unsigned char*)InConnectionString,SQL_NTS,(SQLCHAR*)OutConnectionString,BufferLength,StringLength2Ptr);
	if ((sr == SQL_SUCCESS) || (sr == SQL_NEED_DATA)) return ERR_OK;
	return Make_ErrorSTR("CSqlConnection::BrowseConnect->SQLBrowseConnect ",sr);
}

DWORD CSqlConnection::SetAttribute(SQLINTEGER Attribute, SQLPOINTER ValuePtr, SQLINTEGER StringLength)
{
	SQLRETURN	sr;
	sr = SQLSetConnectAttr(m_henv,Attribute,ValuePtr,StringLength);
	if (sr == SQL_SUCCESS) return ERR_OK;
	return Make_ErrorSTR("CSqlCommand::SetAttribute->SQLSetConnectAttr ",sr);
}

void CSqlConnection::Init()
{
	m_ver =  "Class CSqlConnection " CLASS_VER;
	m_sqldriver = NULL;
	m_henv = NULL;
	m_connect = false;
	m_ontransation = false;
}
