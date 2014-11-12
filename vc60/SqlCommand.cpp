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
	Release();
	if (m_sqlconnection->CreateCommand(&m_henv) == ERR_OK) return ERR_OK;
	return SetError(false,ERR_FATAL,"CSqlCommand::Initialize->%s",m_sqlconnection->GetErrorMsg());
}

DWORD CSqlCommand::Release()
{
	if (m_henv == NULL) return ERR_OK;
	SQLFreeHandle(SQL_HANDLE_STMT,m_henv);
	m_henv = NULL;
	m_err_msg[0] = 0;
	m_beof = true;
	return ERR_OK;
}

DWORD CSqlCommand::Execute(char *sql_cmd)
{
	SQLRETURN	sr;
	char		*fnc_name = "CSqlCommand::Execute";
	if (m_henv == NULL) return InvalidHandle(fnc_name);

	m_beof = false;
	m_plog->_log(LOG_DEBUG,"%s [%s]",fnc_name,sql_cmd);
	sr = SQLExecDirect(m_henv,(SQLCHAR*)sql_cmd, SQL_NTS);
	if (sr == SQL_SUCCESS) return ERR_OK;
	if (sr != SQL_SUCCESS_WITH_INFO) m_beof = true;
	if (sr == SQL_NO_DATA) return ERR_OK;
	m_plog->log_strings(LOG_ERROR,"For SQL = <",sql_cmd,">");
	return Make_ErrorSTR("CSqlCommand::Execute->SQLExecDirect ",sr);
}

DWORD CSqlCommand::GetColumnNameType(SQLUSMALLINT index, char *name, SQLSMALLINT *name_size, SQLSMALLINT *datatype, SQLUINTEGER *datasize)
{
	SQLRETURN	sr;
	SQLSMALLINT	name_csize;
	SQLSMALLINT	scale;
	SQLSMALLINT	prop;
	char	*fnc_name = "CSqlCommand::GetColumnNameType";
	if (m_henv == NULL) return InvalidHandle(fnc_name);

	sr = SQLDescribeCol(m_henv,index,(unsigned char*)name,*name_size,&name_csize,datatype,datasize,&scale,&prop);
	*name_size = name_csize;
	if (sr == SQL_SUCCESS) return ERR_OK;
	Make_ErrorSTR("CSqlCommand::GetColumnNameType->SQLDescribeCol ",sr);
	return ERR_EOF;
}

DWORD CSqlCommand::GetData(SQLUSMALLINT colindex, SQLSMALLINT datatype, SQLPOINTER dataptr, SQLINTEGER datasize, SQLINTEGER *curr_size)
{
	SQLRETURN	sr;
	char	*fnc_name = "CSqlCommand::GetData";
	if (m_henv == NULL) return InvalidHandle(fnc_name);

	sr = SQLGetData(m_henv,colindex,datatype,dataptr,datasize,curr_size);
	if (sr != SQL_SUCCESS) 
	{
		Make_ErrorSTR("CSqlCommand::GetData->SQLGetData ",sr);
		if (sr == SQL_SUCCESS_WITH_INFO) return ERR_TRUNCD;
		return ERR_FATAL;
	}
	if (curr_size == NULL) return ERR_OK;
	if (*curr_size == SQL_NULL_DATA)
	{
		memset(dataptr,0,datasize);	//inicializar en cero toda la variable
		return SetError(false,ERR_NULL,"CSqlCommand::GetData->SQLGetData NULL data for column %u",colindex);
	}
	if (*curr_size == SQL_NO_TOTAL) return(false,ERR_TRUNCD,"CSqlCommand::GetData->SQLGetData Truncate data for column %u",colindex);
	return ERR_OK;
}

DWORD CSqlCommand::NextRow()
{
	char	*fnc_name = "CSqlCommand::NextRow";
	if (m_henv == NULL) return InvalidHandle(fnc_name);

	if (m_beof) return ERR_EOF;
	SQLRETURN	sr;
	sr = SQLFetch(m_henv);
	if (sr == SQL_SUCCESS) return ERR_OK;
	if (sr == SQL_NO_DATA) 
	{
		m_plog->log_strings(LOG_TRACE,"CSqlCommand::NextRow->SQLFetch has return SQL_NO_DATA");
		m_beof = true; 
		return ERR_EOF;
	}
	Make_ErrorSTR("CSqlCommand::NextRow->SQLFetch ",sr);
	return ERR_FATAL;
}

