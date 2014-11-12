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
	CSqlConnection();
	Init();
	SetDriver(pSqlDriver);
}

CSqlConnection::~CSqlConnection()
{
	Release();
}

DWORD CSqlConnection::Initialize()
{
	char	*fnc_name = "CSqlConnection::Initialize";
	if (m_henv != NULL) return ERR_OK;
	if (m_sqldriver->CreateConnection(&m_henv) != ERR_OK) return LOG_TSTACK;
	return ERR_OK;
}

DWORD CSqlConnection::CreateCommand(SQLHENV *psqlenv)
{
	char	*fnc_name = "CSqlConnection::SetAttribute";
	SQLRETURN	sr;
	if (m_henv == NULL) { return SQL_CON_INVALID_HANDLE };
	//sr = SQLAllocHandle(SQL_HANDLE_STMT,m_henv,psqlenv);
	sr = SQLAllocStmt(m_henv,psqlenv);
	if (sr == SQL_SUCCESS) return ERR_OK;
	return SQL_CON_LOG_ERROR sr,"SQLAllocStmt");
}

DWORD CSqlConnection::ConnectTo(char *datasource, char *user, char *password)
{
	char	*fnc_name = "CSqlConnection::ConnectTo";	
	SQLRETURN	sr;
	if (m_henv == NULL) { return SQL_CON_INVALID_HANDLE }
	if (m_connect)		return LOG_TERROR ERR_FATAL,"Connection already open ...");
	//if (Disconnect() != ERR_OK) return ERR_FATAL;
	sr = SQLConnect(m_henv,(unsigned char*)datasource,SQL_NTS,(unsigned char*)user,SQL_NTS,(unsigned char*)password,SQL_NTS);
	if (sr == SQL_SUCCESS) 
	{
		m_connect = true;
		LOG_TLAST "Open connection for dsn %s",datasource);
		return ERR_OK;
	}
	return SQL_CON_LOG_ERROR sr,"SQLConnect dsn = %s, user = %s",datasource,user);
}

DWORD CSqlConnection::Release()
{
	char	*fnc_name = "CSqlConnection::Release";
	if (m_henv == NULL)	return ERR_OK;
	SQLRETURN	sr;
	Disconnect();
	LOG_TLAST "CSqlConnection::Release ...");
	sr = SQLFreeHandle(SQL_HANDLE_DBC,m_henv);
	m_henv = NULL;
	return ERR_OK;
}

DWORD CSqlConnection::TransationEnable(BOOL bstate)
{
	char	*fnc_name = "CSqlConnection::SetAttribute";
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
	return SQL_CON_LOG_ERROR sr,"SQLSetConnectAttr SQL_ATTR_AUTOCOMMIT = %d",bstate);
}

DWORD CSqlConnection::Transation(SQLSMALLINT operation)
{
	char	*fnc_name = "CSqlConnection::SetAttribute";
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
	return SQL_CON_LOG_ERROR sr,"CSqlConnection::Transation->SQLEndTran ",sr);
}

DWORD CSqlConnection::Disconnect()
{
	char	*fnc_name = "CSqlConnection::SetAttribute";
	SQLRETURN	sr;
	if (!m_connect) return ERR_OK;
	if (m_ontransation)	
		Transation_RollBack();
	else
		TransationEnable(false);
	sr = SQLDisconnect(m_henv);
	if (sr != SQL_SUCCESS) return SQL_CON_LOG_ERROR sr,"CSqlConnection::Disconnect->SQLDisconnect ",sr);
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
	char	*fnc_name = "CSqlConnection::SetAttribute";
	SQLRETURN	sr;
	sr = SQLBrowseConnect(m_henv,(unsigned char*)InConnectionString,SQL_NTS,(SQLCHAR*)OutConnectionString,BufferLength,StringLength2Ptr);
	if ((sr == SQL_SUCCESS) || (sr == SQL_NEED_DATA)) return ERR_OK;
	return SQL_CON_LOG_ERROR sr,"CSqlConnection::BrowseConnect->SQLBrowseConnect ",sr);
}

DWORD CSqlConnection::SetAttribute(SQLINTEGER Attribute, SQLPOINTER ValuePtr, SQLINTEGER StringLength)
{
	char	*fnc_name = "CSqlConnection::SetAttribute";
	SQLRETURN	sr;
	if (m_henv == NULL) { return SQL_CON_INVALID_HANDLE };
	sr = SQLSetConnectAttr(m_henv,Attribute,ValuePtr,StringLength);
	if (sr == SQL_SUCCESS) return ERR_OK;
	return SQL_CON_LOG_ERROR sr,"CSqlCommand::SetAttribute->SQLSetConnectAttr ",sr);
}

void CSqlConnection::Init()
{
	m_ver =  "Class CSqlConnection " CLASS_VER;
	m_sqldriver = NULL;
	m_henv = NULL;
	m_connect = false;
	m_ontransation = false;
}

DWORD CSqlConnection::LogError(char *fnc_name, DWORD line, SQLRETURN sr, char *format, ...)
{
	SQLINTEGER  NativeError;
	SQLSMALLINT	csize;
	char	err_msg[255];
	char	err_status[7];
	char	*cptr;
	int		i;
	DWORD	dwr;
	char	msg[1024];
	va_list arg_ptr;
	
	cptr = msg;
	if (sr == SQL_SUCCESS) return ERR_OK;

	for (;;) 
	{
		i = _snprintf(cptr,sizeof(msg)- (cptr-msg-2),"at %d ",line);
		if (i<0) break; cptr += i;
		va_start(arg_ptr, format);
		i = _vsnprintf(cptr,sizeof(msg)- (cptr-msg-2),format,arg_ptr);
		va_end(arg_ptr);
		if (i<0) break; cptr += i;
		err_status[0] = 0;
		err_msg[0] = 0;

		if (sr == SQL_INVALID_HANDLE)
		{
			i = _snprintf(cptr,sizeof(msg)- (cptr-msg-2)," failed because has an Invalid Handle");
			dwr = ERR_HANDLE;
		}
		else
		{
			SQLGetDiagRec(SQL_HANDLE_DBC,m_henv,1,(unsigned char*)err_status,&NativeError,(unsigned char*)err_msg,sizeof(err_msg),&csize);
			if (sr == SQL_SUCCESS_WITH_INFO)
			{
				i = _snprintf(cptr,sizeof(msg)- (cptr-msg-2),"Success with info = %s Status = %s ",err_msg,err_status);
				dwr = ERR_OK;
			}
			else
			{
				i = _snprintf(cptr,sizeof(msg)- (cptr-msg-2)," failed with Message = <%s> Status = [%s]",err_msg,err_status);
				dwr = ERR_FATAL;
			}
		}
		if (i<0) break; cptr += i;
		break;
	}
	return LOG_TERROR dwr,"%s",msg);
}
