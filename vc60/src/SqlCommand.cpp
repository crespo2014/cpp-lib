// SqlCommand.cpp: implementation of the CSqlCommand class.
//
//////////////////////////////////////////////////////////////////////

#include "SqlCommand.h"
#include "logclient.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSqlCommand::~CSqlCommand()
{
	Release();
}

CSqlCommand::CSqlCommand()
{
	Init();
}

CSqlCommand::CSqlCommand(CSqlConnection*	pSqlConnection)
{
	Init();
	SetConnection(pSqlConnection); 
}

DWORD CSqlCommand::Initialize()
{
	char	*fnc_name = "CSqlCommand::Initialize";
	Release();
	if (m_sqlconnection->CreateCommand(&m_henv) == ERR_OK) return ERR_OK;
	return LOG_TSTACK;
}

DWORD CSqlCommand::Release()
{
	if (m_henv == NULL) return ERR_OK;
	SQLFreeHandle(SQL_HANDLE_STMT,m_henv);
	m_henv = NULL;
	m_beof = true;
	return ERR_OK;
}

DWORD CSqlCommand::Execute(char *sql_cmd)
{
	SQLRETURN	sr;
	char		*fnc_name = "CSqlCommand::Execute";
	if (m_henv == NULL) { SQL_CMD_EXIT_INVALID_HANDLE };

	m_beof = false;
	LOG_TLAST "SQL = %s",sql_cmd);
	sr = SQLExecDirect(m_henv,(SQLCHAR*)sql_cmd, SQL_NTS);
	if (sr == SQL_SUCCESS) return ERR_OK;
	if (sr != SQL_SUCCESS_WITH_INFO) m_beof = true;
	if (sr == SQL_NO_DATA) return ERR_OK;
	return SQL_CMD_LOG_ERROR sr,ERR_EOF,"SQLExecDirect for %s ",sql_cmd);
}

DWORD CSqlCommand::GetColumnNameType(SQLUSMALLINT index, char *name, SQLSMALLINT *name_size, SQLSMALLINT *datatype, SQLUINTEGER *datasize)
{
	SQLRETURN	sr;
	SQLSMALLINT	name_csize;
	SQLSMALLINT	scale;
	SQLSMALLINT	prop;
	char	*fnc_name = "CSqlCommand::GetColumnNameType";
	if (m_henv == NULL) { SQL_CMD_EXIT_INVALID_HANDLE };

	sr = SQLDescribeCol(m_henv,index,(unsigned char*)name,*name_size,&name_csize,datatype,datasize,&scale,&prop);
	*name_size = name_csize;
	if (sr == SQL_SUCCESS) return ERR_OK;
	return SQL_CMD_LOG_ERROR sr,ERR_EOF,"SQLDescribeCol");
}

DWORD CSqlCommand::GetData(SQLUSMALLINT colindex, SQLSMALLINT datatype, SQLPOINTER dataptr, SQLINTEGER datasize, SQLINTEGER *curr_size)
{
	SQLRETURN	sr;
	char	*fnc_name = "CSqlCommand::GetData";
	if (m_henv == NULL) { SQL_CMD_EXIT_INVALID_HANDLE };

	sr = SQLGetData(m_henv,colindex,datatype,dataptr,datasize,curr_size);
	if (sr != SQL_SUCCESS) 
	{
		SQL_CMD_LOG_ERROR sr,ERR_FATAL,"SQLGetData column=%d, type=%d, size = %d",colindex,datatype,datasize);
		if (sr == SQL_SUCCESS_WITH_INFO) return ERR_TRUNCD;
		return ERR_FATAL;
	}
	if (curr_size == NULL) return ERR_OK;
	if (*curr_size == SQL_NULL_DATA)
	{
		memset(dataptr,0,datasize);	//inicializar en cero toda la variable
		SQL_CMD_LOG_ERROR sr,ERR_FATAL,"SQLGetData NULL data for column %u",colindex);
		return ERR_NULL;
	}
	if (*curr_size == SQL_NO_TOTAL) 
	{
		SQL_CMD_LOG_ERROR sr,ERR_FATAL,"SQLGetData Truncate data for column %u",colindex);
		return ERR_TRUNCD;
	}
	return ERR_OK;
}

DWORD CSqlCommand::NextRow()
{
	char	*fnc_name = "CSqlCommand::NextRow";
	if (m_henv == NULL) { SQL_CMD_EXIT_INVALID_HANDLE };

	if (m_beof) return ERR_EOF;
	SQLRETURN	sr;
	sr = SQLFetch(m_henv);
	if (sr == SQL_SUCCESS) return ERR_OK;
	if (sr == SQL_NO_DATA) 
	{
		LOG_TLAST "SQLFetch has return SQL_NO_DATA");
		m_beof = true; 
		return ERR_EOF;
	}
	return SQL_CMD_LOG_ERROR sr,ERR_FATAL,"SQLFetch ");;
}