DWORD CSqlCommand::Make_ErrorSTR(char *msg,SQLRETURN sr)
{
	SQLINTEGER  NativeError;
	SQLSMALLINT	csize;
	char	err_msg[255];
	char	err_status[7];
	
	char	*fnc_name = "CSqlCommand::Make_ErrorSTR";
	if (m_henv == NULL) return InvalidHandle(fnc_name);

	err_status[0] = 0;
	err_msg[0] = 0;

	switch(sr)
	{
	case SQL_INVALID_HANDLE: return SetError(true,ERR_FATAL,"%s failed because has an Invalid Handle value",msg);
	case SQL_ERROR:
		{
			SQLGetDiagRec(SQL_HANDLE_STMT,m_henv,1,(unsigned char*)err_status,&NativeError,(unsigned char*)err_msg,sizeof(err_msg),&csize);
			return SetError(false,ERR_FATAL,"%s failed with Message = <%s> Status = [%s]",msg,err_msg,err_status);
		}
	case SQL_SUCCESS_WITH_INFO:
		{
			SQLGetDiagRec(SQL_HANDLE_STMT,m_henv,1,(unsigned char*)err_status,&NativeError,(unsigned char*)err_msg,sizeof(err_msg),&csize);
			return SetError(true,ERR_OK,"%s Success with info = %s Status = %s ",msg,err_msg,err_status);
		}
	case SQL_NEED_DATA:
		{
			return SetError(false,ERR_FATAL,"%s failed with message SQL NEED DATA",msg);
		}
	default:
		{
			return SetError(false,ERR_FATAL,"%s failed with unknown Error Code = %d ",sr);
		}
	}
//	return ERR_FATAL;
}


DWORD CSqlCommand::BindColumn(SQLUSMALLINT col, SQLSMALLINT type, SQLPOINTER varptr, SQLINTEGER varsize, SQLINTEGER *vallen)
{
	SQLRETURN	sr;
	char	*fnc_name = "CSqlCommand::BindColumn";
	if (m_henv == NULL) return InvalidHandle(fnc_name);

	sr = SQLBindCol(m_henv,col,type,varptr,varsize,vallen);
	if (sr == SQL_SUCCESS) return ERR_OK;
	return Make_ErrorSTR("CSqlCommand::BindColumn->SQLBindCol ",sr);
}

DWORD CSqlCommand::Prepared(char *sql)
{
	char	*fnc_name = "CSqlCommand::Prepared";
	SQLRETURN	sr;
	if (m_henv == NULL) return InvalidHandle(fnc_name);

	m_plog->_log(LOG_DEBUG,"%s [%s]",fnc_name,sql);
	sr = SQLPrepare(m_henv,(SQLCHAR*)sql,SQL_NTS);
	if (sr == SQL_SUCCESS) return ERR_OK;
	return Make_ErrorSTR("CSqlCommand::Prepared->SQLPrepare",sr);
}

DWORD CSqlCommand::Execute()
{
	SQLRETURN	sr;
	char	*fnc_name = "CSqlCommand::Execute";
	if (m_henv == NULL) return InvalidHandle(fnc_name);

	m_beof = false;
	sr = SQLExecute(m_henv);
	if (sr == SQL_SUCCESS) return ERR_OK;
	if (sr != SQL_SUCCESS_WITH_INFO) m_beof = true;
	if (sr == SQL_NO_DATA) return ERR_OK;
	m_beof = true;
	return Make_ErrorSTR("CSqlCommand::Execute->SQLExecute ",sr);
}

DWORD CSqlCommand::BindParameter(SQLUSMALLINT index, SQLSMALLINT inout_type, SQLSMALLINT c_type, SQLSMALLINT sql_type, SQLUINTEGER col_size, SQLSMALLINT dec_digits, SQLPOINTER var_ptr, SQLINTEGER var_size, SQLINTEGER *val_len)
{
	SQLRETURN	sr;
	char	*fnc_name = "CSqlCommand::BindParameter";
	if (m_henv == NULL) return InvalidHandle(fnc_name);

	sr = SQLBindParameter(m_henv,index,inout_type,c_type,sql_type,col_size,dec_digits,var_ptr,var_size,val_len);
	if (sr == SQL_SUCCESS) return ERR_OK;
	return Make_ErrorSTR("CSqlCommand::BindParameter->SQLBindParameter ",sr);
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
	if (m_henv == NULL) return InvalidHandle(fnc_name);

	sr = SQLSetStmtAttr(m_henv,Attribute,ValuePtr,StringLength);
	if (sr == SQL_SUCCESS) return ERR_OK;
	return Make_ErrorSTR("CSqlCommand::SetAttribute->SQLSetStmtAttr ",sr);
}

DWORD CSqlCommand::ResetCursor()
{
	SQLRETURN	sr;
	char	*fnc_name = "CSqlCommand::ResetCursor";
	if (m_henv == NULL) return InvalidHandle(fnc_name);

	sr = SQLFreeStmt(m_henv,SQL_CLOSE);
	if (sr != SQL_SUCCESS) return Make_ErrorSTR("CSqlCommand::Reset->SQLFreeStmt ",sr);
	return ERR_OK;
}

