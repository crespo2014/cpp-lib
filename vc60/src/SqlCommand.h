// SqlCommand.h: interface for the CSqlCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SQLCOMMAND_H__6AF26EDB_F457_47BC_89A0_619765A45B11__INCLUDED_)
#define AFX_SQLCOMMAND_H__6AF26EDB_F457_47BC_89A0_619765A45B11__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "sqlconnection.h"

#define SQL_CMD_LOG_ERROR			LogError(fnc_name,__LINE__,
#define SQL_CMD_EXIT_INVALID_HANDLE	return LOG_TERROR	ERR_HANDLE,"Invalid Handle valued call Initialize Before");

class CSqlCommand : public CbObject
{
public:
	BOOL  IsValid()	{ return (m_henv != NULL);};
	BOOL  IsEOF()	{ return m_beof;};
	DWORD NextRow();
	DWORD GetData(SQLUSMALLINT colindex,SQLSMALLINT datatype,SQLPOINTER dataptr,SQLINTEGER datasize,SQLINTEGER* curr_size = NULL);
	DWORD GetColumnNameType(SQLUSMALLINT index,char* name, SQLSMALLINT*  name_size,SQLSMALLINT* datatype,SQLUINTEGER* datasize);
	DWORD Execute(char* sql_cmd);
	DWORD Release();
	DWORD Initialize();
	void SetConnection(CSqlConnection* pSqlConnection);
	CSqlCommand(CSqlConnection*	pSqlConnection);
	CSqlCommand();
	virtual ~CSqlCommand();

private:
	CSqlConnection*	m_sqlconnection;
	SQLHENV	m_henv;
	BOOL	m_beof;
	
public:
	DWORD LogError(char* fnc_name,DWORD line,SQLRETURN sr,DWORD retval, char *format,...);
	DWORD ResetAll();
	void Init();
	DWORD RowCount(SQLINTEGER * pRowCount);
	DWORD log_Row();
	DWORD ResetCursor();
	DWORD SetAttribute(SQLINTEGER Attribute,SQLPOINTER ValuePtr,SQLINTEGER StringLength);
	DWORD BindParameter(SQLUSMALLINT index,SQLSMALLINT  inout_type,SQLSMALLINT c_type,SQLSMALLINT sql_type,SQLUINTEGER col_size,SQLSMALLINT dec_digits,SQLPOINTER var_ptr,SQLINTEGER var_size,SQLINTEGER *val_len = NULL);
	DWORD ExecutePrepared(char *sql);
	DWORD Prepared(char* sql);
	DWORD BindColumn(SQLUSMALLINT col,SQLSMALLINT type,SQLPOINTER varptr,SQLINTEGER varsize,SQLINTEGER * vallen);
	
};

#endif // !defined(AFX_SQLCOMMAND_H__6AF26EDB_F457_47BC_89A0_619765A45B11__INCLUDED_)