DWORD CSqlCommand::BindColumn(SQLUSMALLINT col, SQLSMALLINT type, SQLPOINTER varptr, SQLINTEGER varsize, SQLINTEGER *vallen)
{
	SQLRETURN	sr;
	char	*fnc_name = "CSqlCommand::BindColumn";
	if (m_henv == NULL) { SQL_CMD_EXIT_INVALID_HANDLE };

	sr = SQLBindCol(m_henv,col,type,varptr,varsize,vallen);
	if (sr == SQL_SUCCESS) return ERR_OK;
	return SQL_CMD_LOG_ERROR sr,ERR_FATAL,"SQLBindCol column = %d, type = %d, size = %d",col,type,varsize);
}

DWORD CSqlCommand::Prepared(char *sql)
{
	char	*fnc_name = "CSqlCommand::Prepared";
	SQLRETURN	sr;
	if (m_henv == NULL) { SQL_CMD_EXIT_INVALID_HANDLE };
	sr = SQLPrepare(m_henv,(SQLCHAR*)sql,SQL_NTS);
	if (sr == SQL_SUCCESS) return ERR_OK;
	return SQL_CMD_LOG_ERROR sr,ERR_EOF,"SQLPrepare(%s) ",sql);
}

DWORD CSqlCommand::ExecutePrepared(char *sql)
{
	SQLRETURN	sr;
	char	*fnc_name = "CSqlCommand::Execute";
	if (m_henv == NULL) { SQL_CMD_EXIT_INVALID_HANDLE };

	m_beof = false;
	LOG_TLAST "SQL = %s",sql);
	sr = SQLExecute(m_henv);
	if (sr == SQL_SUCCESS) return ERR_OK;
	if (sr != SQL_SUCCESS_WITH_INFO) m_beof = true;
	if (sr == SQL_NO_DATA) return ERR_OK;
	m_beof = true;
	return SQL_CMD_LOG_ERROR sr,ERR_EOF,"SQLExecute with %s ",sql);
}

DWORD CSqlCommand::BindParameter(SQLUSMALLINT index, SQLSMALLINT inout_type, SQLSMALLINT c_type, SQLSMALLINT sql_type, SQLUINTEGER col_size, SQLSMALLINT dec_digits, SQLPOINTER var_ptr, SQLINTEGER var_size, SQLINTEGER *val_len)
{
	SQLRETURN	sr;
	char	*fnc_name = "CSqlCommand::BindParameter";
	if (m_henv == NULL) { SQL_CMD_EXIT_INVALID_HANDLE };

	sr = SQLBindParameter(m_henv,index,inout_type,c_type,sql_type,col_size,dec_digits,var_ptr,var_size,val_len);
	if (sr == SQL_SUCCESS) return ERR_OK;
	return SQL_CMD_LOG_ERROR sr,ERR_FATAL,"SQLBindParameter index = %d, ctype = %d",index,c_type);
}

void CSqlCommand::SetConnection(CSqlConnection*	pSqlConnection)
{
	Release();
	m_sqlconnection = pSqlConnection;
	m_plog = pSqlConnection->GetLog();
	m_beof = true;
}

DWORD CSqlCommand::SetAttribute(SQLINTEGER Attribute, SQLPOINTER ValuePtr, SQLINTEGER StringLength)
{
	SQLRETURN	sr;
	char	*fnc_name = "CSqlCommand::SetAttribute";
	if (m_henv == NULL) { SQL_CMD_EXIT_INVALID_HANDLE };

	sr = SQLSetStmtAttr(m_henv,Attribute,ValuePtr,StringLength);
	if (sr == SQL_SUCCESS) return ERR_OK;
	return SQL_CMD_LOG_ERROR sr,ERR_EOF,"SQLSetStmtAttr (%d)",Attribute);
}

DWORD CSqlCommand::ResetCursor()
{
	SQLRETURN	sr;
	char	*fnc_name = "CSqlCommand::ResetCursor";
	if (m_henv == NULL) { SQL_CMD_EXIT_INVALID_HANDLE };

	sr = SQLFreeStmt(m_henv,SQL_CLOSE);
	SQL_CMD_LOG_ERROR sr,ERR_EOF,"SQLDescribeCol");
	if (sr != SQL_SUCCESS) 
	{
		return SQL_CMD_LOG_ERROR sr,ERR_EOF,"SQLFreeStmt (SQL_CLOSE)");
	}
	return ERR_OK;
}

DWORD CSqlCommand::log_Row()
{
	// tracear el contenido de la fila actual
	char	*fnc_name = "CSqlCommand::log_Row";
	if (m_henv == NULL) { SQL_CMD_EXIT_INVALID_HANDLE };
	return ERR_OK;
}