//DEL void CSqlCommand::Big_Div_8(BYTE *dividend, BYTE dsize, BYTE divisor, BYTE *quotient, BYTE *remainder)
//DEL {
//DEL 	BYTE	num_size;
//DEL 	BYTE	reminder;
//DEL 	memset(quotient,0,dsize);
//DEL 
//DEL 	_asm
//DEL 	{
//DEL 		mov dh,0;
//DEL 		xor ecx,ecx;
//DEL 		mov cl,dsize;
//DEL 		mov eax,dividend;
//DEL 		mov dl,0;
//DEL loop_0:
//DEL 		cmp [eax],byte ptr 0;
//DEL 		je nxt_0;
//DEL 		mov dh,dl;
//DEL nxt_0:
//DEL 		inc eax;
//DEL 		inc dl;
//DEL 		loop loop_0;
//DEL 		inc dh;
//DEL 		mov num_size,dh	//cantidad de bytes validos * 8 cantidad de bits
//DEL 		mov al,8;
//DEL 		mul dh;
//DEL 		mov cx,ax		// tamaño en bits del numero	
//DEL 		mov bl,divisor	//divisor
//DEL 		mov bh,0	// reminder
//DEL loop_1:
//DEL 		// rotar el dividendo y pasar el bit al reminder
//DEL 		clc;
//DEL 		mov eax,dividend;
//DEL 		call rot_19;
//DEL 		rcl bh,1;
//DEL 		// comparar los numeros
//DEL 		cmp bh,bl;
//DEL 		jb menor;
//DEL 		sub bh,bl;
//DEL 		stc;
//DEL 		jmp rotar
//DEL menor:
//DEL 		clc;
//DEL rotar:		
//DEL 		mov eax,quotient;
//DEL 		call rot_19;
//DEL 		loop loop_1;
//DEL 		jmp end_;
//DEL 
//DEL rot_19:	//rotar los dl numeros apuntados por eax a traves del CF
//DEL 		push cx;
//DEL 		mov ecx,0
//DEL 		mov cl,num_size;
//DEL l_1:
//DEL 		rcl byte ptr [eax],1;
//DEL 		inc eax;
//DEL 		loop l_1;
//DEL 		pop cx;
//DEL 		ret;
//DEL end_:
//DEL 		mov reminder,bh;
//DEL 	}
//DEL 	*remainder = reminder;	
//DEL 
//DEL }

//DEL void CSqlCommand::Big_GetDecimal(BYTE *number, BYTE dsize, char *decimal, BYTE max)
//DEL {
//DEL 	BYTE is0;
//DEL 	BYTE res[20];
//DEL 	BYTE resto;
//DEL 	char str[40];
//DEL 	int	i,k;
//DEL 	k = 0;
//DEL 	if (dsize > sizeof(res)) dsize = sizeof(res);
//DEL 	do
//DEL 	{
//DEL 		Big_Div_8(number,dsize,10,res,&resto);
//DEL 		str[k] = resto+0x30;
//DEL 		k++;
//DEL 		if (k == sizeof(str)) break;
//DEL 	_asm{
//DEL 		lea eax,[res];
//DEL 		mov ecx,0
//DEL 		mov cl,dsize;
//DEL 		mov bh,0;
//DEL lp_1:
//DEL 		or bh,[eax];
//DEL 		inc eax;
//DEL 		loop lp_1;
//DEL 		mov is0,bh;		
//DEL 	}
//DEL 		memcpy(number,res,dsize);
//DEL 	} while (is0 != 0);
//DEL 	i = 0;
//DEL 	
//DEL 	while (k>0)
//DEL 	{
//DEL 		k--;
//DEL 		decimal[i] = str[k];
//DEL 		i++;
//DEL 		if (i == max-1) break;
//DEL 		
//DEL 	}
//DEL 	decimal[i] = 0;
//DEL }

DWORD CSqlCommand::log_Row()
{
	// tracear el contenido de la fila actual
	char	*fnc_name = "CSqlCommand::log_Row";
	if (m_henv == NULL) return InvalidHandle(fnc_name);
	return ERR_OK;
}

DWORD CSqlCommand::RowCount(SQLINTEGER *pRowCount)
{
	SQLRETURN	sr;
	char	*fnc_name = "CSqlCommand::RowCount";
	if (m_henv == NULL) return InvalidHandle(fnc_name);
	sr = SQLRowCount(m_henv,pRowCount);
	if (sr == SQL_SUCCESS) return ERR_OK;
	return Make_ErrorSTR("CSqlCommand::RowCount->SQLRowCount ",sr);

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

	if (m_henv == NULL) return InvalidHandle(fnc_name);

	DWORD	dwr;
	SQLRETURN	sr;
	
	sr = SQLFreeStmt(m_henv,SQL_CLOSE);
	if (sr != SQL_SUCCESS) 
	{
		dwr = Make_ErrorSTR("CSqlCommand::Reset->SQLFreeStmt SQL_CLOSE",sr);
		if (dwr != ERR_OK) return dwr;
	}
	sr = SQLFreeStmt(m_henv,SQL_UNBIND);
	if (sr != SQL_SUCCESS) 
	{
		dwr = Make_ErrorSTR("CSqlCommand::Reset->SQLFreeStmt SQL_UNBIND",sr);
		if (dwr != ERR_OK) return dwr;
	}
	sr = SQLFreeStmt(m_henv,SQL_RESET_PARAMS);
	if (sr != SQL_SUCCESS) 
	{
		dwr = Make_ErrorSTR("CSqlCommand::Reset->SQLFreeStmt SQL_RESET_PARAMS",sr);
		if (dwr != ERR_OK) return dwr;
	}
	return ERR_OK;
}