DWORD CSqlCommand::RowCount(SQLINTEGER *pRowCount)
{
	SQLRETURN	sr;
	char	*fnc_name = "CSqlCommand::RowCount";
	if (m_henv == NULL) { SQL_CMD_EXIT_INVALID_HANDLE };
	sr = SQLRowCount(m_henv,pRowCount);
	if (sr == SQL_SUCCESS) return ERR_OK;
	SQL_CMD_LOG_ERROR sr,ERR_EOF,"SQLDescribeCol");
	return SQL_CMD_LOG_ERROR sr,ERR_EOF,"SQLRowCount ");

}

void CSqlCommand::Init()
{
	m_ver =  "Class CSqlCommand " CLASS_VER;
	m_sqlconnection = NULL;
	m_henv = NULL;
	m_beof = true;
}

DWORD CSqlCommand::ResetAll()
{
	char	*fnc_name = "CSqlCommand::ResetAll";

	if (m_henv == NULL) { SQL_CMD_EXIT_INVALID_HANDLE };

	DWORD	dwr;
	SQLRETURN	sr;
	
	dwr = ERR_FATAL;
	sr = SQLFreeStmt(m_henv,SQL_CLOSE);
	if (sr != SQL_SUCCESS) 
	{
		dwr = SQL_CMD_LOG_ERROR sr,ERR_EOF,"SQLFreeStmt SQL_CLOSE",sr);
		//if (dwr != ERR_OK) return dwr;
	}
	sr = SQLFreeStmt(m_henv,SQL_UNBIND);
	if (sr != SQL_SUCCESS) 
	{
		dwr = SQL_CMD_LOG_ERROR sr,ERR_EOF,"SQLFreeStmt SQL_UNBIND",sr);
		//if (dwr != ERR_OK) return dwr;
	}
	sr = SQLFreeStmt(m_henv,SQL_RESET_PARAMS);
	if (sr != SQL_SUCCESS) 
	{
		dwr = SQL_CMD_LOG_ERROR sr,ERR_EOF,"SQLFreeStmt SQL_RESET_PARAMS",sr);
		//if (dwr != ERR_OK) return dwr;
	}
	return dwr;
}


DWORD CSqlCommand::LogError(char *fnc_name, DWORD line, SQLRETURN sr, DWORD retval, char *format, ...)
{
	SQLINTEGER  NativeError;
	SQLSMALLINT	csize;
	char	err_msg[255];
	char	err_status[7];
	char	*cptr;
	DWORD	dwr;
	char	msg[1024];
	int		i;
	va_list arg_ptr;
	
	cptr = msg;

	for (;;) {
		i = _snprintf(cptr,sizeof(msg)- (cptr-msg-2),"at %d ",line);
		if (i<0) break; cptr += i;
		va_start(arg_ptr, format);
		i = _vsnprintf(cptr,sizeof(msg)- (cptr-msg-2),format,arg_ptr);
		va_end(arg_ptr);
		if (i<0) break; cptr += i;
		err_status[0] = 0;
		err_msg[0] = 0;
		switch(sr)
		{
		case SQL_INVALID_HANDLE: 
			{
				i = _snprintf(cptr,sizeof(msg)- (cptr-msg-2)," failed because has an Invalid Handle");
				dwr = ERR_HANDLE;
				break;
			}
		case SQL_ERROR:
			{
				SQLGetDiagRec(SQL_HANDLE_STMT,m_henv,1,(unsigned char*)err_status,&NativeError,(unsigned char*)err_msg,sizeof(err_msg),&csize);
				i = _snprintf(cptr,sizeof(msg)- (cptr-msg-2)," failed with Message = <%s> Status = [%s]",err_msg,err_status);
				dwr = ERR_FATAL;
			}
		case SQL_SUCCESS_WITH_INFO:
			{
				SQLGetDiagRec(SQL_HANDLE_STMT,m_henv,1,(unsigned char*)err_status,&NativeError,(unsigned char*)err_msg,sizeof(err_msg),&csize);
				i = _snprintf(cptr,sizeof(msg)- (cptr-msg-2),"Success with info = %s Status = %s ",err_msg,err_status);
				dwr = ERR_OK;
			}
		case SQL_NEED_DATA:
			{
				i = _snprintf(cptr,sizeof(msg)- (cptr-msg-2)," failed with message SQL NEED DATA");
				dwr = ERR_FATAL;
			}
		default:
			{
				i = _snprintf(cptr,sizeof(msg)- (cptr-msg-2)," failed with unknown Error Code = %d ",sr);
				dwr = ERR_FATAL;
			}
		}
		if (i<0) break; cptr += i;
		break;
	}
	return LOG_TERROR dwr,"%s",msg);
}
